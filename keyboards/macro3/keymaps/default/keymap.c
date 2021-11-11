#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
	KC_HOME, KC_MUTE, KC_MPLY, KC_MSEL,
	KC_UNDO, KC_CUT,  KC_COPY, LT(1,KC_PSTE)
    ),
    [1] = LAYOUT(
	_______, _______, _______, _______,
	RESET,   _______, _______, _______
    )
};


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif

