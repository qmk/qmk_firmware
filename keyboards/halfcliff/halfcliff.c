/* Copyright 2021 n2
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

#include "quantum.h"

#ifdef OLED_ENABLE

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _DEFAULT = 0,
    _RAISE,
    _LOWER,
    _ADJUST
/*    _FN */
};

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}
oled_rotation_t oled_init_kb(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
  if (!is_keyboard_master()) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
  } else {
      // Host Keyboard Layer Status
      oled_write_P(PSTR("Layer: "), false);
      switch (get_highest_layer(layer_state)) {
          case _DEFAULT:
              oled_write_P(PSTR("DEFAULT\n"), false);
              break;
          case _RAISE:
              oled_write_P(PSTR("RAISE\n"), false);
              break;
          case _LOWER:
              oled_write_P(PSTR("LOWER\n"), false);
          break;
          case _ADJUST:
              oled_write_P(PSTR("ADJUST\n"), false);
          break;
          default:
              // Or use the write_ln shortcut over adding '\n' to the end of your string
          oled_write_ln_P(PSTR("Undefined"), false);
      };
      // Host Keyboard LED Status
      led_t led_state = host_keyboard_led_state();
      oled_write_P(led_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
      oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
      oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK\n") : PSTR("      \n"), false);
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) { /* Left side encoder */
        if (clockwise) {
            tap_code(MS_WHLU);
        } else {
            tap_code(MS_WHLD);
        }
    } else if (index == 1) { /* Right side encoder */
        if (clockwise) {
            tap_code(MS_WHLU);
        } else {
            tap_code(MS_WHLD);
        }
    }
    return true;
}
#endif
