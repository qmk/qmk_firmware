/* Copyright 2017 Wunder
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
#include "xd75.h"
#include "bbaserdem.h"

// Layer shorthand
#define _BASE 0
#define _FUNC 1
#define FUNCT MO(_FUNC)
#define XXX KC_NO
#define RGB_RMD RGB_MODE_REVERSE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = { // QWERTY
  { KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,KC_DEL },
  { KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_HOME,KC_PGUP},
  { KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_BSLS,KC_END, KC_PGDN},
  { KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_NUHH,KC_RSFT,KC_UP,  KC_INS },
  { KC_LCTL,KC_LGUI,KC_LALT,KC_SPC, XXX,    KC_ENT, XXX,    KC_SPC, XXX,    KC_RALT,FUNCT,  KC_CAPS,KC_LEFT,KC_DOWN,KC_RGHT},
 },

[_FUNC] = { // FUNCTION
  { RESET,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_PSCR,KC_INS },
  { BL_BRTG,RGB_RMD,RGB_HUI,RGB_SAI,RGB_VAI,XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX    },
  { BL_STEP,RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    KC_MUTE,XXX    },
  { BL_TOGG,RGB_TOG,XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    XXX,    KC_VOLD,KC_MSTP,KC_VOLU},
  { XXX,    XXX,    XXX,    XXX,    SECRET1,XXX,    SECRET2,XXX,    SECRET3,XXX,    _______,XXX,    KC_MPRV,KC_MPLY,KC_MNXT},
 }
};
