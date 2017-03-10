#include "Maze.h"
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

/**
 * Main constructor.
 */
Maze::Maze(string filePath) {
	Load(filePath);
}

/**
 * Virtual destructor.
 */
Maze::~Maze() {
	for (int i = 0; i < numRows; i++) {
		delete[] tiles[i];
	}

	delete[] tiles;
}

/**
 * Loads a maze file.
 */
void Maze::Load(string filePath) {
	ifstream in;
	string temp;

	in.open(filePath);
	if (in.is_open()) {
		int rows = 0;
		int cols = 0;

		// Determine height and width
		while (getline(in, temp)) {
			numCols = temp.length();
			rows++;
		}

		numRows = rows;

		// Initialize char array pointer
		tiles = new char*[numRows];
		for (int i = 0; i < numRows; i++) {
			tiles[i] = new char[numCols];
		}

		// Reset file position
		in.clear();
		in.seekg(0, in.beg);

		// Populate array
		for (int i = 0; i < numRows; i++) {
			getline(in, temp);

			for (int x = 0; x < numCols; x++) {
				tiles[i][x] = temp[x];
			}
		}

		in.close();
	}
}

/**
 * Gets the number of rows in the maze.
 * @returns an Int represending the rows in the maze.
 */
int Maze::GetNumRows() {
	return numRows;
}

/**
 * Gets the number of columns in the maze.
 * @returns an Int represending the columns in the maze.
 */
int Maze::GetNumCols() {
	return numCols;
}

/**
 * Get a character at coordinates represented by row and col.
 * @param row The row coordinate.
 * @param col The col coordinate.
 * @returns the character at the specified coordinate.
 */
char Maze::GetCharAt(int row, int col) {
	return tiles[row][col];
}

/**
 * Puts a character at coordinates represented by row and col.
 * @param row The row coordinate.
 * @param col The col coordinate.
 * @param c The character to put.
 */
void Maze::PutChatAt(int row, int col, char c) {
	tiles[row][col] = c;
}

/**
 * Saves the maze to a file specified by filePath.
 * @param filePath the path of the file to save the maze into.
 */
void Maze::Save(string filePath)
{
	ofstream out;

	out.open(filePath);

	if (out.is_open()) {
		out << *this;
		out.close();
	}
}

/**
 * Overidden << operator.
 */
ostream & operator<<(ostream & output, Maze & maze) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int row = 0; row < maze.numRows; row++) {
		for (int col = 0; col < maze.numCols; col++) {
			if (maze.tiles[row][col] == '*') {
				output << ' ';
			}
			else if (maze.tiles[row][col] == '#') {
				FlushConsoleInputBuffer(hstdout);
				SetConsoleTextAttribute(hstdout, 12);
				output << maze.tiles[row][col];
				SetConsoleTextAttribute(hstdout, 15);
			}
			else {
				output << maze.tiles[row][col];
			}
		}
		output << endl;
	}

	return output;
}