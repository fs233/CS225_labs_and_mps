/* Your code here! */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include "maze.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze(){
    _height = 0;
    _width = 0;
}
void SquareMaze::makeMaze(int width, int height){
    if(maze.size()!=0){
        maze.clear();
        delete set;
        set = NULL;
    }
    set = new DisjointSets();
    _height = height;
    _width = width;
    set->addelements(width*height);
    //maze = vector<vector<Cell>> (_height, vector<Cell> (_width, Cell(false, false)));
    maze = vector<Cell> (_height*_width, Cell(false, false));

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
       
        if(possible_direction.size()==0) continue;
        int choice = possible_direction[rand()%possible_direction.size()];
        if(choice == 0){//wall on the left
            set->setunion(i, i-1);
            maze[i-1]._right = true;//wall removed, can travel
        }
        if(choice == 1){//wall above
            set->setunion(i, i-_width);
            maze[i-_width]._down = true;
        }
        if(choice == 2){//wall right
            set->setunion(i, i+1);
            maze[i]._right = true;
        }
        if(choice == 3){
            set->setunion(i, i+_width);
            maze[i]._down = true;
        }
    }
    delete set;
}






bool SquareMaze::canTravel(int x, int y, int dir)const{
    int i = x+y*_width;
    if(dir==0){
        return maze[i]._right;
    }
    if(dir == 1){
        return maze[i]._down;
    }
    if(dir==2 && x!=0){
        return maze[i-1]._right;
    }
    if(dir==3 && y!=0){
        return maze[i-_width]._down;
    }
    return false;
}




void SquareMaze::setWall(int x, int y, int dir, bool exists){
    int i = x+y*_width;
    if(dir==0){
        maze[i]._right = !exists;
    }
    if(dir==1){
        maze[i]._down = !exists;
    }

}
int SquareMaze::getx(int input){
    return input%_width;
}
int SquareMaze::gety(int input){
    return input/_width;
}

vector<int> SquareMaze::solveMaze()
{
    vector<int> solution;
    vector<bool> visited = vector<bool>(_width * _height, false);  
    vector<int> path_dir = vector<int>(_width * _height, -1);
    vector<int> next_cell = vector<int>(_width * _height, -1);
    vector<int> distance = vector<int>(_width * _height, 0);
    queue<int> q;
    q.push(0);
    int position = q.front();

    while(!q.empty()){
        q.pop();
        int x = getx(position);
        int y = gety(position);
        if(canTravel(x, y, 0) && !visited[position+1])
        {
            next_cell[position+1] = position;
            path_dir[position+1] = 0;
            visited[position+1] = true;
            distance[position+1] = distance[position]+1;
            q.push(position+1);
        }
        if(canTravel(x, y, 1) && !visited[position+_width])
        {
            next_cell[position+_width] = position;
            path_dir[position+_width] = 1;
            visited[position+_width] = true;
            distance[position+_width] = distance[position]+1;
            q.push(position+_width);
        }
        if(canTravel(x, y, 2) && !visited[position-1])
        {
            next_cell[position-1] = position;
            path_dir[position-1] = 2;
            visited[position-1] = true;
            distance[position-1] = distance[position]+1;
            q.push(position-1);
        }
        if(canTravel(x, y, 3) && !visited[position-_width])
        {
            next_cell[position-_width] = position;
            path_dir[position-_width] = 3;
            visited[position-_width] = true;
            distance[position-_width] = distance[position]+1;
            q.push(position-_width);
        }
        position = q.front();
    }
    int max_cell = _width*(_height-1);
    for(int i = 0; i<_width; i++){
        if(distance[max_cell]<distance[_width*(_height-1)+i]){
            max_cell = _width*(_height-1)+i;
        }
    }
    int current = max_cell;
     while (current>0)
    {
        solution.insert(solution.begin(), path_dir[current]);
        current = next_cell[current];
    }
    return solution;
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
            if(maze[i+j*_width]._right == false){
                for(int k = 0; k<11; k++){
                    HSLAPixel &pixel = maze_canvas->getPixel((i+1)*10, j*10+k);
                    pixel.l = 0;
                }
            }
            if(maze[i+j*_width]._down == false){
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
    PNG* backgroud = this->drawMaze();
    vector<int> answer = this->solveMaze();
    int x = 5;
    int y = 5;
    for(unsigned i = 0; i<answer.size(); i++){
        if(answer[i]==0){
           for(int k = 0; k<11; k++){
                HSLAPixel &pixel = backgroud->getPixel(x+k, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
               
            }
            x = x+10;
            continue;
        }
        if(answer[i]==1){
           for(int k = 0; k<11; k++){
                HSLAPixel &pixel = backgroud->getPixel(x, y+k);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
               
            }
            y = y+10;
            continue;
        }
        if(answer[i]==2){
           for(int k = 0; k<11; k++){
                HSLAPixel &pixel = backgroud->getPixel(x-k, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
               
            }
            x = x-10;
            continue;
        }
        if(answer[i]==3){
           for(int k = 0; k<11; k++){
                HSLAPixel &pixel = backgroud->getPixel(x, y-k);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
               
            }
            y = y-10;
            continue;
        }
    }
    int exit_x = x/10;
    int exit_y = y/10;
    for(int i = 1; i<10; i++){
        HSLAPixel &pixel = backgroud->getPixel(exit_x*10+i, (exit_y+1)*10);
        pixel.l = 1; 
    }

    return backgroud;
}

