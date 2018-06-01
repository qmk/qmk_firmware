/* Copyright 2018 Jack Humbert
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

#include "ch.h"
#include "hal.h"

#ifndef I2C_DRIVER
  #define I2C_DRIVER I2CD1
#endif

#define slaveI2Caddress  0x30       /* Address in our terms - halved by later code */
//#define myOtherI2Caddress 0x19

#ifdef I2C_SLAVE_ENABLE

I2CSlaveMsgCB twi2c_slave_message_process, catchError, clearAfterSend;

void twi2c_slave_init(void);

#endif

void twi2c_init(void);
uint8_t twi2c_start(uint8_t address);
uint8_t twi2c_write(uint8_t data);
uint8_t twi2c_read_ack(void);
uint8_t twi2c_read_nack(void);
uint8_t twi2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t twi2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t twi2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t twi2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void twi2c_stop(void);
