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

/* PROTON C/F303 - using proton c pinout to set default pins, i2c2 alt pins are osc f0/f1 */

#if defined(USE_I2C1_400KHZ) || defined(USE_I2C1_100KHZ)
#    define I2C_DRIVER I2CD1
#    if defined(USE_I2C1_400KHZ)
#        define I2C1_TIMINGR_PRESC 0U
#        define I2C1_TIMINGR_SCLDEL 7U
#        define I2C1_TIMINGR_SDADEL 0U
#        define I2C1_TIMINGR_SCLH 38U
#        define I2C1_TIMINGR_SCLL 129U
#    elif defined(USE_I2C1_100KHZ)
#        define I2C1_TIMINGR_PRESC 1U
#        define I2C1_TIMINGR_SCLDEL 8U
#        define I2C1_TIMINGR_SDADEL 0U
#        define I2C1_TIMINGR_SCLH 141U
#        define I2C1_TIMINGR_SCLL 211U
#    endif
#    if (defined USE_I2C1_SCL_ALT)
#        define I2C1_SCL_BANK GPIOB
#        define I2C1_SCL 8
#        define I2C1_SCL_PAL_MODE 4
#    elif !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOB
#        define I2C1_SCL 6
#        define I2C1_SCL_PAL_MODE 4
#    endif
#    if (defined USE_I2C1_SDA_ALT)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 9
#        define I2C1_SDA_PAL_MODE 4
#    elif !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 7
#        define I2C1_SDA_PAL_MODE 4
#    endif
#endif
