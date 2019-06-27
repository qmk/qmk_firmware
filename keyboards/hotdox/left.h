#pragma once

#include "quantum.h"
#include <stdint.h>
#include "i2c_master.h"
#include <util/delay.h>

#define MCP23017
#define MCP23017_A0 0
#define MCP23017_A1 0
#define MCP23017_A2 0

#define I2C_ADDR        (0x20)
#define I2C_ADDR_WRITE  ((I2C_ADDR << 1) | I2C_WRITE)
#define I2C_ADDR_READ   ((I2C_ADDR << 1) | I2C_READ)


#define MCP23017_B0_IODIRA     0x00
#define MCP23017_B0_IODIRB     0x01
#define MCP23017_B0_IPOLA      0x02
#define MCP23017_B0_IPOLB      0x03
#define MCP23017_B0_GPINTENA   0x04
#define MCP23017_B0_GPINTENB   0x05
#define MCP23017_B0_DEFVALA    0x06
#define MCP23017_B0_DEFVALB    0x07
#define MCP23017_B0_INTCONA    0x08
#define MCP23017_B0_INTCONB    0x09
#define MCP23017_B0_IOCONA     0x0A
#define MCP23017_B0_IOCONB     0x0B
#define MCP23017_B0_GPPUA      0x0C
#define MCP23017_B0_GPPUB      0x0D
#define MCP23017_B0_INTFA      0x0E
#define MCP23017_B0_INTFB      0x0F
#define MCP23017_B0_INTCAPA    0x10
#define MCP23017_B0_INTCAPB    0x11
#define MCP23017_B0_GPIOA      0x12
#define MCP23017_B0_GPIOB      0x13
#define MCP23017_B0_OLATA      0x14
#define MCP23017_B0_OLATB      0x15

#define HOTDOX_I2C_TIMEOUT     100

typedef int16_t i2c_status_t;

void left_init(void);
void left_scan(void);

uint8_t left_read_cols(void);
uint8_t left_get_col(uint8_t col);

matrix_row_t left_read_row(void);

void left_unselect_rows(void);
void left_select_row(uint8_t row);

uint8_t init_mcp23017(void);

