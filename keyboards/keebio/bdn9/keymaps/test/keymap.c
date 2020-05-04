#include QMK_KEYBOARD_H

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, RGB_MOD
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_1);
        } else {
            tap_code(KC_2);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_3);
        } else {
            tap_code(KC_4);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_5);
        } else {
            tap_code(KC_6);
        }
    }
}
