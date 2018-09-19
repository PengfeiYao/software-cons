/*
 * Game.cpp
 *
 *  Created on: 2017/11/12
 *      Author: pengfeiyao
 */
#include <sstream>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
int d;
Game::Game() {

}

/*Game::Game(std::string filename) {
	file = filename;
}*/


void Game::fileParse() {
	std::ifstream istream;
	//string filename;
	//std::cout << "Please type file name:  ";
	//std::cin >> filename;
	istream.open(file);
	if(istream.is_open()) {
		std::string line;
		int i = 0;
		int arrayLoc = 0;
		while(std::getline(istream, line)) {
			//std::cout << i << " i value!" << std::endl;
			if(i == 0) {
				//std::cout << line << "stoi" << std::endl;
				numNodes = std::stoi(line);
				nodes = new Node[numNodes];
			}
			else if(i == 1) {
				if(!checkNode(line)) {
					//Node newNode = Node(line);
					nodes[0] = Node(line);
					arrayLoc++;
				}
				startNode = &nodes[0];
			}

			else if(i == 2) {
				if(!checkNode(line)) {
					nodes[1] = Node(line);
					arrayLoc++;
				}
				endNode = &nodes[1];
			}

			else {
				std::vector<std::string> lineData;
				std::stringstream linestream(line);
				std::string value;
				while(linestream >> value) {
					lineData.push_back(value);
				}
				int j = 0;
				Node* workingNode;
				while(j <= 5) {
					//std::cout << "line data: " << lineData[j] << std::endl;
					if(j == 0) {
						if(!checkNode(lineData[j])) {
							nodes[arrayLoc] = Node(lineData[j]);
							arrayLoc++;
						}
						workingNode = getNode(lineData[j]);
						//std::cout << "working name " << workingNode->getNodeName() << std::endl;
					}
					else if(j == 5) {
						if(lineData[j] == "*")
							workingNode->attachSnakeLadderNode(NULL);
						else if(!checkNode(lineData[j])) {
							nodes[arrayLoc] = Node(lineData[j]);
							arrayLoc++;
							workingNode->attachSnakeLadderNode(getNode(lineData[j]));
						}
						else workingNode->attachSnakeLadderNode(getNode(lineData[j]));
					}
					else {
						if(lineData[j] == "*")
							workingNode->attachNewNode(NULL, j-1);
						else if(!checkNode(lineData[j])) {
							nodes[arrayLoc] = Node(lineData[j]);
							arrayLoc++;
							workingNode->attachNewNode(getNode(lineData[j]), j-1);
						}
						else workingNode->attachNewNode(getNode(lineData[j]), j-1);
					}
					j++;
				}
			}
			//std::cout << "What's going on down here?" << std::endl;
			i++;
		}
		istream.close();
	}
	else std::cout << "Couldn't open file with given name";

}

bool Game::checkNode(std::string name) {
	for(int i = 0; i < numNodes; i++) {
		if(nodes[i].getNodeName() == name)
			return true;
	}
	return false;
}

Node* Game::getNode(std::string name) {
	for(int i = 0; i < numNodes; i++) {
		if(nodes[i].getNodeName() == name) {
			//std::cout<< "LOL " << nodes[i].getNodeName() << std::endl;
			return &nodes[i];
		}
	}
	//Node n = Node();
	return NULL;
}

void Game::movePlayer(Node *node) {
	currentNode = node;
	path.insert(path.begin(), currentNode->getNodeName());
}

