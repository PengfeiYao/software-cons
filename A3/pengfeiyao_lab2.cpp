/*
 * To perform Object-Oriented Analysis, Design, and Testing
 * To develop a non-trivial application using classes and constructor to implemment abstractions
 * To learn distributed communication methods and develop a simple but useful distributed social network system
 * to learn to user file IO and take advantage of the network file System
 * Name:pengfei yao
 * Time:2017/10/12
 * Email:pzy0006@auburn.edu
 */
#include <iostream>
#include "user.h"
#include "group.h"
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<user> users;
vector<group> groups;
vector<int> numOfMessage;
void switchCase(string l);
string optionSelected();
//void createNewUser();
int currentUser = 0;
int currentGroup = 0;
int messageNum = 1;
string message_buffer;
string UserName;
ofstream writeMessageToGroup;
ofstream writeMessageToUser;
ofstream writeNumOfMessageToFile;
bool userFound = false;
void createGroup();
void joinGroup();
//void switchUser();
void Broadcast();
void unicast();
void multicast();
void getHomePage();
void getWallPage();
void readNamesToGroups();
void writeNamesToGroups(string names);
void readInfoToMesaageBuffer();
void readNumOfMessage();
bool findString(std::string::size_type n, std::string &s);
//void messageReader(int end, string subString);
int main() {
	//Providing a main menu

	string option;
	std::cout << "\t===========================================================\n";
    std::cout << "\t|               Distributed TigerBook System!              |\n";
    std::cout << "\t===========================================================\n";
    readNamesToGroups();
    readInfoToMesaageBuffer();
    readNumOfMessage();
    messageNum = numOfMessage.back();//get message number from last user
    //read userName.txt
    //and make sure file has user name
    std::cout << "Please enter user name: ";

    getline(cin, UserName);
    ifstream inFile;
    ofstream openUserFile;
    inFile.open("userName.txt");
    openUserFile.open("userName.txt", ios::app);
    openUserFile << UserName + "\n";
    openUserFile.close();
    if (inFile.fail()) {
    	cerr << "Error opening file" << endl;
    }
    //read each user names
    // if file has name, then keep going
    //

    if (inFile.good()) {
    	userFound = true;
    	std::cout << "\t===========================================================\n";
    	std::cout << "\t|    Welcome to Distributed TigerBook System " + UserName + "!              |\n";
    	std::cout << "\t===========================================================\n";
    	do {
    		   	option = optionSelected();
    		   	switchCase(option);
    	 } while(option != "q");

    	}
    if (userFound == false) {
    	cout << "user not found, plesae check userName.txt! \n";
    }
    inFile.close();
	return 0;
}
//stored groups name into groupsName.txt
//so that user directly join groups that already have.
void writeNamesToGroups(string Name) {
	ofstream writeFile;
	writeFile.open("groupsName.txt", ios::app);
	writeFile << Name + "\n";
	writeFile.close();

}
//at the first, we need read groups name into vector groups
void readNamesToGroups() {
	ifstream readFile;
	string groupsName;
	string lines;
	readFile.open("groupsName.txt");
	while (readFile >> groupsName) {
		groups.push_back(groupsName);
	}
	readFile.close();
	//unique is remove duplicated elements in rang

}
void readNumOfMessage() {
	ifstream readNumOfMessage;
	int numbers;
	readNumOfMessage.open("numOfMessage.txt");
	while (readNumOfMessage >> numbers) {
		numOfMessage.push_back(numbers);
	}
	readNumOfMessage.close();
}
/*void writeNumOfMessageToFile(int i) {
	ofstream writeFile;
	writeFile.open("numOfMessage.txt", ios::app);
	writeFile << i + "\n";
	writeFile.close();
}*/
string optionSelected()
{
	std::cout << "Broadcast (b), Multicast (m), Unicast (u), Wall page (w), Home page (h), Create new group (g),\n" <<
	    		"Join a group (j), Quit (q)";
	cout << "\n";
	std::cout << "\nPlease choose an option: ";
    string option;
    getline(cin, option);
    cout << endl;
    return option;
}
//making user get out this social net work
void quit()
{
	cout << "\t==============================================================" << endl;
    cout << "\t|           Thank you for using DistributedTigerBook System    |" << endl;
    cout << "\t==============================================================" << endl;
}
// switch cases
// user can make a choice by typing letter
//so far we have not down pointer
void switchCase(string l) {
	const char *option = l.c_str();
	switch (*option) {

	case 'b':
		if (groups.size() < 1) {
			cout << "not enough user or group!\n";
		}
		else {
			Broadcast();

		}
		break;
	case 'm':
		if (groups.size() < 1) {
			cout << "not enough group!\n";
		}
		else {
			multicast();
		}
		break;
	case 'u':
		if (userFound) {
			unicast();
			}
			else {
				cout << "not enough group!\n";
			}
		break;
	case 'w':
		if (userFound) {
			getWallPage();
		}
		else {
			cout << "No user defind." << endl;
		}

		break;
	case 'h':
		if (userFound) {
			getHomePage();
		}
		else {
			cout << "No user defind." << endl;
		}
		break;
	case 'g':
		if (userFound) {
			createGroup();
		}
		else {
			cout << "no user defind" << endl;
		}
		break;
	case 'j':
		if (groups.size() == 0) {
			cout << "Please create a group first!";
		}
		else {
			joinGroup();
		}
		break;
	case 'q':
		quit();
		break;
	default:
		cout << "Invalid input." << endl;
		break;
	}
}
// create new user
//users is array that change in size
// so we can easy pick and stored user name
/*void createNewUser() {
	cout << "Please enter user name: ";
		std::string username;
		getline(cin, username);
	    if (users.size() > 0)
	    {
	        currentUser++;
	    }
		users.push_back(user(username));
		cout << "\t===========================================================" << endl;
	    cout << "\t|               Welcome to TigerBook Social Network, " + users[currentUser].getUsername() + "!     |" << endl;
	    cout << "\t===========================================================" << endl;
}*/
//creating a group
// if a group is already, this group won't created again.
//double check group name
void createGroup() {
	ofstream groupName;
	bool valid = true;
	string groupFileName;

	cout << "Please enter the group name: ";
	std::string groupname;
	getline(cin, groupname);
	//if user type group name as #tiger
	//make sure group name without "#", when you create a file
	// then assign to groupFileName

	//checking group
	for (std::size_t i = 0; i < groups.size(); i++) {
			if (groups[i].getGroupName() == groupname) {
				valid = false;
				break;
			}
			currentGroup = i + 1;
	}

	// if not found group, then create it
	// and create current group file
	if (valid) {
		//if user type group name as #tiger
			//make sure group name without "#", when you create a file
			// then assign to groupFileName
		writeNamesToGroups(groupname);
		int i = groupname.rfind("#");
	    int j = groupname.length();
		string newGroupName = groupname.substr(i + 1, j - 1);
		groupFileName = "_" + newGroupName  + ".txt";//groupFileName
		groupName.open(groupFileName);//create file with group name
		groupName.close();
		groups.push_back(group(groupname));
		cout << "\t===========================================================" << endl;
		cout << "\t|    New group " + groups[currentGroup].getGroupName() + " created    |" << endl;
		cout << "\t===========================================================" << endl;

	}
	else {
		cout << "group already have!\n";
	}

}
//user can join a group
// check group, if group already have, then user can join
//if not, display error information
void joinGroup() {
	cout <<"Please enter the group name: ";
	bool vaild = false;
	std::string groupname;
	getline(cin, groupname);
	//make sure group name exit
	for (std::size_t i = 0; i < groups.size(); i++) {
			if (groups[i].getGroupName() == groupname) {
				vaild = true;
				currentGroup = i;
				break;
			}
		}
	if(vaild) {
		cout << "\t===========================================================" << endl;
		cout << "\t|    "+ UserName + " has joined group " + groups[currentGroup].getGroupName() +"    |" << endl;
		cout << "\t===========================================================" << endl;
	}
	else {
		cout << "no group exit!\n";
	}
}
/*void switchUser() {
	cout << "Enter user name: ";
	string username;
	getline(cin, username);
	for (std::size_t i = 0; i < users.size(); i++) {
		if(users[i].getUsername() == username) {
			currentUser = i;
			break;
		}
	}
	if (users[currentUser].getUsername() != username) {
		cout << "User does not exit!\n";
	}
	else {
		cout << "\t===================================================================" << endl;
		cout << "\t|               Welcome back to TigerBook Social Network, " + users[currentUser].getUsername() +
		                "!       |" << endl;
        cout << "\t=====================================================================" << endl;
	}
}*/
void Broadcast() {
	cout << "Enter message: ";
	//new message buffer used to add memssage  to where user want
	//if we add message buffer to writeMessageToGroup or user
	//then we get old message and new message in a file.
	string newMessageBuffer;
	string nowTimes = std::to_string(numOfMessage.back());//get max message nnumber
	message_buffer += "{!" + nowTimes + "!}";
	newMessageBuffer += "{!" + nowTimes + "!}";
	message_buffer += "(" + UserName + ") ";
	message_buffer += "<! #ALL !>:";
	newMessageBuffer += "(" + UserName + ") ";
	newMessageBuffer += "<! #ALL !>:";
	string message;
	while (message != "^!") {
		message_buffer += message;
		newMessageBuffer += message;
		cin.clear();
		getline(cin, message);
		message_buffer += "\n";
		newMessageBuffer += "\n";
	}


	writeMessageToGroup.open("_All.txt", ios::app);
	writeMessageToGroup << newMessageBuffer;
	writeMessageToGroup.close();
	string openUserFile = UserName + ".txt";
	writeMessageToUser.open(openUserFile, ios::app);
	writeMessageToUser << newMessageBuffer;
	writeMessageToUser.close();
	writeMessageToUser.open("AllInformation.txt", ios::app);
	writeMessageToUser << newMessageBuffer;
	writeMessageToUser.close();
	// messageNum is increased,when user send a message
	messageNum++;
	writeNumOfMessageToFile.open("numOfMessage.txt", ios::app);
	string num = std::to_string(messageNum) + "\n";
	writeNumOfMessageToFile << num;
	writeNumOfMessageToFile.close();
	numOfMessage.push_back(messageNum);
	cout << "\t===========================================================" << endl;
	cout << "\t|    "+ UserName + " has broadcast a new message    |" << endl;
	cout << "\t===========================================================" << endl;
	cout << endl;
}
void multicast() {

	cout << "Please enter group name: ";
	string groupname;
	//new message buffer used to add memssage  to where user want
	//if we add message buffer to writeMessageToGroup or user
	//then we get old message and new message in a file.
	string newMessgeBuffer;

	string nowTimes = std::to_string(numOfMessage.back());//get max message nnumber
	message_buffer += "{!" + nowTimes + "!}";
	newMessgeBuffer += "{!" + nowTimes + "!}";
	getline(cin, groupname);
	message_buffer += "(" + UserName + ") " + "<! " + groupname + " !>" + ":";
	newMessgeBuffer += "(" + UserName + ") " + "<! " + groupname + " !>" + ":";
	cout << endl;
	string message;
	cout << "Enter message: ";
	while (message !="^!") {
		message_buffer += message;
		newMessgeBuffer += message;
		cin.clear();
		getline(cin, message);
		message_buffer += "\n";
		newMessgeBuffer += "\n";
	}
	//if user type group name as #tiger
	//make sure group name without "#", when you create a file
	// then assign to groupFileName
	int i = groupname.rfind("#");
	int j = groupname.length();
	string newGroupName = groupname.substr(i + 1, j - 1);
	string openFile = "_" + newGroupName + ".txt";
	writeMessageToGroup.open(openFile, ios::app);
	writeMessageToGroup << newMessgeBuffer;
	writeMessageToGroup.close();
	string openUserFile = UserName + ".txt";
	writeMessageToUser.open(openUserFile, ios::app);
	writeMessageToUser << newMessgeBuffer;
	writeMessageToUser.close();
	writeMessageToUser.open("AllInformation.txt", ios::app);
	writeMessageToUser << newMessgeBuffer;
	writeMessageToUser.close();
	// messageNum is increased,when user send a message
	messageNum++;
	writeNumOfMessageToFile.open("numOfMessage.txt", ios::app);
	string num = std::to_string(messageNum) + "\n";
	writeNumOfMessageToFile << num;
	writeNumOfMessageToFile.close();
	numOfMessage.push_back(messageNum);
	cout << "\t===========================================================" << endl;
    cout << "\t|    "+ UserName + " has multicasted a message to group " + groupname +"    |" << endl;
	cout << "\t===========================================================" << endl;
	cout << endl;
}
void unicast() {
	cout << "Enter the recipient user name: ";
	//new message buffer used to add memssage  to where user want
	//if we add message buffer to writeMessageToGroup or user
	//then we get old message and new message in a file.
	string newMessageBuffer;
	string username;
	string nowTimes = std::to_string(numOfMessage.back());//get max message nnumber
	message_buffer += "{!" + nowTimes + "!}";
	newMessageBuffer += "{!" + nowTimes + "!}";
	getline(cin, username);
	message_buffer += "(" + UserName + ") " + "<! " + username + " !>"+ ":";
	newMessageBuffer += "(" + UserName + ") " + "<! " + username + " !>"+ ":";
	cout <<endl;
	string message;
	cout << "Enter message: ";
	while (message != "^!") {
		message_buffer += message;
		newMessageBuffer += message;
		cin.clear();
		getline(cin, message);
		message_buffer += "\n";
		newMessageBuffer +="\n";
	}
	string openUserFile = UserName + ".txt";
	writeMessageToUser.open(openUserFile, ios::app);
	writeMessageToUser << newMessageBuffer;
	writeMessageToUser.close();
	// write to allInfo file
	writeMessageToUser.open("AllInformation.txt", ios::app);
	writeMessageToUser << newMessageBuffer;
	writeMessageToUser.close();
	// messageNum is increased,when user send a message
	messageNum++;
	writeNumOfMessageToFile.open("numOfMessage.txt", ios::app);
	string num = std::to_string(messageNum) + "\n";
	writeNumOfMessageToFile << num;
	writeNumOfMessageToFile.close();
	numOfMessage.push_back(messageNum);
	cout << "\t===========================================================" << endl;
	cout << "\t|    "+ UserName + " has unicasted a message to " + username +"    |" << endl;
	cout << "\t===========================================================" << endl;
	cout << endl;
}
void getHomePage() {
	cout << "===========================================" << endl;
	cout << "|              " + UserName+ "¡¯s Home Page            |" << endl;
    cout << "===========================================" << endl;
    int nMessages = 0;
    std::string::size_type n;
    string messages = message_buffer;
    while (messages.length() > 0) {



    		int bUserName = messages.rfind("(");
    		int eUserName = messages.rfind(")");
    		string uName;
    		uName = messages.substr(bUserName + 1, eUserName - bUserName -1);
    		int sNames = messages.rfind("<!");
    		int eNames = messages.rfind("!>");
    		string anyName;
    		anyName = messages.substr(sNames + 3, eNames - sNames - 4);
    		int sTimes = messages.rfind("{!");
    		int eTimes = messages.rfind("!}");
    		if (nMessages == 3) {
    		    	string choice;
    		    	do {
    		    		cout << "More messages(yes/no): ";
    		    		getline(cin, choice);
    		    	}while(choice != "yes" && choice != "no");
    		    	if (choice == "no") {
    		    		break;
    		    	}
    		    }
    		// determine next message includes that other user sent to current user
    		// and all message sent to #All group
    		// and current user sent to any groups
    		if (anyName == groups[currentGroup].getGroupName() || anyName == "#ALL" || UserName == anyName || UserName == uName) {
    			// if other user sent to current user
    			//then show printing style like fellow
    			//just print sender
    			if (UserName == anyName) {
    				cout << uName + " >";
    			}
    			else {
    				cout << uName + " (" + anyName + ") > ";
    			}
    			string printMessage = messages.substr(eNames + 3, messages.length() - 2);
    			cout << printMessage << endl;
    			nMessages++;
    		}
    		else {
    			nMessages++;
    			messages = messages.substr(0, bUserName);
    			messages.erase(sTimes, eTimes);
    		}
    		// when we print two messages on the display
    		// i will look whether the remaining message includes current user message.
    		// if the remaining message has messages about current user
    		// then we do nothing
    		// if findName == false
    		// then break
    		if (nMessages == 2) {
    		    string remainString = messages;
    		    string message = remainString.erase(sTimes, messages.length());
    		    //cout << message;
    		    string name = "(" + UserName + ") ";
    		    string group = groups[currentGroup].getGroupName();
    		    //make sure the remaining message whether includes UserName
    		    //if yes, then keep print
    		    // if not, then get out.
    		    n = message.find(name);
    		    bool findName = findString(n, message);
    		    n = message.find(group);
    		    bool findGroup = findString(n, message);

    		    if(findName == false && findGroup == false) {
    		    	cout << "===========================================" << endl;
    		    	cout << "|              End of " + UserName+ "¡¯s Wall Page  |" << endl;
    		    	cout << "===========================================" << endl;
    		    	break;
    		    }
    		   }
    		// when sTimes == 0 means that we are doing last message.
    		// when we already print last message, then we break.
    		if (sTimes == 0) {
    			cout << "===========================================" << endl;
    			cout << "|              End of " + UserName+ "¡¯s Home Page  |" << endl;
    			cout << "===========================================" << endl;
    			break;
    		}

    		messages = messages.substr(0, bUserName);
    		messages.erase(sTimes, eTimes);
    		//cout << messages;


    }
}
	//before start again, we will automatically read information from file that user
    //want, then save as message_buffer
    //  we rerun program each time, message_buffer must be clean
    // we do not worry about message_buffer has some infor.
void readInfoToMesaageBuffer() {
	ifstream readFiles;
	readFiles.open("AllInformation.txt");;
	string lines;
	while(getline(readFiles,lines)){
		message_buffer += lines;
		message_buffer += "\n";
	}
}
void getWallPage() {
	cout << "===========================================" << endl;
	cout << "|              " + UserName + "¡¯s Wall Page            |" << endl;
    cout << "===========================================" << endl;
    int numberOfMessages = 0;
    //bool findName = false;
    std::string::size_type n;
    string subString = message_buffer;
    while (subString.length() > 0) {
    	//getting names as follow like group name and user name quoted by <! !>
       	int startOfNames = subString.rfind("<!");
 	   	int endOfNames = subString.rfind("!>");
       	string names;
 	   	names = subString.substr(startOfNames + 3, endOfNames - startOfNames - 4);
    	//got names as above
 	   int startOfUserName = subString.rfind("(");
       int endOfUserName = subString.rfind(")");
       // user name is a current user.
       string userName = subString.substr(startOfUserName + 1, endOfUserName - startOfUserName - 1);
       int startOfTime = subString.rfind("{!");
       //int endOfTime = subString.rfind("!}");

 	   if (numberOfMessages == 2) {
 	       		string choice;
 	       		do {
 	       			cout << "More messages(yes/no): ";
 	       			getline(cin, choice);
 	       		}while(choice != "yes" && choice != "no");
 	       		if (choice == "no") {
 	       			break;
 	       		}
 	       	}
 	   //if searched name is equal to current user name
 	   // then print message with names
 	   if (UserName == userName) {
 		  cout << " (" + names + ") > ";
 		  string message = subString.substr(endOfNames + 3, subString.length() - 2);
 		  numberOfMessages++;
 		  cout << message << endl;
 		  //subString.erase(startOfTime, endOfTime);
 		  //reset message_buffer, so that we can print out all messages that stored
 		  subString = subString.substr(0, startOfTime);
 		 if (numberOfMessages == 2) {
 		  	    string remainString = subString;
 		  	    string message = remainString.erase(startOfTime, subString.length());

 		  	    string name = "(" + UserName + ") ";
 		  	    string group = groups[currentGroup].getGroupName();
 		  	    //make sure the remaining message whether includes UserName
 		  	    //if yes, then keep print
 		  	    // if not, then get out.
 		  	    n = message.find(name);
 		  	    bool findName = findString(n, message);

 		  	    if(findName == false) {
 		  	    	cout << "===========================================" << endl;
 		  	    	cout << "|              End of " + UserName+ "¡¯s Wall Page  |" << endl;
 		  	    	cout << "===========================================" << endl;
 		  	    break;
 		  	   }
 		  }
 		 if (startOfTime == 0) {
 			cout << "===========================================" << endl;
 			cout << "|              End of " + UserName+ "¡¯s Wall Page  |" << endl;
 			cout << "===========================================" << endl;
 			break;
 		 }
 	   }
 	   else {
 		  subString = subString.substr(0, startOfTime);
 	   }
    }

}
/*
 * find current user's message.
 */
bool findString(std::string::size_type n, std::string &s) {
	bool found = false;
	if (n == std::string::npos) {
		found = false;
	}
	else{
		found = true;
	}
	return found;
}

