#include <Pocuter.h>
Pocuter p;
int i = 0;

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
  p.Sleep->setSleepMode(PocuterSleep::SLEEP_MODE_LIGHT);

  // we whant to wake up through any button, a timer or shaking the device
  p.Sleep->setWakeUpModes(PocuterSleep::WAKEUP_MODE_TIMER | PocuterSleep::WAKEUP_MODE_ANY_BUTTON | PocuterSleep::WAKEUP_MODE_SHAKE); 

  // set the wakeup timer to one minute
  p.Sleep->setWakeUpTimer(60);

  // start the sleep in 15 Sec. it can be interrupted by pressing a button or shaking
  p.Sleep->setInactivitySleep(15, PocuterSleep::SLEEPTIMER_INTERRUPT_BY_BUTTON | PocuterSleep::SLEEPTIMER_INTERRUPT_BY_SHAKE);

  //register the event handler, so we can do stuff when he is goint to sleep or wakes up.
  p.Sleep->registerEventHandler(sleepEvent, NULL);

  
  p.RGBLed->setRGB(0, 255, 255, 255);
}


void loop() {
    char buf[32];
    snprintf(buf, 16, "%d", i);
    p.Display->clearScreen();
    p.ugui->UG_PutString(5, 18, "LightSleep Test");
    p.ugui->UG_PutString(36, 38, buf);
    i++;
    delay(1000);
   
}
