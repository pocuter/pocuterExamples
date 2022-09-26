#include <Pocuter.h>
Pocuter p;

// This variable is reset when we wake up from deep sleep
int i = 0;

// This variable retains its validity even after sleep 
DEEP_SLEEP_MEMORY int d;



bool sleepEvent(PocuterSleep::SLEEP_EVENT e, void*) {
    if (e == PocuterSleep::SLEEP_EVENT_ENTER_SLEEP) {
        // we are giong to sleep. Switch the light off.
        p.RGBLed->setRGB(0, 0, 0, 0);
        
        // if we return false here, entering sleep will be interrupted
        return true;
    } else {
        // we are waking up. Switch the lights on.
        p.RGBLed->setRGB(0, 255, 255, 255);

        // If we return here false, he will immediately fall asleep again.
        return true;
    }
    
}

void setup() {
  p.begin(PocuterDisplay::BUFFER_MODE_DOUBLE_BUFFER);
  
  UGUI* gui = p.ugui;
  gui->UG_FontSelect(&FONT_5X8);
  gui->UG_SetForecolor(C_WHITE);
  gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
  // set the light sleep mode
  p.Sleep->setSleepMode(PocuterSleep::SLEEP_MODE_DEEP);

  // uf you want to use Userports, please configure them first
  p.Ports->initPort(PocuterPorts::PORT_5, PocuterPorts::PORT_DIRECTION_IN, PocuterPorts::PORT_MODE_BINARY, PocuterPorts::PORT_PULLUP_ON);
    
  // we whant to wake up through a timer
  p.Sleep->setWakeUpModes(PocuterSleep::WAKEUP_MODE_TIMER | PocuterSleep::WAKEUP_MODE_USERPORT_5_LOW); 

  // set the wakeup timer to 20 sec
  p.Sleep->setWakeUpTimer(20);

  // start the sleep in 15 Sec. it can be interrupted by pressing a button or shaking
  p.Sleep->setInactivitySleep(15, PocuterSleep::SLEEPTIMER_INTERRUPT_BY_BUTTON | PocuterSleep::SLEEPTIMER_INTERRUPT_BY_SHAKE);

  //register the event handler, so we can do stuff when he is goint to sleep or wakes up.
  p.Sleep->registerEventHandler(sleepEvent, NULL);

  
  p.RGBLed->setRGB(0, 255, 255, 255);
}


void loop() {
    char buf[32];
    
    snprintf(buf, 16, "Saved Memory: %d", d);
    p.Display->clearScreen();
    p.ugui->UG_PutString(5, 18, "Deep Sleep Test");
    snprintf(buf, 16, "normal Mem: %d", i);
    
  
    p.ugui->UG_PutString(0, 30, buf);
    snprintf(buf, 16, "RTC    Mem: %d", d);
    p.ugui->UG_PutString(0, 42, buf);
    i++;
    d++;
    delay(1000);
   
}
