#include QMK_KEYBOARD_H

enum custom_keycodes {KC_PASTA = SAFE_RANGE};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_BSPC, 
		CTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, LT(2, KC_ENT), 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, LT(1, KC_SPC), KC_N, KC_M, KC_COMM, ALT_T(KC_DOT), GUI_T(KC_SLSH), SFT_T(KC_DEL)),

	[1] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_RBRC, KC_BSLS, 
		KC_TRNS, KC_MINS, KC_EQL, KC_BSLS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SCLN, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS),

	[2] = LAYOUT(
		QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_INS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PASTA, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
    switch (keycode) {
            case KC_PASTA:
                if (record->event.pressed) {
                    SEND_STRING("https://i.imgur.com/dzBrlqc.png");
                }
                break;

        }
    }
    return true;
}

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(B2);
  writePinLow(B2);
  // set NumLock LED to output and low
  setPinOutput(B6);
  writePinLow(B6);

}

layer_state_t layer_state_set_user(layer_state_t state)
{
    if (layer_state_cmp(state, 1)) {
        writePinHigh(B2);
    } else if (state & (1<<2)) {
        writePinLow(B2);
        writePinHigh(B6);
    } else if (state & (1<<3)) {
        writePinHigh(B2);
        writePinHigh(B6);
    } else {
        writePinLow(B2);
        writePinLow(B6);
    }
    return state;
}
