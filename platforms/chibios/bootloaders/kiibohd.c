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

/* Kiibohd Bootloader (MCHCK and Infinity KB) */
#define SCB_AIRCR_VECTKEY_WRITEMAGIC 0x05FA0000

const uint8_t sys_reset_to_loader_magic[] = "\xff\x00\x7fRESET TO LOADER\x7f\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

__attribute__((weak)) void bootloader_jump(void) {
    void *volatile vbat = (void *)VBAT;
    __builtin_memcpy(vbat, (const void *)sys_reset_to_loader_magic, sizeof(sys_reset_to_loader_magic));

    // request reset
    SCB->AIRCR = SCB_AIRCR_VECTKEY_WRITEMAGIC | SCB_AIRCR_SYSRESETREQ_Msk;
}
__attribute__((weak)) void mcu_reset(void) {}
