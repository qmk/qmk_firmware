/* Copyright 2021 Dasky
 *
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
#pragma once

/* F103 */

#if defined(USE_I2C1_400KHZ) || defined(USE_I2C1_100KHZ)
#    define I2C_DRIVER I2CD1
#    if defined(USE_I2C1_400KHZ)
#        define I2C1_OPMODE OPMODE_I2C
#        define I2C1_CLOCK_SPEED 400000
#        define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#    elif defined(USE_I2C1_100KHZ)
#        define I2C1_OPMODE OPMODE_I2C
#        define I2C1_CLOCK_SPEED 100000
#        define I2C1_DUTY_CYCLE STD_DUTY_CYCLE
#    endif
#    if !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOB
#        define I2C1_SCL 6
#        define I2C1_SCL_PAL_MODE PAL_MODE_STM32_ALTERNATE_OPENDRAIN
#    endif
#    if !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 7
#        define I2C1_SDA_PAL_MODE PAL_MODE_STM32_ALTERNATE_OPENDRAIN
#    endif
#endif

#if defined(USE_I2C2_400KHZ) || defined(USE_I2C2_100KHZ)
#    define I2C_DRIVER I2CD2
#    if defined(USE_I2C2_400KHZ)
#        define I2C1_OPMODE OPMODE_I2C
#        define I2C1_CLOCK_SPEED 400000
#        define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#    elif defined(USE_I2C2_100KHZ)
#        define I2C1_OPMODE OPMODE_I2C
#        define I2C1_CLOCK_SPEED 100000
#        define I2C1_DUTY_CYCLE STD_DUTY_CYCLE
#    endif
#    if !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOB
#        define I2C1_SCL 10
#        define I2C1_SCL_PAL_MODE PAL_MODE_STM32_ALTERNATE_OPENDRAIN
#    endif
#    if !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 11
#        define I2C1_SDA_PAL_MODE PAL_MODE_STM32_ALTERNATE_OPENDRAIN
#    endif
#endif
