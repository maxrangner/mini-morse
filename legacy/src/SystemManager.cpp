#include "SystemManager.h"

SystemManager::SystemManager(MorseDecoder* decoder) : connectedDecoder(decoder) {

}

void SystemManager::run() {
    connectedDecoder->update();
    if (connectedDecoder->hasNewData()) {
        Serial.println(connectedDecoder->getCharacter());
    }
}