void Game::printOptions() {
	if (checkFile()) {
		fileParse();
		currentNode = startNode;
		path.insert(path.begin(), currentNode->getNodeName());
	}
	else {
		string lastNode;
		ifstream readFile;
		string userNameFile = userName[currentUser] + ".txt";
		string steps;
		readFile.open(userNameFile);
		while(readFile >> steps) {
			lastNode = steps;
		}
		cout << "LOL" + lastNode << endl;
		readFile.close();
		//getNode(lastNode);
		currentNode = getNode(lastNode);

	}



	while(d > 0) {
		std::cout << "You are currently on Node " << currentNode->getNodeName();

		if(currentNode->getSnakeLadderNode() != NULL) {
			std::cout << ", andLadder Node on " << currentNode->getNodeName() << "! ";
			movePlayer(currentNode->getSnakeLadderNode());
		}

		bool n, e, s, w;
		n = e = s = w = false;
		//std::cout << "BOOLS" << n << " " << e << " " << s << " " << w << std::endl;
		int i = 0;
		while(i < 4){
			switch(i) {
				case 0:
					if(currentNode->getAttachedNode(0) != 0)
						n = true;
					break;
				case 1:
					if(currentNode->getAttachedNode(1) != 0)
						e = true;
					break;
				case 2:
					if(currentNode->getAttachedNode(2) != 0)
						s = true;
					break;
				case 3:
					if(currentNode->getAttachedNode(3) != 0)
						w = true;
					break;
			}
			i++;
		}

		std::cout <<", you can go: ";
		if(n) {
			std::cout << "North ";
		}
		if(e) {
			std::cout << "East ";
		}
		if(s) {
			std::cout << "South ";
		}
		if(w) {
			std::cout << "West";
		}

		std::cout << ". What is your choice?";
		string choice;
		getline(cin, choice);

		bool ans = true;
		if(choice != "n" && choice != "e" && choice != "s" && choice != "w")
			ans = false;
		if( (!n && choice == "n") || (!e && choice == "e") || (!s && choice == "s") || (!w && choice == "w"))
			ans = false;
		//add check here for bad nodes
		while(!ans) {
			std::cout << "Not a valid response." << std::endl;
			std::cout << "What is your choice?" << std::endl;
			choice = "";
			getline(std::cin, choice);
			if((choice == "n" && n) || (choice == "e" && e) || (choice == "s" && s) || (choice == "w" && w))
				ans = true;
		}
		if(choice == "n")
			movePlayer(currentNode->getAttachedNode(0));
		else if(choice == "e")
			movePlayer(currentNode->getAttachedNode(1));
		else if(choice == "s")
			movePlayer(currentNode->getAttachedNode(2));
		else if(choice == "w")
			movePlayer(currentNode->getAttachedNode(3));

		/*if(currentNode->getSnakeLadderNode() != NULL) {
			std::cout << "Ladder Node on " << currentNode->getNodeName() << "!" << std::endl;
			movePlayer(currentNode->getSnakeLadderNode());

		}*///check snake/ladder
		cout << currentNode->getNodeName();
		writeSteps();
		if(currentNode == endNode) {
			readSteps();
			int j = winnerSteps.size() - 1;
			std::cout << "Congratulations! " << userName[currentUser] << " is the winner! You have reached the destination point." << std::endl;

			std::cout << "You took " << j << " steps" << std::endl;

			std::cout << "the nodes you visited are: ";
			printPath();
			break;
		}
		//check if end
		d--;

	}

}

void Game::printPath() {
	int i;
	int j = winnerSteps.size();
	for(i = 1; i < j; i++) {
		std::cout << winnerSteps[i] << ", ";
	}
}

void Game::turnUser() {
	//currentUser = 0;
	if (currentNode != endNode) {
	srand (time(NULL));
	d = rand() % 6 + 1;
	checkFile();
	std::cout << "==========================" << endl;
	std::cout << "      " <<userName[currentUser] << "'s turn     " << endl;
	std::cout << "==========================" << endl;
	std::cout << endl;
	std::cout << userName[currentUser] << "'s turn to throw the dice, just hit enter" << endl;
	std::cout << userName[currentUser] << "'s Dice throw is " << d << endl;
	std::cout << userName[currentUser] << " can move to " << d << " nodes" << endl;
	std::cout << endl;

	printOptions();
	runtimes++;
	currentUser++;
	int i = userName.size();
	if(currentUser >= i ) {
			currentUser = 0;
	}
	turnUser();

	}

}

void Game::users() {
	std::cout << "======================================" << endl;
	std::cout << "| Welcome to the Snake and Ladders Maze Game |" << endl;
	std::cout << "======================================" << endl;
	int num;
	std::cout << "Please type file name:";
	cin >> file;
	cin.ignore();
	std::cout << "Enter the number of player: ";
	cin >> num;
	for (int i = 1; i <= num; i++) {
		std::cout << "Enter the name of Player #" << i << ":";
		string name;
		cin >> name;
		cin.ignore();
		userName.push_back(name);
		string userNameFile =  name + ".txt";
		ofstream writeFile;
		writeFile.open(userNameFile, ios::app);
		writeFile << "first\n";
		writeFile.close();
	}
}
void Game::writeSteps() {
	string userNameFile = userName[currentUser] + ".txt";
	ofstream writeFile;
	writeFile.open(userNameFile, ios::app);
	writeFile << currentNode->getNodeName() << "\n";
	writeFile.close();
}
void Game::readSteps() {
	ifstream readFile;
	string userNameFile = userName[currentUser] + ".txt";
	string steps;
	readFile.open(userNameFile);
	while(readFile >> steps) {
		winnerSteps.push_back(steps);
	}
	readFile.close();
}
bool Game::checkFile() {
	bool fileEmpty = false;
	int length = 0;
	ifstream readFile;
	string userNameFile = userName[currentUser] + ".txt";
	string steps;
	readFile.open(userNameFile);
	while(readFile >> steps) {
		length++;
	}
	readFile.close();
	if (length == 1) {
		return fileEmpty = true;
	}
	else {
		return fileEmpty;
	}
}

