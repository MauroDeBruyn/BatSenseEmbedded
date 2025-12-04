#include <Arduino.h>
#include "IOinterface.h"
#include "FSinterface.h"

LED ledGP2(2);  
FS_navigator sys_fs;

void setup() {
  Serial.begin(115200);
  sys_fs.FileOpen("test.txt","r");
  sys_fs.FileRead();
}

void loop() {
  ledGP2.toggle();
  delay(1000);
  Serial.println("delayed invert of led");

}
