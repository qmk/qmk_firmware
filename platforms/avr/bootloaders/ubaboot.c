/* Copyright 2023 Raster Software Vigo
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
#include <avr/wdt.h>

void bootloader_jump(void) {
    /* According to the documentation, user code can enter the bootloader by
     *   - disabling interrupts
     *   - resetting the USB and PLL registers to reset values
     *   - setting SPL, SPH to the top of SRAM
     *   - setting MCUSR to zero
     *   - jumping to the beginning of the bootloader
     */

    asm volatile("cli\n\t"
                 "ldi r16, 0x0A\n\t"
                 "out 0x3E, r16\n\t" // SPH <- 0x0A
                 "ldi r16, 0xFF\n\t"
                 "out 0x3D, r16\n\t" // SPL <- 0xFF
                 "ldi r16, 0x00\n\t"
                 "out 0x34, r16\n\t" // MCUSR <- 0x00
                 "sts 0xDA, r16\n\t" // USBINT <- 0x00
                 "sts 0xD7, r16\n\t" // UHWCON <- 0x00
                 "sts 0xE2, r16\n\t" // UDIEN <- 0x00
                 "ldi r16, 0x20\n\t"
                 "sts 0xD8, r16\n\t" // USBCON <- 0x20
                 "jmp 0x7E00\n\t");
}

void mcu_reset(void) {
    // setup watchdog timeout
    wdt_enable(WDTO_60MS);

    // wait for watchdog timer to trigger
    while (1) {
    }
}
