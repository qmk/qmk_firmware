/*  Copyright (C) 2019 Andrei Purdea
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
 * GitHub repository: https://github.com/g4lvanix/I2C-master-lib
 */

#pragma once

#if defined(I2C_MASTER_DRIVER_VENDOR)
#    if defined(__AVR__)
#        include "../platforms/avr/drivers/i2c_master_avr.h"
#    elif defined(PROTOCOL_CHIBIOS)
#        include "../platforms/chibios/drivers/i2c_master_chibios.h"
#    elif defined(PROTOCOL_ARM_ATSAM)
#        include "../tmk_core/protocol/arm_atsam/i2c_master_arm_atsam.h"
#    else
#        error "Unknown protocol"
#    endif
#elif defined(I2C_MASTER_DRIVER_BITBANG)
#    include "../drivers/i2c_bitbang/i2c_master_bitbang.h"
#endif
