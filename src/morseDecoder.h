#pragma once
#include <Arduino.h>
#include <GawiButtons.h>

constexpr uint8_t inputMaxLen = 5;

class MorseDecoder {
    char inputString[inputMaxLen + 1];
    uint8_t inputStringLen;
    String decodedInput;
    bool isWaitingForNextSymbol;
    bool newCharAvailable;
    unsigned long now;
    unsigned long previousCharInput;
    unsigned long spaceDuration;
    Button* BuiltinButton;
    ButtonManager ButtonMng;
    void addSymbol(char newChar, bool state);
    char decodeChar(const char* morseChar);
    void printInput();
    void clearInputString();
public:
    MorseDecoder();
    void update(Button* sharedButton);
    bool hasNewData();
    char getCharacter();
};