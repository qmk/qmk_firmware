/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"

#define _______ KC_TRNS
#define XXX KC_NO

#define _DV 0
#define _TD 1
#define _QW 2
#define _TQ 3
#define _GM 4
#define _MO 5
#define _SY 6
#define _FN 7
#define _MS 8

enum custom_keycodes {
    TUR_A = SAFE_RANGE,
    TUR_C,
    TUR_G,
    TUR_I,
    TUR_O,
    TUR_S,
    TUR_U,
    TUR_TL,
    PHY_HB,
    UNI_LI,
    UNI_WN,
};

// Tap dance
enum {
    ATD = 0,
    ATQ,
};

// Tap dance feature
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Left Ctrl, second one is momentory switch to layer TUR
    [ATD] =  ACTION_TAP_DANCE_DOUBLE( KC_LALT, MO(_TD) )
    ,[ATQ] = ACTION_TAP_DANCE_DOUBLE( KC_LALT, MO(_TQ) )
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Bklt |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Esc |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  Del |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  Tab |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Ctrl |  Alt | Meta | Symb | Enter| Space| Func | Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_DV] = {
  {BL_STEP, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_BSPC },
  {KC_ESC , KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,  KC_DEL  },
  {KC_TAB , KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,  MO(_MO) },
  {KC_LSFT, KC_LCTL, TD(ATD), KC_LGUI, MO(_SY), KC_ENT,  KC_SPC,  MO(_FN), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT }
},
[_TD] = {
  {_______,_______,_______,_______,_______,_______,_______, TUR_G, TUR_C,  _______,_______,_______},
  {_______, TUR_A,  TUR_O, _______, TUR_U,  TUR_I, _______, PHY_HB,_______,_______, TUR_S, _______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______}
},

// Qwerty layover
[_QW] = {
  {_______, KC_Q,  KC_W,  KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   _______},
  {_______, KC_A,  KC_S,  KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,_______},
  {_______, KC_Z,  KC_X,  KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_QUOT,_______},
  {_______,_______,TD(ATQ),_______,_______,_______,_______,_______,_______,_______,_______,_______}
},
[_TQ] = {
  {_______,_______,_______,_______,_______,_______,_______, TUR_U, TUR_I,  TUR_O,  _______,_______},
  {_______, TUR_A, TUR_S,  _______,_______, TUR_G,  PHY_HB,_______,_______,_______,_______,_______},
  {_______,_______,_______, TUR_C, _______,_______,_______,_______,_______,_______,_______,_______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______}
},
// Game layer
[_GM] = {
  { TG(_GM),   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_UP,    KC_GRAVE, KC_7,    KC_8, KC_9,    KC_ESC  },
  { KC_TILDE,  KC_A,    KC_S,    KC_D,    KC_F,   KC_LEFT, KC_DOWN,  KC_RIGHT, KC_4,    KC_5, KC_6,    KC_ENT  },
  { KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,   KC_F1,   KC_COMMA, KC_DOT,   KC_1,    KC_2, KC_3,    KC_RSFT },
  { KC_LALT,   KC_LCTL, KC_EXLM, KC_QUES, _______,KC_SPC,  KC_SPC,   _______,  KC_SLSH, KC_0, KC_RALT, KC_RCTL }
},

// Mouse control layer
[_MO] = {
  { TG(_MO), XXX,           KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,  XXX,            XXX, XXX,     XXX, XXX,          XXX,          XXX        },
  { XXX,     KC_MS_WH_LEFT, KC_MS_LEFT,    KC_MS_BTN3, KC_MS_RIGHT, KC_MS_WH_RIGHT, XXX, XXX,     XXX, XXX,          XXX,          XXX        },
  { XXX,     KC_MS_BTN4,    KC_MS_WH_DOWN, KC_MS_DOWN, KC_MS_WH_UP, KC_MS_BTN5,     XXX, XXX,     XXX, XXX,          XXX,         _______     },
  { XXX,     XXX,           XXX,           XXX,        _______,     XXX,            XXX, _______, XXX, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2}
},

// Symbols layer
[_SY] = {
  {TG(_SY),KC_QUES,KC_LCBR,KC_LBRC,KC_LPRN,KC_BSLS,KC_SLSH,KC_RPRN,KC_RBRC,KC_RCBR,KC_PIPE,TUR_TL },
  {KC_GRV ,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS},
  {KC_TILD,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_PLUS,KC_EQL ,KC_UNDS},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______}
},

