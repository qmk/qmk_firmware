/* Copyright 2015-2021 Jack Humbert
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

#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif

enum planck_layers {
  _QWERTY,
  _NAV,
  _NUM,
  _FUNC
};

#define NAV MO(_NAV)
#define NUM MO(_NUM)
#define ___x___ KC_NO

#define SC_COPY    LCTL(KC_C)
#define SC_CUT     LCTL(KC_X)
#define SC_UNDO    LCTL(KC_Z)
#define SC_PAST    LCTL(KC_V)
#define SC_REDO    LCTL(KC_Y)

#define LAYOUT_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty 
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   ;  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Win  | Alt  | Ent  | NAV  | NUM  |Space | Bksp | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_wrapper(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SCLN,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_ENT,  NAV,     NUM,     KC_SPC,  KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Navigation (Hold Lwr Key)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |      |      |      |      |      | Ins  | Home | Up   | End  | PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |      |      |      |      |      | Del  | Left | Down | Right| PgDn | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Undo | Cut  | Copy | Pste | Redo |      |      |      |      |      | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Win  | Alt  | Ent  | NAV  | NUM  | Space| Bksp | Left | Down | Up   |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_wrapper(
    KC_TAB,  ___x___, ___x___, ___x___, ___x___, ___x___, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, ___x___,
    KC_ESC,  ___x___, ___x___, ___x___, ___x___, ___x___, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_ENT,
    KC_LSFT, SC_UNDO, SC_CUT,  SC_COPY, SC_PAST, SC_REDO, ___x___, ___x___, ___x___, ___x___, ___x___, KC_LSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_ENT,  _______, _______, KC_SPC,  KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),


/* Number and symbols (Hold Rse Key)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |      |      |      |      |      |   [  |   7  |   8  |   9  |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |      |      |      |      |      |   -  |   4  |   5  |   6  |   =  | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Undo | Cut  | Copy | Pste | Redo |   `  |   1  |   2  |   3  |   \  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Win  | Alt  | Ent  | NAV  | NUM  |Space | Bksp |   0  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_wrapper(
    KC_TAB,  ___x___, ___x___, ___x___, ___x___, ___x___, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, ___x___,
    KC_ESC,  ___x___, ___x___, ___x___, ___x___, ___x___, KC_MINS, KC_4,    KC_5,    KC_6,    KC_EQL,  KC_ENT,
    KC_LSFT, SC_UNDO, SC_CUT,  SC_COPY, SC_PAST, SC_REDO, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, KC_LSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_ENT,  _______, _______, KC_SPC,  KC_BSPC, KC_0,    KC_DOT,  ___x___, ___x___
),

/* Function (Hold both Lwr and Rse together)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |      |QMKBot|QMKRbt|      |      |PrtScr|  F7  |  F8  |  F9  | F10  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |CapLck|      |      |      |      |      |ScrLck|  F4  |  F5  |  F6  | F11  | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |PauBrk|  F1  |  F2  |  F3  | F12  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Win  | Alt  | Ent  | NAV  | NUM  | Mute | Bksp | Left | Down | Up   | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_wrapper(
    KC_TAB,  ___x___, QK_BOOT, QK_RBT,  ___x___, ___x___, KC_PSCR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  ___x___,
    KC_CAPS, ___x___, ___x___, ___x___, ___x___, ___x___, KC_SCRL, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_ENT,
    KC_LSFT, ___x___, ___x___, ___x___, ___x___, ___x___, KC_PAUS, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_LSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_ENT,  _______, _______, KC_MUTE, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NAV, _NUM, _FUNC);
}