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

/* Key matrix configuration. */
#define MATRIX_COL_PINS \
    { GP2, GP1, GP29, GP6, GP7, GP8 }

#define MATRIX_ROW_PINS \
    { GP3, GP5, GP4, GP9 }

/* Handedness. */
#define EE_HANDS

/* SPI & PMW3360 settings. */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MISO_PIN GP19
#define SPI_MOSI_PIN GP20
#define PMW33XX_CS_PIN GP10
#define POINTING_DEVICE_CS_PIN GP10

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define POINTING_DEVICE_DEBUG
#define PMW33XX_LIFTOFF_DISTANCE 0x03
