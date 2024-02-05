/*
 * Copyright 2022 Kevin Gee <info@controller.works>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_portuguese.h"
#include "ghost54.c"


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP),           ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP),           ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  ´   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ç  |  ~   |
 * |------+------+------+------+------+------|  Find |    |  Play |------+------+------+------+------+------|
 * | Win  |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |  º   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \OSL(2)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */

[0] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PSCR,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    PT_ACUT,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    PT_CCED, PT_TILD,
  KC_LWIN,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS, PT_MORD,
                    KC_ENT,  KC_SPC,  MO(1),   KC_FIND                   KC_MPLY, MO(2),   KC_BSPC, KC_DEL
),
/*
 * NUMPAD + Navigation
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |   *  |   /  |                    |      |      |      |      |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   €  |   7  |   8  |   9  |   -  |                    |      | HOME |  UP  |  END |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   $  |   4  |   5  |   6  |   +  |-------.    ,-------| INSRT| LEFT | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------|  Find |    |  Play |------+------+------+------+------+------|
 * | Win  |   £  |   1  |   2  |   3  |   .  |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(0)  /       \OSL(2)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */

[1] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC,
  KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXXX,KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 KC_LGUI,KC_LALT,KC_LCTL,KC_TRNS, KC_ENT,      KC_SPC,  KC_TRNS, KC_RCTL, KC_RALT, KC_RGUI
),
/* Symbols
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |      |      |      |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |      |   «  |   \  |  [   |                    |   ]  |   /  |   »  |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   #  |   @  |   <  |   !  |  (   |-------.    ,-------|   )  |   ?  |   >  |   =  |  |   |      |
 * |------+------+------+------+------+------|  Find |    |  Play |------+------+------+------+------+------|
 * | Win  |      |      |      |   "  |  {   |-------|    |-------|   }  |   '  |  ¨   |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \ MO(0)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */
[2] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* F Keys
 * ,----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |  F10 |  F11 |  F12 |      |                    |      |  F22 |  F23 |  F24 |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  F7  |  F8  |  F9  |      |                    |      |  F19 |  F20 |  F21 |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|      |  F4  |  F5  |  F6  |      |-------.    ,-------|      |  F16 |  F17 |  F18 |      |      |
 * |------+------+------+------+------+------|  Find  |   |  Play |------+------+------+------+------+------|
 * | Win  |      |  F1  |  F2  |  F3  |      |--------|   |-------|      |  F13 |  F14 |  F15 |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \ MO(0)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */
[3] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, _______,   KC_UP, _______,_______, KC_BSPC,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,       _______,  XXXXXXX, _______, XXXXXXX, _______,   XXXXXXX, _______,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
)
};
