
#include QMK_KEYBOARD_H

#define VIAL_KEYBOARD_UID {0x98, 0x56, 0x64, 0x04, 0xAC, 0xE0, 0xDD, 0x1D}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_MPLY
    )
};

