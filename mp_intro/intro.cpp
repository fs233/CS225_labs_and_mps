#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG png;
  png.readFromFile(inputFile);
  unsigned a = png.width();
  unsigned b = png.height();
  cs225::PNG newpng(a,b);
  for (unsigned x = 0; x < a; x++) {
    for (unsigned y = 0; y < b; y++) {
      cs225::HSLAPixel pixel = png.getPixel(x, y);
      newpng.getPixel(a-x-1, b-y-1)=pixel;
    }
  }
  newpng.writeToFile(outputFile);
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
