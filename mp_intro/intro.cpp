#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG png;
  png.readFromFile(inputFile);
  unsigned a = png.width();
  unsigned b = png.height();
  if(!(a%2==0)){
    for (unsigned y = 0; y < b/2 ; y++) {
      cs225::HSLAPixel & pixel1 = png.getPixel(a/2, y);
      cs225::HSLAPixel & pixel2 = png.getPixel(a/2, b-y-1);
      cs225::HSLAPixel pixelt = pixel1;
      pixel1 = pixel2;
      pixel2 = pixelt;
    }
  }
  for (unsigned x = 0; x < a/2; x++) {
    for (unsigned y = 0; y < b; y++) {
      cs225::HSLAPixel & pixel1 = png.getPixel(x, y);
      cs225::HSLAPixel & pixel2 = png.getPixel(a-x-1, b-y-1);
      cs225::HSLAPixel pixelt = pixel1;
      pixel1 = pixel2;
      pixel2 = pixelt;
    }
  }
  png.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = x%360;
      pixel.l=0.5;
      pixel.s = 0.5;
      pixel.a=1;
    }
  }
  return png;
}
