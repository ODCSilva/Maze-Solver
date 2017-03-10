#ifndef MAZESTACKNODE_H
#define MAZESTACKNODE_H
#include "Coordinate.h"

class MazeStackNode
{
private:
	Coordinate data;
	MazeStackNode *next;

public:
	MazeStackNode();
	MazeStackNode(Coordinate data, MazeStackNode* next);
	virtual ~MazeStackNode();

	Coordinate getData();
	void setData(Coordinate data);

	MazeStackNode* getNext();
	void setNext(MazeStackNode *next);
};

#endif
