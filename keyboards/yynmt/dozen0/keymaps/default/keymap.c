/* Copyright 2019 yynmt
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

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base
   * ,-----------------------------------------.
   * |  Cut | Copy |Paste |  Up  |Delete| Bksp |
   * |      |      |      |      |      |Raise |
   * |------+------+------+------+------+------|
   * | Ctrl |Shift | Left | Down |Right |Enter |
   * |      |      |      |      |      |Lower |
   * `-----------------------------------------'
   */
	[_BASE] = LAYOUT(
    LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_UP, KC_DEL, LT(_RAISE,KC_BSPC),
    KC_LCTL, KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, LT(_LOWER,KC_ENT)
  ),

  /* Lower
   * ,-----------------------------------------.
   * |      |      |      | Page |      |      |
   * |      |      |      |  Up  |      |      |
   * |------+------+------+------+------+------|
   * |      |      | Home | Page | End  |      |
   * |      |      |      | Down |      |      |
   * `-----------------------------------------'
   */
  [_LOWER] = LAYOUT(
    _______, _______, _______, KC_PGUP, _______, _______,
    _______, _______, KC_HOME, KC_PGDN, KC_END, _______
  ),

  /* Raise
   * ,-----------------------------------------.
   * |      |      |      |      |      |      |
   * |      |      |      |      |      |      |
   * |------+------+------+------+------+------|
   * |      |      |      |      |      |      |
   * |      |      |      |      |      |      |
   * `-----------------------------------------'
   */
  [_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),

  /* Adjust
   * ,-----------------------------------------.
   * | RGB  | RGB  | RGB  | RGB  | RGB  |      |
   * |Toggle|Mode+ | Hue+ | Sat+ | Val+ |      |
   * |------+------+------+------+------+------|
   * | RGB  | RGB  | RGB  | RGB  | RGB  |      |
   * |Reset |Mode- | Hue- | Sat- | Val- |      |
   * `-----------------------------------------'
   */
  [_ADJUST] = LAYOUT(
    UG_TOGG, UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, _______,
    RGBRST,  UG_PREV, UG_HUED, UG_SATD, UG_VALD, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

int RGB_current_mode;

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  RGB_current_mode = rgblight_config.mode;
  #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        RGB_current_mode = rgblight_config.mode;
      }
      #endif
      break;
  }
  return true;
}
