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

#define DBGMCU_KEY_UNLOCK 0x4B5A6978
#define DBGMCU_CMD_RESET 0x1

__IO uint32_t *DBGMCU_KEY = (uint32_t *)DBGMCU_BASE + 0x0CU;
__IO uint32_t *DBGMCU_CMD = (uint32_t *)DBGMCU_BASE + 0x08U;

__attribute__((weak)) void bootloader_jump(void) {
    /* The MTIMER unit of the GD32VF103 doesn't have the MSFRST
     * register to generate a software reset request.
     * BUT instead two undocumented registers in the debug peripheral
     * that allow issueing a software reset. WHO would need the MSFRST
     * register anyway? Source:
     * https://github.com/esmil/gd32vf103inator/blob/master/include/gd32vf103/dbg.h */
    *DBGMCU_KEY = DBGMCU_KEY_UNLOCK;
    *DBGMCU_CMD = DBGMCU_CMD_RESET;
}

__attribute__((weak)) void mcu_reset(void) {
    // Confirmed by karlk90, there is no actual reset to bootloader.
    // This just resets the controller.
    *DBGMCU_KEY = DBGMCU_KEY_UNLOCK;
    *DBGMCU_CMD = DBGMCU_CMD_RESET;
}

/* Jumping to bootloader is not possible from user code. */
void enter_bootloader_mode_if_requested(void) {}
