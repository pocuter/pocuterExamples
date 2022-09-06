#include <Pocuter.h>
Pocuter* pocuter;


// Let's Encrypt root certificate
const char* rootCA = "------BEGIN CERTIFICATE-----\n\
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n\
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n\
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n\
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n\
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n\
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n\
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n\
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n\
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n\
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n\
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n\
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n\
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n\
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n\
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n\
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n\
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n\
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n\
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n\
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n\
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n\
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n\
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n\
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n\
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n\
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n\
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n\
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n\
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n\
-----END CERTIFICATE-----\n\n";

bool gotIp = false;
void wifiHandler(PocuterWIFI::WIFIEVENT e, void* data, void* userData) {
    if (e == PocuterWIFI::WIFIEVENT_GOT_IP) gotIp = true;
}

void setup() {
  pocuter = new Pocuter();
  pocuter->begin();
 
  UGUI* gui = pocuter->ugui;
    
  uint16_t sizeX;
  uint16_t sizeY;
  pocuter->Display->getDisplaySize(sizeX, sizeY);
  
  

  gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
  gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_BLACK);
  gui->UG_FontSelect(&FONT_5X8);
  gui->UG_SetForecolor(C_WHITE);
  gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
  gui->UG_PutString(1, 1, "Connecting...");
  pocuter->WIFI->registerEventHandler(wifiHandler, NULL);

  if (! pocuter->SDCard->cardIsMounted()){
    gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_RED);
    gui->UG_SetBackcolor(C_RED);
    gui->UG_PutString(1, 1, "no SDCard!");
    return;
  }

  
  pocuter->WIFI->connect();
  int timeOut = 10;
  do {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  } while (! gotIp && --timeOut);
  
  if (! gotIp) {
    gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_RED);
    gui->UG_SetBackcolor(C_RED);
    gui->UG_PutString(1, 1, "WIFI failed");
    return;
  }
  gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
  gui->UG_PutString(1, 1, "Downloading...");

  
  uint8_t percent = 0;
  PocuterHTTP::HTTPERROR err;
    
  gui->UG_FillFrame(8, 18, 88, 32, C_WHITE);
  gui->UG_FillFrame(9, 19, 87, 31, C_BLACK);
    
  do {
      err = pocuter->HTTP->downloadFile((const uint8_t*)"https://letsencrypt.org/documents/LE-SA-v1.2-November-15-2017.pdf", (const uint8_t*)"/sd/LE-SA-v1.2-November-15-2017.pdf", true, &percent, (const uint8_t*)rootCA);
      gui->UG_FillFrame(10, 20, 10 + (percent * 76 / 100), 30, C_WHITE);
  } while( err == PocuterHTTP::HTTPERROR_MORE_STEPS);
  gui->UG_FillFrame(10, 20, 10 + 76, 30, C_WHITE);
  if (err != PocuterHTTP::HTTPERROR_OK) {
      gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_RED);
      gui->UG_SetBackcolor(C_RED);
      gui->UG_PutString(1,1,"Download failed");
  } else {
      gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
      gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
      gui->UG_PutString(1,1,"Download OK!");
  }
  
    
}


void loop() {
   delay(200);
   
}
