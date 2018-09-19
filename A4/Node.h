/*
 * Node.h
 *
 *  Created on: 2017Äê11ÔÂ7ÈÕ
 *      Author: pengfeiyao
 */

#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	Node();
	Node(string newName);
	void setNodeName(string newName);
	string getNodeName();
	void attachNewNode(Node *newNode, int direction);
	Node *getAttachedNode(int direction);
	void attachSnakeLadderNode(Node *newNode);
	Node *getSnakeLadderNode();

private:
	string name;
	Node *attachedNodes[4];
	Node *snakeOrLadderNodes;
};



#endif /* NODE_H_ */
