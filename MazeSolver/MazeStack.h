#ifndef MAZESTACK_H
#define MAZESTACK_H

#include "MazeStackNode.h"
#include "Coordinate.h"
#include <iostream>

using namespace std;
enum err_code { SUCCESS, STACK_UNDERFLOW, STACK_OVERFLOW };

class MazeStack
{
private:
	MazeStackNode *top;

public:
	MazeStack();
	virtual ~MazeStack();
	void Push(Coordinate num);
	Coordinate Peek();
	void Pop();
	friend ostream& operator<<(ostream& output, MazeStack& stack);
};

#endif
