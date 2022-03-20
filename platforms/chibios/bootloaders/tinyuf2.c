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

// From tinyuf2's board_api.h
#define DBL_TAP_MAGIC 0xF01669EF

// defined by linker script
extern uint32_t _board_dfu_dbl_tap[];
#define DBL_TAP_REG _board_dfu_dbl_tap[0]

__attribute__((weak)) void bootloader_jump(void) {
    DBL_TAP_REG = DBL_TAP_MAGIC;
    NVIC_SystemReset();
}

/* not needed, no two-stage reset */
void enter_bootloader_mode_if_requested(void) {}
