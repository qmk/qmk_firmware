/*
 * Copyright 2020 Richard Titmuss <richard.titmuss@gmail.com>
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include "torn.h"

__attribute__((weak)) extern const uint16_t PROGMEM encoder_keymaps[][2][2];

const uint16_t encoder_default[2][2] =  { { KC_PGDN, KC_PGUP }, { KC__VOLDOWN, KC__VOLUP } };

/**
 * Tap on encoder updates using the encoder keymap
 */
bool encoder_update_kb(uint8_t index, bool clockwise) {
    // if (!encoder_update_user(index, clockwise)) return false;

    uint16_t code;

    if (encoder_keymaps) {
      uint8_t layer = get_highest_layer(layer_state);
      do {
          code = pgm_read_word(&encoder_keymaps[layer--][index][clockwise]);
      } while (code == KC_TRNS);
    } else {
      code = encoder_default[index][clockwise];
    }

    tap_code16(code);
    return true;
}
