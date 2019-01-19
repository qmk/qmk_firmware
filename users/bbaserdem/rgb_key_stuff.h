/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bbaserdem.h"
#include "rgb_matrix.h"
#include "color.h"

bool process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record);
uint32_t layer_state_set_rgb_matrix(uint32_t state);
void matrix_init_rgb_matrix(void);
void rgb_matrix_indicators_user(void);
