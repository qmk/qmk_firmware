#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0
 * ,---------------------------------------------.
 * | Encoder A  |   4   |   5   |   6   | Enter  |
 * |------------|-------+-------+-------|        |
 * | Encoder B  |   1   |   2   |   3   |        |
 * `---------------------------------------------'
 */
[0] = LAYOUT( \
  KC_HOME, KC_4, KC_5, KC_6, KC_ENT,
  KC_MUTE, KC_1, KC_2, KC_3
),

[1] = LAYOUT( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[2] = LAYOUT( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[3] = LAYOUT( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)

};


void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Encdoer A
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    } else if (index == 1) { // Encoder B
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}