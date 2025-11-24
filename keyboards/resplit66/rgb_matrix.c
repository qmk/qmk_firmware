/* Copyright 2025 David Girault
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

#include "board.h"
#include "quantum.h"
#include "split_util.h"
#include "rgb_matrix.h"

/* RGB matrix is an optional board placed under the main board. */
#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  uint8_t layer = get_highest_layer(layer_state);
  if (layer > 0) {
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
      for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
        uint8_t index = g_led_config.matrix_co[row][col];
        if (index >= led_min && index < led_max && index != NO_LED &&
            keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
          rgb_matrix_set_color(index, RGB_GREEN);
        }
      }
    }
  }
  return false;
}

/* If our own driver in BSP is enabled, use it. */
#ifdef USE_RGB_LEDS

static void sk6805_init(void) {
  boardRGBLedsOn();
}
static void sk6805_flush(void) {
  boardRGBLedsShow();
}
static void sk6805_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
  boardRGBLedsSetRGB(index, red, green, blue);
}
static void sk6805_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
  unsigned count = boardRGBLedsNum();
  unsigned i;
  for (i = 0; i < count; i++)
    boardRGBLedsSetRGB(i, red, green, blue);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = sk6805_init,
    .flush         = sk6805_flush,
    .set_color     = sk6805_set_color,
    .set_color_all = sk6805_set_color_all,
};

#endif /* USE_RGB_LEDS */


#endif /* RGB_MATRIX_ENABLE */
