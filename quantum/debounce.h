#pragma once
/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
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


#include "matrix.h"

void debounce_init(uint8_t num_rows); //every debounce algorithm will have unique storage needs.

// raw is the current key state
// cooked is the debounced input/output key state
// changed is true if raw has changed since the last call
void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);

bool debounce_active(void);
