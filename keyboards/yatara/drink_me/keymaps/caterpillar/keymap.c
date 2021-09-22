#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LSFT(KC_O),
        LSFT(KC_R),
        LSFT(KC_U),
        LSFT(KC_SLSH)
    )
};
