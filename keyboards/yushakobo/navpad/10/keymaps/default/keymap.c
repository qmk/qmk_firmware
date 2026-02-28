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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] =LAYOUT (
    KC_PSCR,   KC_SCRL,   KC_PAUS,   KC_MUTE,
    KC_INS,    KC_HOME,   KC_PGUP,   KC_ESC,    KC_PSLS,    KC_PAST,   KC_PMNS,
    KC_DEL,    KC_END,    KC_PGDN,   KC_P7,     KC_P8,      KC_P9,     KC_PPLS,
                                     KC_P4,     KC_P5,      KC_P6,     KC_PPLS,
    S(KC_TAB), KC_UP,     KC_TAB,    KC_P1,     KC_P2,      KC_P3,     LT(1,KC_PENT),
    KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_P0,     TAP_00,     KC_PDOT,   LT(1,KC_PENT)
  ),

  [_FN1] =LAYOUT (
    QK_BOOT,   EE_CLR,    KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NUM,    KC_QUOT,   KC_PEQL,    KC_NO,
    KC_CAPS,   KC_NUM,    KC_SCRL,   S(KC_9),   KC_UP,     S(KC_0),    S(KC_SPC),
                                     KC_LEFT,   MS_BTN3,   KC_RGHT,    S(KC_SPC),
    KC_TRNS,   S(KC_ENT), KC_TRNS,   KC_BSPC,   KC_DOWN,   KC_DEL,     KC_TRNS,
    MS_BTN1,   KC_ENT,    S(KC_SPC),LT(2,KC_SPC),KC_SPC,   KC_COMM,    KC_TRNS
  ),

  [_FN2] =LAYOUT (
    UG_TOGG,   UG_NEXT,   UG_PREV,   KC_NO,
    UG_HUEU,   UG_SATU,   UG_VALU,   KC_NO,     KC_NO,     KC_NO,     KC_NO,
    UG_HUED,   UG_SATD,   UG_VALD,   KC_NO,     KC_NO,     KC_NO,     KC_NO,
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO
  ),

  [_FN3] =LAYOUT (
    KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO
  )
};

#ifdef RGBLIGHT_LAYERS
# define LOCK_COLOR_1 HSV_TEAL

const rgblight_segment_t PROGMEM navpad_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
  {4, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad_numlock[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 1, LOCK_COLOR_1},
  {5, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad_scrolllock[] = RGBLIGHT_LAYER_SEGMENTS(
  {2, 1, LOCK_COLOR_1},
  {6, 1, LOCK_COLOR_1}
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
