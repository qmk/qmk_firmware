/* Copyright 2021 QMK
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

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

typedef int16_t spi_status_t;

#define SPI_STATUS_SUCCESS (0)
#define SPI_STATUS_ERROR (-1)
#define SPI_STATUS_TIMEOUT (-2)

#define SPI_TIMEOUT_IMMEDIATE (0)
#define SPI_TIMEOUT_INFINITE (0xFFFF)

#ifdef __cplusplus
extern "C" {
#endif
void spi_init(void);

bool spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor);

spi_status_t spi_write(uint8_t data);

spi_status_t spi_read(void);

spi_status_t spi_transmit(const uint8_t *data, uint16_t length);

spi_status_t spi_receive(uint8_t *data, uint16_t length);

void spi_stop(void);
#ifdef __cplusplus
}
#endif
