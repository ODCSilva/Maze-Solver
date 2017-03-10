#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "Maze.h"
#include "MazeStack.h"
#include <utility>

enum Dir { NORTH, SOUTH, EAST, WEST };

class MazeSolver
{
private:
	const char BREADCRUMB = '*';
	const char PATH = '#';
	int curRow;
	int curCol;
	Dir direction;
	Maze *maze;
	MazeStack mazeStack;
	void Step();
	void StepBack();
	bool CheckForWalls(int row, int col);
	void FindAlternateRoute();

public:
	MazeSolver(Maze *maze);
	void Solve(bool);

};

#endif
