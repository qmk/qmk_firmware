/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "platform_deps.h"

static void disable_jtag(void) {
// To use PF4-7 (PC2-5 on ATmega32A), disable JTAG by writing JTD bit twice within four cycles.
#if (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);
#elif defined(__AVR_ATmega32A__)
    MCUCSR |= _BV(JTD);
    MCUCSR |= _BV(JTD);
#endif
}

void platform_setup(void) {
    disable_jtag();
}
