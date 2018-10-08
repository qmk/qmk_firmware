#ifndef MAP23017_H
#define MAP23017_H

#define MCP23017
#define MCP23017_A0 0
#define MCP23017_A1 0
#define MCP23017_A2 0

#ifdef MCP23017
#define EXPANDER_ADDRa ((0x20|(MCP23017_A0<<0)|(MCP23017_A1<<1)|(MCP23017_A2<<2)) << 1)
#define EXPANDER_ADDR 0x27
#define I2C_TIMEOUT 200 // milliseconds
enum EXPANDER_REGISTERS {
    EXPANDER_REG_IODIRA = 0x00,
    EXPANDER_REG_IODIRB = 0x01,
    EXPANDER_REG_IPOLA = 0x02,
    EXPANDER_REG_IPOLB = 0x03,
    EXPANDER_REG_GPINTENA = 0x04,
    EXPANDER_REG_GPINTENB = 0x05,
    EXPANDER_REG_DEFVALA = 0x06,
    EXPANDER_REG_DEFVALB = 0x07,
    EXPANDER_REG_INTCONA = 0x08,
    EXPANDER_REG_INTCONB = 0x09,
    EXPANDER_REG_IOCONA = 0x0A,
    EXPANDER_REG_IOCONB = 0x0B,
    EXPANDER_REG_GPPUA = 0x0C,
    EXPANDER_REG_GPPUB = 0x0D,
    EXPANDER_REG_INTFA = 0x0E,
    EXPANDER_REG_INTFB = 0x0F,
    EXPANDER_REG_INTCAPA = 0x10,
    EXPANDER_REG_INTCAPB = 0x11,
    EXPANDER_REG_GPIOA = 0x12,
    EXPANDER_REG_GPIOB = 0x13,
    EXPANDER_REG_OLATA = 0x14,
    EXPANDER_REG_OLATB = 0x15
};
#endif

#define GPA0 0x0
#define GPA1 0x1
#define GPA2 0x2
#define GPA3 0x3
#define GPA4 0x4
#define GPA5 0x5
#define GPA6 0x6
#define GPA7 0x7
#define GPB0 0x8
#define GPB1 0x9
#define GPB2 0xA
#define GPB3 0xB
#define GPB4 0xC
#define GPB5 0xD
#define GPB6 0xE
#define GPB7 0xF


void expander_init(void);
void expander_select(uint8_t pin);
void expander_unselect(uint8_t pin);
void expander_unselect_all(void);

#endif