
#include "Pocuter.h"
#include <string.h>
#include <stdlib.h>


Pocuter p;
uint16_t sizeX;
uint16_t sizeY;
#define COUNT_ACCESS_POINTS 6

void setup() {
  p.begin();
  UGUI* gui = p.ugui;
  const char* TITLE = "WIFI Test";
  p.Display->getDisplaySize(sizeX, sizeY);
  
  p.RGBLed->setRGB(0,255,255,255);
  gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
  gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
  gui->UG_FontSelect(&FONT_5X8);
  gui->UG_SetForecolor(C_WHITE);
  gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
  gui->UG_PutString(1, 1, TITLE);
  gui->UG_PutString(1, 20, "Scanning...");
  PocuterWIFI::apInfo accessPoints[COUNT_ACCESS_POINTS];
  uint16_t apSize = COUNT_ACCESS_POINTS;
  uint16_t totalAPs = 0;
  
  PocuterWIFI::WIFIERROR err = p.WIFI->scanAPs(accessPoints, &apSize, &totalAPs);

  if (err != PocuterWIFI::WIFIERROR_OK) {
      p.RGBLed->setRGB(0,255,0,0);
  } else {
      p.RGBLed->setRGB(0,255,255,0);
  }

  gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
  char buf[32];
  for (int i = 0; i < apSize; i++) {
    snprintf(buf, 32, "%s\n", accessPoints[i].ssid);
    gui->UG_PutString(1, 12 + ( i * 8 ), buf);
  }
    
    
}
void loop() {
     delay(10000);
    
}
