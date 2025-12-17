#pragma once

namespace utils {
  void getMac() {
    // Used to configure peer on master
    uint8_t baseMac[6];
    esp_err_t returnVal = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
    if (returnVal == ESP_OK) {
      Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
      Serial.println("");
    } else {
      Serial.println("Failed to get MAC.");
    }
  }
}