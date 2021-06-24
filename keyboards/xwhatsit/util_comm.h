/* Copyright 2020 Purdea Andrei
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

#ifndef UTIL_COMM_H
#define UTIL_COMM_H

#define UTIL_COMM_VERSION_MAJOR 2
#define UTIL_COMM_VERSION_MID 0
#define UTIL_COMM_VERSION_MINOR 5


#define UTIL_COMM_MAGIC { 0x55, 0xAA }

enum command {
    UTIL_COMM_GET_VERSION = 0x11,
    UTIL_COMM_ENTER_BOOTLOADER,
    UTIL_COMM_DISABLE_KEYBOARD,
    UTIL_COMM_ENABLE_KEYBOARD,
    UTIL_COMM_GET_KEYSTATE,
    UTIL_COMM_GET_THRESHOLDS,
    UTIL_COMM_GET_KEYBOARD_FILENAME,
    UTIL_COMM_ERASE_EEPROM,
    UTIL_COMM_GET_SIGNAL_VALUE,
    UTIL_COMM_GET_KEYBOARD_DETAILS,
    UTIL_COMM_SHIFT_DATA,
    UTIL_COMM_SET_DAC_VALUE,
    UTIL_COMM_GET_ROW_STATE,
    UTIL_COMM_SHIFT_DATA_EXT,
};

enum response {
    UTIL_COMM_RESPONSE_OK = 0x22,
    UTIL_COMM_RESPONSE_ERROR
};

#endif
