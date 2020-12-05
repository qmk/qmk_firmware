/* Copyright 2017-2019 Mathias Andersson <wraul@dbox.se>
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
#include "kmac.h"

#define F_ROW_MASK 0b01
#define WASD_MASK 0b10

void backlight_init_ports(void) {
    setPinOutput(B1);
    setPinOutput(B2);
    setPinOutput(B3);
    setPinOutput(B4);
    setPinOutput(D7);
}

/* Backlight pin configuration
 * F-row: High PB1
 * W: Low PB4
 * A: Low PB2
 * S: Low PB3
 * D: Low PD7
 */
void backlight_set(uint8_t level) {
    // F-row
    if (level & F_ROW_MASK) {
        writePinHigh(B1);
    } else {
        writePinLow(B1);
    }

    // WASD
    if (level & WASD_MASK) {
        writePinLow(B2);
        writePinLow(B3);
        writePinLow(B4);
        writePinLow(D7);
    } else {
        writePinHigh(B2);
        writePinHigh(B3);
        writePinHigh(B4);
        writePinHigh(D7);
    }
}
