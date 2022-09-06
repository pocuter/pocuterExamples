#include "Pocuter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
Pocuter p;
uint16_t sizeX;
uint16_t sizeY;

#define WIFI_SSID       "WIFI-SSID"
#define WIFI_PASSWORD   "WIFI-PASSWORD"

  
void wifiEventHandler(PocuterWIFI::WIFIEVENT e, void* data, void* userData) {
    Pocuter* p = (Pocuter*)userData;
    
    if (e == PocuterWIFI::WIFIEVENT_GOT_IP) {
        PocuterWIFI::ipInfo* info = (PocuterWIFI::ipInfo*)data;
        
        PocuterWIFI::wifiCredentials cred;
        p->WIFI->getCredentials(&cred);
        
        p->ugui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
        char buf[100];
        snprintf(buf, 100, "CONNECTED to\n%s", cred.ssid);
        p->ugui->UG_PutString(1, 20, buf);
        p->RGBLed->setRGB(0,0,255,0);
        snprintf(buf, 100, "%s", inet_ntoa(info->ipV4));
        p->ugui->UG_PutString(1, 50, buf);
    }
    if (e == PocuterWIFI::WIFIEVENT_DISCONNECTED) {
       p->ugui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
       p->ugui->UG_PutString(1, 20, "DISCONNECTED");
    }
}


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
  gui->UG_PutString(1, 20, "CONNECTING...");
    
    
  p.WIFI->registerEventHandler(wifiEventHandler, &p);
  PocuterWIFI::wifiCredentials c = {WIFI_SSID , WIFI_PASSWORD};
  PocuterWIFI::WIFIERROR err = p.WIFI->connect(&c);
  if (err != PocuterWIFI::WIFIERROR_OK) {
      p.RGBLed->setRGB(0,255,0,0);
  } else {
      p.RGBLed->setRGB(0,255,255,0);
  }
 
    
    
}

void loop() {
     delay(10000);
    
}
