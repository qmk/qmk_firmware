/* Copyright 2019 /u/KeepItUnder
 * Copyright 2020 Reza Jelveh
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
#include "one2mini.h"

/**
 * @brief   Board-specific bootmagic code.
 * @details We want to avoid entering bootloader without holding two keys.
 *          In this case the Ducky originals - "D" and "L".
 *          These are D {2,3} and L {2,9}
 *          We also need to avoid debounce by scanning twice with delay.
 */
void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();

    uint8_t valMatrixRow = 0U;

    valMatrixRow = matrix_get_row(2);

    if ((valMatrixRow & (1 << 3)) && (valMatrixRow & (1 << 9))) {
        // Jump to bootloader.
        bootloader_jump();
    }

    valMatrixRow = matrix_get_row(3);

    if ((valMatrixRow & (1 << 2)) && (valMatrixRow & (1 << 3))) {
        // Jump to bootloader.
        bootloader_jump();
    }
}
