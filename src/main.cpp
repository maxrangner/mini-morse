#include <Arduino.h>
#include "SystemManager.h"
#include "MorseDecoder.h"

MorseDecoder Decoder;
SystemManager SysManager(&Decoder);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("BOOT!");
}

void loop() {
  SysManager.run();
}
