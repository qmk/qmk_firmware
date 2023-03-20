/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H
#include "tap_dance_macro.h"

#define MY_CESC MT(MOD_LCTL, KC_ESC)
#define MY_CENT MT(MOD_LCTL, KC_ENT)
#define MY_S_SL MT(MOD_LSFT, KC_SLSH)
#define MY_S_Z  MT(MOD_LSFT, KC_Z)
#define MY_TBUI MT(MOD_LGUI, KC_TAB)
#define MY_CLFT C(KC_LEFT)
#define MY_CRGT C(KC_RGHT)

// rename some keys here to allow for the difference in keymap between US and GB
#define MY_PIPE LSFT(KC_NUBS)
#define MY_TILD KC_PIPE
#define MY_AT KC_DQUO
#define MY_DQUO LSFT(KC_2)

enum userspace_layers {
    LBASE = 0,
    LNUM = 1,
    LSYM = 2,
    LMOV = 3
};


enum tap_dance_codes {
    DC0,
    DC1,
    DC2,
    DC3,
    DC4,
    DC5,
    DC6,
    DC7,
    DC8,
    DC9,
};

/**
 * TODO
 * 1.  think about 2/shift-2   what do i want  - also '/"
 * 2.  the old vim-g key is missing
 *
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE Level: Default Layer
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Esc   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -     | =   | \     | ` |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Tab   | Q | W | E | R | T | Y | U | I | O | P | [     | ]   | Backs |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Cont  | A | S | D | F | G | H | J | K | L | ; | '     | Ent |       |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Shift | Z | X | C | V | B | N | M | , | . | / | Shift | Fn0 |       |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|

            |------+------+-----------------------+------+------|
            | LAlt | LGUI | ******* Space ******* | RGUI | RAlt |
            |------+------+-----------------------+------+------|
    */

    [LBASE] = LAYOUT( //  default layer
     TO(LBASE),    TD(DC1),   TD(DC2), TD(DC3), TD(DC4), TD(DC5), TD(DC6), TD(DC7), TD(DC8), TD(DC9), TD(DC0), KC_MINS, KC_EQL, KC_NUBS, KC_DEL,
        KC_TAB,    KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        MY_CESC,   KC_A,      KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, MY_CENT,
    OSM(MOD_LSFT), KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT), KC_LGUI,
                                 OSL(LSYM), OSL(LNUM), LT(LMOV, KC_SPC), OSL(LSYM), KC_LALT
    ),

    /* Layer numpad mode */
    [LNUM] = LAYOUT(
     TO(LBASE), C(KC_F1),C(KC_F2),C(KC_F3),C(KC_F4),C(KC_F5),C(KC_F6),C(KC_F7),C(KC_F8),C(KC_F9),C(KC_F10),C(KC_F11),C(KC_F12), KC_INS, KC_DEL,
        KC_TRNS, KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_PLUS, KC_7,  KC_8,  KC_9,  KC_PERC, KC_NO,  KC_NO, KC_BSPC,
      TO(LBASE), KC_LALT, KC_LCTL, KC_LT, KC_GT, KC_UNDS, KC_MINS, KC_4,  KC_5,  KC_6,  KC_ASTR, KC_NO,  KC_PENT,
        KC_LGUI, KC_LSFT, KC_NO,   KC_NO, KC_NO, KC_NO,   KC_EQL,  KC_1,  KC_2,  KC_3,  KC_SLSH, KC_SPC, KC_TRNS,
                              KC_TRNS, KC_TRNS, KC_0, KC_COMM, KC_DOT
    ),

    [LSYM] = LAYOUT(
     TO(LBASE), S(KC_F1),S(KC_F2),S(KC_F3),S(KC_F4),S(KC_F5),S(KC_F6),S(KC_F7),S(KC_F8),S(KC_F9),S(KC_F10),S(KC_F11),S(KC_F12), KC_INS, KC_DEL,
        KC_CAPS, KC_TRNS, KC_QUES, KC_COLN, KC_SCLN, KC_TRNS, KC_EXLM, KC_LPRN, KC_RPRN,   MY_AT, KC_NUBS,    KC_NO, KC_TRNS, KC_BSPC,
      TO(LBASE), KC_VOLD, KC_VOLU,   KC_LT,   KC_GT,  KC_EQL, KC_NUHS, KC_LBRC, KC_RBRC, MY_PIPE, MY_TILD,  KC_GRV, KC_PENT,
        KC_TRNS,   KC_NO,   KC_NO, KC_QUOT, MY_DQUO,   KC_NO, KC_AMPR, KC_LCBR, KC_RCBR,  KC_DLR, KC_CIRC,  KC_TRNS, KC_TRNS,
                              KC_TRNS, KC_TRNS, KC_UNDS, KC_TRNS, KC_TRNS
    ),

    [LMOV] = LAYOUT(
     TO(LBASE),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, KC_TRNS, MY_CRGT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS, KC_NO,  KC_NO,   KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_UNDS, KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,  KC_PENT,
        KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   MY_CLFT, KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
};


/*******************************************************************************
 *  * Tap dance functions
 *   ******************************************************************************/
TD_TAP_HOLD_FUNCTIONS(0, KC_0, KC_F10)
TD_TAP_HOLD_FUNCTIONS(1, KC_1, KC_F1)
TD_TAP_HOLD_FUNCTIONS(2, KC_2, KC_F2)
TD_TAP_HOLD_FUNCTIONS(3, KC_3, KC_F3)
TD_TAP_HOLD_FUNCTIONS(4, KC_4, KC_F4)
TD_TAP_HOLD_FUNCTIONS(5, KC_5, KC_F5)
TD_TAP_HOLD_FUNCTIONS(6, KC_6, KC_F6)
TD_TAP_HOLD_FUNCTIONS(7, KC_7, KC_F7)
TD_TAP_HOLD_FUNCTIONS(8, KC_8, KC_F8)
TD_TAP_HOLD_FUNCTIONS(9, KC_9, KC_F9)

// list the actions and map to handlers
qk_tap_dance_action_t tap_dance_actions[] = {
    [DC0] = TD_TAP_HOLD_ACTION(0),
    [DC1] = TD_TAP_HOLD_ACTION(1),
    [DC2] = TD_TAP_HOLD_ACTION(2),
    [DC3] = TD_TAP_HOLD_ACTION(3),
    [DC4] = TD_TAP_HOLD_ACTION(4),
    [DC5] = TD_TAP_HOLD_ACTION(5),
    [DC6] = TD_TAP_HOLD_ACTION(6),
    [DC7] = TD_TAP_HOLD_ACTION(7),
    [DC8] = TD_TAP_HOLD_ACTION(8),
    [DC9] = TD_TAP_HOLD_ACTION(9),
};
/*******************************************************************************
 * End Tap dance functions
 ******************************************************************************/
