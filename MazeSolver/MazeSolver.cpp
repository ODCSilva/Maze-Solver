#include "MazeSolver.h"
#include <iostream>
#include <Windows.h>

/**
 * Constructor
 * @param maze Pointer to the maze to be solved.
 */
MazeSolver::MazeSolver(Maze *maze) : maze(maze) {}

/**
 * Solves the maze.
 */
void MazeSolver::Solve(bool slowSolve) {
	COORD coord;
	int endRow = maze->GetNumRows() - 2;
	int endCol = maze->GetNumCols() - 1;
	curRow = 1;
	curCol = 0;

	direction = EAST;
	maze->PutChatAt(curRow, curCol, PATH);

	// Main solving loop.
	while (true) {
		Step();

		if (slowSolve) {
			coord.X = 0;
			coord.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			cout << *maze;
		}

		if (curRow == endRow && curCol == endCol) {
			break;
		}
	}
}

/**
 * Move forward one step in the current direction. If a wall is
 * encountered, check for alternate paths.
 */
void MazeSolver::Step() {
	int row = curRow;
	int col = curCol;

	switch (direction) {
	case NORTH:
		row--;
		break;
	case SOUTH:
		row++;
		break;
	case EAST:
		col++;
		break;
	case WEST:
		col--;
		break;
	}

	if (CheckForWalls(row, col)) {
		curRow = row;
		curCol = col;
		mazeStack.Push(Coordinate(curRow, curCol));
		maze->PutChatAt(curRow, curCol, PATH);
	}
	else {
		FindAlternateRoute();
	}
}

/**
 * Steps back to the previous position.
 */
void MazeSolver::StepBack() {
	maze->PutChatAt(curRow, curCol, BREADCRUMB);
	mazeStack.Pop();

	Coordinate coord = mazeStack.Peek();
	curRow = coord.x;
	curCol = coord.y;
}

/**
 * Checks for a wall one the tile specified by row and col.
 * @param row Row of the tile to check for walls.
 * @param col Col of the tile to check for walls.
 * @returns false is a wall is enountered, true otherwise.
 */
bool MazeSolver::CheckForWalls(int row, int col) {
	char c = maze->GetCharAt(row, col);

	if (c == '+' || c == '-' || c == '|' || c == BREADCRUMB || c == PATH) {
		return false;
	}

	return true;
}

/**
 * Finds an alternate route to move through, otherwise step back
 * to the previous position.
 */
void MazeSolver::FindAlternateRoute() {
	int row = curRow;
	int col = curCol;

	if (CheckForWalls(row, col + 1)) {
		direction = EAST;
	}
	else if (CheckForWalls(row + 1, col)) {
		direction = SOUTH;
	}
	else if (CheckForWalls(row, col - 1)) {
		direction = WEST;
	}
	else if (CheckForWalls(row - 1, col)) {
		direction = NORTH;
	}
	else {
		StepBack();
	}
}