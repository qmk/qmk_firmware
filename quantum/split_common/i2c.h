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

// Address location defines (Keymap should be last, as it's size is dynamic)
#define I2C_BACKLIT_START   0x00
// Need 4 bytes for RGB (32 bit)
#define I2C_RGB_START       0x01
#define I2C_KEYMAP_START    0x06

// Slave buffer (8bit per)
// Rows per hand + backlit space + rgb space
// TODO : Make this dynamically sized
#define SLAVE_BUFFER_SIZE 0x20

// i2c SCL clock frequency
#ifndef SCL_CLOCK
#define SCL_CLOCK  100000L
#endif

// Support 8bits right now (8 cols) will need to edit to take higher (code exists in delta split?)
extern volatile uint8_t i2c_slave_buffer[SLAVE_BUFFER_SIZE];

void i2c_master_init(void);
uint8_t i2c_master_start(uint8_t address);
void i2c_master_stop(void);
uint8_t i2c_master_write(uint8_t data);
uint8_t i2c_master_write_data(void *const TXdata, uint8_t dataLen);
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
