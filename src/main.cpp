#include <Arduino.h>
#include "morseDecoder.h"

MorseDecoder decoder;
int num = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("BOOT!");
}

void loop() {
  decoder.update();
  // Serial.println(num++);
}
