#include "morseDecoder.h"
#include "morseKey.h"
#include "pins.h"

MorseDecoder::MorseDecoder() {
    // Hardware
    BuiltinButton = ButtonMng.addButton(builtinButtonPin, true, 10, 300);
    
    // Data
    inputString[0] = '\0';
    inputStringLen = 0;
    
    // Logic
    isWaitingForNextSymbol = false;
    newCharAvailable = false;
    now = millis();
    previousCharInput = 0;
    spaceDuration = 1000;
}

void MorseDecoder::update(Button* sharedButton) {
    now = millis();
    ButtonMng.updateAll();

    if (inputStringLen < inputMaxLen) {
        if (sharedButton->wasPushed()) {
            Serial.println("Pushed!");
            addSymbol('.', true);
        }
        if (sharedButton->wasHeld()) {
            Serial.println("Held!");
            addSymbol('-', true);
        }
    }

    if (sharedButton->pressed() || sharedButton->released()) {
        previousCharInput = now;
        isWaitingForNextSymbol = true;
    }

    if ((isWaitingForNextSymbol && (now - previousCharInput > spaceDuration)) || inputStringLen >= inputMaxLen) {
        // addToInputString(' ', false); Ska bli "skicka"
        newCharAvailable = true;
        isWaitingForNextSymbol = false;
    }
}

void MorseDecoder::addSymbol(char newChar, bool state) {
    inputString[inputStringLen] = newChar;
    printInput();
    inputString[++inputStringLen] = '\0';
    isWaitingForNextSymbol = state;
}

char MorseDecoder::decodeChar(const char* morseChar) {
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
            clearInputString();
            return morseKey[i].latin;
        }
    }
    clearInputString();
    return morseKey[0].latin; // Unknown char
}

void MorseDecoder::printInput() {
    Serial.print(inputString[inputStringLen]);
}

void MorseDecoder::clearInputString() {
    inputString[0] = '\0';
    inputStringLen = 0;
    Serial.print("   ");
}

bool MorseDecoder::hasNewData() {
    return newCharAvailable;
}

char MorseDecoder::getCharacter() {
    newCharAvailable = false;
    return decodeChar(inputString);
}