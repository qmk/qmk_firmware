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
#include QMK_KEYBOARD_H

// Layer shorthand
#define _WO 0
#define _QW 1
#define _NUM 2
#define _SYM 3
#define _FUN 4


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 [_WO] = { /* WORKMAN */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   MO(_FUN),TG(_NUM),TG(_QW),KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_D,    KC_R,    KC_W,   KC_B,   KC_GRV,  KC_LGUI, KC_QUOT, KC_J,   KC_F,   KC_U,    KC_P,    KC_SCLN, KC_BSLS },
  { CTL_T(KC_ESC),KC_A,KC_S,   KC_H,    KC_T,   KC_G,   KC_EQL,  KC_UP,   KC_MINS, KC_Y,   KC_N,   KC_E,    KC_O,    KC_I,    KC_ENT  },
  { KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,   KC_V,   KC_LEFT, KC_DOWN, KC_RGHT, KC_K,   KC_L,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
  { KC_MEH,KC_LGUI,KC_LALT,KC_LEFT,KC_RGHT,LT(_SYM,KC_SPC),LGUI_T(KC_ENT),KC_SPC,LT(_SYM,KC_TAB),KC_BSPC,KC_DOWN,KC_UP,KC_LBRC,KC_RBRC,MO(_SYM)},
 },

 [_QW] = { /* QWERTY */
  { _______,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   _______, _______, _______, KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    _______ },
  { _______,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   _______, _______, _______, KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    _______ },
  { _______,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   _______, _______, _______, KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, _______ },
  { _______,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   _______, _______, _______, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, _______ },
  { _______,  _______, _______, _______, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, _______ },
 },//

 [_NUM] = { /* NUM */
  { _______,  _______, _______, _______, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, _______ },
  { _______,  _______, _______, _______, _______,_______,KC_7,    KC_8,    KC_9, _______,_______,_______, _______, _______, _______ },
  { _______,  _______, _______, _______, _______,_______,KC_4,    KC_5,    KC_6, _______,_______,_______, _______, _______, _______ },
  { _______,  _______, _______, _______, _______,_______,KC_1,    KC_2,    KC_3, _______,_______,_______, _______, _______, _______ },
  { _______,  _______, _______, _______, _______,_______,_______, KC_0, _______, _______,_______,_______, _______, _______, _______ },
 },
 [_SYM] = { /* SYM */
  { _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  _______, _______, _______, KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_DEL, },
  { _______,  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR,KC_ASTR,_______, KC_F11,  KC_F12,  KC_LABK,KC_HOME,KC_UP,   KC_PGUP, KC_ASTR, _______ },
  { _______,  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN,KC_GRV, _______, _______, _______, KC_RABK,KC_LEFT,KC_DOWN, KC_RIGHT,KC_PLUS, _______ },
  { _______,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC,KC_TILD,_______, _______, _______, KC_AMPR,KC_END, KC_DOWN, KC_PGDN, KC_BSLS, _______ },
  { _______,  _______, _______, _______, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, _______ },
 },
 [_FUN] = { /* FUN */
  { _______,  RGB_RMOD,RGB_MOD, RGB_TOG, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, RESET   },
  { _______,  RGB_HUD, RGB_HUI, RGB_MODE_PLAIN, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, _______ },
  { _______,  RGB_SAD, RGB_SAI, _______, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, _______ },
  { _______,  RGB_VAD, RGB_VAI, _______, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, _______ },
  { _______,  _______, _______, _______, _______,_______,_______, _______, _______, _______,_______,_______, _______, _______, _______ },
 }
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

bool CTRLDOWN = false;
bool WINDOWN = false;
bool SHIFTDOWN = false;
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case 0:
            rgblight_setrgb(0,240, 255);
            break;
        case 1:
            rgblight_setrgb(0,255, 100);
            break;
        case 2:
            rgblight_setrgb(10,255, 0);
            break;
        case 3:
            rgblight_setrgb(255,0, 85);
            break;
        case 4:
            rgblight_setrgb(240,255, 0);
            break;
        default:
            // none
            break;
    }
    if ( SHIFTDOWN) {
        rgblight_setrgb(255,255, 255);
        }
    if ( CTRLDOWN) {
        rgblight_setrgb(240,255, 0);
        }
    if ( WINDOWN) {
        rgblight_setrgb(255,255, 255);
        }



};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LGUI:
      if (record->event.pressed) {
        WINDOWN = true;
        } else {
        WINDOWN = false;
      }
      return true;
    case LGUI_T(KC_ENT):
      if (record->event.pressed) {
        WINDOWN = true;
        } else {
        WINDOWN = false;
      }
      return true;
    case CTL_T(KC_ESC):
      if (record->event.pressed) {
        CTRLDOWN = true;
        } else {
        CTRLDOWN = false;
      }
      return true;
    case KC_LSFT:
      if (record->event.pressed) {
        SHIFTDOWN = true;
        } else {
        SHIFTDOWN = false;
      }
      return true;
    case KC_RSFT:
      if (record->event.pressed) {
        SHIFTDOWN = true;
        } else {
        SHIFTDOWN = false;
      }
      return true;
    default:
      return true; // Process all other keycodes normally
  }
};
