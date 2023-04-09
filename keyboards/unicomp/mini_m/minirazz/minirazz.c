/* Copyright 2023 Purdea Andrei
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

#include <hardware/structs/pads_qspi.h>
void board_init(void) {
    /* The following sets the QSPI drive strengths to 2mA with a slow slew rate. */
    for (int gpio=0;gpio<NUM_QSPI_GPIOS;gpio++) {
        pads_qspi_hw->io[gpio] &= ~(PADS_QSPI_GPIO_QSPI_SCLK_DRIVE_BITS | PADS_QSPI_GPIO_QSPI_SCLK_SLEWFAST_BITS);
    }
}
