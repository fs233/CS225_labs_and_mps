#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image pic1;
  pic1.readFromFile("pic1.png");
  Image i;    
  i.readFromFile("i.png");
  StickerSheet sheet(pic1, 5);
  sheet.addSticker(i, 20, 100);
  sheet.addSticker(i, 70, 100);
  sheet.addSticker(i, 120, 100);
  Image output = sheet.render();
  output.writeToFile("myImage.png");
  
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
