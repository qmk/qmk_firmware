/* Copyright 2026 QMK
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

/*
 * sk32duino bootloader jump stub (SK32F077 / 3Think Cortex-M0).
 *
 * A custom flash bootloader ("sk32duino", VID:PID 1EAF:0003) lives at
 * 0x08000000 and owns the first 16 KB of flash.  The QMK application is
 * linked at 0x08004000.
 *
 * Cortex-M0 has no VTOR, so the bootloader remaps the application vector
 * table into SRAM (SYSCFG CFGR1 MEM_MODE) before jumping to the
 * application.  The first 512 bytes of SRAM (0x20000000..0x200001FF) are
 * therefore reserved and never used by the application.
 *
 * Entering DFU is a two step handshake:
 *   1. bootloader_jump() (QK_BOOT / bootmagic) stores a magic word at
 *      0x200001F0 and performs a system reset.
 *   2. The sk32duino bootloader runs first after the reset, sees the magic,
 *      clears it and stays in USB DFU mode.
 *
 * The magic address/value must match the bootloader source:
 * https://github.com/dadato/sk32duino
 */
#include "bootloader.h"

#include <ch.h>

#define SK32_BOOTLOADER_MAGIC 0x4B32D7A1UL
#define SK32_BOOTLOADER_MAGIC_ADDR ((volatile uint32_t *)0x200001F0UL)

__attribute__((weak)) void bootloader_jump(void) {
    *SK32_BOOTLOADER_MAGIC_ADDR = SK32_BOOTLOADER_MAGIC;
    __DSB();
    NVIC_SystemReset();
    while (true) {
    }
}

__attribute__((weak)) void mcu_reset(void) {
    NVIC_SystemReset();
}

/* The flash bootloader at 0x08000000 examines the magic word on every reset,
 * so the application itself does not need to jump anywhere. */
void enter_bootloader_mode_if_requested(void) {}
