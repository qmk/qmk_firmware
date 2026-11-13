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
#include "wait.h"

#define SCB_AIRCR_VECTKEY_WRITEMAGIC 0x05FA0000

__attribute__((weak)) void bootloader_jump(void) {
    wait_ms(100);
    __BKPT(0);
}

__attribute__((weak)) void mcu_reset(void) {
    /* Ensure all outstanding memory operations complete */
    __DSB();
    __ISB();

    /* Request system reset (preserve PRIGROUP) */
    uint32_t aircr = SCB->AIRCR;
    aircr &= ~SCB_AIRCR_VECTKEY_Msk;
    aircr |= SCB_AIRCR_VECTKEY_WRITEMAGIC;
    aircr |= SCB_AIRCR_SYSRESETREQ_Msk;
    SCB->AIRCR = aircr;

    /* Wait for reset to occur */
    while (true) {
        __NOP();
    }
}
