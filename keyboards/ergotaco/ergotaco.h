#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "i2c_master.h"
#include "matrix.h"


extern i2c_status_t mcp23018_status;
#define ERGODOX_EZ_I2C_TIMEOUT 1000
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses (see "mcp23018.md")
//#define I2C_ADDR        0b0100000
#define I2C_ADDR        0x20
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

void init_ergodox(void);
uint8_t init_mcp23018(void);

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT(                                                          \
    L00,L01,L02,L03,L04,L05,                   R00,R01,R02,R03,R04,R05)  \
                                                                         \
   /* matrix positions */                                                \
    {			\
    {R00},     \
    {R01},     \
    {R02},     \
    {R03},     \
    {R04},     \
    {R05},     \
    {L05},     \
    {L04},     \
    {L03},     \
    {L02},     \
    {L01},     \
    {L00},     \
}
