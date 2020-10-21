#include <stdio.h>
#include <avr/io.h>
#include <util/twi.h>

#define TIMEOUT (F_CPU/1000)

void i2c_init(unsigned long baud) {
	TWAR = 0;
	TWBR = (uint8_t)(((F_CPU / baud) - 16 ) / 2);
	TWCR = 0;
}

int i2c_start(uint8_t addr, bool read) {
	uint32_t count;
	uint8_t twst;

	// transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for end of transmission
	count = TIMEOUT;
	while(!(TWCR & (1<<TWINT)) && count > 0) count -= 1;
	if (count == 0) return -1;

	// check if the start condition was successfully transmitted
	twst = TW_STATUS & 0xF8;
	if ((twst != TW_START) && (twst != TW_REP_START)) return -1;

	// load slave addr into data register
	TWDR = ((addr << 1) | read);
	// start transmission of addr
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	count = TIMEOUT;
	while(!(TWCR & (1<<TWINT)) && count > 0) count -= 1;
	if (count == 0) return -1;

	// check if the device has acknowledged the READ / WRITE mode
	twst = TW_STATUS & 0xF8;
	if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) return -1;

	return 0;
}

void i2c_stop(void) {
	// transmit STOP condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	//TODO: timeout?
	while (TWCR & (1<<TWSTO));
}

int i2c_write(uint8_t * data, int length) {
	int i;
	for (i = 0; i < length; i++) {
		// load data into data register
		TWDR = data[i];
		// start transmission of data
		TWCR = (1<<TWINT) | (1<<TWEN);
		// wait for end of transmission
		uint32_t count = TIMEOUT;
		while(!(TWCR & (1<<TWINT)) && count > 0) count -= 1;
		// timed out
		if (count == 0) return -1;
		// failed to receive ack
		if((TWSR & 0xF8) != TW_MT_DATA_ACK) return -1;
	}

	return i;
}

int i2c_read(uint8_t * data, int length) {
	int i;
	for (i = 0; i < length; i++) {
	    if ((i + 1) < length) {
	    	// start TWI module and acknowledge data after reception
	    	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	    } else {
	        // start receiving without acknowledging reception
	    	TWCR = (1<<TWINT) | (1<<TWEN);
	    }
		// wait for end of transmission
		uint32_t count = TIMEOUT;
		while(!(TWCR & (1<<TWINT)) && count > 0) count -= 1;
		if (count == 0) return -1;
		// return received data from TWDR
		data[i] = TWDR;
	}

	return i;
}

int i2c_recv(uint8_t addr, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, true);
    if (res < 0) return res;

    res = i2c_read(data, length);
    if (res < 0) return res;

	i2c_stop();

	return res;
}

int i2c_send(uint8_t addr, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, false);
    if (res < 0) return res;

    res = i2c_write(data, length);
    if (res < 0) return res;

	i2c_stop();

	return res;
}

int i2c_get(uint8_t addr, uint8_t reg, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, false);
    if (res < 0) return res;

    res = i2c_write(&reg, 1);
    if (res < 0) return res;

    return i2c_recv(addr, data, length);
}

int i2c_set(uint8_t addr, uint8_t reg, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, false);
    if (res < 0) return res;

	res = i2c_write(&reg, 1);
    if (res < 0) return res;

    return i2c_send(addr, data, length);
}
