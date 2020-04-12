/* Copyright 2020 Michele Ferri <zomgsako@gmail.com>
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

#include "quantum.h"
#include "via.h"
#define EEPROM_ENCODER_VALUES (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

enum my_keycodes {
  ENCODER_PRESS = SAFE_RANGE
};

enum encoder_rotation {
    ENCODER_CW = 0,
    ENCODER_CCW
};

uint16_t get_encoder_key(uint8_t rotation);
uint16_t get_custom_encoder_config(uint8_t rotation);
void set_custom_encoder_config(uint8_t rotation, uint16_t new_code);

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT(k0, k1, k2, k3, k4, k5, k7, k8) { \
    { k0, k1, k2, k3, k4, k5, ENCODER_PRESS, k7, k8 } \
}
