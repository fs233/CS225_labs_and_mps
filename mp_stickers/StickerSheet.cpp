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
  Image ** tempsticker = new Image * [sticker_count];
  unsigned * tempx = new unsigned [sticker_count];
  unsigned * tempy = new unsigned [sticker_count];
  for (unsigned i = 0; i < sticker_count; i++) {
    tempsticker[i] = sticker[i];
    tempx[i] = x[i];
    tempy[i] = y[i];
  }
  delete[] sticker;
  delete[] x;
  delete[] y;
  sticker = new Image * [max];
  x = new unsigned[max];
  y = new unsigned[max];
  if (max < sticker_count) {
    for (unsigned i = 0; i < max; i++) {
      sticker[i] = tempsticker[i];
      x[i] = tempx[i];
      y[i] = tempy[i];
    }
    for (unsigned i = max; i < sticker_count; i++) {
      delete tempsticker[i];
      tempsticker[i] = NULL;
    }
    sticker_count = max;
  }else {
    for (unsigned i = 0; i < sticker_count; i++) {
      sticker[i] = tempsticker[i];
      x[i] = tempx[i];
      y[i] = tempy[i];
    }
  }
  sticker_max = max;
  delete[] tempsticker;
  delete[] tempx;
  delete[] tempy;
}

int StickerSheet::addSticker (Image &stickers, unsigned X, unsigned Y){
  if(sticker_count < sticker_max){
      sticker[sticker_count] = new Image(stickers);
      x[sticker_count] = X;
      y[sticker_count] = Y;
      sticker_count++;
      return int(sticker_count-1);
  }else{
    return -1;
  }
}

bool StickerSheet::translate (unsigned index, unsigned X, unsigned Y){
  if(index < sticker_count){
    x[index] = X;
    y[index] = Y;
    return true;
  }
  return false;
}

void StickerSheet::removeSticker (unsigned index){
  delete sticker[index];
  sticker[index] = NULL;
  x[index] = 0;
  y[index] = 0;
  sticker_count--;
  for(unsigned i = index; i < sticker_max-1; i++){
    sticker[i] = sticker[i+1];
    x[i] = x[i+1];
    y[i] = y[i+1];
  }
  sticker[sticker_max-1] = NULL;
  x[sticker_max-1] = 0;
  y[sticker_max-1] = 0;
}

Image * StickerSheet::getSticker (unsigned index){
  if(index>=sticker_count){
    return NULL;
  }
  return sticker[index];
}

Image StickerSheet::render () const{
  Image output = Image(*basepicture);
  for (unsigned i = 0; i < sticker_count; i++) {
    unsigned width = output.width();
    unsigned height = output.height();
		unsigned sticker_width = sticker[i]->width();
		unsigned sticker_height = sticker[i]->height();
    if(x[i]+sticker_width > width){
      output.resize(x[i]+sticker_width, height);
    }
    if(y[i]+sticker_height > height){
      output.resize(width, y[i]+sticker_height);
    }
    for(unsigned j = 0; j<sticker_width; j++){
      for(unsigned k = 0; k< sticker_height; k++){
        cs225::HSLAPixel & output_pixel = output.getPixel(x[i]+j, y[i]+k);
			  cs225::HSLAPixel & sticker_pixel = sticker[i]->getPixel(j, k);
        if(sticker_pixel.a != 0){
          output_pixel = sticker_pixel;
        }
      }
    }
  }
  return output;
}