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

#include <ch.h>
#include <hal.h>
#include "wait.h"

extern uint32_t __ram0_end__;

#ifndef STM32_BOOTLOADER_DUAL_BANK
#    define STM32_BOOTLOADER_DUAL_BANK FALSE
#endif

#if STM32_BOOTLOADER_DUAL_BANK
#    include "config_common.h"

#    ifndef STM32_BOOTLOADER_DUAL_BANK_GPIO
#        error "No STM32_BOOTLOADER_DUAL_BANK_GPIO defined, don't know which pin to toggle"
#    endif

#    ifndef STM32_BOOTLOADER_DUAL_BANK_POLARITY
#        define STM32_BOOTLOADER_DUAL_BANK_POLARITY 0
#    endif

#    ifndef STM32_BOOTLOADER_DUAL_BANK_DELAY
#        define STM32_BOOTLOADER_DUAL_BANK_DELAY 100000
#    endif

__attribute__((weak)) void bootloader_jump(void) {
    // For STM32 MCUs with dual-bank flash, and we're incapable of jumping to the bootloader. The first valid flash
    // bank is executed unconditionally after a reset, so it doesn't enter DFU unless BOOT0 is high. Instead, we do
    // it with hardware...in this case, we pull a GPIO high/low depending on the configuration, connects 3.3V to
    // BOOT0's RC charging circuit, lets it charge the capacitor, and issue a system reset. See the QMK discord
    // #hardware channel pins for an example circuit.
    palSetPadMode(PAL_PORT(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_PAD(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_MODE_OUTPUT_PUSHPULL);
#    if STM32_BOOTLOADER_DUAL_BANK_POLARITY
    palSetPad(PAL_PORT(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_PAD(STM32_BOOTLOADER_DUAL_BANK_GPIO));
#    else
    palClearPad(PAL_PORT(STM32_BOOTLOADER_DUAL_BANK_GPIO), PAL_PAD(STM32_BOOTLOADER_DUAL_BANK_GPIO));
#    endif

    // Wait for a while for the capacitor to charge
    wait_ms(100);

    // Issue a system reset to get the ROM bootloader to execute, with BOOT0 high
    NVIC_SystemReset();
}

// not needed at all, but if anybody attempts to invoke it....
void enter_bootloader_mode_if_requested(void) {}

#else

/* This code should be checked whether it runs correctly on platforms */
#    define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
#    define BOOTLOADER_MAGIC 0xDEADBEEF
#    define MAGIC_ADDR (unsigned long *)(SYMVAL(__ram0_end__) - 4)

__attribute__((weak)) void bootloader_jump(void) {
    *MAGIC_ADDR = BOOTLOADER_MAGIC;  // set magic flag => reset handler will jump into boot loader
    NVIC_SystemReset();
}

void enter_bootloader_mode_if_requested(void) {
    unsigned long *check = MAGIC_ADDR;
    if (*check == BOOTLOADER_MAGIC) {
        *check = 0;
        __set_CONTROL(0);
        __set_MSP(*(__IO uint32_t *)STM32_BOOTLOADER_ADDRESS);
        __enable_irq();

        typedef void (*BootJump_t)(void);
        BootJump_t boot_jump = *(BootJump_t *)(STM32_BOOTLOADER_ADDRESS + 4);
        boot_jump();
        while (1)
            ;
    }
}
#endif
