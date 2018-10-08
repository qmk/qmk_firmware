#ifndef MAP23017_H
#define MAP23017_H

#define MCP23017
#define MCP23017_A0 0
#define MCP23017_A1 0
#define MCP23017_A2 0

#ifdef MCP23017
#define EXPANDER_ADDRa ((0x20|(MCP23017_A0<<0)|(MCP23017_A1<<1)|(MCP23017_A2<<2)) << 1)
#define EXPANDER_ADDR 0x27
enum EXPANDER_REG_BANK0 {
    EXPANDER_REG_IODIRA = 0,
    EXPANDER_REG_IODIRB,
    EXPANDER_REG_IPOLA,
    EXPANDER_REG_IPOLB,
    EXPANDER_REG_GPINTENA,
    EXPANDER_REG_GPINTENB,
    EXPANDER_REG_DEFVALA,
    EXPANDER_REG_DEFVALB,
    EXPANDER_REG_INTCONA,
    EXPANDER_REG_INTCONB,
    EXPANDER_REG_IOCONA,
    EXPANDER_REG_IOCONB,
    EXPANDER_REG_GPPUA,
    EXPANDER_REG_GPPUB,
    EXPANDER_REG_INTFA,
    EXPANDER_REG_INTFB,
    EXPANDER_REG_INTCAPA,
    EXPANDER_REG_INTCAPB,
    EXPANDER_REG_GPIOA,
    EXPANDER_REG_GPIOB,
    EXPANDER_REG_OLATA,
    EXPANDER_REG_OLATB
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
#define GPB2 0xa
#define GPB3 0xb
#define GPB4 0xc
#define GPB5 0xd
#define GPB6 0xe
#define GPB7 0xf


void expander_init(void);
void expander_connect(void);
void expander_select(uint8_t pin);
void expander_unselect(uint8_t pin);
void expander_unselect_all(void);

#endif