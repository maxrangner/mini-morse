#include "morseDecoder.h"
#include "pins.h"

MorseDecoder::MorseDecoder() {
    BuiltinButton = ButtonMng.addButton(builtinButtonPin, true, 10, 300);
    inputString[0] = '\0';
    uint8_t inputStringLen = 0;
}

void MorseDecoder::listen() {
    ButtonMng.updateAll();
    if (inputStringLen < inputMaxLen) {
        if (BuiltinButton->pressed()) {
            inputString[inputStringLen++] = '.';
            inputString[inputStringLen] = '\0';
            printInputString();
        }
        if (BuiltinButton->held()) {
            inputString[inputStringLen++] = '-';
            inputString[inputStringLen] = '\0';
            printInputString();
        }
    }
}

String MorseDecoder::decodeMorse() {
    
}

void MorseDecoder::printInputString() {
    Serial.println(inputString);
}