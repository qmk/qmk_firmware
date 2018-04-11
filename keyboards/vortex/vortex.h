/*
 * Copyright (c) 2018 Charlie Waters
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

#ifndef VORTEX_H
#define VORTEX_H

#include "quantum.h"

#define OVERRIDE

// Microseconds to CPU cycles
#define US2CYC(usec) (((((uint32_t)(usec)) * HT32_CK_AHB_FREQUENCY) + 999999UL) / 1000000UL)

// Sleep for approximately n cpu cycles
static void sleep_cyc(uint32_t n) {
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    uint32_t cnt = DWT->CYCCNT + n;
    while(DWT->CYCCNT < cnt);
}

enum extra_keycodes {
    EX_ECHO = SAFE_RANGE,
    EX_DUMP,
    EX_RESET,
};

void spi_flash_init(void);
void spi_dump(void);

#endif // VORTEX_H
