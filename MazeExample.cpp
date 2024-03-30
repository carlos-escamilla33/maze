#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@       @                     @         @     @             @         @
@ @@@ @ @ @@@@@@@ @@@@@ @@@@@ @ @@@@@@@@@ @ @@@ @ @@@ @@@@@@@ @@@@@ @@@
@   @ @ @ @     @ @   @     @   @         @     @   @ @       @   @   @
@ @@@ @ @@@ @@@ @ @ @ @@@@@ @@@@@ @@@@@@@@@@@@@@@ @ @ @ @@@@@@@@@ @@@ @
@ @   @     @   @ @ @       @             @     @ @ @ @   @     @   @ @
@@@ @@@@@@@@@ @@@@@ @@@@@@@@@ @@@@@@@@@@@@@ @@@ @ @ @@@@@ @@@ @ @ @ @ @
@ @       @ @ @     @       @   @   @       @ @ @ @           @   @ @ @
@ @@@@@@@ @ @ @@@ @@@ @@@@@ @@@ @ @ @ @@@@@@@ @ @@@@@@@ @@@@@@@@@@@@@ @
@       @ @ @   @         @     @ @   @   @     @     @ @     @   @   @
@@@@@@@ @ @ @@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@ @@@@@ @@@ @@@ @@@ @ @ @ @ @
@         @                       @               @       @     @   @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/


void SolveMaze(int row, int col, char maze[][100],
               int rowSize, int colSize,
               bool &foundEnd, string currDir, string &finalDir) {

    // Already found the end from a previous SolveMaze call
    if (foundEnd) {
        return;
    }

    // base case for bounds
    if (row < 0 || col < 0 ||
    row >= rowSize || col >= colSize) {
        return;
    }

    // base case for bound end
    if (maze[row][col] == 'F') {
        finalDir = currDir;
        foundEnd = true;
        return;
    }

    // Base case for previously explored spots
    if (maze[row][col] == '.') {
        return;
    }

    // Base case for walls
    if (maze[row][col] == '@') {
        return;
    }

    maze[row][col] = '.';

    SolveMaze(row - 1, col, maze, rowSize, colSize, foundEnd, currDir + "U", finalDir); // North
    SolveMaze(row + 1, col, maze, rowSize, colSize, foundEnd, currDir + "D", finalDir); // South
    SolveMaze(row, col + 1, maze, rowSize, colSize, foundEnd, currDir + "R", finalDir); // East
    SolveMaze(row, col - 1, maze, rowSize, colSize, foundEnd, currDir + "L", finalDir); // West

    // If I have not found the end after exploring all 4 directions
    // pick up the breadcrumb
    if (!foundEnd) {
        maze[row][col] = ' ';
    }
}

int main()
{
	ifstream mazeFile("maze.txt");
	char maze[100][100]; // make larger than required

	// Initialize the maze
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			maze[i][j] = ' ';
		}

	int row = 0;
	int startRow, startCol;

	// Read the file line by line an initialize the maze
	string line;
	while (getline(mazeFile, line)) {
		cout << line << endl;
		for (int i = 0; i < (int) line.length(); i++) {
			maze[row][i] = line[i];
			if (maze[row][i] == 'S') {
				startRow = row;
				startCol = i;
				maze[row][i] = ' ';
			}
		}
		row++;
	}

	cout << "Start Position: (" << startRow << "," << startCol << ")" << endl;

	// figure out the number of rows and columns
	int rowSz = row;
	int colSz = line.length();
	
	bool foundEnd = false;

	string finaldir = "";
	string currDir = "";
	SolveMaze(startRow, startCol, maze, rowSz, colSz, foundEnd, currDir, finaldir);
	
	cout << "Directions: " << finaldir << endl;

	// Print out the maze with the path shown
	for (int i = 0; i < rowSz; i++) {
		for (int j = 0; j < colSz; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
	
    return 0;
}
