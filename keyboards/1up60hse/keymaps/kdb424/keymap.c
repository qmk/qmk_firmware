/* Copyright 2018 MechMerlin
   Copyright 2018 kdb424
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

#define _DVORAK 0
#define _RAISE 1

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Enable and configure leader key
#define LEADER_TIMEOUT 500
LEADER_EXTERNS();

//Tap Dance Declarations
enum {
  TD_EQUAL_ENTER= 0
  ,TD_DASH_SLASH
  ,TD_BSLASH_EQUAL
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap for backslash, double tap for equal
  [TD_BSLASH_EQUAL]  = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_EQUAL)
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  RAISE,
  REPROGRAM_MACRO,
  PORTAL_BL
};

// Short codes to make reading easier
#define REPROGR REPROGRAM_MACRO
#define U_ARROW LT(1, KC_U)
#define LSHIFT MT(MOD_LSFT, KC_HOME)
#define RSHIFT MT(MOD_RSFT, KC_END)
#define SFT_INS LSFT(KC_INSERT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT_60_ansi( \
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC,  KC_BSPC, \
		KC_LEAD,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, \
		KC_TAB,    KC_A,    KC_O,    KC_E,    U_ARROW, KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,         KC_ENT,  \
		LSHIFT,     KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,                    RSHIFT,  \
		KC_LCTL, KC_LGUI, MO(1),                   KC_SPC,                                 KC_LEFT,    KC_DOWN,    KC_UP,     KC_RGHT  \
    ),

	[_RAISE] = LAYOUT_60_ansi( \
		REPROGR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,     KC_DEL,  \
		_______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_VOLU, KC_PGUP, \
		_______,   _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD,          KC_PGDN, \
		_______,    _______, _______, _______, _______, _______, _______, _______, _______, SFT_INS, _______,                  RGB_TOG, \
		_______, _______, _______,                 _______,                                KC_RALT,   KC_RGUI, PORTAL_BL,      KC_RCTL \
  )
};

void matrix_init_user(void) {
  wait_ms(500);
  set_unicode_input_mode(UC_LNX);
}

void send_unicode_hex_string(char *istr){
  // Needs to make copy as strtok modifies the string
  char str[strlen(istr)];
  strcpy(str, istr);

  // Replacement for tolower function to avoid unneeded library
  for(char *p = str;*p;++p) *p=*p>0x40&&*p<0x5b?*p|0x60:*p;

	char *ptr = strtok(str, " ");
	while(ptr != NULL){
    unicode_input_start();
    send_string_with_delay(ptr, 0);
	  ptr = strtok(NULL, " ");
    unicode_input_finish();
	}
}

void matrix_scan_user(void) {
  // Leader key definitions
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Vim put
    SEQ_ONE_KEY(KC_P) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_V)));
    }
    // Vim yank
    SEQ_ONE_KEY(KC_Y) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
    }
    // Vim yank yank
    SEQ_TWO_KEYS(KC_Y, KC_Y) {
      SEND_STRING(SS_TAP(X_HOME));
      SEND_STRING(SS_LSFT(SS_TAP(X_END)));
      SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
    }
    // Email
    SEQ_ONE_KEY(KC_E) {
      SEND_STRING("kdb424@gmail.com"SS_TAP(X_TAB));
    }
    // Screenshot
    SEQ_TWO_KEYS(KC_S, KC_S) {
      wait_ms(100);
      SEND_STRING(SS_LGUI(SS_TAP(X_R)));
      wait_ms(100);
      SEND_STRING("scrot");
      wait_ms(10);
      SEND_STRING(SS_TAP(X_ENTER));
    }
    // (ノಠ痊ಠ)ノ彡┻━┻
    SEQ_FOUR_KEYS(KC_F, KC_L, KC_I, KC_P) {
      send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B")
    }
    // ⊙.☉
    SEQ_THREE_KEYS(KC_W, KC_A, KC_T) {
      send_unicode_hex_string("2299 002E 2609")
    }
    // 凸(ﾟДﾟ#)
    SEQ_THREE_KEYS(KC_F, KC_F, KC_F) {
      send_unicode_hex_string("51F8 0028 FF9F 0414 FF9F 0023 0029")
    }
    // （￣^￣）凸
    SEQ_TWO_KEYS(KC_F, KC_F) {
      sund_unicode_hex_string("FF08 FFE3 005E FFE3 FF09 51F8")
    }
    // ╮(￣_￣)╭
    SEQ_THREE_KEYS(KC_M, KC_E, KC_H) {
      send_unicode_hex_string("256E 0028 FFE3 005F FFE3 0029 256D")
    }
    // ( ° ∀ ° )ﾉﾞ
    SEQ_FOUR_KEYS(KC_W, KC_A, KC_V, KC_E) {
      send_unicode_hex_string("0028 0020 00B0 0020 2200 0020 00B0 0020 0029 FF89 FF9E")
    }
    // o(^▽^)o
    SEQ_THREE_KEYS(KC_Y, KC_A, KC_Y) {
      send_unicode_hex_string("006F 0028 005E 25BD 005E 0029 006F")
    }
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PORTAL_BL:
      if (record->event.pressed) {
      rgblight_enable();
      rgblight_setrgb_at (0x00, 0xB9, 0xB9, 0);
      rgblight_setrgb_at (0x00, 0xB9, 0xB9, 1);
      rgblight_setrgb_at (0x00, 0xB9, 0xB9, 2);
      rgblight_setrgb_at (0x00, 0xB9, 0xB9, 3);
      rgblight_setrgb_at (0x00, 0xB9, 0xB9, 4);
      rgblight_setrgb_at (0x00, 0xB9, 0xB9, 5);
      rgblight_setrgb_at (0x00, 0xB9, 0xB9, 6);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 7);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 8);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 9);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 10);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 11);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 12);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 13);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 14);
      rgblight_setrgb_at (0xFF, 0x80, 0x00, 15);
      return false;
      break;

      }

    case REPROGRAM_MACRO:
      if (record->event.pressed) {
      rgblight_enable();
      rgblight_setrgb(255, 255, 255);
      SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)));
      wait_ms(500);
      SEND_STRING("~/qmk_firmware" SS_TAP(X_ENTER));
      wait_ms(100);
      SEND_STRING("make "QMK_KEYBOARD":"QMK_KEYMAP":dfu && exit" SS_TAP(X_ENTER));
      wait_ms(100);
      reset_keyboard();
      return false;
      break;
     }
  }
  return true;
}
void led_set_user(uint8_t usb_led) {

}
