#include "MazeStackNode.h"
#include <iostream>

using namespace std;

/**
 * Constructor
 */
MazeStackNode::MazeStackNode() : data(0, 0), next(nullptr) {
}

/**
 * Constructor
 */
MazeStackNode::MazeStackNode(Coordinate data, MazeStackNode* next) : data(data), next(next) {
}

/**
 * Destructor
 */
MazeStackNode::~MazeStackNode() {}

/**
 * Get node data.
 * @returns data as a coordinate object.
 */
Coordinate MazeStackNode::getData() {
	return data;
}

/**
 * Sets node data.
 * @param data The data to be placed.
 */
void MazeStackNode::setData(Coordinate data) {
	data = data;
}

/**
 * Returns pointer to the next node.
 * @returns
 */
MazeStackNode* MazeStackNode::getNext() {
	return next;
}

/**
 * Sets pointer to the next node.
 * @param next Pointer to the next node.
 */
void MazeStackNode::setNext(MazeStackNode *next) {
	next = next;
}