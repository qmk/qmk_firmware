/* Copyright 2021 QMK
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

#include <stddef.h>
#include <stdint.h>

/**
 * The type of the CRC values.
 *
 * This type must be big enough to contain at least 8 bits.
 */
#if defined(CRC8_OPTIMIZE_SPEED)
typedef uint_fast8_t crc_t;
#else
typedef uint_least8_t crc_t;
#endif

/**
 * Initialize crc subsystem.
 */
__attribute__((weak)) void crc_init(void);

/**
 * Generate CRC8 value from given data.
 *
 * \param[in] data     Pointer to a buffer of \a data_len bytes.
 * \param[in] data_len Number of bytes in the \a data buffer.
 * \return             The calculated crc value.
 */
__attribute__((weak)) uint8_t crc8(const void *data, size_t data_len);
