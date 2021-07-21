#include QMK_KEYBOARD_H

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

enum layer_names {
  _ZERO,
  _ONE,
  _TWO,
  _THREE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_ZERO] = LAYOUT(
    KC_MPLY, KC_HOME, KC_MUTE,
    MO(1),   KC_UP,   RGB_MOD,
    KC_LEFT, KC_DOWN, KC_RGHT
),

[_ONE] = LAYOUT(
    RESET,   BL_STEP, KC_STOP,
    _______, KC_HOME, RGB_MOD,
    KC_MPRV, KC_END , KC_MNXT
),

[_TWO] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______
),

[_THREE] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______
)

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
