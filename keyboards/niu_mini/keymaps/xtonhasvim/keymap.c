 /* Copyright 2015-2017 Christon DeWan
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
#include "action_layer.h"
#include "xtonhasvim.h"

/************************************
 * states
 ************************************/

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOVE,
  _MOUSE
};

/************************************
 * keymaps!
 ************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl*|   A* |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;* |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mouse|      | Alt  | GUI  |Lower*|    Space    |Raise*| GUI  | Alt  |      | Vim  |
 * `-----------------------------------------------------------------------------------'
 *
 * - Ctrl acts as Esc when tapped.
 * - Holding A or ; switches to movement layer.
 * - Raise and Lower are one-shot layers.
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,           KC_W,    KC_E,    KC_R,          KC_T,    KC_Y,    KC_U,          KC_I,    KC_O,    KC_P,              KC_BSPC},
  {LCTL_T(KC_ESC), LT(_MOVE,KC_A), KC_S,    KC_D,    KC_F,          KC_G,    KC_H,    KC_J,          KC_K,    KC_L,    LT(_MOVE,KC_SCLN), KC_QUOT},
  {KC_LSFT, KC_Z,           KC_X,    KC_C,    KC_V,          KC_B,    KC_N,    KC_M,          KC_COMM, KC_DOT,  KC_SLSH,   RSFT_T(KC_ENT) },
  {TG(_MOUSE), X_____X,  KC_LALT, KC_LGUI, OSL(_LOWER),   KC_SPC,  KC_SPC,  OSL(_RAISE),   KC_LGUI, KC_LALT, X_____X, VIM_START }
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Del |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | Next | Vol- | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Bail |      |      |      |             |      |      |      | Bail |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_BSPC},
  {KC_DEL, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  X_____X, KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY},
  {X_____X, TO(_QWERTY), _______, _______, _______, KC_BSPC, KC_BSPC, OSL(_ADJUST),    _______,    _______, TO(_QWERTY), X_____X}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Del |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | Next | Vol- | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Bail |      |      |      |             |      |      |      | Bail |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSPC},
  {KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY},
  {X_____X, TO(_QWERTY), _______, _______, OSL(_ADJUST), X_____X, X_____X, _______, _______, _______, TO(_QWERTY), X_____X}
},


/* Adjust (Lower + Raise)
 * ,-------------------------------------------------------------------------------------.
 * |RGBPlain| Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |--------+------+------+------+------+-------------+------+------+------+------+------|
 * |RGBMode-|      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |Lite+ |
 * |--------+------+------+------+------+------|------+------+------+------+------+------|
 * |RGBMode+|Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |Lite- |
 * |--------+------+------+------+------+------+------+------+------+------+------+------|
 * |  RGB   | Bail |      |      |      |             |      |      |      | Bail |      |
 * `-------------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {RGB_MODE_PLAIN, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL },
  {RGB_MODE_REVERSE, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, RGB_VAI},
  {RGB_MODE_FORWARD, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, RGB_VAD},
  {RGB_TOG, TO(_QWERTY), _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY), X_____X}
},


/* movement layer (hold semicolon)
 */
[_MOVE] = {
  {TO(_QWERTY), X_____X, X_____X, X_____X, X_____X, X_____X, KC_HOME, KC_PGDN, KC_PGUP, KC_END, X_____X, X_____X},
  {_______,     X_____X, LGUI(KC_LBRC), LGUI(LSFT(KC_LBRC)), LGUI(LSFT(KC_RBRC)), LGUI(KC_RBRC), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, X_____X, X_____X},
  {_______,     X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______},
  {X_____X,     TO(_QWERTY), _______, _______, _______, X_____X, X_____X, _______, _______, _______, TO(_QWERTY), X_____X}
},

/* mouse layer
 */
[_MOUSE] = {
  {TO(_QWERTY), X_____X, X_____X, KC_MS_UP, X_____X, X_____X, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, X_____X, X_____X  },
  {_______,     X_____X, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, X_____X, X_____X, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, X_____X, X_____X},
  {_______,     X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______},
  {_______,     TO(_QWERTY), _______, _______, _______, X_____X, X_____X, _______, _______, _______, TO(_QWERTY), X_____X}
},

/* vim edit mode. just has an escape -> _CMD key */
[_EDIT] = {
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {VIM_START,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     TO(_QWERTY), _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY), _______}
},

/* vim command layer.
 */
[_CMD] = {
  {X_____X, X_____X, VIM_W, VIM_E, X_____X, X_____X, VIM_Y, VIM_U, VIM_I, VIM_O, VIM_P, X_____X},
  {VIM_ESC,    VIM_A, VIM_S, VIM_D, X_____X, VIM_G, VIM_H, VIM_J, VIM_K, VIM_L, X_____X, X_____X},
  {VIM_SHIFT,     X_____X, VIM_X, VIM_C, VIM_V, VIM_B, X_____X, X_____X, VIM_COMMA, VIM_PERIOD, X_____X, VIM_SHIFT},
  {X_____X,     TO(_QWERTY), _______, _______, X_____X, X_____X, X_____X, X_____X, _______, _______, TO(_QWERTY), X_____X}
}

};

/** Set just 4 LEDs closest to the user. Slightly less annoying to bystanders.*/
void rgbflag(uint8_t r, uint8_t g, uint8_t b) {
  for(int i = 0; i < RGBLED_NUM; i++){
    switch(i) {
      case 9 ... 12:
        // rgblight_setrgb_at(r,g,b,i);
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
        break;
      default:
        // rgblight_setrgb_at(0,0,0,i);
        led[i].r = 0;
        led[i].g = 0;
        led[i].b = 0;
        break;
    }
  }
  rgblight_set();
}

uint32_t layer_state_set_user(uint32_t state) {
  if(rgblight_get_mode() == 1) {
    switch (biton32(state)) {
    case _RAISE:
    case _LOWER:
    case _ADJUST:
        rgbflag(0x00,  0x00, 0xFF);
        break;
    case _MOVE:
    case _MOUSE:
        rgbflag(0xFF,  0x00, 0x00);
        break;
    case _CMD:
        rgbflag(0x00,  0xFF, 0x00);
        break;
    case _EDIT:
        rgbflag(0x7A,  0x00, 0xFF);
        break;
    default: //  for any other layers, or the default layer
        rgbflag(0x00,  0xFF, 0xFF);
        break;
    }
  }
  return state;
}