// Function layer
[_FN] = {
  {TG(_FN),TG(_QW),   TG(_GM),   MU_ON,     _______,   _______,   _______,UNI_LI, UNI_WN ,KC_WAKE,KC_SLEP,KC_PWR },
  {KC_F1,  KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12 },
  {_______,LCTL(KC_Z),LCTL(KC_Y),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),KC_PSCR,KC_INS, KC_HOME,KC_PGDN,KC_PGUP,KC_END },
  {_______,KC_MUTE,   KC_VOLD,   KC_VOLU,   _______,   _______,   _______,_______,KC_MPRV,KC_MSTP,KC_MPLY,KC_MNXT}
},

// Music layer
[_MS] = {
    { MU_OFF, KC_LCTL, KC_LALT, KC_LGUI, KC_UP, KC_DOWN, MU_MOD, XXX, XXX, XXX, XXX, XXX },
    { XXX,    XXX,     XXX,     XXX,     XXX,   XXX,     XXX,    XXX, XXX, XXX, XXX, XXX },
    { XXX,    XXX,     XXX,     XXX,     XXX,   XXX,     XXX,    XXX, XXX, XXX, XXX, XXX },
    { XXX,    XXX,     XXX,     XXX,     XXX,   XXX,     XXX,    XXX, XXX, XXX, XXX, XXX }
}
};

// Set unicode method to linux.
void matrix_init_user(){
  set_unicode_input_mode(UC_LNX);
}

// User defined keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Check for shift letter
  bool shifted = keyboard_report->mods & MOD_BIT(KC_LSFT);

  switch (keycode) {
    case MU_ON:
      if (record->event.pressed) {
          layer_on(_MS);
      }
      return true;
      break;
    case MU_OFF:
      if (record->event.pressed) {
          layer_off(_MS);
      }
      return true;
      break;
    case TUR_A:
      if (record->event.pressed) {
        if ( shifted ) {
            unicode_input_start();
            register_hex(0x00c2);
            unicode_input_finish();
        } else {
            unicode_input_start();
            register_hex(0x00e2);
            unicode_input_finish();
        }
      }
      return false;
      break;
    case TUR_U:
      if (record->event.pressed) {
        if ( shifted ) {
            unicode_input_start();
            register_hex(0x00dc);
            unicode_input_finish();
        } else {
            unicode_input_start();
            register_hex(0x00fc);
            unicode_input_finish();
        }
      }
      return false;
      break;
    case TUR_I:
      if (record->event.pressed) {
        if ( shifted ) {
            unicode_input_start();
            register_hex(0x0130);
            unicode_input_finish();
        } else {
            unicode_input_start();
            register_hex(0x0131);
            unicode_input_finish();
        }
      }
      return false;
      break;
    case TUR_O:
      if (record->event.pressed) {
        if ( shifted ) {
            unicode_input_start();
            register_hex(0x00d6);
            unicode_input_finish();
        } else {
            unicode_input_start();
            register_hex(0x00f6);
            unicode_input_finish();
        }
      }
      return false;
      break;
    case TUR_S:
      if (record->event.pressed) {
        if ( shifted ) {
            unicode_input_start();
            register_hex(0x015e);
            unicode_input_finish();
        } else {
            unicode_input_start();
            register_hex(0x015f);
            unicode_input_finish();
        }
      }
      return false;
      break;
    case TUR_G:
      if (record->event.pressed) {
        if ( shifted ) {
            unicode_input_start();
            register_hex(0x011e);
            unicode_input_finish();
        } else {
            unicode_input_start();
            register_hex(0x011f);
            unicode_input_finish();
        }
      }
      return false;
      break;
    case TUR_C:
      if (record->event.pressed) {
        if ( shifted ) {
            unicode_input_start();
            register_hex(0x00c7);
            unicode_input_finish();
        } else {
            unicode_input_start();
            register_hex(0x00e7);
            unicode_input_finish();
        }
      }
      return false;
      break;
    case TUR_TL:
      if (record->event.pressed) {
        unicode_input_start();
        register_hex(0x20ba);
        unicode_input_finish();
      }
      return false;
      break;
    case PHY_HB:
      if (record->event.pressed) {
          unicode_input_start();
          register_hex(0x0127);
          unicode_input_finish();
      }
      return false;
      break;
    case UNI_LI:
      if( record->event.pressed ) {
          set_unicode_input_mode(UC_LNX);
      }
      return false;
      break;
    case UNI_WN:
      if( record->event.pressed ) {
          set_unicode_input_mode(UC_WIN);
      }
      return false;
      break;
  }
  return true;
}
