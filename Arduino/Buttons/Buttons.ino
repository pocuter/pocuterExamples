#include <Pocuter.h>
Pocuter* pocuter;

void buttonHandler(PocuterButtons::PBUTTONS b, void* d) {
    printf("Button 1: ");
    if (b & PocuterButtons::BUTTON_1) printf("pressed"); else printf("released");
    printf("\n");
    printf("Button 2: ");
    if (b & PocuterButtons::BUTTON_2) printf("pressed"); else printf("released");
    printf("\n");
    printf("Button 3: ");
    if (b & PocuterButtons::BUTTON_3) printf("pressed"); else printf("released");
    printf("\n");
}


void setup() {
  pocuter = new Pocuter();
  pocuter->begin();
  
  PocuterButtons* b = pocuter->Buttons;
  b->registerEventHandler(&buttonHandler, NULL);
    
}


void loop() {
    delay(100);
    
   
}
