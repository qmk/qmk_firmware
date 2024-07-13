/* Protokeeb Copyright 2024 A-Tech Officials (@atechofficials)
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

#include "quantum.h"

extern matrix_row_t matrix[]; // Declare the matrix array

void matrix_scan_kb(void) {
    // Read the encoder button state and update the matrix
    if (gpio_read_pin(ENCODER_BUTTON_PIN) == 0) {
        matrix[ENCODER_BUTTON_ROW] |= (1 << ENCODER_BUTTON_COL);
    } else {
        matrix[ENCODER_BUTTON_ROW] &= ~(1 << ENCODER_BUTTON_COL);
    }
}