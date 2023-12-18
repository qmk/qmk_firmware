/* Copyright 2019 Nick Brassel (tzarc)
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
    Default device configurations:

    For the Sparkfun Qwiic I2C EEPROM module: https://www.sparkfun.com/products/14764
        #define EEPROM_I2C_CAT24C512 // (part number 24512A)
        #define EEPROM_I2C_RM24C512C // (part number 24512C)

    For the Sparkfun I2C EEPROM chip: https://www.sparkfun.com/products/525
        #define EEPROM_I2C_24LC256

    For the Adafruit I2C FRAM chip: https://www.adafruit.com/product/1895
        #define EEPROM_I2C_MB85RC256V
*/
#if defined(EEPROM_I2C_CAT24C512)
#    define EXTERNAL_EEPROM_BYTE_COUNT 65536
#    define EXTERNAL_EEPROM_PAGE_SIZE 128
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#    define EXTERNAL_EEPROM_WRITE_TIME 5
#elif defined(EEPROM_I2C_RM24C512C)
#    define EXTERNAL_EEPROM_BYTE_COUNT 65536
#    define EXTERNAL_EEPROM_PAGE_SIZE 128
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#    define EXTERNAL_EEPROM_WRITE_TIME 3
#elif defined(EEPROM_I2C_24LC256)
#    define EXTERNAL_EEPROM_BYTE_COUNT 32768
#    define EXTERNAL_EEPROM_PAGE_SIZE 64
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#    define EXTERNAL_EEPROM_WRITE_TIME 5
#elif defined(EEPROM_I2C_24LC128)
#    define EXTERNAL_EEPROM_BYTE_COUNT 16384
#    define EXTERNAL_EEPROM_PAGE_SIZE 64
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#    define EXTERNAL_EEPROM_WRITE_TIME 5
#elif defined(EEPROM_I2C_24LC64)
#    define EXTERNAL_EEPROM_BYTE_COUNT 8192
#    define EXTERNAL_EEPROM_PAGE_SIZE 32
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#    define EXTERNAL_EEPROM_WRITE_TIME 5
#elif defined(EEPROM_I2C_24LC32A)
#    define EXTERNAL_EEPROM_BYTE_COUNT 4096
#    define EXTERNAL_EEPROM_PAGE_SIZE 32
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#    define EXTERNAL_EEPROM_WRITE_TIME 5
#elif defined(EEPROM_I2C_MB85RC256V)
#    define EXTERNAL_EEPROM_BYTE_COUNT 32768
#    define EXTERNAL_EEPROM_PAGE_SIZE 128
#    define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#    define EXTERNAL_EEPROM_WRITE_TIME 0
#endif

/*
    The base I2C address of the EEPROM.
    This needs to be shifted up by 1, to match i2c_master requirements.
*/
#ifndef EXTERNAL_EEPROM_I2C_BASE_ADDRESS
#    define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#endif

/*
    The calculated I2C address based on the input memory location.

    For EEPROM chips that embed part of the memory location in the I2C address
    such as AT24M02 you can use something similar to the following (ensuring the
    result is shifted by left by 1):

    #define EXTERNAL_EEPROM_I2C_ADDRESS(loc) \
        (EXTERNAL_EEPROM_I2C_BASE_ADDRESS | ((((loc) >> 16) & 0x07) << 1))

*/
#ifndef EXTERNAL_EEPROM_I2C_ADDRESS
#    define EXTERNAL_EEPROM_I2C_ADDRESS(loc) (EXTERNAL_EEPROM_I2C_BASE_ADDRESS)
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
    >65536, this will likely need to be 2 with the modified variant of
    EXTERNAL_EEPROM_I2C_ADDRESS above.

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
