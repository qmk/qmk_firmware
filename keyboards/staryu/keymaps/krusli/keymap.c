/*
Copyright 2018 Kenneth Aloysius

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
#include "action_layer.h"

#include "../../backlight_staryu.h"

enum layers {
  _LAYER0,
  _LAYER1,
  _LAYER2,
  _LAYER3
};

enum custom_keycodes {
  GIT_ADD = SAFE_RANGE,
  GIT_COMMIT,
  GIT_PUSH,
  MUTE,
  DEAFEN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch(keycode) {
			case GIT_ADD:
				SEND_STRING("git add ."SS_TAP(X_ENTER));
        break;
      case GIT_COMMIT:
        SEND_STRING("git commit -m "SS_DOWN(X_LSHIFT)SS_TAP(X_QUOTE)SS_UP(X_LSHIFT));
        break;
      case GIT_PUSH:
        SEND_STRING("git push"SS_TAP(X_ENTER));
        break;
      case MUTE:
        SEND_STRING(SS_LGUI(SS_LSFT("M")));
        break;
      case DEAFEN:
        SEND_STRING(SS_LGUI(SS_LSFT("D")));
        break;
      return false;
		}
	}
	return true;
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = LAYOUT(                 \
             KC_ESC,     TO(_LAYER1), \
    KC_Z,    KC_X,       KC_SPACE     \
  ),
  [_LAYER1] = LAYOUT(                 \
             MUTE,       TO(_LAYER2), \
    GIT_ADD, GIT_COMMIT, GIT_PUSH     \
  ),
  [_LAYER2] = LAYOUT(                 \
             RGB_MOD,    TO(_LAYER3), \
    RGB_TOG, RGB_HUD,    RGB_HUI      \
  ),
  [_LAYER3] = LAYOUT(                 \
             RGB_VAI,    TO(_LAYER0), \
    RGB_SAD, RGB_VAD,    RGB_SAI      \
  )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE ;
}

void matrix_init_user(void) {
  for (int i=0; i<5; i++) {
    backlight_led_on(i);
  }
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
