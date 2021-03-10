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

/* F411 sda only i2c2/i2c3 alt pins*/

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
#    if (defined USE_I2C1_SCL_ALT)
#        define I2C1_SCL_BANK GPIOB
#        define I2C1_SCL 6
#        define I2C1_SCL_PAL_MODE 4
#    elif !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOB
#        define I2C1_SCL 8
#        define I2C1_SCL_PAL_MODE 4
#    endif
#    if (defined USE_I2C1_SDA_ALT)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 7
#        define I2C1_SDA_PAL_MODE 4
#    elif !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 9
#        define I2C1_SDA_PAL_MODE 4
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
#        define I2C1_SCL_PAL_MODE 4
#    endif
#    if (defined USE_I2C2_SDA_ALT)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 9
#        define I2C1_SDA_PAL_MODE 9
#    elif !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 3
#        define I2C1_SDA_PAL_MODE 9
#    endif
#endif

#if defined(USE_I2C3_400KHZ) || defined(USE_I2C3_100KHZ)
#    define I2C_DRIVER I2CD3
#    if defined(USE_I2C3_400KHZ)
#        define I2C1_OPMODE OPMODE_I2C
#        define I2C1_CLOCK_SPEED 400000
#        define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#    elif defined(USE_I2C3_100KHZ)
#        define I2C1_OPMODE OPMODE_I2C
#        define I2C1_CLOCK_SPEED 100000
#        define I2C1_DUTY_CYCLE STD_DUTY_CYCLE
#    endif
#    if !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOA
#        define I2C1_SCL 8
#        define I2C1_SCL_PAL_MODE 4
#    endif
#    if (defined USE_I2C3_SDA_ALT)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 8
#        define I2C1_SDA_PAL_MODE 9
#    elif !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 4
#        define I2C1_SDA_PAL_MODE 9
#    endif
#endif
