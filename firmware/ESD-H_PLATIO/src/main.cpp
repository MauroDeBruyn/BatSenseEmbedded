#include <Arduino.h>
#include "IOinterface.h"
#include "FSinterface.h"
#include "network.h"

#define SSID "BATSensEmbedded0"
#define PASSWORD "sY!52@51:"

LED ledGP2(2);  

HTTP_server* serverAP;

extern SDinterface* instance;

void setup() {
  Serial.begin(115200);
  serverAP = new HTTP_server(SSID, PASSWORD);
}

void loop() {
    static unsigned long lastScan = 0;
    unsigned long now = millis();

    if (now - lastScan >= 60000) {   // 20 seconds 
        lastScan = now;
        ledGP2.toggle();
        //serverAP->http_main_page = instance->sdFiles_HTML_Format();
    }
}


