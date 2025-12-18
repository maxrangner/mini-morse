#include "WiFi.h"
#include <esp_now.h>
#include <esp_wifi.h>
#include <GawiButtons.h>
#include "../protocol/protocol.h"
#include "../src/utils.h"

constexpr int buttonPin = 9;

void onPacketSend(const esp_now_send_info_t *tx_info, esp_now_send_status_t status);
void updatePacket();
uint8_t slaveMac[6] = {0x64, 0xe8, 0x33, 0xad, 0x23, 0x64};
MorseProtocol::Packet outgoingPacket;
ButtonManager buttonManager;
Button* button;

uint8_t payload = 0;

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
  esp_now_register_send_cb(onPacketSend);
  addPeer(slaveMac);
  button = buttonManager.addButton(buttonPin, true);
}

void loop() {
  buttonManager.updateAll();
  if (button->pressed()) {
    updatePacket();
    esp_err_t result = esp_now_send(slaveMac, (uint8_t *) &outgoingPacket, sizeof(MorseProtocol::Packet));
    if (result == ESP_OK) {
      Serial.println("Packet sent!");
    } else Serial.println("Error sending packet.");
  }
}

void onPacketSend(const esp_now_send_info_t *tx_info, esp_now_send_status_t status) {
  if (status == ESP_OK) {
    Serial.println("Data sent: ");
    Serial.print("Protocol Version: "); Serial.println(outgoingPacket.protocolVersion);
    Serial.print("Device ID: "); Serial.println(outgoingPacket.deviceId);
    Serial.print("Packet Type: "); Serial.println(outgoingPacket.packetType);
    Serial.print("Payload: "); Serial.println(outgoingPacket.payload);
  } else {
    Serial.println("Packet not delivered.");
  }
}

void updatePacket() {
  outgoingPacket.protocolVersion = 1;
  outgoingPacket.deviceId = 1;
  outgoingPacket.packetType = MorseProtocol::PacketType::STATUS;
  outgoingPacket.payload = payload++;
}