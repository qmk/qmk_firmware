// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 2 of the License, or (at your option) any later
// version. This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details. You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H
#include <stdio.h>

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

enum layers { BASE, BUTTON, MEDIA, NAV, MOUSE, SYM, NUM, FUN };

void oled_render_layer_state(void) {
  oled_write("Layer: ", false);

  switch (get_highest_layer(layer_state)) {
  case BASE:
    oled_write("Base", false);
    break;
  case BUTTON:
    oled_write("Button", false);
    break;
  case MEDIA:
    oled_write("Media", false);
    break;
  case NAV:
    oled_write("Navigation", false);
    break;
  case MOUSE:
    oled_write("Mouse", false);
    break;
  case SYM:
    oled_write("Symbol", false);
    break;
  case NUM:
    oled_write("Number", false);
    break;
  case FUN:
    oled_write("Function", false);
    break;
  }

  oled_write("\n", false);
}

void oled_render_led_state(void) {
  led_t led_state = host_keyboard_led_state();

  oled_write(led_state.caps_lock ? "CAPS " : "      ", false);
  oled_write(led_state.scroll_lock ? "SCROLL " : "       ", false);
  oled_write("\n", false);
}

void oled_render_mod_state(void) {
  uint8_t mod_state = get_mods();

  oled_write((mod_state & MOD_MASK_SHIFT) ? "SHIFT " : "      ", false);
  oled_write((mod_state & MOD_MASK_CTRL) ? "CTRL " : "     ", false);
  oled_write((mod_state & MOD_MASK_ALT) ? "ALT " : "    ", false);
  oled_write((mod_state & MOD_MASK_GUI) ? "GUI" : "   ", false);
  oled_write("\n", false);
}

static void oled_render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    /* oled_render_layer_state(); */
    /* oled_render_mod_state(); */
    /* oled_render_led_state(); */
    oled_render_logo();
  } else {
    oled_render_logo();
  }
  return false;
}

#endif // OLED_ENABLE
