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
  const char* TITLE = "TIME Test";
  p.Display->getDisplaySize(sizeX, sizeY);
  
  p.RGBLed->setRGB(0,255,255,255);
  gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
  gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
  gui->UG_FontSelect(&FONT_5X8);
  gui->UG_SetForecolor(C_WHITE);
  gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
  gui->UG_PutString(1, 1, TITLE);

  tm locTime;
  locTime.tm_hour = 16;
  locTime.tm_isdst = 1;
  locTime.tm_mday = 14;
  locTime.tm_min = 45;
  locTime.tm_mon = 5;
  locTime.tm_sec = 0;
  locTime.tm_year = 122;
  
  p.PocTime->setLocalTime(&locTime);
    

  
}
int i = 322;
void loop() {
   
    UGUI* gui = p.ugui;
    const PocuterTime::pocuterTimezone* tz;
    uint16_t count;
    p.PocTime->getAllTimezones(&tz, &count);
    if (i >= count) i = 0;
    
    char buf1[16];
    char buf2[16];
    
    
    p.PocTime->setTimezone(&tz[i], false);
    tm locTime;
    p.PocTime->getLocalTime(&locTime);
    snprintf(buf1, 16, "%02d:%02d:%02d", locTime.tm_hour, locTime.tm_min, locTime.tm_sec);
    snprintf(buf2, 16, "%04d-%02d-%02d\n",locTime.tm_year + 1900,  locTime.tm_mon + 1,  locTime.tm_mday);
    
    gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
    gui->UG_PutString(1, 20, p.PocTime->getCurrentTimezone());  
    gui->UG_PutString(1, 30, buf1);  
    gui->UG_PutString(1, 40, buf2);  
    
    delay(1000);
    i++;
}

