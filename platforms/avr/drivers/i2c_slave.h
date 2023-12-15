/*  Copyright (C) 2019 Elia Ritterbusch
 +
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
/* Library made by: g4lvanix
 * GitHub repository: https://github.com/g4lvanix/I2C-slave-lib

 Info: Inititate the library by giving the required address.
       Read or write to the necessary buffer according to the opperation.
 */

#pragma once

#ifndef I2C_SLAVE_REG_COUNT

#    if defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)
#        include "transport.h"
#        define I2C_SLAVE_REG_COUNT sizeof(split_shared_memory_t)
#    else // defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)
#        define I2C_SLAVE_REG_COUNT 30
#    endif // defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)

#endif // I2C_SLAVE_REG_COUNT

_Static_assert(I2C_SLAVE_REG_COUNT < 256, "I2C target registers must be single byte");

extern volatile uint8_t i2c_slave_reg[I2C_SLAVE_REG_COUNT];

void i2c_slave_init(uint8_t address);
void i2c_slave_stop(void);
