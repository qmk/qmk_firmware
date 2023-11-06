#include QMK_KEYBOARD_H
#include "analog.h"
#include <stdio.h>

enum custom_keycodes {
    ADC_SAMPLE = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(ADC_SAMPLE)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ADC_SAMPLE:
            if (record->event.pressed) {
                int16_t val = analogReadPin(ADC_PIN);

                char buffer[50];
                sprintf(buffer, "ADC:%u\n", val);
#ifdef CONSOLE_ENABLE
                    uprintf("%s", buffer);
#else
                    send_string(buffer);
#endif
            }
            break;
    }
    return false;
};

// adc_mux pinToMux(pin_t pin) {
//     return TO_MUX(ADC_CHANNEL_IN1, 0);
// };
