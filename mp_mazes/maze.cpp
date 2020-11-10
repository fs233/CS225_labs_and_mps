/* Your code here! */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include "maze.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze(){

}
void SquareMaze::makeMaze(int width, int height){
   
    /*_height = height;
    _width = width;
    set->addelements(width*height);
    vector<int> possible_direction;
    for(int i = 0; i<width*height; i++){
        Cell* current = new Cell(false, false); //you can not go right or down, all blocked
        maze.push_back(current);
    }
    for(int i = 0; i<width*height; i++){
        vector<int> direction;
        if((i%_width!=0)&&((set->find(i)!=set->find(i-1)) || (set->find(i)==-1 && set->find(i+_width)==-1))){
            possible_direction.push_back(0);
        }
        if(!(i<_width)&&((set->find(i)!=set->find(i-_width)) || (set->find(i)==-1 && set->find(i+_width)==-1))){
            possible_direction.push_back(1);
        }
        if(!((i+1)%_width)&&((set->find(i)!=set->find(i+1)) || (set->find(i)==-1 && set->find(i+_width)==-1))){
            possible_direction.push_back(2);
        }
        if((i<_width*(_height-1))&&((set->find(i)!=set->find(i+_width)) || (set->find(i)==-1 && set->find(i+_width)==-1))){
            possible_direction.push_back(3);
        }

        if(possible_direction.size()==0) continue;
        int choice = possible_direction[rand()%possible_direction.size()];
        if(choice == 0){//wall on the left
            set->setunion(i-1, i);
            maze[i-1]->_right = true;//wall removed, can travel
        }
        if(choice == 1){//wall above
            set->setunion(i-_width, i);
            maze[i-_width]->_down = true;
        }
        if(choice == 2){//wall rigth
            set->setunion(i, i+1);
            maze[i]->_right = true;
        }
        if(choice == 3){
            set->setunion(i, i+_width);
            maze[i]->_down = true;
        }
    }*/
}






bool SquareMaze::canTravel(int x, int y, int dir)const{return false;}
void SquareMaze::setWall(int x, int y, int dir, bool exists){

}
vector<int> SquareMaze::solveMaze(){
    vector<int> solve;
    solve.push_back(1);
    return solve;
}





PNG* SquareMaze::drawMaze()const{
    /*PNG* maze_canvas = new PNG(_width*10+1, _height*10+1);
    for(int i = 0; i<(_width*10+1); i++){
        HSLAPixel &pixel = maze_canvas->getPixel(0, i);
        pixel.l = 0;
    }
    for(int i = 10; i<(_height*10+1); i++){
        HSLAPixel &pixel = maze_canvas->getPixel(i, 0);
        pixel.l = 0;
    }
    for(int i = 0; i<_width; i++){
        for(int j = 0; j<_height; j++){
            if(maze[i+j*_width]->_right == false){
                for(int k = 0; k<11; k++){
                    HSLAPixel &pixel = maze_canvas->getPixel((i+1)*10, j*10+k);
                    pixel.l = 0;
                }
            }
            if(maze[i+j*_width]->_down == false){
                for(int k = 0; k<11; k++){
                HSLAPixel &pixel = maze_canvas->getPixel(i*10+k, (j+1)*10);
                pixel.l = 0;
                }
            }
        }
    }*/
    return NULL;
}




PNG* SquareMaze::drawMazeWithSolution(){
    //PNG* final_maze = new PNG(_width, _height);
    return NULL;
}

