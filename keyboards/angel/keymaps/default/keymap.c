/* Copyright 2021 James Sa
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _COLEMAKDH, // base
    _PUNCUATION,
    _FUNCTION
};

#define LC(X) MT(MOD_LCTL, X)
#define LA(X) MT(MOD_LALT, X)
#define LS(X) MT(MOD_LSFT, X)
#define LG(X) MT(MOD_LGUI, X)
#define RG(X) MT(MOD_RGUI, X)
#define RS(X) MT(MOD_RSFT, X)
#define RA(X) MT(MOD_RALT, X)
#define RC(X) MT(MOD_RCTL, X)
#define FUN_CAPS LT(_FUNCTION, KC_CAPS)
#define PUN_BS LT(_PUNCUATION, KC_BSPC)
// macOS shortcut
#define MSNCTL  C(KC_DOWN)
#define WKSPLF  C(KC_LEFT)
#define WKSPRT  C(KC_RGHT)
#define COPY    G(KC_C)
#define PSTE    G(KC_V)
#define CUT     G(KC_X)
#define UNDO    G(KC_Z)
#define REDO    G(S(KC_Z))
#define SCNSHOT S(G(KC_4))
// window management utility
#define DIVVY   G(KC_G)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAKDH] LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,             KC_QUOT,          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        LC(KC_A),LA(KC_R),LS(KC_S),LG(KC_T),KC_G,       KC_LBRC,    KC_RBRC,    KC_M,    RG(KC_N),RS(KC_E),RA(KC_I),RC(KC_O),
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MINS, KC_GRV,  KC_EQL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                 KC_ESC,  KC_UP,   KC_DOWN, PUN_BS, FUN_CAPS, KC_ENT,  KC_TAB,  KC_SPC,  KC_LEFT, KC_RGHT, KC_BSLS
    ),
    [_PUNCUATION] LAYOUT(
        KC_PERC, KC_CIRC, KC_AMPR, KC_DLR,  _______,          _______,          _______, KC_7,    KC_8,    KC_9,    KC_PLUS,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_LPRN,    _______,    _______,    KC_RPRN, KC_4,    KC_5,    KC_6,    KC_MINS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_ASTR,
                 _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_COMM, KC_DOT,  KC_SLSH
    ),
    [_FUNCTION] LAYOUT(
        _______, SCNSHOT, DIVVY,   _______, _______,          _______,          _______, _______, KC_UP,   KC_VOLD, KC_VOLU,
        UNDO,    CUT,     COPY,    PSTE,    _______,    _______,    _______,    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,
        REDO,    WKSPLF,  MSNCTL,  WKSPRT,  _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
}
