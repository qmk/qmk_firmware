/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#pragma once

// clang-format off
#if defined(KEYBOARD_bastardkb_dilemma_3x5_2_splinky) || defined (KEYBOARD_bastardkb_dilemma_3x5_2_assembled)
#    include "3x5_2.h"
#elif defined(KEYBOARD_bastardkb_dilemma_3x5_3)
#    include "3x5_3.h"
#else
#    error "Unsuported format"
#endif
// clang-format on

#include "quantum.h"

#ifdef POINTING_DEVICE_ENABLE
#    ifndef NO_DILEMMA_KEYCODES
enum dilemma_keycodes {
#        ifdef VIA_ENABLE
    POINTER_DEFAULT_DPI_FORWARD = USER00,
#        else
    POINTER_DEFAULT_DPI_FORWARD = SAFE_RANGE,
#        endif // VIA_ENABLE
    POINTER_DEFAULT_DPI_REVERSE,
    POINTER_SNIPING_DPI_FORWARD,
    POINTER_SNIPING_DPI_REVERSE,
    SNIPING_MODE,
    SNIPING_MODE_TOGGLE,
    DRAGSCROLL_MODE,
    DRAGSCROLL_MODE_TOGGLE,
    DILEMMA_SAFE_RANGE,
};

#        define DPI_MOD POINTER_DEFAULT_DPI_FORWARD
#        define DPI_RMOD POINTER_DEFAULT_DPI_REVERSE
#        define S_D_MOD POINTER_SNIPING_DPI_FORWARD
#        define S_D_RMOD POINTER_SNIPING_DPI_REVERSE
#        define SNIPING SNIPING_MODE
#        define SNP_TOG SNIPING_MODE_TOGGLE
#        define DRGSCRL DRAGSCROLL_MODE
#        define DRG_TOG DRAGSCROLL_MODE_TOGGLE
#    endif // !NO_DILEMMA_KEYCODES

/** \brief Return the current DPI value for the pointer's default mode. */
uint16_t dilemma_get_pointer_default_dpi(void);

/**
 * \brief Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to DILEMMA_DEFAULT_DPI_CONFIG_STEP.
 *
 * The new value is persisted in EEPROM.
 */
void dilemma_cycle_pointer_default_dpi(bool forward);

/**
 * \brief Same as `dilemma_cycle_pointer_default_dpi`, but do not write to
 * EEPROM.
 *
 * This means that reseting the board will revert the value to the last
 * persisted one.
 */
void dilemma_cycle_pointer_default_dpi_noeeprom(bool forward);

/** \brief Return the current DPI value for the pointer's sniper-mode. */
uint16_t dilemma_get_pointer_sniping_dpi(void);

/**
 * \brief Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to DILEMMA_SNIPING_DPI_CONFIG_STEP.
 *
 * The new value is persisted in EEPROM.
 */
void dilemma_cycle_pointer_sniping_dpi(bool forward);

/**
 * \brief Same as `dilemma_cycle_pointer_sniping_dpi`, but do not write to
 * EEPROM.
 *
 * This means that reseting the board will revert the value to the last
 * persisted one.
 */
void dilemma_cycle_pointer_sniping_dpi_noeeprom(bool forward);

/** \brief Whether sniper-mode is enabled. */
bool dilemma_get_pointer_sniping_enabled(void);

/**
 * \brief Enable/disable sniper mode.
 *
 * When sniper mode is enabled the dpi is reduced to slow down the pointer for
 * more accurate movements.
 */
void dilemma_set_pointer_sniping_enabled(bool enable);

/** \brief Whether drag-scroll is enabled. */
bool dilemma_get_pointer_dragscroll_enabled(void);

/**
 * \brief Enable/disable drag-scroll mode.
 *
 * When drag-scroll mode is enabled, horizontal and vertical pointer movements
 * are translated into horizontal and vertical scroll movements.
 */
void dilemma_set_pointer_dragscroll_enabled(bool enable);
#endif // POINTING_DEVICE_ENABLE
