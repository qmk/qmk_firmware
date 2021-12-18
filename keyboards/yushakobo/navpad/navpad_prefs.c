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

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch (keycode) 
  case TAP_00:
    if (record->event.pressed){
      tap_code(KC_P0);
      tap_code(KC_P0);
      }
    break;
  
  default:
    break;
  }
  return true; 
}

#ifdef RGBLIGHT_LAYERS
# define LOCK_COLOR_1 HSV_TEAL

# if defined(KEYBOARD_yushakobo_navpad_10)

  const rgblight_segment_t PROGMEM navpad_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 1, LOCK_COLOR_1}
  );

  const rgblight_segment_t PROGMEM navpad_numlock[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, LOCK_COLOR_1},
    {5, 1, LOCK_COLOR_1}
  );

  const rgblight_segment_t PROGMEM navpad_scrolllock[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, LOCK_COLOR_1},
    {8, 1, LOCK_COLOR_1}
  );

# elif defined(KEYBOARD_yushakobo_navpad_10_helix_r)

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
    {8,  1, LOCK_COLOR_1},
    {26, 1, LOCK_COLOR_1}
  );
# endif

bool led_update_kb(led_t led_state) {
    if (!led_update_user(led_state)) { return led_state; }

    rgblight_set_layer_state(0, host_keyboard_led_state().caps_lock);
    rgblight_set_layer_state(1, (host_keyboard_led_state().num_lock && IS_LAYER_ON(_BASE)));
    rgblight_set_layer_state(2, host_keyboard_led_state().scroll_lock);

    return led_state;
}

  const rgblight_segment_t* const PROGMEM navpad_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    navpad_capslock,
    navpad_numlock,
    navpad_scrolllock
  );

void keyboard_post_init_kb(void) {
    rgblight_sethsv_noeeprom(HSV_WHITE);
    // Enable the LED layers
    rgblight_layers = navpad_rgb_layers;

    keyboard_post_init_user();
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) { /* Navpad side encoder */
      switch (get_highest_layer(layer_state|default_layer_state)) {
      case _BASE:
        if (clockwise) {
          tap_code16(KC_VOLU);
        } else {
          tap_code16(KC_VOLD);
        }
        break;
      
      case _FN1:
        if (clockwise) {
          rgblight_increase_hue();
        } else {
          rgblight_decrease_hue();
        }
        break;
      
      case _FN2:
        if (clockwise) {
          rgblight_increase_sat();
        } else {
          rgblight_decrease_sat();
        }
        break;

      default:
        break;
      }
    }
    if (index == 1) { /* Helix side encoder */
      switch (get_highest_layer(layer_state|default_layer_state)) {
      case _BASE:
        if (clockwise) {
          tap_code(KC_RBRC);
        } else {
          tap_code(KC_LBRC);
        }
        break;
      
      case _FN1:
        if (clockwise) {
          tap_code16(KC_RPRN);
        } else {
          tap_code16(KC_LPRN);
        }
        break;
      
      case _FN2:
        if (clockwise) {
          tap_code16(KC_RCBR);
        } else {
          tap_code16(KC_LCBR);
        }
        break;

      default:
        break;
      }
    }
    return false;
  }
# endif
#endif
