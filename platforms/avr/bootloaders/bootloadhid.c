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

#include "bootloader.h"

#include <avr/eeprom.h>
#include <avr/wdt.h>

__attribute__((weak)) void bootloader_jump(void) {
    // force bootloadHID to stay in bootloader mode, so that it waits
    // for a new firmware to be flashed
    // NOTE: this byte is part of QMK's "magic number" - changing it causes the EEPROM to be re-initialized
    // thus every time the device is flashed the EEPROM will be wiped
    eeprom_write_byte((uint8_t *)1, 0x00);

    // watchdog reset
    wdt_enable(WDTO_250MS);
    for (;;)
        ;
}
