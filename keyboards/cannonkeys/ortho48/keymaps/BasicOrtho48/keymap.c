/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "keyDefinitions.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _RAISE 1
#define _LOWER 2
#define _NUM 3
#define _CHEESE 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NUM,
  CHEESE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Num  | Ctrl | Alt  | GUI  |Lower |Space |Sh_Spc|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_ortho_4x12(
    KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,       KC_G,   KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,   KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    MO(_NUM), KC_LCTL, KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, RS(SPC), MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  | Home | PgUp | Prev | Play | Next |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | End  | PgDn |      |      |      |      |      |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |AltF4 |      |      |             |      |      |VolDn |VolUp |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_HOME, KC_PGUP,  KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_END,  KC_PGDN,  _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    _______, _______, A(KC_F4), _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bspc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Caps |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |BriDn |BriUp |Cheese|
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CAPS, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    RGB_TOG, RGB_MOD, BL_INC,  BL_DEC,  _______, _______, _______, _______, _______, KC_BRID, KC_BRIU, MO(_CHEESE)
),

/* Num -- Numpad Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |NUM_7 |NUM_8 |NUM_9 |NUM_/ |NUM_- | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |NUM_4 |NUM_5 |NUM_6 |NUM_* |NUM_+ |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |NUM_0 |NUM_1 |NUM_2 |NUM_3 |NUM_. |NUM_= |nEnter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______, KP_7,    KP_8,    KP_9,    KSSH,    KMIN,    KC_BSPC,
    _______, _______, _______, _______, _______, _______, KP_4,    KP_5,    KP_6,    STAR,    PLUS,    _______,
    _______, _______, _______, _______, _______, KP_0,    KP_1,    KP_2,    KP_3,    KDOT,    KEQL,    KNTR,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Cheese --
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | F13  | F14  | F15  | F16  | F17  | F18  |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | F19  | F20  | F21  | F22  | F23  | F24  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_CHEESE] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, F_13,    F_14,    F_15,    F_16,    F_17,    F_18,    _______, _______, _______, _______, _______,
    _______, F_19,    F_20,    F_21,    F_22,    F_23,    F_24,    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
};
