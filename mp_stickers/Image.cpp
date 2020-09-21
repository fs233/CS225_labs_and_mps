#include <iostream>
#include <cmath>
#include "Image.h"
#include "math.h"
void Image::lighten(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.l<0.9){
        pixel.l = pixel.l+0.1;
      }else{
        pixel.l=1;
      }
    }
  }
}
void Image::lighten(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.l + amount<1){
        pixel.l = pixel.l + amount;
      }else{
        pixel.l = 1;
      }
      
    }
  }
}
void Image::darken(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
       if(pixel.l>0.1){
        pixel.l = pixel.l-0.1;
      }else{
        pixel.l=0;
      }
    }
  }
}
void Image::darken(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.l - amount>0){
        pixel.l = pixel.l - amount;
      }else{
        pixel.l = 0;
      }
    }
  }
}
void Image::saturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.s<0.9){
        pixel.s = pixel.s+0.1;
      }else{
        pixel.s=1;
      }
    }
  }
}
void Image::saturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.s + amount<1){
        pixel.s = pixel.s + amount;
      }else{
        pixel.s = 1;
      }
    }
  }
}
void Image::desaturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
       if(pixel.s>0.1){
        pixel.s = pixel.s-0.1;
      }else{
        pixel.s=0;
      }
    }
  }
}
void Image::desaturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.s - amount > 0){
        pixel.s = pixel.s - amount;
      }else{
        pixel.s = 0;
      }
    }
  }
}
void Image::grayscale(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}
void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.h = pixel.h + degrees;
      while(pixel.h>360){
       pixel.h = pixel.h-360.0;
      }
      while(pixel.h<0){
       pixel.h = pixel.h+360.0;
      }
    }
  }
}
void Image::illinify(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if(fmin(abs(pixel.h-11),abs(360-pixel.h+11)) < fmin(abs(pixel.h-216),abs(360-pixel.h+216))){
        pixel.h = 11;
      }else{
        pixel.h = 216;
      }
    }
  }
}
void Image::scale(double factor){
  unsigned width = (this->width())*factor;
  unsigned height = (this->height())*factor;
  PNG* png = new PNG(*this);
  this->resize(width, height);
  if(factor>=1){
    for (unsigned x = 0; x < png->width(); x++) {
      for (unsigned y = 0; y < png->height(); y++) {
        double x1 = (double)x;
        double y1 = (double)y;
        cs225::HSLAPixel & pixel = this->getPixel(ceil(x1*factor),ceil(y1*factor));
        cs225::HSLAPixel & pixel2 = png->getPixel(x, y);
        pixel = pixel2;
      }
    }
  }else{
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        double x1 = (double)x;
        double y1 = (double)y;
        cs225::HSLAPixel & pixel = png->getPixel(ceil(x1/factor),ceil(y1/factor));
        cs225::HSLAPixel & pixel2 = this->getPixel(x, y);
        pixel2 = pixel;
      }
    }
  }
    delete png;
}
void Image::scale(unsigned w, unsigned h){
  double wid = (double)this->width();
  double hei = (double)this->height();
  double ww = (double)w;
  double hh = (double)h;
  double fac = std::min(ww/wid, hh/hei);
  this->Image::scale(fac);
}