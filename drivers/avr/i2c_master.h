/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-master-lib
 */

#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#define I2C_READ 0x01
#define I2C_WRITE 0x00

typedef i2c_status_t int16_t
#define I2C_STATUS_TIMEOUT (-1)

#define I2C_NO_TIMEOUT 0

void i2c_init(void);
i2c_status_t i2c_start(uint8_t address, uint8_t timeout);
i2c_status_t i2c_write(uint8_t data, uint8_t timeout);
i2c_status_t i2c_read_ack(uint8_t timeout);
i2c_status_t i2c_read_nack(uint8_t timeout);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
i2c_status_t i2c_stop(uint8_t timeout);

#endif // I2C_MASTER_H
