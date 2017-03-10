#include "MazeStackNode.h"
#include "MazeStack.h"
#include <iostream>

using namespace std;

/**
 * Main constructor.
 */
MazeStack::MazeStack() : top(nullptr) {}

/**
 * Virtual destructor.
 */
MazeStack::~MazeStack() {
	while (top != nullptr) {
		Pop();
	}
}

/**
 * Pushes a new node into the stack list.
 * @param coord Coodinate to insert as data for the new node.
 */
void MazeStack::Push(Coordinate coord) {
	top = new MazeStackNode(coord, top);
}

/**
 * Gets the value of the top node.
 */
Coordinate MazeStack::Peek() {
	if (top != nullptr) {
		return top->getData();
	}

	return Coordinate(-1, -1);
}

/**
 * Pops a node out of the stack list.
 */
void MazeStack::Pop() {
	if (top != nullptr) {
		MazeStackNode* node = top;
		top = top->getNext();
		delete node;
	}
}

/**
 * Overridden << operator. 
 */
ostream& operator<<(ostream& output, MazeStack& stack) {
	MazeStackNode *node = stack.top;

	while (node != nullptr) {
		cout << "X: " << node->getData().x << " Y: " << node->getData().y << endl;
		node = node->getNext();
	}

	return output;
}