#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define I2C_READ 1
#define I2C_WRITE 0

#define I2C_ACK 1
#define I2C_NACK 0

#define SLAVE_BUFFER_SIZE 0x10

// i2c SCL clock frequency
#define SCL_CLOCK  100000L

extern volatile uint8_t i2c_slave_buffer[SLAVE_BUFFER_SIZE];

void i2c_master_init(void);
uint8_t i2c_master_start(uint8_t address);
void i2c_master_stop(void);
uint8_t i2c_master_write(uint8_t data);
uint8_t i2c_master_read(int);
void i2c_reset_state(void);
void i2c_slave_init(uint8_t address);


static inline unsigned char i2c_start_read(unsigned char addr) {
  return i2c_master_start((addr << 1) | I2C_READ);
}

static inline unsigned char i2c_start_write(unsigned char addr) {
  return i2c_master_start((addr << 1) | I2C_WRITE);
}

// from SSD1306 scrips
extern unsigned char i2c_rep_start(unsigned char addr);
extern void i2c_start_wait(unsigned char addr);
extern unsigned char i2c_readAck(void);
extern unsigned char i2c_readNak(void);
extern unsigned char i2c_read(unsigned char ack);

#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak();

#endif
