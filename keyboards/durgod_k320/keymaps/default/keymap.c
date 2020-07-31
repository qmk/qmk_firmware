/* Copyright 2020 kuenhlee
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
#define _BL     0u
#define _FL     1u
#define _SL     2u

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  KC_TGUI = SAFE_RANGE  // Toggle between GUI Lock or Unlock. Currently NOT implemented.
};

enum unicode_names {
  TBD,
};

const uint32_t PROGMEM unicode_map[] = {
  [TBD]   = 0x0000, // NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_ansi_tkl( /* Base Layer */
      KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SLCK,  KC_PAUS,  \
      KC_GRV,	  KC_1,	    KC_2,	    KC_3,	    KC_4,	    KC_5,	    KC_6,	    KC_7,	    KC_8,	    KC_9,	    KC_0,	    KC_MINS,  KC_EQL,		          KC_BSPC,	KC_PGUP,  \
      KC_TAB,	  KC_Q,	    KC_W,	    KC_E,	    KC_R,	    KC_T,	    KC_Y,	    KC_U,	    KC_I,	    KC_O,	    KC_P,	    KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_INS,	  KC_HOME,  \
      KC_CAPS,	KC_A,	    KC_S,	    KC_D,	    KC_F,	    KC_G,	    KC_H,	    KC_J,	    KC_K,	    KC_L,	    KC_SCLN,  KC_QUOT,	          KC_DEL,	  KC_END,	  KC_PGDN,  \
      KC_LSFT,	          KC_Z,	    KC_X,	    KC_C,	    KC_V,	    KC_B,	    KC_N,	    KC_M,	    KC_COMM,	KC_DOT,	  KC_SLSH,	          KC_RSFT,	KC_ENT,	  KC_UP,    \
      KC_LCTL,	KC_LGUI,	KC_LALT,				                        KC_SPC,				                          KC_RALT,	MO(_FL),	KC_APP,	  KC_RCTL,	KC_LEFT,	KC_DOWN,  \
                                                                                                                                                            KC_RGHT   \
  ),

  [_FL] = LAYOUT_ansi_tkl( /* First Layer */
      KC_TRNS,  KC_MPLY,  KC_MSTP,  KC_MRWD,  KC_MFFD,  KC_MUTE,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_CALC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,		        XXXXXXX,	XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,  KC_MSEL,  XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  KC_WHOM,	XXXXXXX,	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,	          XXXXXXX,	XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	          XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	KC_MAIL,  XXXXXXX,	XXXXXXX,  XXXXXXX,	          XXXXXXX,	XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,				                        XXXXXXX,				                        MO(_SL),	KC_TRNS,	XXXXXXX,  XXXXXXX,	XXXXXXX,	XXXXXXX,  \
                                                                                                                                                            XXXXXXX   \
  ),

  [_SL] = LAYOUT_ansi_tkl( /* Second / System Layer */
      XXXXXXX,  KC_SLEP,  XXXXXXX,  XXXXXXX,  KC_PWR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,		        XXXXXXX,	XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,	          XXXXXXX,	XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	          XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,	XXXXXXX,  XXXXXXX,	XXXXXXX,  XXXXXXX,	          XXXXXXX,	XXXXXXX,  XXXXXXX,  \
      XXXXXXX,	XXXXXXX,	XXXXXXX,				                        XXXXXXX,				                        KC_TRNS,	KC_TRNS,	XXXXXXX,  XXXXXXX,	XXXXXXX,	XXXXXXX,  \
                                                                                                                                                            XXXXXXX   \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TGUI:
      if (record->event.pressed) {
        // Nothing to do when keycode KC_TGUI is pressed
      } else {
        // Check the current state of the GUI Lock when keycode KC_TGUI is released
        // Toggle the state and send out the updated Keycode.
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
