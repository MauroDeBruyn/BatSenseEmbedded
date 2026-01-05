#include <Arduino.h>
#include "IOinterface.h"
#include "FSinterface.h"
#include "network.h"

#define SSID "BATSensEmbedded0"
#define PASSWORD "sY!52@51:"

LED ledGP2(2);  

HTTP_server* serverAP;

extern SDinterface* instance;
static unsigned long lastScan = 0;
unsigned long now{0};
void setup() {
  Serial.begin(115200);
  serverAP = new HTTP_server(SSID, PASSWORD);
  if(!instance)
    return;

  now = millis();
  if(instance->CS){
    instance->CS = false;
    instance->_spiBlockoutTime = millis() + SPI_BLOCKOUT_PERIOD;

  } else {
    serverAP->http_main_page = instance->sdFiles_HTML_Format();
  }
}

void loop() {
    now = millis();
    if(instance->CS){
      instance->CS = false;
      instance->_spiBlockoutTime = millis() + SPI_BLOCKOUT_PERIOD;
    } else{
      // problem logic is split over 2 files... why check if CS in this file but not other file?
      //make it more straight to the point 1 class does thi other does this no logic correction inside main...
      if (now - lastScan >= 61000) {  
        lastScan = now;
        ledGP2.toggle();
        serverAP->http_main_page = instance->sdFiles_HTML_Format();
      }
    } 
}


