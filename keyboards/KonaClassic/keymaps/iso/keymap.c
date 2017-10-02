/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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
#include "KonaClassic.h"

// Helpful defines
#define ______ KC_TRNS
#define XXXXXX KC_NO

#define _DEFAULT 0
#define _FN 1

//RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEFAULT] = KEYMAP(
		KC_F1, KC_F2,  KC_ESC,	KC_1,    KC_2,     KC_3,   KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
		KC_F3, KC_F4,  KC_TAB,	KC_Q,    KC_W,     KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT, \
		KC_F5, KC_F6,  KC_CAPS, KC_A,    KC_S,     KC_D,   KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NONUS_HASH,  ______, \
		KC_F7, KC_F8,  KC_LSFT, KC_BSLS,  KC_Z,     KC_X,   KC_C,    KC_V,    KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,   ______, \
		KC_F9, KC_F10, KC_LCTL, KC_LGUI, KC_LALT,  ______,          KC_SPC, ______,                    KC_LALT, KC_RGUI, ______,  MO(_FN), KC_RCTL
	),
	[_FN] = KEYMAP(
		F(4),F(5), KC_TILD, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, RESET, \
		______,  ______,  ______,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
		F(6),F(7), ______,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
		F(8),F(9), ______,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
		F(10),F(11), ______,  ______, ______, ______,         ______, ______,                 ______, ______, ______, ______, ______
	)
};

enum function_id {
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL,
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
    [0]  = ACTION_LAYER_MOMENTARY(2),  // Momentary Fn overlay
    [1]  = ACTION_LAYER_TOGGLE(1),     // Toggle Arrow Layer overlay
    [2]  = ACTION_LAYER_TAP_KEY(2, KC_CAPS), // Tap to toggle caps lock and hold to activate function layer
    [3]  = ACTION_LAYER_TOGGLE(3),     // Toggle Underglow Layer overlay
    [4]  = ACTION_FUNCTION(RGBLED_TOGGLE), //Turn on/off underglow
    [5]  = ACTION_FUNCTION(RGBLED_STEP_MODE), // Change underglow mode
    [6]  = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
    [7]  = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
    [8]  = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
    [9]  = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
    [10] = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
    [11] = ACTION_FUNCTION(RGBLED_DECREASE_VAL),
    [12] = ACTION_FUNCTION(SHIFT_ESC),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

void matrix_scan_user(void) {
};

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case RGBLED_TOGGLE:
      //led operations
      if (record->event.pressed) {
        rgblight_toggle();
        }
        break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        rgblight_increase_hue();
        }
        break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        rgblight_decrease_hue();
        }
        break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        rgblight_increase_sat();
        }
        break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        rgblight_decrease_sat();
        }
        break;
    case RGBLED_INCREASE_VAL:
        if (record->event.pressed) {
          rgblight_increase_val();
        }
        break;
    case RGBLED_DECREASE_VAL:
        if (record->event.pressed) {
          rgblight_decrease_val();
        }
        break;
    case RGBLED_STEP_MODE:
        if (record->event.pressed) {
          rgblight_step();
        }
        break;
    static uint8_t shift_esc_shift_mask;
    // Shift + ESC = ~
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    }
};
