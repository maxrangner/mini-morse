#include <Arduino.h>

int num = 0;

void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.println("BOOT!");
}

void loop() {
  Serial.println(num++);
  delay(500);
}
