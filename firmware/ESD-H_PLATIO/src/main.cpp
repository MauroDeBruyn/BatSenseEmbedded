#include <Arduino.h>
#include "IOinterface.h"
#include "FSinterface.h"
#include "network.h"

#define SSID "BATSensEmbedded0"
#define PASSWORD "sY!52@51:"

LED ledGP2(2);  

HTTP_server* serverAP;

void setup() {
  //Serial.begin(115200);
  serverAP = new HTTP_server(SSID, PASSWORD);
  SDinterface sd;
  sd.read_file("data_test.txt");
}

void loop() {
  ledGP2.toggle();
  delay(1000);
}
