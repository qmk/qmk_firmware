/* Copyright 2020 tominabox1
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

enum layers {
    _QWERTY = 0,
    _NAV_MED,
    _RSYM,
    _LSYM,
    _NUM_FUN,
    _ALWAYS
};

// Left-hand mods
#define GUI_A LGUI_T(KC_A)
#define CTL_S LCTL_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define RSYM_F LT(_RSYM, KC_F)
#define ALT_Z LALT_T(KC_Z)
#define NAVMED MO(_NAV_MED)

// Right-hand mods
#define LSYM_J LT(_LSYM, KC_J)
#define SFT_K RSFT_T(KC_K)
#define CTL_L LCTL_T(KC_L)
#define GUI_SCLN LGUI_T(KC_SCLN)
#define ALT_SLSH LALT_T(KC_SLSH)
#define ALW_SPC LT(_ALWAYS, KC_SPC)
#define NUMFUN MO(_NUM_FUN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,  KC_MPLY,  KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
    GUI_A,  CTL_S,  SFT_D,  RSYM_F, KC_G,            KC_H,   LSYM_J,  SFT_K,  CTL_L,  GUI_SCLN,
    ALT_Z,  KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M, KC_COMM, KC_DOT,  ALT_SLSH,
                            NAVMED, KC_BSPC,         ALW_SPC, NUMFUN
  ),

  [_RSYM] = LAYOUT(
    _______, _______, _______, _______, _______, KC_TRNS, _______, KC_TILD, KC_SLSH, KC_QUOT, _______,
    KC_CIRC, KC_ASTR, KC_AMPR, XXXXXXX, _______,          KC_HASH, KC_MINS, KC_PIPE, KC_DQUO, KC_DLR,
    _______, _______, _______, _______, _______,          _______, KC_UNDS, KC_BSLS, KC_GRV,  _______,
    			       _______, _______,          _______, _______
  ),

  [_LSYM] = LAYOUT(
    _______, _______, _______, _______, _______, KC_TRNS, _______, _______, _______, _______, _______,
    KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,            _______, XXXXXXX, KC_EQL,  KC_PPLS, KC_PERC,
    _______, KC_EXLM, KC_LBRC, KC_RBRC, _______,	  _______, _______, _______, _______, _______,
    			       _______, _______, 	  _______, _______
  ),

  [_NAV_MED] = LAYOUT(
    _______, _______, _______, _______, _______, KC_TRNS,  _______, KC_PGDN, KC_PGUP, _______, KC_DEL,
    KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, _______,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
    _______, KC_VOLD, KC_MUTE, KC_VOLU, _______,           _______, KC_END,  KC_HOME, _______, _______,
			       XXXXXXX, _______, 	   _______, _______
  ),

  [_NUM_FUN] = LAYOUT(
    _______, KC_7,    KC_8,    KC_9,    _______, KC_TRNS, _______, KC_F7,   KC_F8,   KC_F9,   KC_F12,
    KC_0   , KC_4,    KC_5,    KC_6,    _______,	  _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    KC_DOT,  KC_1,    KC_2,    KC_3,    _______,	  _______, KC_F1,   KC_F2,   KC_F3,   KC_F10,
    			       _______, _______,          _______, XXXXXXX
  ),

  [_ALWAYS] = LAYOUT(
    _______, _______, KC_COLN, KC_ESC,  _______, KC_TRNS, _______, _______, _______, _______, RESET,
    _______, KC_PERC, KC_SLSH, KC_ENT,  _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, KC_EXLM, _______,          _______, _______, _______, _______, _______,
    			       _______, KC_TAB,  	  XXXXXXX, _______
  ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
