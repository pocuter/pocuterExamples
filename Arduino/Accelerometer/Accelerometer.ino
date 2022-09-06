#include "Pocuter.h"

Pocuter p;

void accEventHandler(PocuterAccelerometer::ACCEVENT e, void* userData) {
  PocuterAccelerometer::State state;
  int8_t temp;

  if ( e == PocuterAccelerometer::ACC_ORIENTATION ) {
    Serial.println("Pocuter changed orientation");
    
  }
  if ( e == PocuterAccelerometer::ACC_SHAKE ) {
     Serial.println("Pocuter was Shaked");
  }
  p.Accelerometer->getState(&state);
  p.Accelerometer->getTemperature(&temp);
  Serial.printf("x: %d, y: %d, z:%d\n", state.x, state.y, state.z);
  Serial.printf("Temperature: %d\n", temp);
  
}


void setup() {
   Serial.begin(115200);
   p.begin();
   if (p.Accelerometer->isOnline() != PocuterAccelerometer::ACCERROR_OK) {
      Serial.println("Accelerometer is offline!"); 
      return;
   }
   
   
   p.Accelerometer->setScale(PocuterAccelerometer::G2);
   p.Accelerometer->registerEventHandler(accEventHandler, NULL);
    
}

void loop() {
  
    
     delay(500);
   
}
