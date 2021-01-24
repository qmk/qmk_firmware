#include <stdio.h>
#include <avr/io.h>
#include <util/twi.h>

#include "i2c.h"

#define TIMEOUT (F_CPU/1000)

// Initialize I2C with specified buad rate
void i2c_init(unsigned long baud) {
    TWAR = 0;
    TWBR = (uint8_t)(((F_CPU / baud) - 16 ) / 2);
    TWCR = 0;
}

// Send an I2C start condition, a 7-bit address, and a read bit
// Returns zero on success or negative number on error
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

// Send an I2C stop condition
// Always successful
void i2c_stop(void) {
    // transmit STOP condition
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    //TODO: timeout?
    while (TWCR & (1<<TWSTO));
}

// Write data to the I2C bus
// Returns bytes written on success or negative number on error
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

// Read a byte from the I2C bus, sending an ack if specified
// Returns byte data on success or negative number on error
int i2c_read_byte(bool ack) {
    if (ack) {
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
    return (int)TWDR;
}

// Read data from the I2C bus
// Returns bytes read on success or negative number on error
int i2c_read(uint8_t * data, int length) {
    int res;
    int i;

    for (i = 0; i < length; i++) {
        bool ack = (i + 1) < length;
        res = i2c_read_byte(ack);
        if (res < 0) return res;
        data[i] = (uint8_t)res;
    }

    return i;
}

// Receive data from a specified address on the I2C bus
// Returns bytes read on success or negative number on error
int i2c_recv(uint8_t addr, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, true);
    if (res < 0) return res;

    res = i2c_read(data, length);
    if (res < 0) return res;

    i2c_stop();

    return res;
}

// Send data to a specified address on the I2C bus
// Returns bytes written on success or negative number on error
int i2c_send(uint8_t addr, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, false);
    if (res < 0) return res;

    res = i2c_write(data, length);
    if (res < 0) return res;

    i2c_stop();

    return res;
}

// Get data from a specified address and register on the I2C bus
// Returns bytes read on success or negative number on error
int i2c_get(uint8_t addr, uint8_t reg, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, false);
    if (res < 0) return res;

    res = i2c_write(&reg, 1);
    if (res < 0) return res;

    return i2c_recv(addr, data, length);
}

// Set data in a specified address and register on the I2C bus
// Returns bytes written on success or negative number on error
int i2c_set(uint8_t addr, uint8_t reg, uint8_t* data, int length) {
    int res = 0;

    res = i2c_start(addr, false);
    if (res < 0) return res;

    res = i2c_write(&reg, 1);
    if (res < 0) return res;

    res = i2c_write(data, length);
    if (res < 0) return res;

    i2c_stop();

    return res;
}
