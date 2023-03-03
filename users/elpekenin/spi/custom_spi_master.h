/* Copyright 2020 Nick Brassel (tzarc)
 * Copyright 2023 Pablo Martinez (elpekenin)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <ch.h>
#include <hal.h>
#include <stdbool.h>

#include "gpio.h"
#include "chibios_config.h"

#include "util.h"

#ifdef CUSTOM_SPI_DEBUG
#    include <debug.h>
#    include <print.h>
#    include <wait.h>
#    define spi_dprintf(...) dprintf(__VA_ARGS__)
#else
#    define spi_dprintf(...) do { } while (0)
#endif

#if !defined(SPI_DRIVERS)
#    if defined(SPI_DRIVER)
#        define SPI_DRIVERS { &SPI_DRIVER }
#    else
#        error "Select drivers for SPI"
#    endif
#endif

#define SPI_COUNT (ARRAY_SIZE((SPIDriver* [])SPI_DRIVERS))

#if !defined(SPI_SCK_PINS)
#    if defined(SPI_SCK_PIN)
#        define SPI_SCK_PINS { SPI_SCK_PIN }
#    else
#        error "Select pins for SCK"
#    endif
#endif

#if !defined(SPI_MOSI_PINS)
#    if defined(SPI_MOSI_PIN)
#        define SPI_MOSI_PINS { SPI_MOSI_PIN }
#    else
#        error "Select pins for MOSI"
#    endif
#endif

#ifndef SPI_MISO_PINS
#    if defined(SPI_MISO_PIN)
#        define SPI_MISO_PINS { SPI_MISO_PIN }
#    else
#        error "Select pins for MISO"
#    endif
#endif


#ifndef SPI_SCK_PAL_MODE
#    if defined(USE_GPIOV1)
#        define SPI_SCK_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_SCK_PAL_MODE 5
#    endif
#endif

#ifndef SPI_MOSI_PAL_MODE
#    if defined(USE_GPIOV1)
#        define SPI_MOSI_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_MOSI_PAL_MODE 5
#    endif
#endif

#ifndef SPI_MISO_PAL_MODE
#    if defined(USE_GPIOV1)
#        define SPI_MISO_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_MISO_PAL_MODE 5
#    endif
#endif

typedef int16_t spi_status_t;

#define SPI_STATUS_SUCCESS (0)
#define SPI_STATUS_ERROR (-1)
#define SPI_STATUS_TIMEOUT (-2)

#define SPI_TIMEOUT_IMMEDIATE (0)
#define SPI_TIMEOUT_INFINITE (0xFFFF)

#ifdef __cplusplus
extern "C" {
#endif
void custom_spi_init(uint8_t index);

bool custom_spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor, uint8_t index);

spi_status_t custom_spi_write(uint8_t data, uint8_t index);

spi_status_t custom_spi_read(uint8_t index);

spi_status_t custom_spi_transmit(const uint8_t *data, uint16_t length, uint8_t index);

spi_status_t custom_spi_receive(uint8_t *data, uint16_t length, uint8_t index);

void custom_spi_stop(uint8_t index);
#ifdef __cplusplus
}
#endif

/* TODO: Fix compatibility with single-driver code
 *
 * Perhaps an #ifdef block on spi_master.h to not declare functions when using multi-SPI
 * Then, we could use these aliases to make old code fallback to index 0
 */
// #define spi_init() custom_spi_init(0)
// #define spi_start(cs, lsb, mode, div) custom_spi_start(cs, lsb, mode, div, 0)
// #define spi_write(data) custom_spi_write(data, 0)
// #define spi_read() custom_spi_read(0)
// #define spi_transmit(data, len) custom_spi_transmit(data, len, 0)
// #define spi_receive(data, len) custom_spi_receive(data, len, 0)
