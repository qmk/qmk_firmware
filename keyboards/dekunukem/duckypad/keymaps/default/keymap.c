/*

Default Keymap for dekuNukem/duckyPad QMK firmware

Copyright (C) 2020 Max Bridgland

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define LOGO_SIZE 384

bool rgbToggled = false;

enum layer_codes {
  RGB_LAYER = SAFE_RANGE
};

enum my_keycodes {
    Z0 = SAFE_RANGE, Z1, Z2,
    Z3, Z4, Z5,
    Z6, Z7, Z8,
    Z9, Z10, Z11,
    Z12, Z13, Z14
};

enum layers {
  _DEFAULT,
  _RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  ,=========================================.
  | Numpad 1    | Numpad 2    | Numpad 3    |
  |=========================================|
  | Numpad 4    | Numpad 5    | Numpad 6    |
  |=========================================|
  | Numpad 7    | Numpad 8    | Numpad 9    |
  |=========================================|
  | Numpad .    | Numpad 0    |  Numpad =   |
  |=========================================| ,---------------------.
  |  Numpad -   |  Numpad +   |  Numpad *   | | RGB Menu | Blank    |
  `=========================================' `--------------------'
  */
  [_DEFAULT] = LAYOUT(
      KC_P1, KC_P2, KC_P3,
      KC_P4, KC_P5, KC_P6,
      KC_P7, KC_P8, KC_P9,
      KC_PDOT, KC_P0, KC_PENT,
      KC_PMNS, KC_PPLS, KC_EQL,
      RGB_LAYER, KC_NO
  ),
  /*
  ,=========================================.
  | Plain RGB   | Breathe RGB | Rainbow RGB |
  |=========================================|
  | Swirl RGB   | Speed Down  | Speed Up    |
  |=========================================|
  | Effect Up   | Sat. Down   | Sat. Up     |
  |=========================================|
  | Effect Down | Hue Down    | Hue Up      |
  |=========================================| ,----------------------.
  | Toggle RGB  | Brt. Down   | Brt. Up     | | Norm Menu | Blank    |
  `=========================================' `---------------------'
  */
  [_RGB] = LAYOUT(
      RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW,
      RGB_MODE_SWIRL, RGB_SPD, RGB_SPI,
      RGB_MOD, RGB_SAD, RGB_SAI,
      RGB_RMOD, RGB_HUD, RGB_HUI,
      RGB_TOG, RGB_VAD, RGB_VAI,
      RGB_LAYER, KC_NO
  )
};

static void render_logo(void) {
   static const char PROGMEM ducky_logo[LOGO_SIZE] = {
      0, 0, 0, 0,128,128,128,128,128, 0, 0,252,252,252, 0, 0, 0,128,128,128, 0, 0, 0, 0, 0,128,128,128, 0, 0, 0, 0, 0,128,128,128,128,128, 0, 0, 0, 0, 0,252,252,252, 0, 0, 0, 0, 0,128,128,128,128,128,128, 0, 0, 0, 0, 0, 0,128,128,128,128, 0,248,248,248, 56, 56, 56, 56, 56, 56,120,240,224,192, 0, 0,128,128,128,128,128,128, 0, 0, 0, 0, 0, 0, 0, 0,128,128,128,128,128, 0, 0,252,252,252, 0, 0, 0, 0, 0,232, 24, 24,232, 0, 24, 48, 48, 24, 0,232, 24, 24,232, 0, 0,
      0,248,254,255,143, 7, 3, 3, 3, 7,142,255,255,255, 0, 0, 0,255,255,255, 0, 0, 0, 0, 0,255,255,255, 0,248,254,255,143, 7, 3, 3, 3, 3,143, 7, 2, 0, 0,255,255,255,240,120,252,254,231,131, 1, 0, 1, 7, 63,254,240,192, 0,224,252,127, 31, 3, 0, 0,255,255,255,112,112,112,112,112,112, 56, 63, 31, 15,193,231,243,115, 51, 51, 51, 55,255,255,252, 0, 0,248,254,255,143, 7, 3, 3, 3, 7,142,255,255,255, 0, 0, 0, 0, 0, 21,127,127,252,252,252,253,253,252,252,252,255,255,255, 0, 0,
      0, 0, 3, 7, 15, 15, 14, 14, 14, 7, 3, 15, 15, 15, 0, 0, 0, 3, 7, 15, 15, 14, 14, 6, 3, 15, 15, 15, 0, 0, 3, 7, 7, 15, 14, 14, 14, 14, 7, 7, 2, 0, 0, 15, 15, 15, 0, 0, 0, 1, 3, 15, 15, 12,136,224,224,224,247,127,127, 31, 3, 0, 0, 0, 0, 0, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 15, 14, 14, 14, 6, 3, 15, 15, 15, 0, 0, 0, 3, 7, 15, 15, 14, 14, 14, 7, 3, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 11, 3, 11, 7, 11, 7, 7, 31, 0, 0
   };
   oled_write_raw_P(ducky_logo, LOGO_SIZE);
}

char* make_menu_text(void){
  char *s = malloc((30 * 6) * sizeof(*s));
  int width = 3;
  sprintf(s, "%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s",
    width, MT_0_0, width, MT_0_1, width, MT_0_2,
    width, MT_0_3, width, MT_0_4, width, MT_0_5,
    width, MT_0_6, width, MT_0_7, width, MT_0_8,
    width, MT_0_9, width, MT_0_10, width,MT_0_11,
    width, MT_0_12, width, MT_0_13, width, MT_0_14
  );
  return s;
};

char* make_rgb_text(void){
  char *s = malloc((30 * 6) * sizeof(*s));
  int width = 3;
  sprintf(
    s, "%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s\n%-*s %-*s %-*s",
    width, MT_1_0, width, MT_1_1, width, MT_1_2,
    width, MT_1_3, width, MT_1_4, width, MT_1_5,
    width, MT_1_6, width, MT_1_7, width, MT_1_8,
    width, MT_1_9, width, MT_1_10, width,MT_1_11,
    width, MT_1_12, width, MT_1_13, width, MT_1_14
  );
  return s;
};

bool oled_task_user(void) {
  render_logo();
  oled_set_cursor(0,3);
  if (rgbToggled) {
    char *s = make_rgb_text();
    oled_write_ln_P(s, false);
    free(s);
  } else {
    char *s = make_menu_text();
    oled_write_ln_P(s, false);
    free(s);
  }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_LAYER:
      if (record->event.pressed) {
        if (rgbToggled) {
          rgbToggled = false;
          layer_clear();
        } else {
          rgbToggled = true;
          layer_on(_RGB);
        }
      }
      return false;
    default:
      return true;
  }
  return false;
}
