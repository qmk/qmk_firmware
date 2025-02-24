// Copyright 2024, 2025 Richard Dawe
// SPDX-License-Identifier: GPL-2.0-or-later

// Convert this into a printable keymap on Linux using:
/*
grep -B12 --group-separator="$(echo)" -E 'LAYOUT\(' keyboards/oxwich50/keymaps/richdawe/keymap.c | grep -v LAYOUT > oxwich50-keymap-richdawe.txt
enscript -v -r -f Courier9 --media=A4 oxwich50-keymap-richdawe.txt -o oxwich50-keymap-richdawe.ps
ps2pdf oxwich50-keymap-richdawe.ps oxwich50-keymap-richdawe.pdf
*/

#include QMK_KEYBOARD_H

#define LT1_SPC LT(1, KC_SPC)
#define LT2_ESC LT(2, KC_ESC)
#define LT3_TAB LT(3, KC_TAB)

#define MT_LASL LALT_T(KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer
     *
     * +------+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+--------+
     * |TabL3 |  Q  |  W  |  E  |  R  |  T  |  [  |  |  ]  |  Y  |  U  |  I  |  O  |  P  |  Bspc  |
     * +-+----++----++----++----++----++----++----++ ++----++----++----++----++----++----++-----+-+
     *   |ESCL2|  A  |  S  |  D  |  F  |  G  |  ~  |  |  -  |  H  |  J  |  K  |  L  |  ;  |  '  |
     * +-+-----+--+--+--+--+--+--+--+--+--+--+--+--+  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |  Shift   |  Z  |  X  |  C  |  V  |  B  |        |  B  |  N  |  M  |  ,  |  .  | Up  |ShEnt|
     * +-------+--+----++-----+-----+-----+----++        ++----+-----+--+--+-----+-----+-----+-----+
     * | Ctrl  | Win   | Alt  |  Space / L1    |          | Space / L1  | /  Alt |Left |Down |Right|
     * +-------+-------+------+----------------+          +-------------+--------+-----+-----+-----+
     */
    [0] = LAYOUT(
        LT3_TAB, KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_LBRC, KC_RBRC,  KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
        LT2_ESC, KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_TILD, KC_MINS,  KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,             KC_B,     KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_UP,   SC_SENT,
        KC_LCTL, KC_LGUI, KC_LALT,           LT1_SPC,                             LT1_SPC,           MT_LASL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    /* Layer 1: Numbers and symbols layer
     *
     * +------+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+--------+
     * |  :   |  1  |  2  |  3  |  4  |  5  |  [  |  |  ]  |  6  |  7  |  8  |  9  |  0  |  Bspc  |
     * +-+----++----++----++----++----++----++----++ ++----++----++----++----++----++----++-----+-+
     *   |  .  |  !  |  "  |  #  |  $  |  %  |     |  |     |  ^  |  &  |  *  |  (  |  )  |  \  |
     * +-+-----+--+--+--+--+--+--+--+--+--+--+--+--+  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |          |  \  |  ~  |  `  |  |  |  +  |        |  -  |  !  |  =  |  [  |  ]  |PgUp |     |
     * +-------+--+----++-----+-----+-----+----++        ++----+-----+--+--+-----+-----+-----+-----+
     * |       |       |      |                |          |             |        |Home |PgDn | End |
     * +-------+-------+------+----------------+          +-------------+--------+-----+-----+-----+
     */
    [1] = LAYOUT(
        KC_COLN, KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_LBRC, KC_RBRC,  KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DOT,  S(KC_1), S(KC_2), S(KC_3),  S(KC_4), S(KC_5), _______, _______,  S(KC_6), S(KC_7),  S(KC_8), S(KC_9), S(KC_0), KC_BSLS,
        _______, KC_BSLS, KC_TILD, KC_GRV,   KC_PIPE, KC_PLUS,          KC_MINS,  S(KC_1), KC_EQL,   KC_LBRC, KC_RBRC, KC_PGUP, _______,
        _______, _______, _______,           _______,                             _______,           _______, KC_HOME, KC_PGDN, KC_END
    ),

    /* Layer 2: F-keys and media
     *
     * +------+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+--------+
     * | F12  | F1  | F2  | F3  | F4  | F5  |     |  |     | F6  | F7  | F8  | F9  | F10 |  F11   |
     * +-+----++----++----++----++----++----++----++ ++----++----++----++----++----++----++-----+-+
     *   |     |     |     |     |     |     |     |  |     |Left |Down | Up  |Right|     |     |
     * +-+-----+--+--+--+--+--+--+--+--+--+--+--+--+  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |          |     |     |     |     |     |        |     |     |     |     |Mute |VolUp|     |
     * +-------+--+----++-----+-----+-----+----++        ++----+-----+--+--+-----+-----+-----+-----+
     * |       |       |      |                |          |             | MPlay  |MPrev|VolDn|MNext|
     * +-------+-------+------+----------------+          +-------------+--------+-----+-----+-----+
     */
    [2] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   XXXXXXX, XXXXXXX,  KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,          XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, KC_MUTE, KC_VOLU, _______,
        _______, _______, _______,           _______,                             _______,           KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT
    ),

    /* Layer 3: Boot
     *
     * +------+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+--------+
     * |      |     |     |     |     |     |     |  |     |     |     |     |     |     | Delete |
     * +-+----++----++----++----++----++----++----++ ++----++----++----++----++----++----++-----+-+
     *   |     |     |     |     |     |     |     |  |     |     |     |     |     |     |     |
     * +-+-----+--+--+--+--+--+--+--+--+--+--+--+--+  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |          |     |     |     |     |     |        |     |     |     |     |     |     |     |
     * +-------+--+----++-----+-----+-----+----++        ++----+-----+--+--+-----+-----+-----+-----+
     * | Boot  |       |      |                |          |             |        |     |     |     |
     * +-------+-------+------+----------------+          +-------------+--------+-----+-----+-----+
     */
    [3] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,          XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX,           XXXXXXX,                             XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
