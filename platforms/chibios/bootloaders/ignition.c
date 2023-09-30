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
#include "gpio.h"

#define APP_ADDRESS 0x08002000

__attribute__((weak)) void bootloader_jump(void) {
    // The ignition bootloader is checking for a high signal on A8 for 100ms when powering on the board.
    // Setting both A8 and A9 high will charge the capacitor quickly.
    // Setting A9 low before reset will cause the capacitor to discharge
    // thus making the bootloder unlikely to trigger twice between power cycles.
    setPinOutputPushPull(A9);
    setPinOutputPushPull(A8);
    writePinHigh(A9);
    writePinHigh(A8);
    wait_ms(500);
    writePinLow(A9);

    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    // When resetting the MCU, we want to jump to the application.
    SCB->AIRCR = APP_ADDRESS & 0xFFFF;

    // Set the stack pointer to the applications stack pointer
    __asm__ volatile("msr msp, %0" ::"g"(*(volatile uint32_t *)APP_ADDRESS));

    // Jump to the application
    (*(void (**)())(APP_ADDRESS + 4))();
    while (1)
        ;
}

__attribute__((weak)) void enter_bootloader_mode_if_requested(void) {}