/* Copyright 2020 Nick Brassel (tzarc)
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

/*
    The slave select pin of the EEPROM.
    This needs to be a normal GPIO pin_t value, such as A7.
*/
#ifndef EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN
#    error "No chip select pin defined -- missing EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN"
#endif

/*
    The clock divisor for SPI to ensure that the MCU is within the
    specifications of the EEPROM chip. Generally this will be PCLK divided by
    the intended divisor -- check your clock settings and the datasheet of
    your EEPROM.
*/
#ifndef EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR
#    define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 64
#endif

/*
    The SPI mode to communicate with the EEPROM.
*/
#ifndef EXTERNAL_EEPROM_SPI_MODE
#    define EXTERNAL_EEPROM_SPI_MODE 0
#endif

/*
    Whether or not the SPI communication between the MCU and EEPROM should be
    LSB-first.
*/
#ifndef EXTERNAL_EEPROM_SPI_LSBFIRST
#    define EXTERNAL_EEPROM_SPI_LSBFIRST false
#endif

/*
    The total size of the EEPROM, in bytes. The EEPROM datasheet will usually
    specify this value in kbits, and will require conversion to bytes.
*/
#ifndef EXTERNAL_EEPROM_BYTE_COUNT
#    define EXTERNAL_EEPROM_BYTE_COUNT 8192
#endif

/*
    The page size in bytes of the EEPROM, as specified in the datasheet.
*/
#ifndef EXTERNAL_EEPROM_PAGE_SIZE
#    define EXTERNAL_EEPROM_PAGE_SIZE 32
#endif

/*
    The address size in bytes of the EEPROM. For EEPROMs with <=256 bytes, this
    will likely be 1. For EEPROMs >256 and <=65536, this will be 2. For EEPROMs
    >65536, this will likely need to be 4.

    As expected, consult the datasheet for specifics of your EEPROM.
*/
#ifndef EXTERNAL_EEPROM_ADDRESS_SIZE
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#endif

/*
    The write cycle time of the EEPROM in milliseconds, as specified in the
    datasheet.
*/
#ifndef EXTERNAL_EEPROM_WRITE_TIME
#    define EXTERNAL_EEPROM_WRITE_TIME 5
#endif
