#pragma once
#include <Arduino.h>
#include "morseDecoder.h"

constexpr uint8_t timeOutDuration = 10;

enum class SystemStates {
    IDLE,
    IN_ROOM,
    READY
};

class SystemManager {
    SystemStates currentState;
    String currentMessage;
    unsigned long timeOut;
    MorseDecoder* connectedDecoder;
public:
    SystemManager(MorseDecoder* decoder);
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