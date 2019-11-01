/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2019 Clueboard
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

#ifndef LED_MATRIX_PINMATRIX_DRIVER_H
#define LED_MATRIX_PINMATRIX_DRIVER_H

void led_matrix_pinmatrix_init_pins(void);
void led_matrix_pinmatrix_set_value(int index, uint8_t value);
void led_matrix_pinmatrix_set_value_all(uint8_t value);
void led_matrix_pinmatrix_flush(void);
void led_matrix_pinmatrix_select_row(uint8_t row);
void led_matrix_pinmatrix_unselect_row(uint8_t row);
void led_matrix_pinmatrix_unselect_rows(void);

#endif  // LED_MATRIX_PINMATRIX_DRIVER_H
