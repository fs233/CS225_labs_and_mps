#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze maze;
	maze.makeMaze(2, 2);
	PNG * actualOutput = maze.drawMaze();
	actualOutput->writeToFile("testMaze"+ string(".png"));
    return 0;
}
