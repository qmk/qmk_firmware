#include QMK_KEYBOARD_H
#include "analog.h"
#include <stdio.h>

#ifndef ADC_PIN
#    define ADC_PIN A0
#endif

enum custom_keycodes {
    ADC_SAMPLE = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(ADC_SAMPLE)  //
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ADC_SAMPLE:
            if (record->event.pressed) {
                int16_t val = analogReadPin(ADC_PIN);

                char buffer [50];
                sprintf(buffer, "ADC:%u\n", val);
#ifdef CONSOLE_ENABLE
                    printf(buffer);
#else
                    SEND_STRING(buffer);
#endif
            }
            break;
    }
    return false;
};
