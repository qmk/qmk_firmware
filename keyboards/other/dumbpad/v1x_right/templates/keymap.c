#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {__KEYMAP_GOES_HERE__};


void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                if (clockwise) {
                    tap_code(KC_MS_R);
                } else {
                    tap_code(KC_MS_L);
                }
                break;

            default:
                if (clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
        }
    }
}
