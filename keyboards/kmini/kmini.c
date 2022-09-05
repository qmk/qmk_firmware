/* Copyright 2018 Evy Dekkers
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
#include "kmini.h"

void led_init_ports(void) {
    DDRB |= (1<<1); // OUT
    DDRB |= (1<<2); // OUT
    DDRB |= (1<<3); // OUT
}

/* LED pin configuration
 * Caps Lock: Low B1
 * Side1: Low B3
 * Side2: Low B2
 */
