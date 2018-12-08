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

/* This library is only valid for STM32 processors.
 * This library follows the convention of the AVR i2c_master library.
 * As a result addresses are expected to be already shifted (addr << 1).
 * I2CD1 is the default driver which corresponds to pins B6 and B7. This
 * can be changed.
 * Please ensure that HAL_USE_I2C is TRUE in the halconf.h file and that
 * STM32_I2C_USE_I2C1 is TRUE in the mcuconf.h file. Pins B6 and B7 are used
 * but using any other I2C pins should be trivial.
 */

#include "i2c_master.h"
#include "quantum.h"
#include <string.h>
#include <hal.h>

static uint8_t i2c_address;

// This configures the I2C clock to 400khz assuming a 72Mhz clock
// For more info : https://www.st.com/en/embedded-software/stsw-stm32126.html
static const I2CConfig i2cconfig = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};

__attribute__ ((weak))
void i2c_init(void)
{
  //palSetGroupMode(GPIOB, GPIOB_PIN6 | GPIOB_PIN7, 0, PAL_MODE_INPUT);

  // Try releasing special pins for a short time
  palSetPadMode(GPIOB, 6, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 7, PAL_MODE_INPUT);

  chThdSleepMilliseconds(10);
 
  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);

  //i2cInit(); //This is invoked by halInit() so no need to redo it.
}

// This is usually not needed
uint8_t i2c_start(uint8_t address)
{
  i2c_address = address;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  return 0;
}

uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_address = address;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  return i2cMasterTransmitTimeout(&I2C_DRIVER, (i2c_address >> 1), data, length, 0, 0, MS2ST(timeout));
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_address = address;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  return i2cMasterReceiveTimeout(&I2C_DRIVER, (i2c_address >> 1), data, length, MS2ST(timeout));
}

uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_address = devaddr;
  i2cStart(&I2C_DRIVER, &i2cconfig);

  uint8_t complete_packet[length + 1];
  for(uint8_t i = 0; i < length; i++)
  {
    complete_packet[i+1] = data[i];
  }
  complete_packet[0] = regaddr;

  return i2cMasterTransmitTimeout(&I2C_DRIVER, (i2c_address >> 1), complete_packet, length + 1, 0, 0, MS2ST(timeout));
}

uint8_t i2c_readReg(uint8_t devaddr, uint8_t* regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_address = devaddr;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  return i2cMasterTransmitTimeout(&I2C_DRIVER, (i2c_address >> 1), regaddr, 1, data, length, MS2ST(timeout));
}

// This is usually not needed. It releases the driver to allow pins to become GPIO again.
uint8_t i2c_stop(uint16_t timeout)
{
  i2cStop(&I2C_DRIVER);
  return 0;
}
