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

#define MAGIC_BOOT 0x544F4F42UL
#define MAGIC_REG *(volatile uint32_t*)0x20004000

void bootloader_jump(void) {
    MAGIC_REG = MAGIC_BOOT;
    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    NVIC_SystemReset();
}

__attribute__((weak)) void enter_bootloader_mode_if_requested(void) {}
