#pragma once
#include <Arduino.h>
#include "WiFi.h"
#include <esp_now.h>
#include <esp_wifi.h>
#include "../protocol/protocol.h"
#include "../src/utils.h"

constexpr uint8_t maxPeers = 10;
constexpr uint8_t wifiChannel = 1;

class EspNowNetwork {
    const uint8_t broadcastAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t peers[maxPeers][6];
    uint8_t peersNum;
    uint8_t payload;
    void addPeer(const uint8_t* mac_addr);
    public:
    EspNowNetwork();
    void initializeEspNow();
    void broadcast(const String &message);
    void handleSend(const uint8_t *mac_addr, esp_now_send_status_t status);
    void handleReceive(const uint8_t* mac_addr, const uint8_t* data, int data_len);
};

void sentCallback(const uint8_t *mac_addr, esp_now_send_status_t status);
void receiveCallback(const uint8_t *mac_addr, const uint8_t *data, int data_len);