/* Copyright 2023 Alabastard (@Alabastard-64)
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
#include "pointing_device_modes.h"

/* ----------Handling pointing mode id changes on keypress-------------------------------------------------------- */
void pointing_mode_key_momentary(uint8_t mode_id, bool pressed); // momentary change of pointing mode while button is held
void pointing_mode_key_toggle(uint8_t mode_id, bool pressed);    // toggle pointing mode on/off on keypress
void pointing_mode_key_set_device(uint8_t device, bool pressed); // set current device

/* ----------For builtin keycodes--------------------------------------------------------------------------------- */
bool process_pointing_mode_records(uint16_t keyrecord, keyrecord_t* record); // handle processing of built in keyrecords (in process_record stack)
