
#pragma once
#include <stdint.h>
#include <string.h>
#include "apidef.h"

#ifndef CONFIG_PIN_SCL
#define CONFIG_PIN_SCL 6
#endif
#ifndef CONFIG_PIN_SDA
#define CONFIG_PIN_SDA 5
#endif

#ifndef CONFIG_I2C_FREQ
#define CONFIG_I2C_FREQ I2C_FREQ_400K
#endif

#ifndef CONFIG_I2C_ADDR1
#define CONFIG_I2C_ADDR1 0x21
#endif

#ifndef CONFIG_I2C_ADDR2
#define CONFIG_I2C_ADDR2 0x10
#endif

#ifndef I2C_MAX_DATA_LEN
#define I2C_MAX_DATA_LEN 2048
#endif

#ifndef I2C_7BIT_ADDR
#    define I2C_7BIT_ADDR(addr) (addr << 1)
#endif

#ifndef I2C_8BIT_ADDR
#    define I2C_8BIT_ADDR(addr) (addr)
#endif

static inline int i2c_init(void)
{
  const bmp_api_i2cm_config_t config =
  {
    .freq = CONFIG_I2C_FREQ,
    .scl = CONFIG_PIN_SCL,
    .sda = CONFIG_PIN_SDA,
  };
  return BMPAPI->i2cm.init(&config);
}

static inline void i2c_uninit(void)
{
  BMPAPI->i2cm.uninit();
}

static inline uint8_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout)
{
  uint8_t i2c_temporary_buffer[I2C_MAX_DATA_LEN];
  uint8_t *p_send;

  if (data <= (uint8_t*)0xFFFFF)
  {
    // copy data on ROM to RAM
    if(sizeof(i2c_temporary_buffer)/sizeof(i2c_temporary_buffer[0]) < length) return 1;
    memcpy(i2c_temporary_buffer, data, length);
    p_send = i2c_temporary_buffer;
  }
  else
  {
    p_send = (uint8_t*)data;
  }

  return BMPAPI->i2cm.transmit(address >> 1, (uint8_t*)p_send, length);
}

static inline uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
  return BMPAPI->i2cm.receive(address >> 1, data, length);
}

static inline uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
  return BMPAPI->i2cm.read_reg(devaddr >> 1, regaddr, data, length, timeout);
}

static inline uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)
{
  uint8_t i2c_temporary_buffer[I2C_MAX_DATA_LEN];
  uint8_t *p_send;

  if (data <= (uint8_t*)0xFFFFF)
  {
    // copy data on ROM to RAM
    if(sizeof(i2c_temporary_buffer)/sizeof(i2c_temporary_buffer[0]) < length) return 1;
    memcpy(i2c_temporary_buffer, data, length);
    p_send = i2c_temporary_buffer;
  }
  else
  {
    p_send = (uint8_t*)data;
  }

  return BMPAPI->i2cm.write_reg(devaddr >> 1, regaddr, p_send, length, timeout);
}


static inline int i2cs_init(void)
{
  bmp_api_i2cs_config_t config = {
    .sda = CONFIG_PIN_SDA,
    .scl = CONFIG_PIN_SCL,
    .address = {CONFIG_I2C_ADDR1, CONFIG_I2C_ADDR2},
  };
  return BMPAPI->i2cs.init(&config);
}

static inline void i2cs_uninit(void)
{
  BMPAPI->i2cs.uninit();
}

static inline void i2cs_prepare(uint8_t* const dat, uint8_t len)
{
  BMPAPI->i2cs.prepare(dat, len);
}
