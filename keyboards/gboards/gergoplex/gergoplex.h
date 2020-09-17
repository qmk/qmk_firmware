#pragma once

#include "quantum.h"
#include "i2c_master.h"

extern i2c_status_t mcp23018_status;
#define I2C_TIMEOUT 1000
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz 0x00

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR 0x20  // 0b0100000
#define I2C_ADDR_WRITE ((I2C_ADDR << 1) | I2C_WRITE)
#define I2C_ADDR_READ ((I2C_ADDR << 1) | I2C_READ)
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C  // GPIO pull-up resistor register
#define GPPUB 0x0D
#define GPIOA 0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB 0x13
#define OLATA 0x14  // output latch register
#define OLATB 0x15

uint8_t init_mcp23018(void);

// Create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
    L00, L01, L02, L03, L04,        R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14,        R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24,        R20, R21, R22, R23, R24, \
                L30, L31, L32,    R30, R31, R32 \
    ) \
    { \
        {KC_##L04, KC_##L14, KC_##L24, KC_NO}, \
        {KC_##L03, KC_##L13, KC_##L23, KC_##L32}, \
        {KC_##L02, KC_##L12, KC_##L22, KC_##L31}, \
        {KC_##L01, KC_##L11, KC_##L21, KC_##L30}, \
        {KC_##L00, KC_##L10, KC_##L20, KC_NO}, \
        {KC_##R00, KC_##R10, KC_##R20, KC_NO}, \
        {KC_##R01, KC_##R11, KC_##R21, KC_##R30}, \
        {KC_##R02, KC_##R12, KC_##R22, KC_##R31}, \
        {KC_##R03, KC_##R13, KC_##R23, KC_##R32}, \
        {KC_##R04, KC_##R14, KC_##R24, KC_NO}, \
    }
