/* Copyright 2021 Stefan Kerkmann
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

#pragma once

#include <cstddef>
#include <string>
#include "keycode_util.hpp"
extern "C" {
#include "keyboard.h"
#include "test_matrix.h"
}

#include <cassert>

typedef uint8_t layer_t;

struct KeymapKey {
    KeymapKey(layer_t layer, uint8_t col, uint8_t row, uint16_t keycode) : layer(layer), position({.col = col, .row = row}), code(keycode), report_code(keycode), name(get_keycode_identifier_or_default(keycode)) {
        validate();
    }

    KeymapKey(layer_t layer, uint8_t col, uint8_t row, uint16_t keycode, uint16_t report_code) : layer(layer), position({.col = col, .row = row}), code(keycode), report_code(report_code), name{get_keycode_identifier_or_default(keycode)} {
        validate();
    }

    void press();
    void release();

    const layer_t  layer;
    const keypos_t position;
    const uint16_t code;
    std::string    name;
    /* Sometimes the keycode does not match the code that is send in the usb report, so we provide it here. */
    const uint16_t report_code;

   private:
    void validate() {
        assert(position.col <= MATRIX_COLS);
        assert(position.row <= MATRIX_ROWS);
    }
    uint32_t timestamp_pressed;
};
