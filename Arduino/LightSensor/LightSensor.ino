#include <Pocuter.h>

uint16_t sizeX;
uint16_t sizeY;
Pocuter p;

void lEventHandler(PocuterLightSensor::LIGHTEVENT e, void*) {
     switch(e) {
        case PocuterLightSensor::LIGHT_ABOVE_LIMIT: 
            p.ugui->UG_FillFrame(0, 20, sizeX - 1, 29, C_BLACK);
            p.ugui->UG_PutString(1, 20, "Light is ON");
            break;
        case PocuterLightSensor::LIGHT_UNDER_LIMIT:
            p.ugui->UG_FillFrame(0, 20, sizeX - 1, 29, C_BLACK);
            p.ugui->UG_PutString(1, 20, "Light is OFF");
            break;
        default:
            break;
    }
    p.ugui->UG_FillFrame(0, 30, sizeX - 1, 39, C_BLACK);
    char buf[14];
    snprintf(buf, 14, "Value: %d", p.LightSensor->getValue());
    p.ugui->UG_PutString(1, 30, buf);
    
}

void setup() {
  
    p.begin();
    UGUI* gui = p.ugui;
    const char* TITLE = "Light sensor";

    p.Display->getDisplaySize(sizeX, sizeY);

    
    gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
    gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
    gui->UG_FontSelect(&FONT_5X8);
    gui->UG_SetForecolor(C_WHITE);
    gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
    gui->UG_PutString(1, 1, TITLE);
       
    p.LightSensor->registerEventHandler(lEventHandler, 30, 5, NULL);
    
}


void loop() {
   delay(200);
   
}
