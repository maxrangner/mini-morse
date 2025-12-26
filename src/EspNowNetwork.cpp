#include "EspNowNetwork.h"

static Network* globalNetwork = nullptr;

Network::Network() : peersNum(0) {
    globalNetwork = this;
    this->initializeEspNow();
    payload = 0;
}

void Network::initializeEspNow() {
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.print("ESP-NOW failed to initialize.");
        while (true) {
            Serial.print(".");
            delay(2000);
        }
    } else {
        Serial.println("ESP-NOW initialized!");
        esp_now_register_send_cb(sentCallback);
        esp_now_register_recv_cb(receiveCallback);
    }
}

void Network::handleSend(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void Network::handleReceive(const uint8_t* mac, const uint8_t* data, int len) {
}

void Network::broadcast() { 
}

void sentCallback(const uint8_t *mac_addr, esp_now_send_status_t status) {
    // if (globalNetwork != nullptr) {
    //     globalNetwork->handleSend();
    // }
}

void receiveCallback(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    // if (globalNetwork != nullptr) {
    //     globalNetwork->handleReceive();
    // }
}