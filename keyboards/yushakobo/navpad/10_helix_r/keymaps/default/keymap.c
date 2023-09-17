/* Copyright 2021 yushakobo
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

#include "navpad_prefs.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] =LAYOUT (
    KC_PSCR,   KC_SCRL,   KC_PAUS,   KC_MUTE,
    KC_INS,    KC_HOME,   KC_PGUP,   KC_ESC,    KC_PSLS,    KC_PAST,   KC_PMNS,                     KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_DEL,
    KC_DEL,    KC_END,    KC_PGDN,   KC_P7,     KC_P8,      KC_P9,     KC_PPLS,                     KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
                                     KC_P4,     KC_P5,      KC_P6,     KC_PPLS,                     KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
    S(KC_TAB), KC_UP,     KC_TAB,    KC_P1,     KC_P2,      KC_P3,     LT(1,KC_PENT), KC_RBRC, 	    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_ENT,
    KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_P0,     KC_P0,      KC_PDOT,   LT(1,KC_PENT), LT(1,KC_SPC),LT(2,KC_ENT),KC_NO,      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT
  ),

  [_FN1] =LAYOUT (
    QK_BOOT,   EE_CLR,    KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NUM,    KC_QUOT,   KC_PEQL,    KC_NO,                       KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_DEL,
    KC_CAPS,   KC_NUM,    KC_SCRL,   S(KC_9),   KC_UP,     S(KC_0),    S(KC_SPC),                   KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_BSPC,
                                     KC_LEFT,   KC_BTN3,   KC_RGHT,    S(KC_SPC),                   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_QUOT,
    KC_TRNS,   S(KC_ENT), KC_TRNS,   KC_BSPC,   KC_DOWN,   KC_DEL,     KC_TRNS,       KC_RBRC,      KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_ENT,
    KC_BTN1,   KC_ENT,    S(KC_SPC),LT(2,KC_SPC),KC_SPC,   KC_COMM,    KC_TRNS,       KC_TRNS,      KC_TRNS,    KC_NO,      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT
  ),

  [_FN2] =LAYOUT (
    RGB_TOG,   RGB_MOD,   RGB_RMOD,  KC_NO,
    RGB_HUI,   RGB_SAI,   RGB_VAI,   KC_NO,     KC_NO,     KC_NO,     KC_NO,                        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    RGB_HUD,   RGB_SAD,   RGB_VAD,   KC_NO,     KC_NO,     KC_NO,     KC_NO,                        KC_BSPC,    KC_DEL,     KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,                        KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_RBRC,       KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_NO,      KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_TRNS,       KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO
  ),

  [_FN3] =LAYOUT (
    KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,                        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,                        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,                        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_RBRC,       KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_TRNS,       KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO
  )
};

#ifdef RGBLIGHT_LAYERS
# define LOCK_COLOR_1 HSV_TEAL

const rgblight_segment_t PROGMEM navpad_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
  {4,  1, LOCK_COLOR_1},
  {15, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad_numlock[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,  1, LOCK_COLOR_1},
  {5,  1, LOCK_COLOR_1},
  {14, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad_scrolllock[] = RGBLIGHT_LAYER_SEGMENTS(
  {2,  1, LOCK_COLOR_1},
  {6,  1, LOCK_COLOR_1},
  {26, 1, LOCK_COLOR_1}
);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, host_keyboard_led_state().caps_lock);
    rgblight_set_layer_state(1, (host_keyboard_led_state().num_lock && IS_LAYER_ON(_BASE)));
    rgblight_set_layer_state(2, host_keyboard_led_state().scroll_lock);
    return true;
}

const rgblight_segment_t* const PROGMEM navpad_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  navpad_capslock,
  navpad_numlock,
  navpad_scrolllock
);

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_WHITE);
    // Enable the LED layers
    rgblight_layers = navpad_rgb_layers;
}
#endif
