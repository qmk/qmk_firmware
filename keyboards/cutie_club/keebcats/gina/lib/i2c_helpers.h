/* Copyright 2023 Cutie Club

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "i2c_master.h"

#define RETURN_IF_I2C_FAIL(i2c_status, return_value) \
    if (i2c_status != I2C_STATUS_SUCCESS) {          \
        return return_value;                         \
    }
#define RETURN_STATUS_IF_I2C_FAIL(i2c_status) \
    if (i2c_status != I2C_STATUS_SUCCESS) {   \
        return i2c_status;                    \
    }

i2c_status_t i2c_updateRegBit(uint8_t devaddr, uint8_t register_to_update, uint8_t bit, uint8_t value, uint16_t timeout);
