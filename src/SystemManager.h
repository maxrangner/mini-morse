#pragma once
#include <GawiButtons.h>
#include <Arduino.h>
#include "morseDecoder.h"
#include "EspNowNetwork.h"

enum class SystemStates {
    IDLE,
    IN_ROOM,
    READY
};

class SystemManager {
    uint8_t deviceMAC[6];
    EspNowNetwork EspNetwork;
    MorseDecoder Decoder;
    Button* builtinButton;
    ButtonManager ButtonMng;
    SystemStates currentState;
    String currentMessage;
    unsigned long timeOut;
    unsigned long timeOutDuration;
public:
    SystemManager();
    void initialize();
    void run();
};
