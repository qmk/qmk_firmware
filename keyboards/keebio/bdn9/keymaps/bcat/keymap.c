#include QMK_KEYBOARD_H

enum layer {
    LAYER_FIRST,
    LAYER_SECOND,
};

#define LY_SECND MO(LAYER_SECOND)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_FIRST] = LAYOUT(
        KC_MUTE,  LY_SECND, BL_BRTG,
        KC_F4,    KC_F5,    KC_F6,
        KC_F1,    KC_F2,    KC_F3
    ),

    [LAYER_SECOND] = LAYOUT(
        EEP_RST,  _______,  RESET,
        KC_F10,   KC_F11,   KC_F12,
        KC_F7,    KC_F8,    KC_F9
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        /* Top-left encoder (volume) */
        case 0:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
    
        /* Top-right encoder (backlight brightness) */
        case 1:
            if (clockwise) {
                backlight_increase();
            } else {
                backlight_decrease();
            }
            break;
    }
}
