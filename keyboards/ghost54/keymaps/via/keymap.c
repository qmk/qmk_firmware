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

enum custom_keycodes {
  ZEROx3 = SAFE_RANGE,
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
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
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
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
  KC_LWIN,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    PT_COMM, PT_DOT,  KC_MINS, PT_MORD,
                    KC_ENT,  KC_SPC,  MO(1),   LGUI(KC_TAB)              KC_MPLY, OSL(2),  KC_BSPC, KC_DEL
),
/*
 * NUMPAD + Navigation
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |NUMLCK|   /  |   *  |   ^  |                    |      |      |      |      |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   €  |   7  |   8  |   9  |   -  |                    |      | PGUP |  UP  | PGDN |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   0  |   4  |   5  |   6  |   +  |-------.    ,-------|      | LEFT | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
 * | Win  |  000 |   1  |   2  |   3  |   .  |-------|    |-------|      | HOME | INSRT|  END |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(0)  /       \OSL(2)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */

[1] = LAYOUT(
  KC_ESC,   ____,   KC_NUM,  KC_PSLS, KC_PAST, S(PT_TILD),               ____,     ____,    ____,     ____,    ____,  KC_PSCR,
  KC_TAB,   PT_EURO,KC_P7,   KC_P8,   KC_P9,   KC_MINS,                  ____,     KC_PGUP, KC_UP,    KC_PGDN, ____,  ____,
  KC_LSFT,  KC_P0,  KC_P4,   KC_P5,   KC_P6,   KC_PLUS,                  ____,     KC_LEFT, KC_DOWN,  KC_RIGHT,____,  ____,
  KC_LWIN,  ZEROx3, KC_P1,   KC_P2,   KC_P3,   PT_DOT,                   ____,     KC_HOME, KC_INSERT,KC_END,  ____,  ____,
                    KC_ENT,  KC_SPC,  MO(0),   LGUI(KC_TAB)              KC_MPLY,  OSL(2),  KC_BSPC,  KC_DEL
),
/* Symbols
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |      |      |      |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |      |   «  |   \  |  [   |                    |   ]  |   /  |   »  |   ¨  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   #  |   @  |   <  |   !  |  (   |-------.    ,-------|   )  |   ?  |   >  |   =  |  |   |      |
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
 * | Win  |      |      |   -  |   "  |  {   |-------|    |-------|   }  |   '  |   _  |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \ MO(0)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */
[2] = LAYOUT(
  KC_ESC,    ____,   ____,   ____,   ____,   ____,                  ____,   ____,   ____,   ____,  ____,  KC_PSCR,
  KC_TAB,    ____,   ____,    ,    ,    ,                   ,    ,    ,    ,    ____,  ____,
  KC_LSFT,   S(PT_3),ALGR(PT_2),PT_LABK,  S(PT_1), S(PT_8),                  S(PT_9), S(PT_QUOT), PS(PT_LABK)T_LABK, , , ____,
  KC_LWIN,   ____,   ____, , , ,                  , , , ____, ____, ____,
                     KC_ENT,  KC_SPC,  MO(1),   LGUI(KC_TAB)              KC_MPLY, MO(0),  KC_BSPC, KC_DEL
),
/* F Keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |  F10 |  F11 |  F12 |      |                    |      |  F22 |  F23 |  F24 |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  F7  |  F8  |  F9  |      |                    |      |  F19 |  F20 |  F21 |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|      |  F4  |  F5  |  F6  |      |-------.    ,-------|      |  F16 |  F17 |  F18 |      |      |
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
 * | Win  |      |  F1  |  F2  |  F3  |      |-------|    |-------|      |  F13 |  F14 |  F15 |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \OSL(2)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */
[3] = LAYOUT(
  KC_ESC,  _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,KC_PSCR,
  KC_TAB,   KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, _______,   KC_UP, _______,_______, KC_BSPC,
  KC_LSFT, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
  KC_LWIN,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,       _______,  XXXXXXX, _______, XXXXXXX, _______,   XXXXXXX, _______,
                    KC_ENT,  KC_SPC,  MO(1),   LGUI(KC_TAB)              KC_MPLY, OSL(2),  KC_BSPC, KC_DEL
)
};
