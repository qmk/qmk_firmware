/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-master-lib
 */

#include <avr/io.h>
#include <util/twi.h>

#include "i2c_master.h"
#include "timer.h"

#ifndef F_SCL
#define F_SCL 400000UL // SCL frequency
#endif
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

void i2c_init(void)
{
  TWSR = 0;     /* no prescaler */
  TWBR = (uint8_t)TWBR_val;
}

i2c_status_t i2c_start(uint8_t address, uint16_t timeout)
{
  // reset TWI control register
  TWCR = 0;
  // transmit START condition
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
      return I2C_STATUS_TIMEOUT;
    }
  }

  // check if the start condition was successfully transmitted
  if(((TW_STATUS & 0xF8) != TW_START) && ((TW_STATUS & 0xF8) != TW_REP_START)){ return I2C_STATUS_ERROR; }

  // load slave address into data register
  TWDR = address;
  // start transmission of address
  TWCR = (1<<TWINT) | (1<<TWEN);

  timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
      return I2C_STATUS_TIMEOUT;
    }
  }

  // check if the device has acknowledged the READ / WRITE mode
  uint8_t twst = TW_STATUS & 0xF8;
  if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return I2C_STATUS_ERROR;

  return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_write(uint8_t data, uint16_t timeout)
{
  // load data into data register
  TWDR = data;
  // start transmission of data
  TWCR = (1<<TWINT) | (1<<TWEN);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
      return I2C_STATUS_TIMEOUT;
    }
  }

  if( (TW_STATUS & 0xF8) != TW_MT_DATA_ACK ){ return I2C_STATUS_ERROR; }

  return I2C_STATUS_SUCCESS;
}

int16_t i2c_read_ack(uint16_t timeout)
{

  // start TWI module and acknowledge data after reception
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
      return I2C_STATUS_TIMEOUT;
    }
  }

  // return received data from TWDR
  return TWDR;
}

int16_t i2c_read_nack(uint16_t timeout)
{

  // start receiving without acknowledging reception
  TWCR = (1<<TWINT) | (1<<TWEN);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
      return I2C_STATUS_TIMEOUT;
    }
  }

  // return received data from TWDR
  return TWDR;
}

i2c_status_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_status_t status = i2c_start(address | I2C_WRITE, timeout);
  if (status) return status;

  for (uint16_t i = 0; i < length; i++) {
    status = i2c_write(data[i], timeout);
    if (status) return status;
  }

  status = i2c_stop(timeout);
  if (status) return status;

  return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_status_t status = i2c_start(address | I2C_READ, timeout);
  if (status) return status;

  for (uint16_t i = 0; i < (length-1); i++) {
    status = i2c_read_ack(timeout);
    if (status >= 0) {
      data[i] = status;
    } else {
      return status;
    }
  }

  status = i2c_read_nack(timeout);
  if (status >= 0 ) {
    data[(length-1)] = status;
  } else {
    return status;
  }

  status = i2c_stop(timeout);
  if (status) return status;

  return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_status_t status = i2c_start(devaddr | 0x00, timeout);
  if (status) return status;

  status = i2c_write(regaddr, timeout);
  if (status) return status;

  for (uint16_t i = 0; i < length; i++) {
    status = i2c_write(data[i], timeout);
    if (status) return status;
  }

  status = i2c_stop(timeout);
  if (status) return status;

  return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
  i2c_status_t status = i2c_start(devaddr, timeout);
  if (status) return status;

  status = i2c_write(regaddr, timeout);
  if (status) return status;

  status = i2c_stop(timeout);
  if (status) return status;

  status = i2c_start(devaddr | 0x01, timeout);
  if (status) return status;

  for (uint16_t i = 0; i < (length-1); i++) {
    status = i2c_read_ack(timeout);
    if (status >= 0) {
      data[i] = status;
    } else {
      return status;
    }
  }

  status = i2c_read_nack(timeout);
  if (status >= 0 ) {
    data[(length-1)] = status;
  } else {
    return status;
  }

  status = i2c_stop(timeout);
  if (status) return status;

  return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_stop(uint16_t timeout)
{
  // transmit STOP condition
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

  uint16_t timeout_timer = timer_read();
  while(TWCR & (1<<TWSTO)) {
    if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
      return I2C_STATUS_TIMEOUT;
    }
  }

  return I2C_STATUS_SUCCESS;
}
