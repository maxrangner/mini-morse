#include <Arduino.h>
#include "SystemManager.h"

SystemManager SysManager;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("BOOT!");
}

void loop() {
  SysManager.run();
}
