/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-slave-lib

 Info: Inititate the library by giving the required address.
       Read or write to the necessary buffer according to the opperation.
 */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#define I2C_SLAVE_REG_COUNT 30

extern volatile uint8_t i2c_slave_reg[I2C_SLAVE_REG_COUNT];

void i2c_slave_init(uint8_t address);
void i2c_slave_stop(void);

#endif // I2C_SLAVE_H