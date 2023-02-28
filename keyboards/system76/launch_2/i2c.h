#ifndef I2C_H
#define I2C_H

#include <stdbool.h>
#include <stdint.h>

// Initialize I2C with specified buad rate
void i2c_init(unsigned long baud);

// Send an I2C start condition, a 7-bit address, and a read bit
// Returns zero on success or negative number on error
int i2c_start(uint8_t addr, bool read);

// Send an I2C stop condition
// Always successful
void i2c_stop(void);

// Write data to the I2C bus
// Returns bytes written on success or negative number on error
int i2c_write(uint8_t * data, int length);

// Read a byte from the I2C bus, sending an ack if specified
// Returns byte data on success or negative number on error
int i2c_read_byte(bool ack);

// Read data from the I2C bus
// Returns bytes read on success or negative number on error
int i2c_read(uint8_t * data, int length);

// Receive data from a specified address on the I2C bus
// Returns bytes read on success or negative number on error
int i2c_recv(uint8_t addr, uint8_t* data, int length);

// Send data to a specified address on the I2C bus
// Returns bytes written on success or negative number on error
int i2c_send(uint8_t addr, uint8_t* data, int length);

// Get data from a specified address and register on the I2C bus
// Returns bytes read on success or negative number on error
int i2c_get(uint8_t addr, uint8_t reg, uint8_t* data, int length);

// Set data in a specified address and register on the I2C bus
// Returns bytes written on success or negative number on error
int i2c_set(uint8_t addr, uint8_t reg, uint8_t* data, int length);

#endif // I2C_H
