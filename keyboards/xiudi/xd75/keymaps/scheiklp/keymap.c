// Copyright 2021 Paul Maria Scheikl (@ScheiklP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "koy_keys_on_quertz_de_latin1.h"

// Layer shorthand
#define _1 0
#define _3 1
#define _4 2
#define _7 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 1
 * .---------------------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC     | 1       | 2      | 3      | 4      | 5      |  Record 1 | Play 1    | 6      | 7       | 8      | 9      | 0      |     DEL   | BACKSP  |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | TAB     | K       | .      | O      | ,      | Y      |  Record 2 | Play 2P   | V      | G       | C      | L      | ẞ      | Z         |         |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | Layer 3 | H       | A      | E      | I      | U      |  Undo     | Stop Rec. | D      | T       | R      | N      | S      | F         | Layer 3 |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LSHIFT  | X       | Q      | Ä      | Ü      | Ö      |  Copy     | Cut       | B      | P       | W      | M      | J      | RSHIFT    | RSHIFT  |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LCTRL   | Layer 4 |        | LGUI   | LALT   | SPACE  |  Paste    |  SPACE    | SPACE  | Layer 4 | RCTRL  |        |        | KEYLOCK   | Layer 7 |
 * '---------------------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_1] = LAYOUT_ortho_5x15( /* KOY */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,   DM_REC1,  DM_PLY1, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL,  KC_BSPC, 
    KC_TAB,  KC_K,    KC_DOT,  KC_O,    KC_COMM,  N_Y,    DM_REC2,  DM_PLY2, KC_V,   KC_G,    KC_C,    KC_L,    N_SS,   N_Z,     KC_TRNS,
    MO(_3),  KC_H,    KC_A,    KC_E,    KC_I,     KC_U,   N_UNDO,   DM_RSTP, KC_D,   KC_T,    KC_R,    KC_N,    KC_S,   KC_F,    MO(_3),
    KC_LSFT, KC_X,    KC_Q,    N_AE,    N_UE,     N_OE,   N_COPY,   N_CUT,   KC_B,   KC_P,    KC_W,    KC_M,    KC_J,   KC_RSFT, KC_RSFT,
    KC_LCTL, MO(_4),  KC_TRNS, KC_LGUI, KC_LALT,  KC_SPC, N_PASTE,  KC_SPC,  KC_SPC, MO(_4),  KC_RCTL, KC_TRNS, KC_TRNS,KC_LOCK, MO(_7)
  ),

/* Layer 3
 * .---------------------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC     | F1      | F2     | F3     | F4     | F5     |           |           | F6     | F7      | F8     | F9     | F0     |     DEL   | BACKSP  |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | TAB     | …       | _      | [      | ]      | ^      |           |           | !      | <       | >      | =      | &      |           |         |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | Layer 5 | \       | /      | {      | }      | *      |           |           | ?      | (       | )      | -      | :      | @         | Layer 5 |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LSHIFT  | #       | $      | |      | ~      | `      |           |           | +      | %       | "      | '      | ;      | RSHIFT    | RSHIFT  |
 * |---------+---------+--------+--------+--------+--------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LCTRL   |         |        |        | LALT   |        |           |           |        |         |        |        |        |           |         |
 * '---------------------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_3] = LAYOUT_ortho_5x15( /* Layer 3 */
    KC_ESC,   KC_F1,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
    KC_TAB,   N_DOTS,  N_USC,   N_LSQBR, N_RSQBR, N_CIRC,  KC_TRNS, KC_TRNS, N_EXKL,  N_LT,    N_GT,    N_EQ,    N_AMP,   KC_TRNS, KC_TRNS,
    KC_TRNS,  N_BSLS,  N_SLSH,  N_LCUBR, N_RCUBR, N_ASTR,  KC_TRNS, KC_TRNS, N_QUES,  N_LPARN, N_RPARN, N_MINS,  N_COLN,  N_AT,    KC_TRNS, 
    KC_LSFT,  N_HASH,  N_DLR,   N_PIPE,  N_TILD,  N_GRAVE, KC_TRNS, KC_TRNS, N_PLUS,  N_PERC,  N_QUOT,  N_SING,  N_SEMI,  KC_RSFT, KC_RSFT,
    KC_LCTL,  KC_TRNS, KC_TRNS, KC_LALT, KC_TRNS, KC_SPC,  KC_TRNS, KC_SPC,  KC_SPC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

