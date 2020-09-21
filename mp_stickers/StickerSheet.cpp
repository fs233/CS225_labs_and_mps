#include <iostream>
#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

StickerSheet::StickerSheet (const Image &picture, unsigned max){
  basepicture = new Image(picture);
  sticker_max = max;
  x = new unsigned[max];
  y = new unsigned[max];
  sticker = new Image* [max];
  sticker_count = 0;
  for (unsigned i = 0; i < max; i++) {
    sticker[i] = NULL;
    x[i] = 0;
    y[i] = 0;
  }
}

void StickerSheet::copy(const StickerSheet &other){
  sticker_max = other.sticker_max;
	sticker_count = other.sticker_count;
	basepicture = new Image(*(other.basepicture));
	sticker = new Image *[sticker_max];
	x = new unsigned[sticker_max];
	y = new unsigned[sticker_max];
	for (unsigned i = 0; i < sticker_count; i++) {
		sticker[i] = new Image(*(other.sticker[i]));
		x[i] = other.x[i];
		y[i] = other.y[i];
	}
}

StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}

StickerSheet::~StickerSheet(){
  clear();
}

void StickerSheet::clear(){
  for (unsigned i = 0; i < sticker_count; i++) {
		  delete sticker[i];
      sticker[i] = NULL;
	}
	delete basepicture;
	delete[] sticker;
	delete[] x;
	delete[] y;
  }

const StickerSheet& StickerSheet::operator=(const StickerSheet & other){
  if(this!=&other){
    clear();
    copy(other);
  }
  return *this;
}



void StickerSheet::changeMaxStickers (unsigned max){
  if(max==sticker_max){
    return;
  }
  Image** tempsticker = new Image*[max];
  unsigned* tempx = new unsigned[max];
  unsigned* tempy = new unsigned[max];
  for (unsigned i = 0; i < max; i++) {
    tempsticker[i] = sticker[i];
    tempx[i] = x[i];
    tempy[i] = y[i];
  }
  if(max>sticker_max){
    for(unsigned i = sticker_max; i < max; i++){
      tempsticker[i] = NULL;
      x[i] = 0;
      y[i] = 0;
    }
  }
  sticker = tempsticker;
  x = tempx;
  y = tempy;
  sticker_max = max;
  delete[] tempsticker;
  delete[] tempx;
  delete[] tempy;
}
  
int StickerSheet::addSticker (Image &stickers, unsigned X, unsigned Y){
  for(unsigned i = 0; i<sticker_max; i++){
    if(sticker[i]==NULL){
      sticker[i] = new Image(stickers);
      x[i] = X;
      y[i] = Y;
      sticker_count++;
      return int(i);
    }
  }
  return -1;
}

bool StickerSheet::translate (unsigned index, unsigned X, unsigned Y){
  if(sticker[index] != NULL){
    x[index] = X;
    y[index] = Y;
    return true;
  }
  return false;
}

void StickerSheet::removeSticker (unsigned index){
  if(sticker[index] == NULL){
    return;
  }
  delete sticker[index];
  sticker[index] = NULL;
  x[index] = 0;
  y[index] = 0;
  sticker_count--;
}

Image * StickerSheet::getSticker (unsigned index){
  if(sticker[index] == NULL){
    return NULL;
  }
  return sticker[index];
}

Image StickerSheet::render () const{
  Image *output = new Image(*basepicture);
  for (unsigned i = 0; i < sticker_max; i++) {
    if(sticker[i] != NULL){
    unsigned width = output->width();
    unsigned height = output->height();
    std::cout<<"139"<<std::endl;
		unsigned sticker_width = sticker[i]->width();
		std::cout<<"141"<<std::endl;
		unsigned sticker_height = sticker[i]->height();
		std::cout<<"142"<<std::endl;
    if(x[i]+sticker_width > width){
      output->resize(x[i]+sticker_width, height);
    }
    if(y[i]+sticker_height > height){
      output->resize(width, y[i]+sticker_height);
    }
    }
    continue;
  }
  for (unsigned i = 0; i < sticker_max; i++) { 
    if(sticker[i] == NULL){
      continue;
    }
    Image s = *sticker[i];
    unsigned sticker_width = s.width();
		unsigned sticker_height = s.height();
    for(unsigned j = x[i]; j<x[i]+sticker_width; j++){
      for(unsigned k = y[i]; k< y[i]+sticker_height; k++){
        cs225::HSLAPixel & output_pixel = output->getPixel(j, k);
			  cs225::HSLAPixel & sticker_pixel = s.getPixel(j-x[i], k-y[i]);
        if(output_pixel.a != 0){
          output_pixel = sticker_pixel;
        }
      }
    }
  }
  return *output;
}