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

#include "spi_master.h"

/**
 * Driver for SN74HC595 8-bit shift registers with 3-state output registers
 * https://www.ti.com/document-viewer/SN74HC595/datasheet
 * use this as output
 * note: i tested on st32f401cc blackpill, the matrix scan rate performance drop significanly from 28xxHz to 12xxHz.
 */

/*
    The slave select pin of the SN74HC595.
    This needs to be a normal GPIO pin_t value, such as B14.
*/
#ifndef SN74HC595_SPI_SLAVE_SELECT_PIN
#    error "No chip select pin defined -- missing SN74HC595_SPI_SLAVE_SELECT_PIN"
#endif

/*
    The clock divisor for SPI to ensure that the MCU is within the
    specifications of the SN74HC595 chip. Generally this will be PCLK divided by
    the intended divisor -- check your clock settings and the datasheet of
    your SN74HC595.
*/
#ifndef SN74HC595_SPI_CLOCK_DIVISOR
#    ifdef __AVR__
#        define SN74HC595_SPI_CLOCK_DIVISOR 8
#    else
#        define SN74HC595_SPI_CLOCK_DIVISOR 64
#    endif
#endif

/*
    The SPI mode to communicate with the SN74HC595.
*/
#ifndef SN74HC595_SPI_MODE
#    define SN74HC595_SPI_MODE 0
#endif

/*
    Whether or not the SPI communication between the MCU and SN74HC595 should be
    LSB-first.
*/
#ifndef SN74HC595_SPI_LSBFIRST
#    define SN74HC595_SPI_LSBFIRST false
#endif

/*
    How many you use SN74HC595 chip aka daisy-chain.
    if you just using 1 chip, you can leave it
*/
#ifndef SN74HC595_LENGTH
#    define SN74HC595_LENGTH 1
#endif

/*
    init first
*/
void sn74hc595_init(void);

/*
    set pin number on sn74hc595
*/
spi_status_t sn74hc595_setPin(uint8_t pin, bool set);

/*
    for easy to use
*/
spi_status_t sn74hc595_set_raw(uint8_t* raw_value);
/*
    set a pin high
*/
spi_status_t sn74hc595_setPinLow(uint8_t pin);

/*
    set a pin high
*/
spi_status_t sn74hc595_setPinLow(uint8_t pin);
/*
    set all pin high
*/
spi_status_t sn74hc595_AllPin_High(void);

/*
    set all pin low
*/
spi_status_t sn74hc595_AllPin_Low(void);
