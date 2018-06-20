/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-master-lib
 */

#include <avr/io.h>
#include <util/twi.h>

#include "i2c_master.h"
#include "timer.h"

#define F_SCL 400000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

void i2c_init(void)
{
  TWSR = 0;     /* no prescaler */
	TWBR = (uint8_t)TWBR_val;
  //TWBR = 10;
}

i2c_status_t i2c_start(uint8_t address, uint8_t timeout)
{
	// reset TWI control register
	TWCR = 0;
	// transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if (timeout && (timer_read() - timeout_timer) > timeout) {
      return I2C_STATUS_TIMEOUT;
    }
  }

	// check if the start condition was successfully transmitted
	if(((TW_STATUS & 0xF8) != TW_START) && ((TW_STATUS & 0xF8) != TW_REP_START)){ return 1; }

	// load slave address into data register
	TWDR = address;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);

  timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if (timeout && (timer_read() - timeout_timer) > I2C_TIMEOUT) {
      return I2C_STATUS_TIMEOUT;
    }
  }

	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

	return 0;
}

i2c_status_t i2c_write(uint8_t data, uint8_t timeout)
{
	// load data into data register
	TWDR = data;
	// start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if (timeout && (timer_read() - timeout_timer) > I2C_TIMEOUT) {
      return I2C_STATUS_TIMEOUT;
    }
  }

	if( (TW_STATUS & 0xF8) != TW_MT_DATA_ACK ){ return 1; }

	return 0;
}

i2c_status_t i2c_read_ack(uint8_t timeout)
{

	// start TWI module and acknowledge data after reception
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if (timeout && (timer_read() - timeout_timer) > I2C_TIMEOUT) {
      return I2C_STATUS_TIMEOUT;
    }
  }

	// return received data from TWDR
	return TWDR;
}

i2c_status_t i2c_read_nack(uint8_t timeout)
{

	// start receiving without acknowledging reception
	TWCR = (1<<TWINT) | (1<<TWEN);

  uint16_t timeout_timer = timer_read();
  while( !(TWCR & (1<<TWINT)) ) {
    if (timeout && (timer_read() - timeout_timer) > I2C_TIMEOUT) {
      return I2C_STATUS_TIMEOUT;
    }
  }

	// return received data from TWDR
	return TWDR;
}

i2c_status_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address | I2C_WRITE)) return 1;

	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_write(data[i])) return 1;
	}

	i2c_stop();

	return 0;
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address | I2C_READ)) return 1;

	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();

	i2c_stop();

	return 0;
}

uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	if (i2c_start(devaddr | 0x00)) return 1;

	i2c_write(regaddr);

	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_write(data[i])) return 1;
	}

	i2c_stop();

	return 0;
}

uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	if (i2c_start(devaddr)) return 1;

	i2c_write(regaddr);

	if (i2c_start(devaddr | 0x01)) return 1;

	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();

	i2c_stop();

	return 0;
}

i2c_status_t i2c_stop(uint8_t timeout)
{
	// transmit STOP condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

  uint16_t timeout_timer = timer_read();
  while(TWCR & (1<<TWSTO)) {
      if (timeout && (timer_read() - timeout_timer) > I2C_TIMEOUT) {
      return I2C_STATUS_TIMEOUT;
    }
  }

  return 0;
}
