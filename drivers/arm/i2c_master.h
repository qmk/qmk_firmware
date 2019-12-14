/* Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
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

/* This library follows the convention of the AVR i2c_master library.
 * As a result addresses are expected to be already shifted (addr << 1).
 * I2CD1 is the default driver which corresponds to pins B6 and B7. This
 * can be changed.
 * Please ensure that HAL_USE_I2C is TRUE in the halconf.h file and that
 * STM32_I2C_USE_I2C1 is TRUE in the mcuconf.h file.
 */
#pragma once

#include "ch.h"
#include <hal.h>

#if defined(STM32F1XX) || defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F4XX) || defined(STM32L0xx) || defined(STM32L1xx)
#    define USE_I2CV1
#endif

#ifdef I2C1_BANK
#    define I2C1_SCL_BANK I2C1_BANK
#    define I2C1_SDA_BANK I2C1_BANK
#endif

#ifndef I2C1_SCL_BANK
#    define I2C1_SCL_BANK GPIOB
#endif

#ifndef I2C1_SDA_BANK
#    define I2C1_SDA_BANK GPIOB
#endif

#ifndef I2C1_SCL
#    define I2C1_SCL 6
#endif
#ifndef I2C1_SDA
#    define I2C1_SDA 7
#endif

#if defined(STM32F1XX) || defined(STM32F1xx)
#    define USE_GPIOV1
#endif

#ifndef USE_GPIOV1
// The default PAL alternate modes are used to signal that the pins are used for I2C
#    ifndef I2C1_SCL_PAL_MODE
#        define I2C1_SCL_PAL_MODE 4
#    endif
#    ifndef I2C1_SDA_PAL_MODE
#        define I2C1_SDA_PAL_MODE 4
#    endif
#endif

#ifdef USE_I2CV1
#    ifndef I2C1_OPMODE
#        define I2C1_OPMODE OPMODE_I2C
#    endif
#    ifndef I2C1_CLOCK_SPEED
#        define I2C1_CLOCK_SPEED 100000 /* 400000 */
#    endif
#    ifndef I2C1_DUTY_CYCLE
#        define I2C1_DUTY_CYCLE STD_DUTY_CYCLE /* FAST_DUTY_CYCLE_2 */
#    endif
#else
// The default timing values below configures the I2C clock to 400khz assuming a 72Mhz clock
// For more info : https://www.st.com/en/embedded-software/stsw-stm32126.html
#    ifndef I2C1_TIMINGR_PRESC
#        define I2C1_TIMINGR_PRESC 0U
#    endif
#    ifndef I2C1_TIMINGR_SCLDEL
#        define I2C1_TIMINGR_SCLDEL 7U
#    endif
#    ifndef I2C1_TIMINGR_SDADEL
#        define I2C1_TIMINGR_SDADEL 0U
#    endif
#    ifndef I2C1_TIMINGR_SCLH
#        define I2C1_TIMINGR_SCLH 38U
#    endif
#    ifndef I2C1_TIMINGR_SCLL
#        define I2C1_TIMINGR_SCLL 129U
#    endif
#endif

#ifndef I2C_DRIVER
#    define I2C_DRIVER I2CD1
#endif

typedef int16_t i2c_status_t;

#define I2C_STATUS_SUCCESS (0)
#define I2C_STATUS_ERROR (-1)
#define I2C_STATUS_TIMEOUT (-2)

void         i2c_init(void);
i2c_status_t i2c_start(uint8_t address);
i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_transmit_receive(uint8_t address, uint8_t* tx_body, uint16_t tx_length, uint8_t* rx_body, uint16_t rx_length);
i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
void         i2c_stop(void);
