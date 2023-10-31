/*
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
#include "pin_defs.h"
// clang-format off
#define LAYOUT_F_3x5( \
K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09, \
K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19, \
K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29, \
              K32,   K33,   K34,          K35,   K36,   K37 \
) \
LAYOUT_charybdis_3x5( \
K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09, \
K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19, \
K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29, \
              K32,   K33,   K34,          K35,   K36 \
)
// clang-format on

/* Handedness. */
#define MASTER_RIGHT

/* VBUS detection. */
#ifdef USB_VBUS_PIN
#    undef USB_VBUS_PIN
#endif
#define USB_VBUS_PIN GP19

/* SPI & PMW3360 settings. */
#define SPI_DRIVER SPID0
#ifdef SPI_SCK_PIN
#    undef SPI_SCK_PIN
#endif
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#ifdef SPI_MOSI_PIN
#    undef SPI_MOSI_PIN
#endif
#define SPI_MOSI_PIN GP23
#ifdef POINTING_DEVICE_CS_PIN
#    undef POINTING_DEVICE_CS_PIN
#endif
#define POINTING_DEVICE_CS_PIN GP16

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17

#define AUTO_SHIFT_TIMEOUT 250
#define TAPPING_TERM 175

#define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)

#define ENABLE_RGB_MATRIX_SOLID_COLOR
#ifdef RGB_MATRIX_DEFAULT_MODE
#    undef RGB_MATRIX_DEFAULT_MODE
#endif
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT 255
#ifdef RGB_MATRIX_DEFAULT_VAL
#    undef RGB_MATRIX_DEFAULT_VAL
#endif
#define RGB_MATRIX_DEFAULT_VAL 100

#ifdef OS_DETECTION_ENABLE
#    if (os_variant_t == OS_VARIANT_MACOS)
#        define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS
#    else
#        define UNICODE_SELECTED_MODES UNICODE_MODE_WINC
#    endif
#else
#    define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS
#endif

#define PMW33XX_CPI 3000

#ifdef ROTATIONAL_TRANSFORM_ANGLE
#    undef ROTATIONAL_TRANSFORM_ANGLE
#endif
#define ROTATIONAL_TRANSFORM_ANGLE -90