#include <Pocuter.h>
#define CS (const uint8_t*)

Pocuter* pocuter;
UG_BMP bmp;

void setup() {
  pocuter = new Pocuter();
  pocuter->begin();

  PocuterConfig config(CS"testApp");
  config.set(CS"Test1", CS"testValue", CS"Hello World3!");
  config.set(CS"Test1", CS"testValue2", CS"Hello World4!");
  config.set(CS"Test1", CS"testNumber", 12345);
  config.setEncrypted(CS"Test1", CS"testEncrypted", CS"Hello Encrypted3!");
  
  char binaryData[16];
  for (int i = 0; i < 16; i++) binaryData[i] = i;
  config.setBinary(CS"Test1", CS"testBinary", binaryData, 16);
  
  
  uint8_t result[128];
  size_t rLength = 128;
  if (config.get(CS"Test1", CS"testValue", result, rLength)) {
      printf("testValue: %s\n", result);  
  }
  
  
  if (config.get(CS"Test1", CS"testValue2", result, rLength)) {
    printf("testValue2: %s\n", result);  
  }
  
  
  if (config.getEncrypted(CS"Test1", CS"testEncrypted", result, rLength)) {
    printf("testEncrypted: %s\n", result);
  }

  printf("testNumber: %d\n", config.get(CS"Test1", CS"testNumber"));
  
  config.del(CS"Test1", CS"testNumber");
  
  if (config.get(CS"Test1", CS"testNumber")) {
    printf("Should not be there!\n");
  } else {
    printf("testNumber Deleted!\n");
  }

  
  for (int i = 0; i < 16; i++) binaryData[i] = 0;
  config.getBinary(CS"Test1", CS"testBinary", binaryData, 16);
  printf("binaryData: ");
  for (int i = 0; i < 16; i++) printf("%02x ", binaryData[i]);
  printf("\n");
 
}
void loop() {
   delay(200);
   
}
