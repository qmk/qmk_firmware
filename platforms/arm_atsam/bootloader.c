/* Copyright 2017 Fred Sundvik
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

#include "bootloader.h"
#include "samd51j18a.h"
#include "md_bootloader.h"

// Set watchdog timer to reset. Directs the bootloader to stay in programming mode.
void bootloader_jump(void) {
#ifdef KEYBOARD_massdrop_ctrl
    // CTRL keyboards released with bootloader version below must use RAM method. Otherwise use WDT method.
    uint8_t  ver_ram_method[] = "v2.18Jun 22 2018 17:28:08";  // The version to match (NULL terminated by compiler)
    uint8_t *ver_check        = ver_ram_method;               // Pointer to version match string for traversal
    uint8_t *ver_rom          = (uint8_t *)0x21A0;            // Pointer to address in ROM where this specific bootloader version would exist

    while (*ver_check && *ver_rom == *ver_check) {  // While there are check version characters to match and bootloader's version matches check's version
        ver_check++;                                // Move check version pointer to next character
        ver_rom++;                                  // Move ROM version pointer to next character
    }

    if (!*ver_check) {                   // If check version pointer is NULL, all characters have matched
        *MAGIC_ADDR = BOOTLOADER_MAGIC;  // Set magic number into RAM
        NVIC_SystemReset();              // Perform system reset
        while (1) {
        }  // Won't get here
    }
#endif

    WDT->CTRLA.bit.ENABLE = 0;
    while (WDT->SYNCBUSY.bit.ENABLE) {
    }
    while (WDT->CTRLA.bit.ENABLE) {
    }
    WDT->CONFIG.bit.WINDOW   = 0;
    WDT->CONFIG.bit.PER      = 0;
    WDT->EWCTRL.bit.EWOFFSET = 0;
    WDT->CTRLA.bit.ENABLE    = 1;
    while (WDT->SYNCBUSY.bit.ENABLE) {
    }
    while (!WDT->CTRLA.bit.ENABLE) {
    }
    while (1) {
    }  // Wait on timeout
}
