#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR        (0b0100000<<1)
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA  0x0C  // GPIO pull-up resistor register
#define GPPUB  0x0D
#define GPIOA  0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB  0x13
#define OLATA  0x14  // output latch register
#define OLATB  0x15


extern i2c_status_t mcp23018_status;
#define ERGODOX_EXTENDED_I2C_TIMEOUT 100

void init_ergodox(void);
uint8_t init_mcp23018(void);

typedef union {
  uint32_t raw;
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
