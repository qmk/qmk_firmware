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



#define EXTERNAL_EEPROM_BYTE_COUNT 1024 //
#define EXTERNAL_EEPROM_PAGE_SIZE 32
#define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#define EXTERNAL_EEPROM_WRITE_TIME 5
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100010

#ifndef EXTERNAL_EEPROM_I2C_ADDRESS
#    define EXTERNAL_EEPROM_I2C_ADDRESS(loc) (EXTERNAL_EEPROM_I2C_BASE_ADDRESS)
#endif

void he_eeprom_driver_init(void);
void he_eeprom_driver_erase(void);
void he_eeprom_read_block(void *buf, const void *addr, size_t len);
void he_eeprom_write_block(const void *buf, void *addr, size_t len);

