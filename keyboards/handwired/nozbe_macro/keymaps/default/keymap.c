#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(BL_TOGG, BL_STEP, KC_3, LALT(KC_D))};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code16(LALT(KC_DOWN));
    } else {
        tap_code16(LALT(KC_UP));
    }

    return true;
}
