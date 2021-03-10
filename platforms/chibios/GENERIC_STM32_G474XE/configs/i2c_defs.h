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

/* G474 - All i2c run from pclk1*/

#if defined(USE_I2C1_400KHZ) || defined(USE_I2C2_400KHZ) || defined(USE_I2C3_400KHZ) || defined(USE_I2C4_400KHZ)
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 15U
#    define I2C1_TIMINGR_SDADEL 0U
#    define I2C1_TIMINGR_SCLH 123U
#    define I2C1_TIMINGR_SCLL 255U
#elif defined(USE_I2C1_100KHZ) || defined(USE_I2C2_100KHZ) || defined(USE_I2C3_100KHZ) || defined(USE_I2C4_100KHZ)
#    define I2C1_TIMINGR_PRESC 3U
#    define I2C1_TIMINGR_SCLDEL 9U
#    define I2C1_TIMINGR_SDADEL 0U
#    define I2C1_TIMINGR_SCLH 157U
#    define I2C1_TIMINGR_SCLL 236U
#endif

#if defined(USE_I2C1_400KHZ) || defined(USE_I2C1_100KHZ)
#    define I2C_DRIVER I2CD1
#    if (defined USE_I2C1_SCL_ALT)
#        define I2C1_SCL_BANK GPIOA
#        define I2C1_SCL 13
#        define I2C1_SCL_PAL_MODE 4
#    elif !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOA
#        define I2C1_SCL 15
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

#if defined(USE_I2C2_400KHZ) || defined(USE_I2C2_100KHZ)
#    define I2C_DRIVER I2CD2
#    if (defined USE_I2C2_SCL_ALT)
#        define I2C1_SCL_BANK GPIOA
#        define I2C1_SCL 9
#        define I2C1_SCL_PAL_MODE 4
#    elif !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOC
#        define I2C1_SCL 4
#        define I2C1_SCL_PAL_MODE 4
#    endif
#    if (defined USE_I2C2_SDA_ALT)
#        define I2C1_SDA_BANK GPIOA
#        define I2C1_SDA 8
#        define I2C1_SDA_PAL_MODE 4
#    elif !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOF
#        define I2C1_SDA 0
#        define I2C1_SDA_PAL_MODE 4
#    endif
#endif

#if defined(USE_I2C3_400KHZ) || defined(USE_I2C3_100KHZ)
#    define I2C_DRIVER I2CD3
#    if (defined USE_I2C3_SCL_ALT)
#        define I2C1_SCL_BANK GPIOA
#        define I2C1_SCL 8
#        define I2C1_SCL_PAL_MODE 2
#    elif !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOC
#        define I2C1_SCL 8
#        define I2C1_SCL_PAL_MODE 8
#    endif
#    if (defined USE_I2C3_SDA_ALT)
#        define I2C1_SDA_BANK GPIOC
#        define I2C1_SDA 11
#        define I2C1_SDA_PAL_MODE 8
#    elif !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOC
#        define I2C1_SDA 9
#        define I2C1_SDA_PAL_MODE 8
#    endif
#endif

#if defined(USE_I2C4_400KHZ) || defined(USE_I2C4_100KHZ)
#    define I2C_DRIVER I2CD4
#    if (defined USE_I2C4_SCL_ALT)
#        define I2C1_SCL_BANK GPIOA
#        define I2C1_SCL 13
#        define I2C1_SCL_PAL_MODE 3
#    elif !(defined I2C1_SCL)
#        define I2C1_SCL_BANK GPIOC
#        define I2C1_SCL 6
#        define I2C1_SCL_PAL_MODE 8
#    endif
#    if (defined USE_I2C4_SDA_ALT)
#        define I2C1_SDA_BANK GPIOB
#        define I2C1_SDA 7
#        define I2C1_SDA_PAL_MODE 3
#    elif !(defined I2C1_SDA)
#        define I2C1_SDA_BANK GPIOC
#        define I2C1_SDA 7
#        define I2C1_SDA_PAL_MODE 8
#    endif
#endif
