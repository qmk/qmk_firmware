/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#if defined(KEYBOARD_bastardkb_charybdis_lite_3x5)
#include "3x5/3x5.h"
#elif defined(KEYBOARD_bastardkb_charybdis_lite_4x6)
#include "4x6/4x6.h"
#else
#error "Unsuported format"
#endif

#ifdef POINTING_DEVICE_ENABLE
#include "quantum.h"

/** Return the current DPI value for the pointer's default mode. */
uint32_t charybdis_get_pointer_default_dpi(void);

/**
 * Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to CHARYBDIS_DEFAULT_DPI_CONFIG_STEP.
 *
 * The new value is persisted in EEPROM.
 */
void charybdis_cycle_pointer_default_dpi(bool forward);

/**
 * Same as `charybdis_cycle_pointer_default_dpi`, but do not write to EEPROM.
 *
 * This means that reseting the board will revert the value to the last
 * persisted one.
 */
void charybdis_cycle_pointer_default_dpi_noeeprom(bool forward);

/** Return the current DPI value for the pointer's sniper-mode. */
uint32_t charybdis_get_pointer_sniping_dpi(void);

/**
 * Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to CHARYBDIS_SNIPING_DPI_CONFIG_STEP.
 *
 * The new value is persisted in EEPROM.
 */
void charybdis_cycle_pointer_sniping_dpi(bool forward);

/**
 * Same as `charybdis_cycle_pointer_sniping_dpi`, but do not write to EEPROM.
 *
 * This means that reseting the board will revert the value to the last
 * persisted one.
 */
void charybdis_cycle_pointer_sniping_dpi_noeeprom(bool forward);

/** Whether sniper-mode is enabled. */
bool charybdis_get_pointer_sniping_enabled(void);

/**
 * Enable/disable sniper mode (decrease dpi to slow down the pointer for more
 * accurate movements).
 */
void charybdis_set_pointer_sniping_enabled(bool enable);

/** Whether drag-scroll is enabled. */
bool charybdis_get_pointer_dragscroll_enabled(void);

/**
 * Enable/disable drag-scroll mode (pointer movements scroll horizontally and
 * vertically instead of moving the pointer's position).
 */
void charybdis_set_pointer_dragscroll_enabled(bool enable);

/**
 * Process raw mouse report from sensor, ie. `pointing_device_get_report()`.
 */
void process_mouse_report(report_mouse_t* mouse_report);

/**
 * Process PMW report, and update mouse report accordingly.
 *
 * This function is called by `process_mouse_report(report_mouse_t*)` to augment
 * the mouse report.
 *
 * `mouse_report.x` and `mouse_report.y` need to be normalized to HID size, ie.
 *     (-127 <= x <= 127) and (-127 <= y <= 127)
 */
void process_pmw_report(report_mouse_t* mouse_report, int16_t dx, int16_t dy);
#endif  // POINTING_DEVICE_ENABLE
