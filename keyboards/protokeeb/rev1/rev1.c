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

// Override the matrix read function to include the encoder button
void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    if (current_row == ENCODER_BUTTON_ROW) {
        if (readPin(ENCODER_BUTTON_PIN) == 0) {
            current_matrix[current_row] |= (1 << ENCODER_BUTTON_COL);
        } else {
            current_matrix[current_row] &= ~(1 << ENCODER_BUTTON_COL);
        }
    }
}