/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H

enum
{
    BASE,
    HHKB,
    MIRROR,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE Level: Default Layer
       ,-----------------------------------------------------------.
       |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10|  -|  =|Yen|Bsp|
       |-----------------------------------------------------------|
       |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |
       |------------------------------------------------------` Ent|
       |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|    |
       |-----------------------------------------------------------|
       |Shft   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  \| Up|Sft|
       |-----------------------------------------------------------|
       |   ||Ctl|Alt|Cmd|   |   Spc   |   |   |   |   ||Lft|Dwn|Rgh|
       `-----------------------------------------------------------'
    */
    [BASE] = LAYOUT_JP(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_UP, KC_RSFT,
        MO(HHKB), KC_ZKHK, KC_LGUI, KC_LALT, KC_MHEN, LT(MIRROR, KC_SPC), KC_HENK, KC_KANA, KC_RALT, MO(HHKB), KC_LEFT, KC_DOWN, KC_RGHT),

    /* Layer HHKB: HHKB mode (HHKB Fn)
       ,-----------------------------------------------------------.
       |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
       |-----------------------------------------------------------|
       |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
       |------------------------------------------------------`    |
       |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|   |    |
       |-----------------------------------------------------------|
       |       |   |   |   |   |   |  +|  -|End|PgD|Dow|   |   |   |
       |-----------------------------------------------------------|
       |   ||   |   |   |   |         |   |   |   |   ||   |   |   |
       `-----------------------------------------------------------'
     */

    [HHKB] = LAYOUT_JP(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /* Mirror Level: when hold space bar
       ,-----------------------------------------------------------.
       |   |  0|  9|  8|  7|  6|  5|  4|  3|  2|  1|   |   |   |   |
       |-----------------------------------------------------------|
       |     |  P|  O|  I|  U|  Y|  T|  R|  E|  W|  Q|   |   |     |
       |------------------------------------------------------`    |
       |      |  ;|  L|  K|  J|  H|  G|  F|  D|  S|  A|   |   |    |
       |-----------------------------------------------------------|
       |       |  .|  ,|  M|  N|  B|  V|  C|  X|  Z|   |   |   |   |
       |-----------------------------------------------------------|
       |   ||   |   |   |   |         |   |   |   |   ||   |   |   |
       `-----------------------------------------------------------'
    */
    [MIRROR] = LAYOUT_JP(
        _______, KC_0, KC_9, KC_8, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1, _______, _______, _______, _______,
        _______, KC_P, KC_O, KC_I, KC_U, KC_Y, KC_T, KC_R, KC_E, KC_W, KC_Q, _______, _______,
        _______, KC_SCLN, KC_L, KC_K, KC_J, KC_H, KC_G, KC_F, KC_D, KC_S, KC_A, _______, _______, _______,
        _______, KC_DOT, KC_COMM, KC_M, KC_N, KC_B, KC_V, KC_C, KC_X, KC_Z, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_SPC, _______, _______, _______, _______, _______, _______, _______)};

