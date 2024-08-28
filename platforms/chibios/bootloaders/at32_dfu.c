/* Copyright 2021-2023 QMK
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
#include "util.h"

#include <ch.h>
#include <hal.h>
#include "wait.h"

#ifndef AT32_BOOTLOADER_RAM_SYMBOL
#    define AT32_BOOTLOADER_RAM_SYMBOL __ram0_end__
#endif

extern uint32_t AT32_BOOTLOADER_RAM_SYMBOL;


/* This code should be checked whether it runs correctly on platforms */
#    define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
#    define BOOTLOADER_MAGIC 0xDEADBEEF
#    define MAGIC_ADDR (unsigned long *)(SYMVAL(AT32_BOOTLOADER_RAM_SYMBOL) - 4)

__attribute__((weak)) void bootloader_marker_enable(void) {
    uint32_t *marker = (uint32_t *)MAGIC_ADDR;
    *marker          = BOOTLOADER_MAGIC; // set magic flag => reset handler will jump into boot loader
}

__attribute__((weak)) bool bootloader_marker_active(void) {
    const uint32_t *marker = (const uint32_t *)MAGIC_ADDR;
    return (*marker == BOOTLOADER_MAGIC) ? true : false;
}

__attribute__((weak)) void bootloader_marker_disable(void) {
    uint32_t *marker = (uint32_t *)MAGIC_ADDR;
    *marker          = 0;
}

__attribute__((weak)) void bootloader_jump(void) {
    bootloader_marker_enable();
    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    NVIC_SystemReset();
}

void enter_bootloader_mode_if_requested(void) {
    if (bootloader_marker_active()) {
        bootloader_marker_disable();

        struct system_memory_vector_t {
            uint32_t stack_top;
            void (*entrypoint)(void);
        };
        const struct system_memory_vector_t *bootloader = (const struct system_memory_vector_t *)(AT32_BOOTLOADER_ADDRESS);

        __disable_irq();

#    if defined(QMK_MCU_ARCH_CORTEX_M7)
        SCB_DisableDCache();
        SCB_DisableICache();
#    endif

#    if defined(__MPU_PRESENT) && (__MPU_PRESENT == 1U)
        ARM_MPU_Disable();
#    endif

        SysTick->CTRL = 0;
        SysTick->VAL  = 0;
        SysTick->LOAD = 0;

        // Clear interrupt enable and interrupt pending registers
        for (int i = 0; i < ARRAY_SIZE(NVIC->ICER); i++) {
            NVIC->ICER[i] = 0xFFFFFFFF;
            NVIC->ICPR[i] = 0xFFFFFFFF;
        }

        __set_CONTROL(0);
        __set_MSP(bootloader->stack_top);
        __enable_irq();

        // Jump to bootloader
        bootloader->entrypoint();
        while (true) {
        }
    }
}
