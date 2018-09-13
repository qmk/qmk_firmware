/* Copyright 2015-2017 Jack Humbert
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
#include "drashna.h"

#ifdef BACKLIGHT_ENABLE
enum planck_keycodes {
  BACKLIT = NEW_SAFE_RANGE,
};
#else
  #define BACKLIT OSM(MOD_LSFT)
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12_wrapper(
  KC_ESC,  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_BSPC,
  KC_TAB,  _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_QUOT,
  KC_MLSF, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_ENT,
  BACKLIT, OS_LCTL, OS_LALT, OS_LGUI, SP_LWER, BK_LWER, DL_RAIS, ET_RAIS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_COLEMAK] = LAYOUT_ortho_4x12_wrapper(
  KC_ESC,  _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_BSPC,
  KC_TAB,  _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_QUOT,
  KC_MLSF, _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, KC_ENT,
  BACKLIT, OS_LCTL, OS_LALT, OS_LGUI, SP_LWER, BK_LWER, DL_RAIS, ET_RAIS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_DVORAK] = LAYOUT_ortho_4x12_wrapper(
  KC_ESC,  _________________DVORAK_L1_________________, _________________DVORAK_R1_________________, KC_BSPC,
  KC_TAB,  _________________DVORAK_L2_________________, _________________DVORAK_R2_________________, KC_SLSH,
  KC_MLSF, _________________DVORAK_L3_________________, _________________DVORAK_R3_________________, KC_ENT,
  BACKLIT, OS_LCTL, OS_LALT, OS_LGUI, SP_LWER, BK_LWER, DL_RAIS, ET_RAIS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_WORKMAN] = LAYOUT_ortho_4x12_wrapper(
  KC_TAB,  _________________WORKMAN_L1________________, _________________WORKMAN_R1________________, KC_BSPC,
  KC_ESC,  _________________WORKMAN_L2________________, _________________WORKMAN_R2________________, KC_QUOT,
  KC_MLSF, _________________WORKMAN_L3________________, _________________WORKMAN_R3________________, KC_ENT,
  BACKLIT, OS_LCTL, OS_LALT, OS_LGUI, SP_LWER, BK_LWER, DL_RAIS, ET_RAIS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_MODS] = LAYOUT_ortho_4x12_wrapper(
  _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  KC_LSFT, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LOWER] = LAYOUT_ortho_4x12_wrapper(
  KC_TILD, _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_BSPC,
  KC_DEL,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PIPE,
  _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_RAISE] = LAYOUT_ortho_4x12_wrapper(
  KC_GRV,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_BSPC,
  KC_DEL,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
  _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
  _______, _______, _______, _______, _______, _______, _______, _________________RAISE_R3__________________
),

[_ADJUST] = LAYOUT_ortho_4x12_wrapper(
  KC_MAKE, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, KC_RST,
  VRSN,    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, EPRM,
  _______, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, TG_MODS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

#ifdef BACKLIGHT_ENABLE
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
#endif
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
    case BK_LWER:
    case SP_LWER:
    case DL_RAIS:
    case ET_RAIS:
      return false;
    default:
      return true;
  }
}

#ifdef RGB_MATRIX_ENABLE


void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, bool default_layer) {
  rgb_led led;
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    led = g_rgb_leds[i];
    if (led.matrix_co.raw < 0xFF) {
      if (led.modifier) {
          rgb_matrix_set_color( i, red, green, blue );
      }
    }
  }
}

void rgb_matrix_indicators_user(void) {
  uint8_t this_mod = get_mods();
  uint8_t this_led = host_keyboard_leds();
  uint8_t this_osm = get_oneshot_mods();

  switch (biton32(layer_state)) {
    case _RAISE:
      rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, false); break;
    case _LOWER:
      rgb_matrix_layer_helper(0x00, 0xFF, 0x00, false); break;
    case _ADJUST:
      rgb_matrix_layer_helper(0xFF, 0x00, 0x00, false); break;
    default:
      switch (biton32(default_layer_state)) {
        case _QWERTY:
          rgb_matrix_layer_helper(0x00, 0xFF, 0xFF, true); break;
        case _COLEMAK:
          rgb_matrix_layer_helper(0xFF, 0x00, 0xFF, true); break;
        case _DVORAK:
          rgb_matrix_layer_helper(0x00, 0xFF, 0x00, true); break;
        case _WORKMAN:
          rgb_matrix_layer_helper(0xD9, 0xA5, 0x21, true); break;
      }
  }

  switch (biton32(default_layer_state)) {
    case _QWERTY:
      rgb_matrix_set_color(42, 0x00, 0xFF, 0xFF); break;
    case _COLEMAK:
      rgb_matrix_set_color(42, 0xFF, 0x00, 0xFF); break;
    case _DVORAK:
      rgb_matrix_set_color(42, 0x00, 0xFF, 0x00); break;
    case _WORKMAN:
      rgb_matrix_set_color(42, 0xD9, 0xA5, 0x21); break;
  }

  if (this_mod & MODS_SHIFT_MASK || this_led & (1<<USB_LED_CAPS_LOCK) || this_osm & MODS_SHIFT_MASK) {
    rgb_matrix_set_color(24, 0x00, 0xFF, 0x00);
    rgb_matrix_set_color(36, 0x00, 0xFF, 0x00);
  }
  if (this_mod & MODS_CTRL_MASK || this_osm & MODS_CTRL_MASK) {
    rgb_matrix_set_color(25, 0xFF, 0x00, 0x00);
    rgb_matrix_set_color(34, 0xFF, 0x00, 0x00);
    rgb_matrix_set_color(37, 0xFF, 0x00, 0x00);

  }
  if (this_mod & MODS_GUI_MASK || this_osm & MODS_GUI_MASK) {
    rgb_matrix_set_color(39, 0xFF, 0xD9, 0x00);
  }
  if (this_mod & MODS_ALT_MASK || this_osm & MODS_ALT_MASK) {
    rgb_matrix_set_color(38, 0x00, 0x00, 0xFF);
  }
}

void matrix_init_keymap(void) {
  rgblight_mode(RGB_MATRIX_MULTISPLASH);
}
#endif //RGB_MATRIX_INIT
