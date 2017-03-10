#include "Maze.h"
#include "MazeSolver.h"
#include <conio.h>
#include <iostream>
#include <regex>
#include <sstream>
#include <Windows.h>

/**
 * Checks if the file path specified is a valid Windows file path.
 * @param filePath The path to be verified.
 * @returns True if path is valid, false otherwise.
 */
bool isValidFileName(string filePath) {
	char fullDir[_MAX_DIR];
	char fileName[_MAX_FNAME];
	char fileExt[_MAX_EXT];

	_splitpath_s(filePath.c_str(), NULL, 0, fullDir, _MAX_DIR, fileName, _MAX_FNAME, fileExt, _MAX_EXT);
	stringstream ss;

	ss << fileName;
	string fileNameWithExt = ss.str();

	try {
		regex reservedNames("^(?:CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(?:.[^.]*)?$");
		regex invalidChars("^.*?(?:[<>:\"/\\\\|?*]\\B|[<>:\"/\\\\|?*]\\b).*?$");
		regex invalidEnd("^.*[\\ \\.]$");

		if (regex_match(fileNameWithExt, reservedNames)
			|| regex_match(fileNameWithExt, invalidChars)
			|| regex_match(fileNameWithExt, invalidEnd)
			|| filePath.length() > _MAX_PATH
			|| filePath.length() == 0)
		{
			return false;
		}
	}
	catch (const regex_error &e) {
		cerr << e.what() << endl;
	}

	return true;
}

/**
 * Draws the main menu.
 */
void DisplayMainMenu() {
	COORD coord;
	cout << endl;
	cout << " +==============================================+" << endl;
	cout << " | Welcome to Maze Solver!                      |" << endl;
	cout << " +----------------------------------------------+" << endl;
	cout << " | Select the maze file you want me to solve.   |" << endl;
	cout << " +----------------------------------------------+" << endl;
	cout << " | Available Maze files :                       |" << endl;
	cout << " |                                              |" << endl;
	cout << " |    1. maze.txt                               |" << endl;
	cout << " |    2. maze2.txt                              |" << endl;
	cout << " |    3. maze3.txt                              |" << endl;
	cout << " |    4. maze4.txt                              |" << endl;
	cout << " |    5. mazex.txt                              |" << endl;
	cout << " |                                              |" << endl;
	cout << " +----------------------------------------------+" << endl;
	cout << " |                                              |" << endl;
	cout << " +==============================================+" << endl;
	coord.X = 3;
	coord.Y = 15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "Make a selection : ";
}

/**
 * MAIN FUNCTION
 */
int main() {
	regex correct("^[1-5]$");
	regex yesNo("^[yYnN]$");
	smatch match;
	COORD coord;
	int mazeNum;
	string outFile;
	Maze *maze;
	string mazes[] = {
		"mazes/maze.txt",
		"mazes/maze2.txt",
		"mazes/maze3.txt",
		"mazes/maze4.txt",
		"mazes/mazex.txt"
	};

	while (true) {
		DisplayMainMenu();

		string selection;
		cin >> selection;

		if (regex_search(selection, match, correct)) {
			bool toMain = false;

			while (!toMain) {
				system("cls");
				mazeNum = stoi(match[0].str()) - 1;
				cout << endl;
				cout << " +==============================================+" << endl;
				cout << " |                                              |" << endl;
				cout << " +----------------------------------------------+" << endl;
				coord.X = 3;
				coord.Y = 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				cout << "Maze selected: " << mazes[mazeNum];
				coord.X = 0;
				coord.Y = 4;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				cout << " | Enter the path of the file you wish to save  |" << endl;
				cout << " | the solved maze into                         |" << endl;
				cout << " +----------------------------------------------+" << endl;
				cout << " >> ";
				cin.clear();
				ws(cin);
				getline(cin, outFile);

				if (isValidFileName(outFile)) {
					bool isSlow = false;
					maze = new Maze(mazes[mazeNum]);

					system("cls");
					cout << *maze << endl;
					cout << " Maze loaded! Press <ESC> to view the solving process," << endl;
					cout << " (takes longer) or any other key to solve quickly: ";
					char r = _getch();

					if (r == 27) {
						isSlow = true;
					}

					system("cls");
					// Solve the maze
					MazeSolver solver(maze);
					solver.Solve(isSlow);

					system("cls");
					cout << *maze << endl;
					cout << " Maze solved! Press any key to continue: ";
					maze->Save(outFile);
					_getch();

					while (!toMain) {
						system("cls");
						cout << endl;
						cout << " +==============================================+" << endl;
						cout << " |                                              |" << endl;
						cout << " +----------------------------------------------+" << endl;
						coord.X = 3;
						coord.Y = 2;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						cout << "Solve another maze? [Y/N]: ";
						string choice;
						cin >> choice;

						if (regex_search(choice, match, yesNo)) {
							string o = match[0].str();

							if (o == "y" || o == "Y") {
								toMain = true;
								system("cls");
								break;
							}
							else {
								return 0;
							}
						}
						else {
							continue;
						}
						_getch();
						system("cls");
					}
				}
				else {
					system("cls");
					cout << endl;
					cout << " +==============================================+" << endl;
					cout << " | Invalid file name, try again.                |" << endl;
					cout << " +----------------------------------------------+" << endl;
					_getch();
					system("cls");
					continue;
				}
			}
		}
		else {
			system("cls");
			cout << " +==============================================+" << endl;
			cout << " | Invalid selection, try again.                |" << endl;
			cout << " +----------------------------------------------+" << endl;
			_getch();
			system("cls");
		}
	}

	_getch();
	return 0;
}