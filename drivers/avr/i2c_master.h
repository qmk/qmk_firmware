/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-master-lib
 */

#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#define I2C_READ 0x01
#define I2C_WRITE 0x00

typedef int16_t i2c_status_t;

#define I2C_STATUS_SUCCESS (0)
#define I2C_STATUS_ERROR   (-1)
#define I2C_STATUS_TIMEOUT (-2)

#define I2C_TIMEOUT_IMMEDIATE (0)
#define I2C_TIMEOUT_INFINITE (0xFFFF)

void i2c_init(void);
i2c_status_t i2c_start(uint8_t address, uint16_t timeout);
i2c_status_t i2c_write(uint8_t data, uint16_t timeout);
int16_t i2c_read_ack(uint16_t timeout);
int16_t i2c_read_nack(uint16_t timeout);
i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
void i2c_stop(void);

#endif // I2C_MASTER_H
