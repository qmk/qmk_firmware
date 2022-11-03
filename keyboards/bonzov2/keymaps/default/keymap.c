// Copyright 2022 dear
 
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
	_FN1,
    _FN2
};

// Defines the keycodes used by our macros in process_record_user
/*enum custom_keycodes {
    
};
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 
		KC_ESCAPE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, MO(_FN1), 
		KC_LCTL, MO(_FN), KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_ALGR, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, 
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_BSLS, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, MO(_FN1), 
		KC_LCTL, MO(_FN), KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_ALGR, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[_FN1] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 
		KC_ESCAPE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, MO(_FN1), 
		KC_LCTL, MO(_FN), KC_LALT, KC_SPC, RESET, KC_SPC, KC_ALGR, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN2] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 
		KC_ESCAPE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, MO(_FN1), 
		KC_LCTL, MO(_FN), KC_LALT, KC_SPC, RESET, KC_SPC, KC_ALGR, KC_LEFT, KC_DOWN, KC_RGHT
    )
};

/*bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n1");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}
*/
/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
