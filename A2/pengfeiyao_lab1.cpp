#include <iostream>
#include "user.h"
#include "group.h"
#include <vector>
#include <algorithm>
using namespace std;

vector<user> users;
vector<group> groups;
void switchCase(string l);
string optionSelected();
void createNewUser();
int currentUser = 0;
int currentGroup = 0;
string message_buffer;
void createGroup();
void joinGroup();
void switchUser();
void Broadcast();
void unicast();
void multicast();
void getHomePage();
void getWallPage();
void messageReader(int end, string subString);
int main() {
	//Providing a main menu
	string option;
	std::cout << "\t===========================================================\n";
    std::cout << "\t|               The TigerBook Social Network              |\n";
    std::cout << "\t===========================================================\n";

    do {
    	option = optionSelected();
    	switchCase(option);
    } while(option != "q");

	return 0;
}
string optionSelected()
{
	std::cout << "Create new user (n), Broadcast (b), Multicast (m), Unicast (u), Wall page (w), Home page (h), Create new group (g),\n" <<
	    		"Join a group (j), Switch user (s), Quit (q)";
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
    cout << "\t|           Thank you for using TigerBook Social Network    |" << endl;
    cout << "\t==============================================================" << endl;
}
// switch cases
// user can make a choice by typing letter
//so far we have not down pointer
void switchCase(string l) {
	const char *option = l.c_str();
	switch (*option) {
	case 'n':
		createNewUser();
		break;
	case 'b':
		if (users.size() < 1 || groups.size() < 1) {
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
		if (users.size() < 2) {
				cout << "not enough group!\n";
			}
			else {
				unicast();
			}
		break;
	case 'w':
		if (users.size() < 1) {
			cout << "No user defind." << endl;
		}
		else {
			getWallPage();
		}

		break;
	case 'h':
		if (users.size() < 1) {
					cout << "No user defind." << endl;
		}
		else {
			getHomePage();
		}
		break;
	case 'g':
		if (users.size() < 1) {
			cout << "no user defind" << endl;

		}
		else {
			createGroup();
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
	case 's':
		if (users.size() < 2) {
			cout << "Not enough users!/n";
		}
		else {
			switchUser();
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
void createNewUser() {
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
}
//creating a group
// if a group is already, this group won't created again.
//double check group name
void createGroup() {
	bool valid = true;
	cout << "Please enter the group name: ";
	std::string groupname;
	getline(cin, groupname);
	for (std::size_t i = 0; i < groups.size(); i++) {
			if (groups[i].getGroupName() == groupname) {
				valid = false;
				break;
			}
			currentGroup = i + 1;
	}

	if (valid) {
		groups.push_back(group(groupname));

		cout << "\t===========================================================" << endl;
			cout << "\t|                " + groups[currentGroup].getGroupName() + " group created     |" << endl;
			cout << "\t===========================================================" << endl;
			//currentGroup++;
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
	if(vaild && users.size() > 0) {
		cout << "\t===========================================================" << endl;
		cout << "\t|              " + users[currentUser].getUsername() + " is in " + groups[currentGroup].getGroupName() + " group       |"     << endl;
		cout << "\t===========================================================" << endl;
	}
	else {
		cout << "no group exit!\n";
	}
}
void switchUser() {
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
}
void Broadcast() {
	cout << "Enter message: ";
	message_buffer += "(" + users[currentUser].getUsername() + ") ";
	message_buffer += "<! #ALL !>:";
	string message;
	while (message != "^!") {
		message_buffer += message;
		//message_buffer += "^!";
		cin.clear();
		getline(cin, message);
	}
	cout << endl;
}
void multicast() {
	cout << "Please enter group name: ";
	string groupname;
	getline(cin, groupname);
	message_buffer += "(" + users[currentUser].getUsername() + ") " + "<! " + groupname + " !>" + ":";
	cout << endl;
	string message;
	cout << "Enter message: ";
	while (message !="^!") {
		message_buffer += message;
		//message_buffer += "^!";
		cin.clear();
		getline(cin, message);
	}
	cout << endl;
}
void unicast() {
	cout << "Enter the recipient user name: ";
	string username;
	getline(cin, username);
	message_buffer += "(" + users[currentUser].getUsername() + ") " + "<! " + username + " !>"+ ":";
	cout <<endl;
	string message;
	cout << "Enter message: ";
	while (message != "^!") {
		message_buffer += message;
		//message_buffer += "^!";
		cin.clear();
		getline(cin, message);
	}
	cout << endl;
}
void getHomePage() {
	cout << "===========================================" << endl;
	cout << "|              " + users[currentUser].getUsername() + "¡¯s Home Page            |" << endl;
    cout << "===========================================" << endl;
    int numberOfMessages = 0;
    string subString = message_buffer;
    while (subString.length() > 0) {

    	//getting user name as follow
    	int startOfUserName = subString.rfind("(");

    	int endOfUserName = subString.rfind(")");
    	string userName;
    	userName = subString.substr(startOfUserName + 1, endOfUserName - startOfUserName - 1);
    	//got user name as above
    	//getting names as follow like group name and user name quoted by <! !>
    	int startOfNames = subString.rfind("<!");
    	int endOfNames = subString.rfind("!>");
    	string names;
    	names = subString.substr(startOfNames + 3, endOfNames - startOfNames - 4);

    	//got names as above
    	numberOfMessages++;
    	// more messsages?
    	// if yes, keep going
    	// if no, break
    	if (numberOfMessages == 3) {
    		string choice;
    		do {
    			cout << "More messages(yes/no): ";
    			getline(cin, choice);
    		}while(choice != "yes" && choice != "no");
    		if (choice == "no") {
    			break;
    		}
    	}
    	// print user name and names
    	cout << userName + " (" + names + ") > ";
    	//print latest message
    	string message = subString.substr(endOfNames + 3, subString.length() - 2);
    	cout << message << endl;
    	//reset message_buffer, so that we can print out all messages that stored
    	subString = subString.substr(0, startOfUserName);

    	cout << endl;
    }
}
void getWallPage() {
	cout << "===========================================" << endl;
	cout << "|              " + users[currentUser].getUsername() + "¡¯s Wall Page            |" << endl;
    cout << "===========================================" << endl;
    int numberOfMessages = 0;
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
       numberOfMessages++;
 	   if (numberOfMessages == 3) {
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
 	   if (users[currentUser].getUsername() == userName) {
 		   cout << " (" + names + ") > ";
 		   string message = subString.substr(endOfNames + 3, subString.length() - 2);
 		   cout << message << endl;
 		   //reset message_buffer, so that we can print out all messages that stored
 		   subString = subString.substr(0, startOfUserName);

 	   }
 	   else {
 		  subString = subString.substr(0, startOfUserName);
 	   }
    }
}

