#pragma once
#include <Arduino.h>
#include "WiFi.h"
#include <esp_now.h>
#include <esp_wifi.h>
#include "../protocol/protocol.h"
#include "../src/utils.h"

constexpr uint8_t maxPeers = 10;

class Network {
    uint8_t peers[maxPeers][6];
    uint8_t peersNum;
    uint8_t payload;
    void initializeEspNow();
    void handleSend(const uint8_t *mac_addr, esp_now_send_status_t status);
    void handleReceive(const uint8_t* mac, const uint8_t* data, int len);
    void broadcast();
public:
    Network();
    void send();
};

void sentCallback(const uint8_t *mac_addr, esp_now_send_status_t status);
void receiveCallback(const uint8_t *mac_addr, const uint8_t *data, int data_len);