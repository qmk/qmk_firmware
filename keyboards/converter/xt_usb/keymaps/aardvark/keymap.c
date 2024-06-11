#include QMK_KEYBOARD_H

#include "keymap_nordic.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum layer_id {
  _BASE = 0,
  _SYMB,
  _FUNC,
  _MOD,
};

enum endgame_keycodes {
    BASE = SAFE_RANGE,
    SYMB,
    FUNC,
    MOD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* IBM XT keyboard layout
     * ,-------.  ,--------------------------------------------------------------------------.
     * | F1| F2|  |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  BS  |NumLck |ScrLck |
     * |-------|  |--------------------------------------------------------------------------|
     * | F3| F4|  | Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ] |   |  7|  8|  9|  -|
     * |-------|  |------------------------------------------------------|Ent|---------------|
     * | F5| F6|  | Ctrl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|   |  4|  5|  6|   |
     * |-------|  |----------------------------------------------------------------------|   |
     * | F7| F8|  |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift|  *|  1|  2|  3|  +|
     * |-------|  |----------------------------------------------------------------------|   |
     * | F9|F10|  |  Alt  |               Space                  |CapsLck|   0   |   .   |   |
     * `-------'  `--------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_xt(
        KC_UNDO,  KC_AGAIN, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NUM,           KC_SCRL,
        KC_COPY,  KC_HOME,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_CUT,   SYMB,     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_GRV,  KC_ENT,  KC_P4,   KC_P5,   KC_P6,
        KC_PASTE, KC_END,   KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
        KC_APP,   KC_LGUI,  KC_LALT,                                              KC_SPC,                                      KC_ALGR,          KC_P0,            KC_PDOT
    ),

    [_SYMB] = LAYOUT_xt(
        _______, _______,   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NUM,           KC_SCRL,
        _______, _______,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        _______, _______,   KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_GRV,  KC_ENT,  KC_P4,   KC_P5,   KC_P6,
        _______, _______,   KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
        _______, _______,   KC_LALT,                                              KC_SPC,                                      _______,          _______,          KC_PDOT
    ),

    [_FUNC] = LAYOUT_xt(
        DM_PLY1, DM_PLY2,   KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, KC_NUM,  KC_SCRL,
        DM_REC1, DM_REC2,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        DM_RSTP, DM_RSTP,   KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_GRV,  KC_ENT,  KC_P4,   KC_P5,   KC_P6,
        KC_F7,   KC_F8,     KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
        KC_F9,   KC_F10,    OSL(MOD),                                             KC_SPC,                                      _______,          _______,          KC_PDOT
    ),

    [_MOD] = LAYOUT_xt(
        KC_F1,   KC_F2,     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NUM,           KC_SCRL,
        KC_F3,   KC_F4,     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_F5,   KC_F6,     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_GRV,  KC_ENT,  KC_P4,   KC_P5,   KC_P6,
        KC_F7,   KC_F8,     KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
        KC_F9,   KC_F10,    KC_LALT,                                              KC_SPC,                                      _______,          _______,          KC_PDOT
    ),
};

const uint16_t PROGMEM combo_caps[] = {KC_LSFT, KC_RSFT, COMBO_END};
const uint16_t PROGMEM combo_sleep[] = {KC_LALT, KC_SCRL, COMBO_END};
const uint16_t PROGMEM combo_func[] = {KC_C,    KC_D,    COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_caps, KC_CAPS),
    COMBO(combo_sleep, KC_SLEP),
    COMBO(combo_func, MO(_FUNC)),
};
