/*
 * pengfei_yao_lab3.cpp
 *	maze game
 *  Created on: 2017/11/7
 *      Author: pengfeiyao
 */

#include "Game.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	//cout << "Enter name of maze file: " << endl;
	//string file;
	//getline(cin, file);
	//cout << file << " file before call" << endl;
	Game g = Game();
	g.users();
	g.turnUser();

}


