#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>

extern i2c_status_t mcp23018_status;
#define I2C_TIMEOUT			1000
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

uint8_t init_mcp23018(void);

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

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT_buzzsaw(																																	\
    N00,N01,N02,N03,N04,N05,N06,         N07,N08,N09,N10,N11,N12,N13,N14,				A01,		\
    L00,L01,L02,L03,L04,L05,             R00,R01,R02,R03,R04,R05,R06,R07,				A02,		\
    L10,L11,L12,L13,L14,L15,								 R10,R11,R12,R13,R14,R15,R16,				A03,		\
    L20,L21,L22,L23,L24,L25,										 R20,R21,R22,R23,R24,R25,				K00,		\
    L30,L31,L32,L33,																						 R30,R31,   K01,K02,K03)\
{																					 \
		{ N06, KC_NO, KC_NO, KC_NO, KC_NO },   \
		{ N05, L05,		L15,	 L25,		KC_NO },	 \
		{ N04, L04,		L14,	 L24,		KC_NO},		 \
		{ N03, L03,		L13,	 L23,		L33},			 \
		{ N02, L02,		L12,   L22,		L32},			 \
		{ N01, L01,		L11,	 L21,		L31},      \
		{ N00, L00,		L10,   L20,		L30},      \
																					 \
    { N07,   R00,		R10,   R20,		R30},    \
    { N08,	 R01,   R11,   R21,		R31},    \
    { N09,   R02,   R12,   R22,   K01},   \
    { N10,   R03,   R13,   R23,		K02},   \
    { N11,   R04,   R14,   R24,		K03},   \
    { N12,   R05,   R15,   R25,		KC_NO},  \
    { N13,   R06,   R16,   K00,		KC_NO},  \
    { N14,   R07,   A03,	 KC_NO, KC_NO},  \
    { A01,   A02,   KC_NO, KC_NO, KC_NO},  \
}
