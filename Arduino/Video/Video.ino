#include <Pocuter.h>

Pocuter p;
uint16_t sizeX;
uint16_t sizeY;
FILE * fp = NULL;
uint8_t row = 0;
uint8_t failed = false;
unsigned long startFrame;

#define FRAMES_PER_SEC 24

void setup() {
    p.begin(PocuterDisplay::BUFFER_MODE_DOUBLE_BUFFER);
    p.Display->getDisplaySize(sizeX, sizeY);
    p.ugui->UG_FontSelect(&FONT_5X8);
    p.ugui->UG_SetForecolor(C_WHITE);
    p.ugui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
    p.Display->continuousScreenUpdate(false);
    startFrame = millis();
}
void showFailed() {
    UGUI* gui = p.ugui;
    gui->UG_SetForecolor(C_WHITE);
    gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
    gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
    gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
    gui->UG_PutString(1, 1, "Failed!");
    gui->UG_SetForecolor(C_WHITE);
    gui->UG_PutString(1, 10, "Could not find file bunny.rgb. Please put the file in root of SD");
    
    
}

char buf[96*2];

void loop() {
    
    if (failed) return;
    if (p.SDCard->cardIsMounted()) {
      
        if (fp == NULL) {
          char fileName[64];
          
          snprintf(fileName, 64, "%s%s", p.SDCard->getMountPoint(), "/bunny.rgb");
          fp = fopen (fileName, "r");
          if (fp == NULL) {
            failed = true;
            showFailed();
            return;
          }
        }
        
        size_t fr = 0;
        fr = fread(buf, 1, 96*2, fp);
        if (fr == 96*2) {
           p.Display->draw16BitScanLine(0, row, 96, (uint16_t*)buf);
            
            if (++row == 64){
                int32_t waitMillis = (1000 / FRAMES_PER_SEC) - (millis() - startFrame);
                if (waitMillis > 0) vTaskDelay((configTICK_RATE_HZ / 1000) * waitMillis);
                startFrame = millis();
                p.Display->updateScreen();
                row = 0;
                
                // set ambilight LED
                uint32_t oab = 0,oar = 0,oag = 0;
                for (int i = 0; i < 96; i++) {
                  oab += (( buf[i] & 0b00011111 ) << 3) / 41;
                  oar += (( buf[i] & 0b11111000 ) << 3) / 41;
                  oag +=  (((uint8_t(buf[i]) >> 5) | (buf[i] << 3)) << 2) / 41;
                }
                p.setStatusLED(oar / 96, oag / 96, oab / 96);
    
                
            }
        } else {
            fclose(fp);
            fp = NULL;                  
        }
    } else {
       failed = true;
       showFailed();
       return;
    }
   
}
