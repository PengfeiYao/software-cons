/*
 * Game.h
 *
 *  Created on: 2017/11/12
 *      Author: pengfeiyao
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.h"

class Game {

	public:
		Game();
		//Game(std::string filename);
		void printOptions();
		void users();
		void turnUser();

	private:
		Node* nodes;
		Node *currentNode;
		Node *startNode;
		Node *endNode;
		std::string file;
		std::vector<std::string> userName;
		std::vector<std::string> path;
		std::vector<std::string> winnerSteps;
		int numNodes;
		int diceNum;
		int currentUser = 0;
		int runtimes = 1;
		void movePlayer(Node *node);
		//void snakeLadderNode();
		//void fileParse(std::string filename);
		void fileParse();
		bool checkNode(std::string name);
		Node* getNode(std::string name);
		void printPath();
		void writeSteps();
		void readSteps();
		void getlastNode();
		bool checkFile();

};



#endif
