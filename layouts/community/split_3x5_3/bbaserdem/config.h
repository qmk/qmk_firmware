
/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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

<<<<<<<< HEAD:keyboards/bastardkb/charybdis/3x6/v2/splinky_3/config.h
/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { GP26, GP5, GP4, GP9 }
#define MATRIX_COL_PINS \
    { GP27, GP28, GP21, GP6, GP7, GP8 }

/* Handedness. */
#define MASTER_RIGHT

// To use the handedness pin, resistors need to be installed on the adapter PCB.
// If so, uncomment the following code, and undefine MASTER_RIGHT above.
// #define SPLIT_HAND_PIN GP15
// #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.

/* RGB settings. */
#define RGB_DI_PIN GP0

/* SPI & PMW3360 settings. */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP23
#define POINTING_DEVICE_CS_PIN GP16

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
========
// Split definition; use the following to flash;
//  pro-micro:      avrdude-split-left/right
//  elite-c:        dfu-split-left/right
#define EE_HANDS

#ifdef KEYBOARD_crkbd_rev1
    // Corne overrides
#   ifdef RGBLED_NUM
#   undef RGBLED_NUM
#   endif
#   ifdef DRIVER_LED_TOTAL
#   undef DRIVER_LED_TOTAL
#   endif
#   define RGBLED_NUM 48
#   define DRIVER_LED_TOTAL RGBLED_NUM
#endif // KEYBOARD_crkbd_rev1
>>>>>>>> f271c985ce (Revert "Merge branch 'hex6c-rev2' of https://github.com/mechlovin/qmk_firmware into hex6c-rev2"):layouts/community/split_3x5_3/bbaserdem/config.h
