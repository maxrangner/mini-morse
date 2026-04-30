#include "WiFi.h"
#include <esp_now.h>
#include <esp_wifi.h>
#include "../protocol/protocol.h"
#include "../src/utils.h"

constexpr int ledPin = 8;

void onPacketReceive(const esp_now_recv_info *info, const uint8_t *incomingPacket, int len);
MorseProtocol::Packet receivePacket;

void setup() {
  Serial.begin(115200);
  delay(1500);
  Serial.println("BOOT!");
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.print("ESP-NOW failed to initialize.");
    while (true) {
      Serial.print(".");
      delay(2000);
    }
  }
  esp_now_register_recv_cb(onPacketReceive);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void onPacketReceive(const esp_now_recv_info *info, const uint8_t *incomingPacket, int len) {
  if (len == sizeof(MorseProtocol::Packet)) {
    memcpy(&receivePacket, incomingPacket, sizeof(MorseProtocol::Packet));
    Serial.print("Data received: "); Serial.println(len);
    Serial.print("Protocol Version: "); Serial.println(receivePacket.protocolVersion);
    Serial.print("Device ID: "); Serial.println(receivePacket.deviceId);
    Serial.print("Packet Type: "); Serial.println(receivePacket.packetType);
    Serial.print("Payload: "); Serial.println(receivePacket.payload);
    if (receivePacket.payload % 2 == 0) {
      digitalWrite(ledPin, HIGH);
    } else digitalWrite(ledPin, LOW);
  } else {
    Serial.println("Error with packet.");
  }
}