/*  -*-  eval: (turn-on-orgtbl); -*-
 * cinaeco's HHKB Layout
 */
#include QMK_KEYBOARD_H

// Layers.
#define QWER 0
#define COLE 1
#define DVOR 2
#define HHKB 3
#define UTIL 4
#define MREC 5

// Easier-to-read Layer Arrays.
#define ____ KC_TRNS

enum hhkb_keycodes
{
    DYNAMIC_MACRO_RANGE = SAFE_RANGE,
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWER Layer: Qwerty Default
     *
     * ,--------------------------------------------------------------.
     * |Esc|    1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |--------------------------------------------------------------|
     * |Tab  |Q/MREC|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |--------------------------------------------------------------|
     * |Ctrl  |     A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Ent/Ctrl|
     * |--------------------------------------------------------------|
     * |Shift   |     Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
     * `--------------------------------------------------------------'
     *       |Alt|Gui  |       Space/UTIL      |Gui  |Alt|
     *       `-------------------------------------------'
     *
     */

    [QWER] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, LT(MREC, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, CTL_T(KC_ENT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LGUI, LT(UTIL, KC_SPC), KC_RGUI, KC_RALT),

    /* COLE Layer: Colemak
     *
     * ,--------------------------------------------------------------.
     * |Esc|    1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |--------------------------------------------------------------|
     * |Tab  |Q/MREC|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|Backs|
     * |--------------------------------------------------------------|
     * |Ctrl  |     A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Ent/Ctrl|
     * |--------------------------------------------------------------|
     * |Shift   |     Z|  X|  C|  V|  K|  B|  M|  ,|  .|  /|Shift |Fn0|
     * `--------------------------------------------------------------'
     *       |Alt|Gui  |       Space/UTIL      |Gui  |Alt|
     *       `-------------------------------------------'
     *
     */

    [COLE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, LT(MREC, KC_Q), KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, CTL_T(KC_ENT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_K, KC_B, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LGUI, LT(UTIL, KC_SPC), KC_RGUI, KC_RALT),

    /* DVOR Layer: Dvorak
     *
     * ,--------------------------------------------------------------.
     * |Esc|    1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|  \|  `|
     * |--------------------------------------------------------------|
     * |Tab  |'/MREC|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|Backs|
     * |--------------------------------------------------------------|
     * |Ctrl  |     A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|Ent/Ctrl|
     * |--------------------------------------------------------------|
     * |Shift   |     ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z|Shift |Fn0|
     * `--------------------------------------------------------------'
     *       |Alt|Gui  |       Space/UTIL      |Gui  |Alt|
     *       `-------------------------------------------'
     *
     */

    [DVOR] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        KC_TAB, LT(MREC, KC_QUOT), KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL, KC_BSPC,
        KC_LCTL, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, CTL_T(KC_ENT),
        KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LGUI, LT(UTIL, KC_SPC), KC_RGUI, KC_RALT),

    /* HHKB Layer: HHKB mode (HHKB Fn)
     *
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |PLA|PRV|NXT|   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|Ejc|   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |STOP |   |
     *       `-------------------------------------------'
     */

    [HHKB] = LAYOUT(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, KC_MPLY, KC_MPRV, KC_MNXT, ____, ____, ____, ____, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, ____, KC_BSPC,
        ____, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, ____, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        ____, ____, ____, ____, ____, ____, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, ____, ____,
        ____, ____, ____, KC_MSTP, ____),

    /* UTIL Layer: Extra utilities
     *
     * ,-------------------------------------------------------------.
     * |DFU|PLY1|PLY2|   |   |   |   |   |   |   |   |QWE|COL|DVO|DBG|
     * |-------------------------------------------------------------|
     * |     |MLB |M-Up|MRB|MwU|   |Hom|PgD|PgU|End|   |   |   |     |
     * |-------------------------------------------------------------|
     * |      |M-Lt|M-Dn|M-R|MwD|   |LEF|DOW|UP |RIG|   |   |        |
     * |-------------------------------------------------------------|
     * |        |    |    |   |   |SPC|   |   |   |   |   |      |   |
     * `-------------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     *
     */

    [UTIL] = LAYOUT(
        RESET, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, ____, ____, ____, ____, ____, ____, ____, ____, DF(QWER), DF(COLE), DF(DVOR), DEBUG,
        ____, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, ____, KC_HOME, KC_PGDN, KC_PGUP, KC_END, ____, ____, ____, ____,
        ____, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, ____, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, ____, ____, ____,
        ____, ____, ____, ____, ____, KC_SPC, ____, ____, ____, ____, ____, ____, ____,
        ____, ____, ____, ____, ____),

    /* MREC Layer: Record macros with `q`
     *
     * ,-------------------------------------------------------------.
     * |   |REC1|REC2|   |   |   |   |   |   |   |   |   |   |   |   |
     * |-------------------------------------------------------------|
     * |     |    |    |   |   |   |   |   |   |   |   |   |   |     |
     * |-------------------------------------------------------------|
     * |      |    |RSTP|   |   |   |   |   |   |   |   |   |        |
     * |-------------------------------------------------------------|
     * |        |    |    |   |   |   |   |   |   |   |   |      |   |
     * `-------------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     *
     */

    [MREC] = LAYOUT(
        ____, DYN_REC_START1, DYN_REC_START2, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
        ____, ____, DYN_REC_STOP, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
        ____, ____, ____, ____, ____)

};

// For Dynamic Macros.
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!process_record_dynamic_macro(keycode, record))
    {
        return false;
    }
    return true;
}
