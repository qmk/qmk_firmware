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

#include <avr/wdt.h>

#define FLASH_SIZE (FLASHEND + 1L)

#if !defined(MCUCSR)
#    if defined(MCUSR)
#        define MCUCSR MCUSR
#    endif
#endif

__attribute__((weak)) void bootloader_jump(void) {
    // Taken with permission of Stephan Baerwolf from https://github.com/tinyusbboard/API/blob/master/apipage.c

    wdt_enable(WDTO_15MS);
    wdt_reset();
    asm volatile("cli                    \n\t"
                 "ldi    r29 ,       %[ramendhi] \n\t"
                 "ldi    r28 ,       %[ramendlo] \n\t"
#if (FLASHEND > 131071)
                 "ldi    r18 ,       %[bootaddrhi]   \n\t"
                 "st     Y+,         r18     \n\t"
#endif
                 "ldi    r18 ,       %[bootaddrme]   \n\t"
                 "st     Y+,     r18     \n\t"
                 "ldi    r18 ,       %[bootaddrlo]   \n\t"
                 "st     Y+,     r18     \n\t"
                 "out    %[mcucsrio],    __zero_reg__    \n\t"
                 "bootloader_startup_loop%=:         \n\t"
                 "rjmp bootloader_startup_loop%=     \n\t"
                 :
                 : [mcucsrio] "I"(_SFR_IO_ADDR(MCUCSR)),
#if (FLASHEND > 131071)
                   [ramendhi] "M"(((RAMEND - 2) >> 8) & 0xff), [ramendlo] "M"(((RAMEND - 2) >> 0) & 0xff), [bootaddrhi] "M"((((FLASH_SIZE - BOOTLOADER_SIZE) >> 1) >> 16) & 0xff),
#else
                   [ramendhi] "M"(((RAMEND - 1) >> 8) & 0xff), [ramendlo] "M"(((RAMEND - 1) >> 0) & 0xff),
#endif
                   [bootaddrme] "M"((((FLASH_SIZE - BOOTLOADER_SIZE) >> 1) >> 8) & 0xff), [bootaddrlo] "M"((((FLASH_SIZE - BOOTLOADER_SIZE) >> 1) >> 0) & 0xff));
}

__attribute__((weak)) void mcu_reset(void) {
    // setup watchdog timeout
    wdt_enable(WDTO_15MS);

    // wait for watchdog timer to trigger
    while (1) {
    }
}
