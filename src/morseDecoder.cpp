#include "morseDecoder.h"
#include "morseKey.h"
#include "pins.h"

MorseDecoder::MorseDecoder() {
    BuiltinButton = ButtonMng.addButton(builtinButtonPin, true, 10, 300);
    inputString[0] = '\0';
    inputStringLen = 0;
    isWriting = false;
    now = 0;
    previousCharInput = 0;
    spaceDuration = 1000;
}

void MorseDecoder::update() {
    now = millis();
    ButtonMng.updateAll();

    if (inputStringLen < inputMaxLen) {
        if (BuiltinButton->pressed()) addToInputString('.', true);
        if (BuiltinButton->held()) addToInputString('-', true);
    }
    if (BuiltinButton->released()) previousCharInput = now;
    if ((now > previousCharInput + spaceDuration) && isWriting) {
        addToInputString(' ', false);
        printInputString();
    }
}

void MorseDecoder::addToInputString(char newChar, bool state) {
    inputString[inputStringLen++] = newChar;
    inputString[inputStringLen] = '\0';
    previousCharInput = now;
    isWriting = state;
}

char MorseDecoder::decodeMorseChar(const char* morseChar) {
    for (uint8_t i = 0; i < morseKeyLen; i++) {
        bool isMatching = true;
        uint8_t j = 0;
        while (morseChar[j] != '\0' && morseKey[i].morse[j] != '\0') {
            if (morseChar[j] != morseKey[i].morse[j]) {
                isMatching = false;
                break;
            }
            j++;
        }
        if (isMatching && (morseChar[j] == '\0' && morseKey[i].morse[j] == '\0')) {
            return morseKey[i].latin;
        }
    }
    return morseKey[0].latin; // Unknown char
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