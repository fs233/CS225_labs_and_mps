#include <iostream>
#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet (const Image &picture, unsigned max){
 
}
StickerSheet::~StickerSheet (){
  return 0;
}
StickerSheet::StickerSheet (const StickerSheet &other){
  return 0;
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
  return 0;
}
void StickerSheet::changeMaxStickers (unsigned max){
  return 0;
}
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  return 1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  return ture;
}
void StickerSheet::removeSticker (unsigned index){
  return 0;
}
Image * StickerSheet::getSticker (unsigned index){
  Image* a = new image();
  return a;
}
Image StickerSheet::render () const{
  Image* b = new image();
  return &b;
}