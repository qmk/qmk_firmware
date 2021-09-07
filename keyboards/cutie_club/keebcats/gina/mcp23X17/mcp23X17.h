#pragma once

#ifndef __ASSEMBLER__
#include <stdint.h>
// IOCON is duplicated by the IC, I have named each instance IOCON for simplicity
// On reset the IC sets the following: BANK = 0, Sequential mode is enabled

// The following addressing is used when IOCON.BANK = 0
#define BANK0_IODIRA    0x00
#define BANK0_IODIRB    0x01
#define BANK0_IPOLA     0x02
#define BANK0_IPOLB     0x03
#define BANK0_GPINTENA  0x04
#define BANK0_GPINTENB  0x05
#define BANK0_DEFVALA   0x06
#define BANK0_DEFVALB   0x07
#define BANK0_INTCONA   0x08
#define BANK0_INTCONB   0x09
#define BANK0_IOCON     0x0A
#define BANK0_IOCON_ALT 0x0B
#define BANK0_GPPUA     0x0C
#define BANK0_GPPUB     0x0D
#define BANK0_INTFA     0x0E
#define BANK0_INTFB     0x0F
#define BANK0_INTCAPA   0x10
#define BANK0_INTCAPB   0x11
#define BANK0_GPIOA     0x12
#define BANK0_GPIOB     0x13
#define BANK0_OLATA     0x14
#define BANK0_OLATB     0x15

// The following addressing is used when IOCON.BANK = 1
#define BANK1_IODIRA    0x00
#define BANK1_IPOLA     0x01
#define BANK1_GPINTENA  0x02
#define BANK1_DEFVALA   0x03
#define BANK1_INTCONA   0x04
#define BANK1_IOCON     0x05
#define BANK1_GPPUA     0x06
#define BANK1_INTFA     0x07
#define BANK1_INTCAPA   0x08
#define BANK1_GPIOA     0x09
#define BANK1_OLATA     0x0A

#define BANK1_IODIRB    0x10
#define BANK1_IPOLB     0x11
#define BANK1_GPINTENB  0x12
#define BANK1_DEFVALB   0x13
#define BANK1_INTCONB   0x14
#define BANK1_IOCON_ALT 0x15
#define BANK1_GPPUB     0x16
#define BANK1_INTFB     0x17
#define BANK1_INTCAPB   0x18
#define BANK1_GPIOB     0x19
#define BANK1_OLATB     0x1A


/*
================ BIT MASKS ================
*/
// IOCON
#define IOCON_BANK   (1 << 7)
#define IOCON_MIRROR (1 << 6)
#define IOCON_SEQOP  (1 << 5)
#define IOCON_DISSLW (1 << 4)
#define IOCON_HAEN   (1 << 3)
#define IOCON_ODR    (1 << 2)
#define IOCON_INTPOL (1 << 1)


// GPIO
typedef enum mcp_gpio_state{LOW, HIGH} mcp_gpio_state;
typedef enum mcp_gpio_dir{OUTPUT, INPUT, INPUT_PULLUP} mcp_gpio_dir;
typedef uint8_t mcp_gpio_pin;

#define PORT_A 0
#define PORT_B 1
#define GET_PORT(pin) (pin >> 7)
#define GET_PIN_NUMBER(pin) (pin & 0b0111111)
#define BANK0_REGISTER_FOR_PIN(pin, register) (GET_PORT(pin) == PORT_A ? BANK0_##register##A : BANK0_##register##B)

#define MCP_A0 (PORT_A << 7) | 0
#define MCP_A1 (PORT_A << 7) | 1
#define MCP_A2 (PORT_A << 7) | 2
#define MCP_A3 (PORT_A << 7) | 3
#define MCP_A4 (PORT_A << 7) | 4
#define MCP_A5 (PORT_A << 7) | 5
#define MCP_A6 (PORT_A << 7) | 6
#define MCP_A7 (PORT_A << 7) | 7

#define MCP_B0 (PORT_B << 7) | 0
#define MCP_B1 (PORT_B << 7) | 1
#define MCP_B2 (PORT_B << 7) | 2
#define MCP_B3 (PORT_B << 7) | 3
#define MCP_B4 (PORT_B << 7) | 4
#define MCP_B5 (PORT_B << 7) | 5
#define MCP_B6 (PORT_B << 7) | 6
#define MCP_B7 (PORT_B << 7) | 7

#endif
