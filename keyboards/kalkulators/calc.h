/* Copyright 2024 georgsnarbuts
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

void countDigitsAndDecimalPlaces(double input, int *wholeDigits, int *decimalPlaces);
void reset_states(void);
void reset_states_after_enter(void);
void display_result(const char* text);
void display_final_result(void);
void into_current_input(double input);
void equals_operation(void);
void plus_operation(void);
void minus_operation(void);
void multiply_operation(void);
void divide_operation(void);
void clear_operation(void);
void process_input(double input);