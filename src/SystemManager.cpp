#include "SystemManager.h"
#include "pins.h"

SystemManager::SystemManager() {
    currentState = SystemStates::IDLE;
    builtinButton = ButtonMng.addButton(
        builtinButtonPin, // input pin
        true // pull up
        );
    currentMessage = "";
    timeOut = 0;
    timeOutDuration = 4000;
}

void SystemManager::initialize() {
    EspNetwork.initializeEspNow();
}

void SystemManager::run() {
    ButtonMng.updateAll();
    Decoder.update(builtinButton);
    if (Decoder.hasNewData()) {
        currentMessage += Decoder.getCharacter();
        EspNetwork.broadcast(currentMessage);
        Serial.println(currentMessage);
    }
}