#include "SystemManager.h"
#include "pins.h"

SystemManager::SystemManager() {
    uint8_t deviceId = 01;
    SystemStates currentState = SystemStates::IDLE;
    builtinButton = ButtonMng.addButton(builtinButtonPin, true);
    String currentMessage = "";
    unsigned long timeOut = 0;
    const unsigned long timeOutDuration = 4000;
}

void SystemManager::run() {
    Decoder.update(builtinButton);
    if (Decoder.hasNewData()) {
        Serial.println(Decoder.getCharacter());
    }
}