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

#include <NUC123.h>
#include <ch.h>

// this is called by `reset_keyboard()`
__attribute__((weak)) void bootloader_jump(void) {
    // Unlock the registries
    UNLOCKREG();

    // Set boot from LDROM
    FMC->ISPCON |= FMC_ISPCON_BS_Msk;

    NVIC_SystemReset();
}

// this is called by `soft_reset_keyboard()`
__attribute__((weak)) void mcu_reset(void) {
    // Unlock the registries
    UNLOCKREG();

    // Set boot from APROM
    FMC->ISPCON &= ~FMC_ISPCON_BS_Msk;

    NVIC_SystemReset();
}

__attribute__((weak)) void enter_bootloader_mode_if_requested(void) {}
