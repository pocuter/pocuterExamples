#include <Pocuter.h>

Pocuter* pocuter;
UG_BMP bmp;

void setup() {
  pocuter = new Pocuter();
  pocuter->begin();

  if (pocuter->SDCard->cardIsMounted()) {
     FILE * fp;
     char fileName[64];
     snprintf(fileName, 64, "%s%s", pocuter->SDCard->getMountPoint(), "/hello.txt");
     fp = fopen (fileName, "w");
     if (! fp) {
      printf("Could not open %s to write!\n", fileName);
     } else {
        fprintf(fp, "Hello World!\n");
        fclose(fp); 
        printf("File written!\n");
     }
     
  } else {
    printf("SDCard not Mounted!\n");
  }
}
void loop() {
   delay(200);
   
}
