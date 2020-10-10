#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator():t(NULL){
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point &start, double tolerance, PNG & png)
:t(traversal), start_(start), tolerance_(tolerance), image_(png){
    current = t->peek();
    passed.resize(image_.width()*image_.height(), false);
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
if(!t->empty()){
    HSLAPixel star = image_.getPixel(start_.x, start_.y);
    passed[current.x+current.y*image_.width()]=true;
  while(passed[current.x+current.y*image_.width()]==true && !t->empty()){
    current = t->pop();
    //std::cout<<"poppedoff"<<std::endl;
    //std::cout<<current<<std::endl;
    Point right(current.x+1, current.y);
    Point below(current.x, current.y+1);
    Point left(current.x-1,current.y);
    Point above(current.x, current.y-1);
    if(0<=right.x && right.x<image_.width() && 0<=right.y && right.y<image_.height() && passed[right.x+right.y*image_.width()]==false){
      HSLAPixel curr = image_.getPixel(right.x, right.y);
      if(calculateDelta(star, curr) < tolerance_){
          t->add(right);
         //std::cout<<"right add"<<std::endl;
         //std::cout<<right<<std::endl;
      }
    }
    if(0<=below.x && below.x<image_.width() && 0<=below.y && below.y<image_.height()  && passed[below.x+below.y*image_.width()]==false){
      HSLAPixel curr = image_.getPixel(below.x, below.y);
      if(calculateDelta(star, curr) < tolerance_){
          t->add(below);
          //std::cout<<"below add"<<std::endl;
          //std::cout<<below<<std::endl;
      }
    }
    if(0<=left.x && left.x<image_.width() && 0<=left.y && left.y<image_.height() && passed[left.x+left.y*image_.width()]==false){
      HSLAPixel curr = image_.getPixel(left.x, left.y);
      if(calculateDelta(star, curr) < tolerance_){
          t->add(left);
          //std::cout<<"left add"<<std::endl;
          //std::cout<<left<<std::endl;
      }
    }
    if(0<=above.x && above.x<image_.width() && 0<=above.y && above.y<image_.height() && passed[above.x+above.y*image_.width()]==false){
      HSLAPixel curr = image_.getPixel(above.x, above.y);
      if(calculateDelta(star, curr) < tolerance_){
          t->add(above);
          //std::cout<<"above add"<<std::endl;
         //std::cout<<above<<std::endl;
      }
    }
    if(!t->empty()){
      current = t->peek();
    }
  }
}   //std::cout<<"current: "<<current<<std::endl;
    return *this;
}
    

  

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(t==NULL){return false;}
  if(t->empty() && other.t==NULL){
    return false;
  }
  return true;
}

