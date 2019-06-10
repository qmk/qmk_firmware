#include QMK_KEYBOARD_H

//Tap Dance Declarations
/*
enum
{
  TD_SHIFT_CAPS = 0,
  // TD_TAB_HYPER = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Esc, twice for Caps Lock
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
    // Other declarations would go here, separated by commas, if you have them
    // [TD_TAB_HYPER] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_MINUS, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_EQL,
        TD(TD_SHIFT_CAPS), KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_SLSH,
        KC_LCTL, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_NO, KC_NO, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_BSLS,
        KC_LALT, KC_LGUI, KC_SFTENT, KC_SPC, TT(1), KC_LALT),
    [1] = LAYOUT(
        KC_GRV, KC_NO, KC_1, KC_2, KC_3, KC_NO, KC_NO, TO(0), TO(2), TO(3), KC_NO, KC_DEL,
        KC_NO, KC_MINUS, KC_4, KC_5, KC_6, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_MFFD, KC__VOLUP,
        KC_NO, KC_LBRC, KC_7, KC_8, KC_9, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_MPLY, KC__VOLDOWN,
        KC_NO, KC_RBRC, KC_NO, KC_0, KC_NO, KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MRWD, KC__MUTE,
        KC_NO, KC_NO, KC_SPC, KC_SFTENT, KC_TRNS, TT(2)),
    [2] = LAYOUT(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_NO,
        TD(TD_SHIFT_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_NO,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        KC_NO, KC_NO, KC_NO, KC_SFTENT, KC_SPC, KC_NO, KC_TRNS)};
