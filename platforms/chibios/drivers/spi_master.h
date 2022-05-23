// Copyright 2020 Nick Brassel (tzarc)
// Copyright 2022 Stefan Kerkmann (KarlK90)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <ch.h>
#include <hal.h>
#include <stdbool.h>

#include "gpio.h"
#include "chibios_config.h"
#include "spi_lld.h"

typedef enum {
    SPI_STATUS_SUCCESS = 0,
    SPI_STATUS_ERROR   = -1,
    SPI_STATUS_TIMEOUT = -2,
} spi_status_t;

/**======================
 *!    SPI DRIVER
 *========================**/

#if !defined(SPI_DRIVER_LLD)
#    define SPI_DRIVER_LLD SPID2
#endif

#if !defined(SPI_DRIVER)
#    define SPI_DRIVER SPI_DRIVER_LLD
#endif

/**======================
 *!    SPI CLOCK PIN
 *========================**/

#if !defined(SPI_SCK_PIN_LLD)
#    define SPI_SCK_PIN_LLD B13
#endif

#if !defined(SPI_SCK_PIN)
#    define SPI_SCK_PIN SPI_SCK_PIN_LLD
#endif

#if !defined(SPI_SCK_PAL_MODE_LLD)
#    if defined(USE_GPIOV1)
#        define SPI_SCK_PAL_MODE_LLD PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_SCK_PAL_MODE_LLD 5
#    endif
#endif

#if !defined(SPI_SCK_PAL_MODE)
#    define SPI_SCK_PAL_MODE SPI_SCK_PAL_MODE_LLD
#endif

/**======================
 *!    SPI MOSI PIN
 *========================**/

#if !defined(SPI_MOSI_PIN_LLD)
#    define SPI_MOSI_PIN_LLD B15
#endif

#if !defined(SPI_MOSI_PIN)
#    define SPI_MOSI_PIN SPI_MOSI_PIN_LLD
#endif

#if !defined(SPI_MOSI_PAL_MODE_LLD)
#    if defined(USE_GPIOV1)
#        define SPI_MOSI_PAL_MODE_LLD PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_MOSI_PAL_MODE_LLD 5
#    endif
#endif

#if !defined(SPI_MOSI_PAL_MODE)
#    define SPI_MOSI_PAL_MODE SPI_MOSI_PAL_MODE_LLD
#endif

/**======================
 *!    SPI MISO PIN
 *========================**/

#if !defined(SPI_MISO_PIN_LLD)
#    define SPI_MISO_PIN_LLD B14
#endif

#if !defined(SPI_MISO_PIN)
#    define SPI_MISO_PIN SPI_MISO_PIN_LLD
#endif

#if !defined(PI_MISO_PAL_MODE_LLD)
#    if defined(USE_GPIOV1)
#        define SPI_MISO_PAL_MODE_LLD PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_MISO_PAL_MODE_LLD 5
#    endif
#endif

#if !defined(SPI_MISO_PAL_MODE)
#    define SPI_MISO_PAL_MODE SPI_MISO_PAL_MODE_LLD
#endif

void         spi_init(void);
bool         spi_start(const pin_t slave_pin, const bool lsb_first, const uint8_t spi_mode, const uint16_t clock_divisor);
uint8_t      spi_write(uint8_t data);
uint8_t      spi_read(void);
spi_status_t spi_transmit(const uint8_t *data, uint16_t length);
spi_status_t spi_receive(uint8_t *data, uint16_t length);
void         spi_stop(void);

bool    spi_start_lld(SPIConfig *const spi_config, const bool lsb_first, const uint8_t spi_mode, const uint16_t clock_divisor);
int32_t round_clock_divisor(uint16_t clock_divisor);
