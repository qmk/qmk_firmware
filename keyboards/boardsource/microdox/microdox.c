/*
Copyright 2022 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef OLED_ENABLE
#include "oled_driver.h"
#include "bitwise.h"
#include "action_layer.h"

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_180;
  return rotation;
}

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
  };
  oled_write_P(qmk_logo, false);
}
static void render_status(void) {
   switch (get_highest_layer(layer_state)) {
    case 0:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("^\n"), false);
      oled_write_P(PSTR("Layer: Base\n"), false);
      break;
    case 1:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("  ^\n"), false);
      oled_write_P(PSTR("Layer: Raise\n"), false);
      break;
    case 2:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("    ^\n"), false);
      oled_write_P(PSTR("Layer: Lower\n"), false);
      break;
    case 3:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("      ^\n"), false);
      oled_write_P(PSTR("Layer: Adjust\n"), false);
      break;
    default:
      oled_write_P(PSTR("B R L A O"), false);
      oled_write_P(PSTR("        ^\n"), false);
      oled_write_P(PSTR("Layer: Other\n"), false);
  }
}

bool oled_task_kb(void) {
  if (!oled_task_user()) { return false; }
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
  return false;
}
#endif

#ifdef ENCODER_ENABLE
#include "encoder.h"
bool encoder_update_kb(uint8_t index, bool clockwise) {
  if (!encoder_update_user(index, clockwise)) { return false; }
  if (index == 0) {
    if (clockwise) {
      tap_code_delay(KC_VOLU, 10);
    } else {
      tap_code_delay(KC_VOLD, 10);  
    }
  } else {
    if (clockwise) {
      tap_code(KC_MNXT);
    } else {
      tap_code(KC_MPRV);
    }
  }
  return true;
}
#endif
