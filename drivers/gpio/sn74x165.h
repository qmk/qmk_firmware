/* Copyright 2022
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

#include <stdint.h>
#include <stdbool.h>

// #include "spi_master.h"

/**
 * Driver for 74x165 8-bit serial or parallel-in/serial-out shift registers.
 * https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf
 */

/*
    The slave select pin of the SN74X165.
    This needs to be a normal GPIO pin_t value, such as B14.
*/
#ifndef SN74X165_SPI_SLAVE_SELECT_PIN
#    error "No chip select pin defined -- missing SN74X165_SPI_SLAVE_SELECT_PIN"
#endif

/*
    The latch pin of the SN74X165.
    This needs to be a normal GPIO pin_t value, such as B15.
*/
#ifndef SN74X165_LATCH_PIN
#    error "No latch pin defined -- missing SN74X165_LATCH_PIN"
#endif

/*
    The clock divisor for SPI to ensure that the MCU is within the
    specifications of the SN74X165 chip. Generally this will be PCLK divided by
    the intended divisor -- check your clock settings and the datasheet of
    your SN74X165.
*/
#ifndef SN74X165_SPI_CLOCK_DIVISOR
#    ifdef __AVR__
#        define SN74X165_SPI_CLOCK_DIVISOR 8
#    else
#        define SN74X165_SPI_CLOCK_DIVISOR 64
#    endif
#endif

/*
    The SPI mode to communicate with the SN74X165.
*/
#ifndef SN74X165_SPI_MODE
#    define SN74X165_SPI_MODE 0
#endif

/*
    Whether or not the SPI communication between the MCU and SN74X165 should be
    LSB-first.
*/
#ifndef SN74X165_SPI_LSBFIRST
#    define SN74X165_SPI_LSBFIRST false
#endif

/*
    How many you use SN74X165 chip aka daisy-chain.
    if you just using 1 chip, you can leave it
*/
#ifndef SN74X165_LENGTH
#    define SN74X165_LENGTH 1
#endif

/*
    Init first.
*/
void sn74x165_init(void);

/*
    Read values.
*/
bool sn74x165_spi_receive(uint8_t* out);