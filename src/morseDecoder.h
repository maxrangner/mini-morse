#pragma once
#include <Arduino.h>
#include <GawiButtons.h>

constexpr uint8_t inputMaxLen = 100;

class MorseDecoder {
    char inputString[inputMaxLen + 1];
    uint8_t inputStringLen;
    String decodedInput;
    bool isWriting;
    unsigned long now;
    unsigned long previousCharInput;
    unsigned long spaceDuration;
    Button* BuiltinButton;
    ButtonManager ButtonMng;
public:
    MorseDecoder();
    void update();
    void addToInputString(char newChar, bool state);
    char decodeMorseChar(const char* morseChar);
    String decodeMorseString();
    void printInputString();
};