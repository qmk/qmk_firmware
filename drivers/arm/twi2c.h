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

I2CSlaveMsgCB twi2c_slave_message_process, catchError, clearAfterSend;

void twi2c_slave_init(void);

void twi2c_master_init(void);
