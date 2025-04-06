// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

/**
 * \file
 *
 * \defgroup spi_master SPI Master API
 *
 * \brief API to communicate with SPI devices.
 * \{
 */

// Hardware SS pin is defined in the header so that user code can refer to it
#ifdef __AVR__
#    if defined(__AVR_AT90USB162__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#        define SPI_SS_PIN B0
#    elif defined(__AVR_ATmega32A__)
#        define SPI_SS_PIN B4
#    elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#        define SPI_SS_PIN B2
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

typedef struct spi_start_config_t {
    pin_t    slave_pin;
    bool     lsb_first;
    uint8_t  mode;
    uint16_t divisor;
    bool     cs_active_low;
} spi_start_config_t;

/**
 * \brief Initialize the SPI driver. This function must be called only once, before any of the below functions can be called.
 */
void spi_init(void);

/**
 * \brief Start an SPI transaction.
 *
 * \param slavePin The GPIO pin connected to the desired device's `SS` line.
 * \param lsbFirst Determines the endianness of the transmission. If `true`, the least significant bit of each byte is sent first.
 * \param mode The SPI mode to use.
 * \param divisor The SPI clock divisor.
 *
 * \return `true` if the operation was successful, otherwise `false` if the supplied parameters are invalid or the SPI peripheral is already in use.
 */
bool spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor);

bool spi_start_extended(spi_start_config_t *start_config);

/**
 * \brief Write a byte to the selected SPI device.
 *
 * \param data The byte to write.
 *
 * \return `SPI_STATUS_TIMEOUT` if the timeout period elapses, or `SPI_STATUS_SUCCESS`.
 */
spi_status_t spi_write(uint8_t data);

/**
 * \brief Read a byte from the selected SPI device.
 *
 * \return `SPI_STATUS_TIMEOUT` if the timeout period elapses, otherwise the byte read from the device.
 */
spi_status_t spi_read(void);

/**
 * \brief Send multiple bytes to the selected SPI device.
 *
 * \param data A pointer to the data to write from.
 * \param length The number of bytes to write. Take care not to overrun the length of `data`.
 *
 * \return `SPI_STATUS_TIMEOUT` if the timeout period elapses, `SPI_STATUS_ERROR` if some other error occurs, otherwise `SPI_STATUS_SUCCESS`.
 */
spi_status_t spi_transmit(const uint8_t *data, uint16_t length);

/**
 * \brief Receive multiple bytes from the selected SPI device.
 *
 * \param data A pointer to a buffer to read into.
 * \param length The number of bytes to read. Take care not to overrun the length of `data`.
 *
 * \return `SPI_STATUS_TIMEOUT` if the timeout period elapses, `SPI_STATUS_ERROR` if some other error occurs, otherwise `SPI_STATUS_SUCCESS`.
 */
spi_status_t spi_receive(uint8_t *data, uint16_t length);

/**
 * \brief End the current SPI transaction. This will deassert the slave select pin and reset the endianness, mode and divisor configured by `spi_start()`.
 *
 */
void spi_stop(void);

#ifdef __cplusplus
}
#endif

/** \} */
