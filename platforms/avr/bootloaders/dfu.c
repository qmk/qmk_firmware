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
#include <util/delay.h>

#define FLASH_SIZE (FLASHEND + 1L)

/** \brief Entering the Bootloader via Software
 *
 * http://www.fourwalledcubicle.com/files/LUFA/Doc/120730/html/_page__software_bootloader_start.html
 */
#define BOOTLOADER_RESET_KEY 0xB007B007
uint32_t reset_key __attribute__((section(".noinit,\"aw\",@nobits;")));

__attribute__((weak)) void bootloader_jump(void) {
    UDCON  = 1;
    USBCON = (1 << FRZCLK);  // disable USB
    UCSR1B = 0;
    _delay_ms(5);  // 5 seems to work fine

    // watchdog reset
    reset_key = BOOTLOADER_RESET_KEY;
    wdt_enable(WDTO_250MS);
    for (;;)
        ;
}

/* this runs before main() */
void bootloader_jump_after_watchdog_reset(void) __attribute__((used, naked, section(".init3")));
void bootloader_jump_after_watchdog_reset(void) {
    if ((MCUSR & (1 << WDRF)) && reset_key == BOOTLOADER_RESET_KEY) {
        reset_key = 0;

        ((void (*)(void))((FLASH_SIZE - BOOTLOADER_SIZE) >> 1))();
    }
}
