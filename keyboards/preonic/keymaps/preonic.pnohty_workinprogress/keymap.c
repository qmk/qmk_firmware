// qmk compile -kb <keyboard> -km <keymap>
// qmk compile -kb preonic -km keymap_w_subarrays.c

// keyboard agnostic keymap
#include QMK_KEYBOARD_H

// QoL abbreviations
// #include "keycodes.h"

// local definitions
enum preonic_layers { _bas, _num, _sym, _tri };
#define NUM MO(_num)
#define SYM MO(_sym)
#define TRI MO(_tri)

// enum combos { _topl, _btml, _thml, _midl, _topr, _btmr, _thmr, COMBO_LENGTH };
// uint16_t COMBO_LEN = COMBO_LENGTH;

// const cmbo_topl[] = {KC_W, KC_E, COMBO_END};
// const cmbo_btml[] = {KC_X, KC_C, COMBO_END};
// const cmbo_thml[] = {SYM, KC_SPC, COMBO_END};
// const cmbo_midl[] = {KC_G, KC_H, COMBO_END};
// const cmbo_topr[] = {KC_I, KC_O, COMBO_END};
// const cmbo_btmr[] = {KC_COMM, KC_DOT, COMBO_END};
// const cmbo_thmr[] = {KC_RSFT, NUM, COMBO_END};

// combo_t key_combos[] = {[_topl] = COMBO(cmbo_topl, KC_TAB), [_btml] = COMBO(cmbo_btml, KC_LCTL), [_thml] = COMBO(cmbo_thml, KC_LGUI), [_midl] = COMBO(cmbo_midl, KC_NO), [_topr] = COMBO(cmbo_topr, KC_NO), [_btmr] = COMBO(cmbo_btmr, KC_ENT), [_thmr] = COMBO(cmbo_thmr, KC_LALT)};

// Define the keymaps
const keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_bas] = LAYOUT_ortho_5x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, KC_NO, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_BSPC, KC_NO, KC_NO, KC_NO, SYM, KC_SPC, KC_NO, KC_NO, KC_RSFT, NUM, KC_NO, KC_NO, KC_NO),
    [_num] = LAYOUT_ortho_5x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_4, KC_5, KC_6, KC_NO, KC_NO, KC_NO, KC_NO, KC_PIPE, KC_MINS, KC_SLSH, KC_NO, KC_DOT, KC_1, KC_2, KC_3, KC_0, KC_NO, KC_NO, KC_NO, KC_DQUO, KC_UNDS, KC_EQL, TRI, KC_TILD, KC_7, KC_8, KC_9, KC_NO, KC_NO, KC_NO, KC_NO, KC_PLUS, KC_QUES, KC_EXLM, KC_DEL, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_SPC, KC_NO, KC_NO, KC_RSFT, KC_TRNS, KC_NO, KC_NO, KC_NO),
    [_sym] = LAYOUT_ortho_5x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_BSLS, KC_PERC, KC_DLR, KC_NO, KC_NO, KC_NO, KC_NO, KC_CIRC, KC_LCBR, KC_RCBR, KC_NO, KC_ASTR, KC_LPRN, KC_RPRN, KC_COLN, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUOT, KC_LBRC, KC_RBRC, KC_SCLN, KC_NO, KC_GRV, KC_AT, KC_AMPR, KC_NO, KC_NO, KC_NO, KC_NO, KC_HASH, KC_COMM, KC_DOT, KC_DEL, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_SPC, KC_NO, KC_NO, KC_RSFT, KC_TRNS, KC_NO, KC_NO, KC_NO),
    [_tri] = LAYOUT_ortho_5x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC, KC_F4, KC_F5, KC_F6, KC_F10, KC_NO, KC_NO, KC_NO, KC_HOME, KC_UP, KC_END, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F11, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F12, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_SPC, KC_NO, KC_NO, KC_RSFT, KC_TRNS, KC_NO, KC_NO, KC_NO),
};
