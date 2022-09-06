#include <Pocuter.h>
Pocuter* pocuter;
void setup() {
  pocuter = new Pocuter();
  pocuter->begin();
 
  UGUI* gui = pocuter->ugui;
  uint16_t sizeX;
  uint16_t sizeY;
  pocuter->Display->getDisplaySize(sizeX, sizeY);
    
  const char* TITLE = "Pocuter 0.1";

  gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
  gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_DARK_BLUE);
  gui->UG_FontSelect(&FONT_5X8);
  gui->UG_SetForecolor(C_WHITE);
  gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
  gui->UG_PutString(1, 1, TITLE);

 
}


void loop() {
    
   delay(100);
   
}
