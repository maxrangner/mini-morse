#include "EspNowNetwork.h"

static EspNowNetwork* globalNetwork = nullptr;

EspNowNetwork::EspNowNetwork() : peersNum(0) {
    globalNetwork = this;
    payload = 0;
}

void EspNowNetwork::initializeEspNow() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    esp_wifi_set_channel(wifiChannel, WIFI_SECOND_CHAN_NONE);
    if (esp_now_init() != ESP_OK) {
        Serial.print("ESP-NOW failed to initialize.");
        while (true) {
            Serial.print(".");
            delay(2000);
        }
    } else {
        Serial.println("ESP-NOW initialized!");
        addPeer(broadcastAddress);
        esp_now_register_send_cb(sentCallback);
        esp_now_register_recv_cb(receiveCallback);
    }
}

void EspNowNetwork::addPeer(const uint8_t* mac_addr) {
    esp_now_peer_info_t peerInfo = {};
    memcpy(&peerInfo.peer_addr, mac_addr, 6);
    if (!esp_now_is_peer_exist(mac_addr)) esp_now_add_peer(&peerInfo);
}

void EspNowNetwork::broadcast(const String &message) { 
    esp_err_t result = esp_now_send(broadcastAddress, (const uint8_t *)message.c_str(), message.length());
}

void EspNowNetwork::handleSend(
    const uint8_t *mac_addr, // MAC Adress of recepient
    esp_now_send_status_t status // status of packet
) {
}

void EspNowNetwork::handleReceive(
    const uint8_t* mac_addr, // MAC Adress of sender
    const uint8_t* data, // Packet data
    int data_len // Lenght of data
) {
    char buffer[250];
    strncpy(buffer, (const char *)data, 250);
    buffer[data_len] = 0;
    Serial.println(buffer);
}

// Global callback wrappers
void sentCallback(
    const uint8_t *mac_addr, // MAC Adress of sender
    esp_now_send_status_t status // status of packet
) {
    if (globalNetwork != nullptr) {
        globalNetwork->handleSend(mac_addr, status);
    }
}

void receiveCallback(
    const uint8_t *mac_addr, // MAC Adress of sender
    const uint8_t *data, // Packet data
    int data_len // Lenght of data
) {
    if (globalNetwork != nullptr) {
        globalNetwork->handleReceive(mac_addr, data, data_len);
    }
}