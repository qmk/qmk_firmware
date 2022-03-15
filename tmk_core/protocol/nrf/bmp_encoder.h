/*
Copyright 2020 Sekigon

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
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "apidef.h"

void bmp_encoder_init(bmp_encoder_config_t const* const config);
void bmp_encoder_read(bmp_encoder_config_t const* const config, uint32_t key_event_cnt);

bool encoder_update_kb(int8_t index, bool clockwise);
bool encoder_update_user(int8_t index, bool clockwise);
void encoder_key_interrupt_kb(int8_t index);
void encoder_key_interrupt_user(int8_t index);
void encoder_no_move_kb(int8_t index);
void encoder_no_move_user(int8_t index);
