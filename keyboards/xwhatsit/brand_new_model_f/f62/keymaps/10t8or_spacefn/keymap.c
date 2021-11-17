/* Copyright 2o2o 10t8or
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
enum tent_layers {
	_DEF,
	_ALTF,
	_FN,
	_SFN
};

// Defines the keycodes used by our macros in process_record_user
enum tent_keycodes {
	REBOOT = SAFE_RANGE,
	MAS_CRM,
	MAS_PRP,
	MAS_RED,
	MAS_GRN,
	MAS_BLU,
	MAS_CYN,
	MAS_MGT,
	MAS_YEL,
	MAS_KEY,
	MAS_WHT,
};

enum tent_custom_keycodes {
	QMKBEST = SAFE_RANGE,
 	QMKURL,
  	QMKOTH,
  	QMKJ2,
  	QMKYM1,
  	QMKYM2,
        QMKYM3,
  	QMKYM4,
  	QMKYM5,
  	QMKYM6,
  	QMKYM7,
  	QMKYM8,
 	QMKYM9
};

/*
MO(layer) - momentarily activates layer. As soon as you let go of the key, the layer is deactivated.
LM(layer, mod) - Momentarily activates layer (like MO), but with modifier(s) mod active. Only supports layers 0-15 and the left modifiers: MOD_LCTL, MOD_LSFT, MOD_LALT, MOD_LGUI (note the use of MOD_ constants instead of KC_). These modifiers can be combined using bitwise OR, e.g. LM(_RAISE, MOD_LCTL | MOD_LALT).
LT(layer, kc) - momentarily activates layer when held, and sends kc when tapped. Only supports layers 0-15.
OSL(layer) - momentarily activates layer until the next key is pressed. See One Shot Keys for details and additional functionality.
OSM(mod) - Momentarily hold down mod. You must use the MOD_* keycodes as shown in Mod Tap, not the KC_* codes
TG(layer) - toggles layer, activating it if it's inactive and vice versa
*/

//extern bool autoshift_enabled;
// KC_ASTG is to enable autoshift (currently toggle with RGB+ESC)
#define _V_V_V_ KC_TRNS
#define LT_END  LT(_FN,   KC_END)
#define LT_SPC  LT(_SFN,  KC_SPC)
#define MT_SLSH RSFT_T(KC_SLSH)
#define MT_UP   RSFT_T(KC_UP)
#define MT_LT   RALT_T(KC_LEFT)
#define MT_DN   RGUI_T(KC_DOWN)
#define MT_RT   RCTL_T(KC_RIGHT)
#define LM_LALT LM(_ALTF, MOD_LALT)
#define OL_LSFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Default */
        //      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        //      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        //      KC_LCTRL,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        //      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(_FN),
        //      KC_CAPS, KC_LGUI, KC_LALT,                   KC_SPC,                                               KC_RALT, KC_NLCK, KC_RCTRL
        /* BASE */
	[_DEF] = LAYOUT_ansi_hhkb_split_shift_regular_backspace(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
		KC_DEL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           \
                OL_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  MT_SLSH,          MT_UP,   LT_END,  \
		KC_LCTL, KC_LGUI, LM_LALT,                   LT_SPC,                                               MT_LT,   MT_DN,   MT_RT    \
	),
        /* LALT-1..10 triggers Alt-F1..10 */
	[_ALTF] = LAYOUT_ansi_hhkb_split_shift_regular_backspace(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
		_______, _______, _V_V_V_,                   _______,                                              _______, _______, _______  \
	),
        /* Additional FN layer for reset, klock, backlight, media, etc. */
	[_FN] = LAYOUT_ansi_hhkb_split_shift_regular_backspace(
		RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
		KC_NLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
                KC_SLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_VOLU, _V_V_V_, \
		QMKOTH,  _______, _______,                   _______,                                              KC_MUTE, KC_VOLD, KC_MPLY  \
	),
        /* Space-FN layer for quick access on 60% */
	[_SFN] = LAYOUT_ansi_hhkb_split_shift_regular_backspace(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  \
		KC_CALC, QMKBEST, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  _______, KC_PSCR, KC_PAUS, KC_BSPC, \
		_______, QMKURL,  _______, _______, _______, _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,          \
                _______, _______, _______, _______, _______, KC_SPC,  KC_PGDN, _______, _______, _______, _______,          KC_PGUP, _______, \
		_______, _______, _______,                   _V_V_V_,                                              KC_HOME, KC_PGDN, KC_END   \
	)
};

/*
void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

bool led_update_user(led_t led_state) {
    return true;
}

*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("ä");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://duckduckgo.com/?q=search\n");
      } else {
        // when keycode QMKURL is released
      }
      break;
    case QMKOTH:
      if (record->event.pressed) {
        SEND_STRING("autocmd filetype yaml setlocal ai ts=2 sw=2 et sts=2 cuc cul" SS_TAP(X_ENTER)); // useful vim yaml mnemonic
      }
      break;
    case QMKJ2:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM1:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM2:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM3:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM4:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM5:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM6:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM7:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
    case QMKYM8:
      if (record->event.pressed) {
        SEND_STRING("--- \n\
"); // .yaml templ
      }
      break;
    case QMKYM9:
      if (record->event.pressed) {
        SEND_STRING(""); // templ
      }
      break;
  }
  return true;
};

