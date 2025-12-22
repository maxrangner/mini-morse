#pragma once
#include <Arduino.h>
#include <GawiButtons.h>

constexpr uint8_t inputMaxLen = 100;

class MorseDecoder {
    char inputString[inputMaxLen + 1];
    uint8_t inputStringLen;
    String decodedInput;
    long long previousCharInput;
    Button* BuiltinButton;
    ButtonManager ButtonMng;
public:
    MorseDecoder();
    void listen();
    String decodeMorse();
    void printInputString();
};