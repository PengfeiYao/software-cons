/*
 * Node.cpp
 *
 *  Created on: 2017Äê11ÔÂ7ÈÕ
 *      Author: pengfeiyao
 */
#include "Node.h"
#include <iostream>

Node::Node() {

}
Node::Node(string newName) {
	name = newName;
}

void Node::setNodeName(string newName) {
	name = newName;
}

string Node::getNodeName() {
	return name;
}

void Node::attachNewNode(Node *newNode, int direction) {
	attachedNodes[direction] = newNode;
}

Node *Node::getAttachedNode(int direction) {
	return attachedNodes[direction];
}

void Node::attachSnakeLadderNode(Node *newNode) {
	snakeOrLadderNodes = newNode;
}

Node *Node::getSnakeLadderNode() {
	return snakeOrLadderNodes;
}