/* Layer 4
 * .------------------------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC     |         |        |        |        |           |           |           |        |         |        |        |        |           |         |
 * |---------+---------+--------+--------+--------+-----------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | TAB     | Page up | BACKSP | Up     | DEL    | Page down |           |           |  /     | 7       | 8      | 9      | −      |           |         |
 * |---------+---------+--------+--------+--------+-----------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * |         | Home    | Left   | Down   | Right  | End       |           |           |  *     | 4       | 5      | 6      | .      |           |         |
 * |---------+---------+--------+--------+--------+-----------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LSHIFT  | ESC     | TAB    | Insert | Enter  | Undo      |           |           |  Enter | 1       | 2      | 3      | ;      | RSHIFT    | RSHIFT  |
 * |---------+---------+--------+--------+--------+-----------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LCTRL   |         |        |  LALT  |        |   0       |           |    0      |   0    |         |        |        |        |           |         |
 * '------------------------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_4] = LAYOUT_ortho_5x15( /* Layer 4 */
    KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS,
    KC_TAB,  KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,   KC_PGDN, KC_TRNS, KC_TRNS, KC_KP_SLASH,    KC_7,    KC_8,    KC_9,    KC_KP_MINUS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  KC_TRNS, KC_TRNS, KC_KP_ASTERISK, KC_4,    KC_5,    KC_6,    KC_KP_PLUS,  KC_TRNS,  KC_TRNS,
    KC_LSFT, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER, N_UNDO,  KC_TRNS, KC_TRNS, KC_KP_ENTER,    KC_1,    KC_2,    KC_3,    KC_KP_DOT,   KC_RSFT,  KC_RSFT,
    KC_LCTL, KC_TRNS, KC_TRNS, KC_LALT, KC_TRNS,  KC_0,    KC_TRNS, KC_0,    KC_0,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS
  ),

/* Layer 7
 * .--------------------------------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC     |          |          | Button 3 |          |            |           |           |        |         |        |        |        |           |  QK_BOOT  |
 * |---------+----------+----------+----------+----------+------------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | TAB     | Wheel up | Button 2 | Up       | Button 1 | Wheel down |           |           |        |         |        |        |        |           |         |
 * |---------+----------+----------+----------+----------+------------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * |         | Veloc 0  | Left     | Down     | Right    |            |           |           |        |         |        |        |        |           |         |
 * |---------+----------+----------+----------+----------+------------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LSHIFT  | Veloc 1  |          |          |          |            |           |           |        |         |        |        |        |           |         |
 * |---------+----------+----------+----------+----------+------------+-----------+-----------+--------+---------+--------+--------+--------+-----------+---------|
 * | LCTRL   | Veloc 2  |          |  LALT    |          |            |           |           |        |         |        |        |        |           |         |
 * '--------------------------------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_7] = LAYOUT_ortho_5x15( /* Layer 7 */
    KC_ESC,  KC_TRNS,      KC_TRNS,    KC_MS_BTN3, KC_TRNS,     KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
    KC_TAB,  KC_MS_WH_UP,  KC_MS_BTN2, KC_MS_UP,   KC_MS_BTN1,  KC_MS_WH_DOWN,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_MS_ACCEL0, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LSFT, KC_MS_ACCEL1, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LCTL, KC_MS_ACCEL2, KC_TRNS,    KC_LALT,    KC_TRNS,     KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )

};

