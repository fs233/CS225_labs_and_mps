
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;      png.readFromFile("tests/i.png");
  FloodFilledImage image(png);
  BFS bfs(png, Point(60,60), 0.1);
  MyColorPicker color1(216);
  DFS dfs(png, Point(40, 40), 0.05);
  MyColorPicker color2(45);
  image.addFloodFill( bfs, color1 );
  image.addFloodFill( dfs, color2 );
  Animation animation = image.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");


  return 0;
}
