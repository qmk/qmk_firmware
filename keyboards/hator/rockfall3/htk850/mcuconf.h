/* Copyright (C) 2024 koosikus
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

#include_next <mcuconf.h>

#undef WB32_USB_HOST_WAKEUP_DURATION
#define WB32_USB_HOST_WAKEUP_DURATION 2

#undef WB32_SERIAL_USE_UART1
#define WB32_SERIAL_USE_UART1 TRUE

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE

// // The interrupt priority of the WS2812 driver must be higher than that of other SPI devices.
// #undef WB32_SPI_QSPI_IRQ_PRIORITY
// #define WB32_SPI_QSPI_IRQ_PRIORITY 9

// #undef WB32_SPI_SPIM2_IRQ_PRIORITY
// #define WB32_SPI_SPIM2_IRQ_PRIORITY 10

#undef WB32_I2C_USE_I2C1
#define WB32_I2C_USE_I2C1 TRUE

/* system clock set to 96Mhz */
#undef WB32_PLLDIV_VALUE
#define WB32_PLLDIV_VALUE 2

#undef WB32_PLLMUL_VALUE
#define WB32_PLLMUL_VALUE 16

#undef WB32_USBPRE
#define WB32_USBPRE WB32_USBPRE_DIV2
