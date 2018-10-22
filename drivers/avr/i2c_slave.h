/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-slave-lib

 Info: Inititate the library by giving the required address.
       Read or write to the necessary buffer according to the opperation.
 */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#define TX_BUFFER_SIZE 30
#define RX_BUFFER_SIZE 30

volatile uint8_t buffer_address;
static volatile bool slave_has_register_set = false;
volatile uint8_t txbuffer[TX_BUFFER_SIZE];
volatile uint8_t rxbuffer[RX_BUFFER_SIZE];

void i2c_init(uint8_t address);
void i2c_stop(void);
ISR(TWI_vect);

#endif // I2C_SLAVE_H