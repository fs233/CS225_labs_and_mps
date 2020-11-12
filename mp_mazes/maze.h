/* Your code here! */
#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace cs225;

class SquareMaze{
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir)const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze()const;
        PNG* drawMazeWithSolution();
        int _height;
        int _width;
        
        DisjointSets* set;
        
        class Cell{
            public:
            Cell(bool right, bool down){
                _right = right;
                _down = down;
            }
                bool _right;
                bool _down; 
        };
        vector<Cell*> maze;
        
};
