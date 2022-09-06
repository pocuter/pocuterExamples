#include <Pocuter.h>
Pocuter* pocuter;
void setup() {
  pocuter = new Pocuter();
  pocuter->begin();
 
}


uint8_t ledR = 1;
uint8_t ledG = 0;
uint8_t ledB = 0;
int8_t ledRA = 1;
int8_t ledGA = 1;
int8_t ledBA = 1;
uint8_t led = 0;
void loop() {
    
    pocuter->setStatusLED(ledR,ledG,ledB);
    
    if (led == 0) ledR+=ledRA; else ledR = 0;
    if (led == 1) ledG+=ledGA; else ledG = 0;
    if (led == 2) ledB+=ledBA; else ledB = 0;

    if (ledB == 8) ledBA = -1;
    if (ledB == 0 && led == 2) {ledBA = 1; led = 0; return;}
    
    if (ledG == 8) ledGA = -1;
    if (ledG == 0 && led == 1) {ledGA = 1; led = 2;}
    
    if (ledR == 8) ledRA = -1;
    if (ledR == 0 && led == 0) {ledRA = 1; led = 1;}

    delay(100);
   
}
