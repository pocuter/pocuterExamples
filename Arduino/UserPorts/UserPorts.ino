#include <Pocuter.h>
Pocuter p;
uint16_t sizeX;
uint16_t sizeY;



void portEvent(PocuterPorts::PORT_NUMBER n, bool portValue, void* m){
   
   p.Display->clearWindow(0, n*10, sizeX, 10);
   if (n == PocuterPorts::PORT_1 && portValue) p.ugui->UG_PutString(10, 10, "Port 1: ON");
   if (n == PocuterPorts::PORT_1 && !portValue) p.ugui->UG_PutString(10, 10, "Port 1: OFF");
   if (n == PocuterPorts::PORT_2 && portValue) p.ugui->UG_PutString(10, 20, "Port 2: ON");
   if (n == PocuterPorts::PORT_2 && !portValue) p.ugui->UG_PutString(10, 20, "Port 2: OFF");
   if (n == PocuterPorts::PORT_3 && portValue) p.ugui->UG_PutString(10, 30, "Port 3: ON");
   if (n == PocuterPorts::PORT_3 && !portValue) p.ugui->UG_PutString(10, 30, "Port 3: OFF");
   if (n == PocuterPorts::PORT_4 && portValue) p.ugui->UG_PutString(10, 40, "Port 4: ON");
   if (n == PocuterPorts::PORT_4 && !portValue) p.ugui->UG_PutString(10, 40, "Port 4: OFF");
   if (n == PocuterPorts::PORT_5 && portValue) p.ugui->UG_PutString(10, 50, "Port 5: ON");
   if (n == PocuterPorts::PORT_5 && !portValue) p.ugui->UG_PutString(10, 50, "Port 5: OFF");
   p.Display->updateScreen();
}



void setup() {
  
    p.begin(PocuterDisplay::BUFFER_MODE_DOUBLE_BUFFER);
    p.Display->getDisplaySize(sizeX, sizeY);
    p.Display->continuousScreenUpdate(false);
    
    UGUI* gui = p.ugui;
    gui->UG_FontSelect(&FONT_5X8);
    gui->UG_SetForecolor(C_WHITE);
    gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
    p.Display->clearScreen();
   

    p.Ports->initPort(PocuterPorts::PORT_0, PocuterPorts::PORT_DIRECTION_IN, PocuterPorts::PORT_MODE_ADC, PocuterPorts::PORT_PULLUP_OFF);
    p.Ports->initPort(PocuterPorts::PORT_1, PocuterPorts::PORT_DIRECTION_IN, PocuterPorts::PORT_MODE_BINARY, PocuterPorts::PORT_PULLUP_OFF);
    p.Ports->initPort(PocuterPorts::PORT_2, PocuterPorts::PORT_DIRECTION_IN, PocuterPorts::PORT_MODE_BINARY, PocuterPorts::PORT_PULLUP_OFF);
    p.Ports->initPort(PocuterPorts::PORT_3, PocuterPorts::PORT_DIRECTION_IN, PocuterPorts::PORT_MODE_BINARY, PocuterPorts::PORT_PULLUP_OFF);
    p.Ports->initPort(PocuterPorts::PORT_4, PocuterPorts::PORT_DIRECTION_IN, PocuterPorts::PORT_MODE_BINARY, PocuterPorts::PORT_PULLUP_OFF);
    p.Ports->initPort(PocuterPorts::PORT_5, PocuterPorts::PORT_DIRECTION_IN, PocuterPorts::PORT_MODE_BINARY, PocuterPorts::PORT_PULLUP_ON);
    
    p.Ports->registerEventHandler(PocuterPorts::PORT_1, portEvent, NULL);
    p.Ports->registerEventHandler(PocuterPorts::PORT_2, portEvent, NULL);
    p.Ports->registerEventHandler(PocuterPorts::PORT_3, portEvent, NULL);
    p.Ports->registerEventHandler(PocuterPorts::PORT_4, portEvent, NULL);
    p.Ports->registerEventHandler(PocuterPorts::PORT_5, portEvent, NULL);


    // call the event handler for each binary port only to draw the screen
    bool value;
    for (int i = PocuterPorts::PORT_1; i <= PocuterPorts::PORT_5; i++) {
        p.Ports->getValue((PocuterPorts::PORT_NUMBER)i, &value);
        portEvent((PocuterPorts::PORT_NUMBER)i, value, NULL);
    }
   
    
    
}

void loop() {
  char buf[16];
  uint16_t adcValue;
  p.Ports->getValue(PocuterPorts::PORT_0, &adcValue);
  snprintf(buf, 16, "ADC: %d", adcValue);
   p.Display->clearWindow(0, 0, sizeX, 10);
   p.ugui->UG_PutString(10, 0, buf);
   p.Display->updateScreen();
   delay(350);
}
