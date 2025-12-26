#pragma once
#include <GawiButtons.h>
#include <Arduino.h>
#include "morseDecoder.h"

enum class SystemStates {
    IDLE,
    IN_ROOM,
    READY
};

class SystemManager {
    uint8_t deviceId;
    MorseDecoder Decoder;
    Button* builtinButton;
    ButtonManager ButtonMng;
    SystemStates currentState;
    String currentMessage;
    unsigned long timeOut;
    unsigned long timeOutDuration;
public:
    SystemManager();
    void run();
};







/*
void MorseDecoder::addToInputString(char newChar, bool state) {
    inputString[inputStringLen++] = newChar;
    inputString[inputStringLen] = '\0';
    isWaitingForNextSymbol = state;
}

String MorseDecoder::decodeMorseString() {
    String decodedOutput;
    char charBuffer[20];
    uint8_t charBufferLen = 0;

    for (uint8_t i = 0; i < inputStringLen; i++) {
        if (inputString[i] != ' ') {
            charBuffer[charBufferLen++] = inputString[i];
        } else {
            charBuffer[charBufferLen] = '\0';
            decodedOutput += decodeMorseChar(charBuffer);
            charBufferLen = 0;
        }
    }
    if (charBufferLen > 0) {
        charBuffer[charBufferLen] = '\0';
        decodedOutput += decodeMorseChar(charBuffer);
    }
    return decodedOutput;
}

void MorseDecoder::printInputString() {
    Serial.print(inputString); Serial.print("    ");
    Serial.println(decodeMorseString());
}
*/