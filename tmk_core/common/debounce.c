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
#include "debounce.h"
#include "matrix.h"
//Default implementation - no debouncing
__attribute__((weak)) void matrix_debounce_init(void) {}
__attribute__((weak)) void matrix_debounce(void) {}
__attribute__((weak)) matrix_row_t matrix_debounce_get_row(uint8_t row)
{
  return matrix_get_row(row);
}
