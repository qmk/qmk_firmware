/* Copyright 2021 MajorKoos <https://github.com/majorkoos>
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

#include "lz_clsm.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "i2c_master.h"
#include "../tinycmdapi.h"

void keyboard_pre_init_kb(void)
{
    /*
    PA  [0:7]   col[0:7]
    PB  [0:7]   col[8:15]
    PC  [0]     SCL
        [1]     SDA
        [2:6]   row[0:6]
    PD  [0]     USB D+- level shifter(high 3.3v, low 5v)
        [1]     PS2 pull-up for CLK
        [2]     CLK[D+]
        [3]     DATA[D-]
        [4:7]   col[16:19]

        signal direction : row -> col
    */
    PORTA   = 0xFF; // pull up
    DDRA    = 0x00; // input
    PORTB   = 0xFF; // pull up
    DDRB    = 0x00; // input
    PORTC   = 0xFF; // pull up
    DDRC	= 0x00; // input
    PORTD   = 0xF1; // col(pull up) D-(pull up) D+(pull up) PS2PU(low) USBSHIFT(high)
    DDRD    = 0x03; // input
    #ifdef WATCHDOG_ENABLE
    wdt_enable(WDTO_2S);
    #endif
    i2c_init();
}

void matrix_scan_kb(void)
{
    #ifdef WATCHDOG_ENABLE
    wdt_reset();
    #endif
    matrix_scan_user();
}
