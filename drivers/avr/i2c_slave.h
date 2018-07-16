/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-slave-lib

 Info: Inititate the library by giving the required address.
       Read or write to the necessary buffer according to the opperation.
 */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

volatile uint8_t buffer_address;
volatile uint8_t txbuffer[0xFF];
volatile uint8_t rxbuffer[0xFF];

void i2c_init(uint8_t address);
void i2c_stop(void);
ISR(TWI_vect);

#endif // I2C_SLAVE_H
