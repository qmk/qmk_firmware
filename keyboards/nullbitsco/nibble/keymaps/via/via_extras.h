/* Copyright 2020 Jay Greco
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

#include "nibble_encoder.h"
#include "via.h"
#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "tmk_core/common/eeprom.h"

enum nibble_keyboard_value_id {
  id_encoder_modes = 0x80,
  id_unused_mode_1,
  id_encoder_custom,
  id_unused_mode_2
};

// Encoder Behavior
extern uint8_t encoder_value,
  encoder_mode,
  enabled_encoder_modes;

void raw_hid_receive_kb(uint8_t *data, uint8_t length),
  encoder_update_kb(uint8_t index, bool clockwise),
  custom_config_load(void),
  via_init_kb(void);