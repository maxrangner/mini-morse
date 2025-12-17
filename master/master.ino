#include "WiFi.h"
#include <esp_now.h>
#include <esp_wifi.h>
#include "../protocol/protocol.h"
#include "../src/utils.h"

uint8_t slaveMac[6] = {0x64, 0xe8, 0x33, 0xad, 0x23, 0x64};
MorseProtocol::Packet myData;

void addPeer(uint8_t* mac) {
  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr, mac, 6);
  peerInfo.ifidx = WIFI_IF_STA;
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.print("Could not add peer.");
    while (true) {
      Serial.print(".");
      delay(2000);
    } 
  } else Serial.println("Peer added!");
}

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
  } else Serial.println("ESP-NOW initialized!");
  addPeer(slaveMac);
}

void loop() {
  // put your main code here, to run repeatedly:

}
