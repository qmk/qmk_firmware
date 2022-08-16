/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bbaserdem.h"

// Hook to encoder stuff
bool encoder_update_user(uint8_t index, bool clockwise);
// Complicated code for what the encoder keys do when pressed
bool process_record_encoder(uint16_t keycode, keyrecord_t *record);
// Clear the encoder settings
void reset_encoder_state(void);
// This is so that encoder state is synched between two halves
void housekeeping_task_encoder(void);
// This is purely for oled; should it want to use it
void encoder_state_string(uint8_t index, uint8_t layer, char* buffer);
