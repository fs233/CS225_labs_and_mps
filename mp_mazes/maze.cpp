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
    _height = 0;
    _width = 0;
    set = new DisjointSets();

}
void SquareMaze::makeMaze(int width, int height){
    if(set->size){
        
    }
    _height = height;
    _width = width;
    set->addelements(width*height);
    
    for(int i = 0; i<width*height; i++){
        Cell* current = new Cell(false, false); //you can not go right or down, all blocked
        maze.push_back(current);
    }

    for(int i = 0; i<width*height; i++){
        vector<int> possible_direction;
        if((i%_width!=0)&&(set->find(i)!=set->find(i-1))){//can go left
            possible_direction.push_back(0);
        }
        if(!(i<_width)&&(set->find(i)!=set->find(i-_width))){//can go up
            possible_direction.push_back(1);
        }
        if(i+1<width*height){
            if(((i+1)%_width!=0)&&(set->find(i)!=set->find(i+1))){//can go right
                possible_direction.push_back(2);
            }
        }
        if((i<_width*(_height-1))&&(set->find(i)!=set->find(i+_width))){//can go down
                possible_direction.push_back(3);
        }
       /* std::cout<<"possible d"<<std::endl;
        std::cout<<i<<std::endl;
        for(int j: possible_direction){
            std::cout<<j<<std::endl;
        }*/
       // std::cout<<"size"<<possible_direction.size()<<std::endl;
        if(possible_direction.size()==0) continue;
        int choice = possible_direction[rand()%possible_direction.size()];
        //std::cout<<"ch"<<choice<<std::endl;
        if(choice == 0){//wall on the left
            set->setunion(i, i-1);
            maze[i-1]->_right = true;//wall removed, can travel
        }
        if(choice == 1){//wall above
            set->setunion(i, i-_width);
            maze[i-_width]->_down = true;
        }
        if(choice == 2){//wall right
            set->setunion(i, i+1);
            maze[i]->_right = true;
        }
        if(choice == 3){
            set->setunion(i, i+_width);
            maze[i]->_down = true;
        }
    }
}






bool SquareMaze::canTravel(int x, int y, int dir)const{
    int i = x+y*_width;
    if(dir==0){
        return maze[i]->_right;
    }
    if(dir == 1){
        return maze[i]->_down;
    }
    if(dir==2 && x!=0){
        return maze[i-1]->_right;
    }
    if(dir==3 && y!=0){
        return maze[i-_width]->_down;
    }
    return false;
}




void SquareMaze::setWall(int x, int y, int dir, bool exists){
    int i = x+y*_width;
    if(dir==0){
        maze[i]->_right = !exists;
    }
    if(dir==1){
        maze[i]->_down = !exists;
    }

}
vector<int> SquareMaze::solveMaze(){
    vector<int> solve;
    solve.push_back(1);
    return solve;
}





PNG* SquareMaze::drawMaze()const{
    PNG* maze_canvas = new PNG(_width*10+1, _height*10+1);
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
                HSLAPixel &pixel = maze_canvas->getPixel((i*10)+k, (j+1)*10);
                pixel.l = 0;
                }
            }
        }
    }
    return maze_canvas;
}




PNG* SquareMaze::drawMazeWithSolution(){
    PNG* final_maze = new PNG(_width, _height);
    return final_maze;
}

