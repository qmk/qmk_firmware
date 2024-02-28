#include QMK_KEYBOARD_H
#include "stdlib.h"
#include "analog.h"
#include "qmk_midi.h"

uint8_t divisor = 0;

void slider(void) {

    static int previousPotValue = 0;
    int currentPotValue = analogReadPin(POT1_PIN);
    int threshold = 25;  

    if (abs(currentPotValue - previousPotValue) > threshold) {
        midi_send_cc(&midi_device, 2, 0x0A, 0x7F - (currentPotValue >> 3));
        previousPotValue = currentPotValue;
    }


    static int previousPotValue2 = 0;
    int currentPotValue2 = analogReadPin(POT2_PIN);


    if (abs(currentPotValue2 - previousPotValue2) > threshold) {
        midi_send_cc(&midi_device, 2, 0x0B, 0x7F - (currentPotValue2 >> 3));
        previousPotValue2 = currentPotValue2;
    }


    static int previousPotValue3 = 0;
    int currentPotValue3 = analogReadPin(POT3_PIN);


    if (abs(currentPotValue3 - previousPotValue3) > threshold) {
        midi_send_cc(&midi_device, 2, 0x0C, 0x7F - (currentPotValue3 >> 3));
        previousPotValue3 = currentPotValue3;
    }
    

    static int previousPotValue4 = 0;
    int currentPotValue4 = analogReadPin(POT3_PIN);


    if (abs(currentPotValue4 - previousPotValue4) > threshold) {
        midi_send_cc(&midi_device, 2, 0x0D, 0x7F - (currentPotValue4 >> 3));
        previousPotValue4 = currentPotValue4;
    }
}

void matrix_scan_user(void) {
    slider();
}
