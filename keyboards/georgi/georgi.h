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
#define LAYOUT_georgi(                                            \
    L00,L01,L02,L03,L04,L05,            R00,R01,R02,R03,R04,R05,  \
    L10,L11,L12,L13,L14,L15,            R10,R11,R12,R13,R14,R15,  \
               	L20,L21,L22,            R20,R21,R22)              \
                                                                  \
    {                         \
    { KC_NO,  R00,   R10,   R21},     \
    { KC_NO,  R01,   R11,   R20},     \
    { KC_NO,  R02,   R12,   R22},     \
    { KC_NO,  R03,   R13,   KC_NO},   \
    { KC_NO,  R04,   R14,   KC_NO},   \
    { KC_NO,  R05,   R15,   KC_NO},   \
    { KC_NO,  KC_NO, KC_NO, KC_NO},     \
							  \
    { KC_NO,  L05,   L15,   L22},     \
    { KC_NO,  L04,   L14,   L21},     \
    { KC_NO,  L03,   L13,   L20},     \
    { KC_NO,  L02,   L12,   KC_NO},   \
    { KC_NO,  L01,   L11,   KC_NO},   \
    { KC_NO,  L00,   L10,   KC_NO},   \
    { KC_NO,  KC_NO, KC_NO, KC_NO},     \
                              \
}

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- 
#define LAYOUT_GERGO(                                                    \
    L00,L01,L02,L03,L04,L05,                   R00,R01,R02,R03,R04,R05,  \
    L10,L11,L12,L13,L14,L15,L16,           R10,R11,R12,R13,R14,R15,R16,  \
    L20,L21,L22,L23,L24,L25,L26,           R20,R21,R22,R23,R24,R25,R26,  \
                L31,L32,                           R33,R34,              \
                            L30,           R30,                          \
                        L33,L34,           R31,R32)                      \
                                                                         \
    {                               \
    { KC_NO, L16,   L26,  L30},     \
    { L05,   L15,   L25,  L34},     \
    { L04,   L14,   L24,  L33},     \
    { L03,   L13,   L23,  L32},     \
    { L02,   L12,   L22,  L31},     \
    { L01,   L11,   L21,  KC_NO},   \
    { L00,   L10,   L20,  KC_NO},   \
                                    \
    { KC_NO, R10, R20, R30},      \
    { R00,   R11,   R21, R31},      \
    { R01,   R12,   R22, R32},      \
    { R02,   R13,   R23, R33},      \
    { R03,   R14,   R24, R34},      \
    { R04,   R15,   R25, KC_NO},    \
    { R05,   R16,   R26, KC_NO},    \
} */
