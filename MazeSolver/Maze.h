#ifndef MAZE_H
#define MAZE_H
#include <string>

using namespace std;

class Maze
{
private:
	int numRows = 0;
	int numCols = 0;
	char **tiles;
	void Load(string filePath);
public:
	Maze(string filePath);
	virtual ~Maze();
	int GetNumRows();
	int GetNumCols();
	char GetCharAt(int row, int col);
	void PutChatAt(int row, int col, char c);
	void Save(string filePath);
	friend ostream& operator<<(ostream& output, Maze& maze);
};

#endif // MAZE_H
