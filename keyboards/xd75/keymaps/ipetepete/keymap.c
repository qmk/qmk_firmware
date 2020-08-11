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


// Layer shorthand
enum layers{
  _QWERTY = 0,
  _LOWER,
  _GAMR,
  _SPCFN,
  _FUN,
};

enum keycodes{
  QWERTY = SAFE_RANGE,
  LO,
  UP,
  SPCFN,
  LED,
  GAMER
};

// Needs clean up, I don't think I'm using all of these
#define ESCCTRL CTL_T(KC_ESC)
#define KC_SPFN LT(_SPCFN, KC_SPC) // press for space, hold for function layer (aka spacefn)
#define ROT_LED M(LED)
#define HYPER MT(MOD_HYPR, KC_ENT)
#define ENTSFT SFT_T(KC_ENT)
#define KC_FUN MO(_FUN)
#define APPTOG LGUI(KC_TAB) // toggles last two apps used
#define APPWIN LGUI(KC_GRV) // toggles app windows (Mac/Linux)
#define SPCRGT LCTL(KC_RGHT) // Switch workspaces
#define SPCLFT LCTL(KC_LEFT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = {
        {KC_GRV,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,  KC_F10,  KC_F11,  KC_F12,    KC_6,   KC_7, KC_8,    KC_9,    KC_0,    KC_BSPC},
        {KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,  KC_F7,   KC_F8,   KC_F9,     KC_Y,   KC_U, KC_I,    KC_O,    KC_P,    KC_BSLS},
        {ESCCTRL, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,  KC_F4,   KC_F5,   KC_F6,     KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT},
        {KC_LSFT, KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,  KC_F1,   KC_F2,   KC_F3,     KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH, ENTSFT},
        {KC_FUN,KC_LALT, KC_LGUI,KC_LCTL,MO(_LOWER), KC_SPFN, KC_HOME, KC_PGDN, KC_END, KC_SPFN, KC_RCTL, KC_RALT, KC_RGUI, HYPER,KC_FUN},
    },
    [_GAMR] = {
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {KC_FUN,KC_LGUI,KC_LALT,KC_LCTL,  KC_SPC,KC_SPFN,KC_LEFT, KC_DOWN, KC_LEFT, KC_SPFN, KC_RCTL, KC_RALT, KC_RGUI, MOD_HYPR,KC_FUN},
    },
    [_LOWER] = {
        {KC_ESC, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______, _______, _______, _______},
        {APPTOG,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_7   , KC_8   , KC_9   , KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  XXXXXXX},
        {APPWIN,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_4   , KC_5   , KC_6   , KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX},
        {_______, _______, _______, _______, _______, KC_PIPE, KC_1   , KC_2   , KC_3   , KC_BSLS, _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, KC_0,    KC_PDOT, KC_EQL ,  _______, _______, _______, _______, _______, _______},
    },
    [_SPCFN] = {
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_MINS,  KC_EQL, KC_DEL},
        {KC_GRV,  _______, _______, KC_PGUP, _______, KC_LBRC, _______, _______, _______, KC_RBRC, _______, KC_UP,   _______, _______, _______},
        {_______, _______, KC_HOME, KC_PGDN, KC_END,  KC_LCBR, _______, _______, _______, KC_RCBR, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______},
        {_______, _______, _______, _______, _______, KC_LPRN, _______, _______, _______,   KC_RPRN, _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______, _______, KC_MUTE, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY},
    },

    [_FUN] = {
        {RESET,   _______,   _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, _______, _______, _______, BL_DEC, BL_INC, BL_ON},
        {_______, QWERTY,_______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, BL_STEP, BL_OFF },
         {_______, _______,   _______, _______, _______, GAMER, _______, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______},
        {KC_NLCK, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______, _______,   _______, _______, _______, _______, AG_NORM, AG_SWAP, _______, _______, _______, _______, _______, _______, _______},
    }
};

const uint16_t PROGMEM fn_actions[] = {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
  if(record->event.pressed){
    switch(keycode){
      // Flip RGB mode on game/qwerty mode
      case QWERTY:
        if(record->event.pressed){
          layer_off(_GAMR);
          layer_on(_QWERTY);
          rgblight_mode(1);
            //rgblight_setrgb(40, 80, 255);
        }
        return true;
      case GAMER:
        if(record->event.pressed){
          layer_on(_GAMR);
          rgblight_mode(10);
            //rgblight_setrgb(255, 40, 40);
        }
        return true;
      default:
        return true;
    }
  }
  return true;
}
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
