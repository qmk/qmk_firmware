/*
Copyright 2016 Ralf Schmitt <ralf@bunkertor.net>

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

#include "i2c.h"
#include <avr/interrupt.h>

// General TWI Master staus codes
#define TWSR_START          0x08  // START has been transmitted
#define TWSR_REP_START      0x10  // Repeated START has been transmitted
#define TWSR_STATUS_MASK    0xF8

#define TWCR_CMD_MASK       0x0F

// TWI Master Transmitter staus codes
#define TWI_MTX_ADR_ACK    0x18  // SLA+W has been tramsmitted and ACK received
#define TWI_MTX_DATA_ACK   0x28  // Data byte has been tramsmitted and ACK received

// TWI Master Receiver staus codes
#define TWI_MRX_ADR_ACK    0x40  // SLA+R has been tramsmitted and ACK received
#define TWI_MRX_DATA_ACK   0x50  // Data byte has been received and ACK tramsmitted

void i2c_init(uint16_t bitrate)
{
  TWBR = (((F_CPU / 1000l) / bitrate) - 16) / 2;
  TWCR |= (1<<TWEN);
  TWCR |= (1<<TWEA);
}

bool i2c_start(void)
{
  TWCR |= (1<<TWINT) | (1<<TWSTA);
  i2c_wait();
  uint8_t status = TWSR & TWSR_STATUS_MASK;
  return status == TWSR_START || status == TWSR_REP_START;
}

void i2c_stop(void)
{
  TWCR |= (1<<TWINT) | (1<<TWEA) | (1<<TWSTO);
  while(!(TWCR & (1<<TWSTO)));
}

bool i2c_write(uint8_t data)
{
  TWDR = data;
  /* TWCR |= (1<<TWINT); */
  TWCR = (TWCR & TWCR_CMD_MASK) | (1<<TWINT);
  i2c_wait();
  uint8_t status = TWSR & TWSR_STATUS_MASK;
  return status == TWI_MTX_DATA_ACK || status == TWI_MTX_ADR_ACK ||
     status == TWI_MRX_DATA_ACK || status == TWI_MRX_ADR_ACK;
}

uint8_t i2c_read(bool ack)
{
  if(ack) {
    TWCR |= (1<<TWEA);
  }
  TWCR |= (1<<TWINT);
  i2c_wait();
  return TWDR;
}

void i2c_wait(void)
{
  while(!(TWCR & (1<<TWINT)));
}

bool i2c_send(uint8_t address, uint8_t* data, uint8_t length)
{
  if(!i2c_start()) {
    return false;
  }
  if(!i2c_write(address & 0xfe)) {
    return false;
  }
  while(length) {
    if(!i2c_write(*data++)) {
      return false;
    }
    length--;
  }
  i2c_stop();
  return true;
}

bool i2c_recv(uint8_t address, uint8_t* data, uint8_t length)
{
  if(!i2c_start()) {
    return false;
  }
  if(!i2c_write(address | 0x01)) {
    return false;
  }
  while(length > 1) {
    *data++ = i2c_read(true);
    length--;
  }
  *data++ = i2c_read(false);
  i2c_stop();
  return true;
}
