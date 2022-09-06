#include <Pocuter.h>
#include <inttypes.h>
Pocuter p;


void setup() {
   Serial.begin(115200);
   p.begin();
   
}



void loop() {
  
    if (p.SDCard->cardIsMounted()) {
        std::vector<uint64_t> apps;
        
        
        Serial.printf("#################\nApps on SD: %d \n",p.OTA->getAppsCount());
        p.OTA->getApps(&apps, 5, 0);
        for (int i = 0; i < apps.size(); i++) {
            uint8_t version_major;
            uint8_t version_minor;
            uint8_t version_patch;
            char appversion[19];appversion[0] = 0;
            PocuterOTA::OTAERROR perr;

            perr =  p.OTA->getAppVersion(apps.at(i), &version_major, &version_minor, &version_patch);
            if (perr == PocuterOTA::OTAERROR_OK) {
                  uint8_t appName[32];appName[0] = 0;
                  PocuterConfig config(apps.at(i));
                  if (config.get((const uint8_t*)"APPDATA", (const uint8_t*)"Name", appName, 32)){
                      Serial.printf("APP ID     : %" PRIu64 "\n", apps.at(i));
                      Serial.printf("   Name    : %s\n", appName);
                      Serial.printf("   Version : %d.%d.%d\n", version_major, version_minor, version_patch);
                  } else {
                      Serial.printf("Getting App failed from ID  %" PRIu64 "\n", apps.at(i));
                  }
                  
            }
        }
        Serial.printf("#################\n\n\n");

        
    }
    delay(1000);
   
}
