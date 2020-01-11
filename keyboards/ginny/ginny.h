#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>


extern i2c_status_t mcp23018_status;
#define I2C_TIMEOUT 1000
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

uint8_t init_mcp23018(void);

/*  -------- LEFT HAND------RIGHT HAND ---------- */
#define LAYOUT_ginny( L00,L01,L02,L03,L04, R00,R01,R02,R03,R04 ) { \
                        \
    { KC_NO,   R00 },      \
    { R01,   KC_NO },    \
    { R02,   KC_NO },    \
    { R03,   KC_NO },    \
   	{ R04, 	 KC_NO},  	  \
    { L03, 		L04},    \
    { L02, 		KC_NO},    \
    { L01, 		KC_NO},   	\
    { L00, 		KC_NO},    \
}

    /*{ KC_NO,  L04},  	  \
    {	KC_NO,  L03},    \
    {	KC_NO,  L02},    \
    { KC_NO,  L01},   	\
    { L00, 		KC_NO },    \*/
