/*
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

#include "mechmini.h"
#include "rgblight.h"
#include "quantum.h"

#define MAX_BRIGHTNESS 15
#define MAX_BRIGHTNESS_IOS 5  // max brightness suitable for iOS devices

#define _BL 0
#define _FN1 1
#define _FN2 2
#define _FN3 3
#define _____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_BL] = KEYMAP(
     KC_ESC,     KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
     KC_TAB,     KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_ENT,
     KC_LSFT,    KC_Z,       KC_X,       KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   MO(_FN2),
     KC_LCTL,    KC_LGUI,    KC_LALT,         _____,         KC_SPC,        _____,                   MO(_FN1), MO(_FN3)
   ),
   [_FN1] = KEYMAP(
     KC_GRAVE,   _____,      KC_UP,      KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_SLCK,  KC_PAUS,  KC_DEL,
     KC_CAPS,    KC_LEFT,    KC_DOWN,    KC_RIGHT, _____,    _____,    _____,    KC_INS,   KC_HOME,  KC_PGUP,  KC_PSCR,
     _____,      _____,      M(0),       M(1),     M(2),     _____,    _____,    KC_END,   KC_PGDN,  _____,    _____,
     _____,      _____,      _____,            _____,        _____,         _____,                   _____,    _____
   ),
   [_FN2] = KEYMAP(
     KC_GRAVE,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
     KC_CAPS,    _____,      _____,      _____,    _____,    KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_MINS,  KC_EQL,   _____,
     _____,      _____,      _____,      _____,    _____,    _____,    _____,    KC_SCLN,  KC_QUOT,  KC_SLSH,  _____,
     _____,      _____,      _____,            _____,        _____,         _____,                   _____,    _____
   ),
   [_FN3] = KEYMAP(
     KC_F1,      KC_F2,      KC_F3,      KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
     _____,      M(3),       M(4),       M(5),     _____,    _____,    _____,    _____,    _____,    _____,    _____,
     _____,      M(6),       _____,      _____,    _____,    _____,    _____,    _____,    _____,    _____,    _____,
     _____,      _____,      _____,            _____,        _____,         _____,                   _____,    _____
   )
};

/**
 * Blank keymap
 [0] = KEYMAP(
   _____,      _____,      _____,      _____,    _____,    _____,    _____,    _____,    _____,    _____,    _____,    _____
   _____,      _____,      _____,      _____,    _____,    _____,    _____,    _____,    _____,    _____,    _____,
   _____,      _____,      _____,      _____,    _____,    _____,    _____,    _____,    _____,    _____,    _____,
   _____,      _____,      _____,            _____,        _____,         _____,                   _____,    _____
 )
 */

uint8_t current_level = 4;
int is_on = 0;

uint8_t r = 0xFF;
uint8_t g = 0xFF;
uint8_t b = 0xFF;

uint8_t max_brightness = MAX_BRIGHTNESS_IOS;

enum macro_id {
  TOGGLE_RGB,
  BRIGHTNESS_DOWN,
  BRIGHTNESS_UP,
  COLOR_1,
  COLOR_2,
  COLOR_3,
  ENABLE_MAX_BRIGHTNESS
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  keyevent_t event = record->event;

  switch (id) {
    case TOGGLE_RGB:
      if (event.pressed) {
       if (!is_on) {
         current_level = 4;
         is_on = 1;
       } else {
         is_on = 0;
       }
      }
    case BRIGHTNESS_DOWN:
      if (event.pressed && current_level > 0) {
        current_level--;
      }
      break;
    case BRIGHTNESS_UP:
      if (event.pressed && current_level < max_brightness) {
        current_level++;
      }
      break;
    case COLOR_1:  // set to pink
      if (event.pressed) {
        r = 0xFF;
        g = 0x81;
        b = 0xC2;
      }
      break;
    case COLOR_2:  // set to cyan
      if (event.pressed) {
        r = 0x00;
        g = 0xE0;
        b = 0xFF;
      }
      break;
    case COLOR_3:  // set to white
      if (event.pressed) {
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
      }
      break;
    case ENABLE_MAX_BRIGHTNESS: // enable all 16 brightness steps
      if (event.pressed) {
        max_brightness = MAX_BRIGHTNESS;
      }
      break;
  }

  return MACRO_NONE;
}

const uint16_t fn_actions[] PROGMEM = {
};

void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b);

uint8_t dim(uint8_t color, uint8_t opacity) {
   return ((uint16_t) color * opacity / 0xFF) & 0xFF;
}

void user_setrgb(uint8_t r, uint8_t g, uint8_t b) {
   uint8_t alpha = current_level * 0x11;
   rgblight_setrgb(dim(r, alpha), dim(g, alpha), dim(b, alpha));
}

void matrix_scan_user(void) {
  if (!is_on) {
    current_level = 0;
    user_setrgb(r, g, b);
  } else {
    user_setrgb(r, g, b);
  }
}
