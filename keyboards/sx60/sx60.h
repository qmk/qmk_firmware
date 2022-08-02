#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>

/* I2C aliases and register addresses (see "mcp23018.md") */
#define I2C_ADDR        (0b0100000 << 1)
#define I2C_TIMEOUT     100
#define IODIRA          0x00            /* i/o direction register */
#define IODIRB          0x01
#define GPPUA           0x0C            /* GPIO pull-up resistor register */
#define GPPUB           0x0D
#define GPIOA           0x12            /* general purpose i/o port register (write modifies OLAT) */
#define GPIOB           0x13
#define OLATA           0x14            /* output latch register */
#define OLATB           0x15

extern uint8_t mcp23018_status;

uint8_t init_mcp23018(void);

#define XXX KC_NO

#define LAYOUT( \
          k00, k01, k02, k03, k04, k05, k06,    k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10,  k11,    k12, k13, k14, k15, k16,    k18, k19, k1A, k1B, k1C, k1D, k1E,  k1F, \
    k20,    k21,    k22, k23, k24, k25, k26,    k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, \
    k30,   k31,  k32, k33, k34, k35, k36, k37,    k38, k39, k3A, k3B, k3C,  k3D,   k3E, \
    k40,  k41,   k42,   k43,   k44,   k45,       k48,     k49,    k4A,   k4B, k4C, k4D \
) { \
    { k00, k01, k02, k03, k04, k05, k06, XXX, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, XXX, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, XXX, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3E }, \
    { k40, k41, k42, k43, k44, k45, XXX, XXX, k48, k49, k4A, k4B, k4C, k4D, XXX, XXX } \
}

#define LAYOUT_ansi_split_bs_rshift( \
          k00, k01, k02, k03, k04, k05, k06,    k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10,  k11,   k12, k13, k14, k15, k16,    k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F, \
    k20,    k21,  k22, k23, k24, k25, k26,    k28, k29, k2A, k2B, k2C, k2D,      k2E, \
    k30,     k31,   k33, k34, k35, k36, k37,    k38, k39, k3A, k3B, k3C,   k3D,    k3E, \
    k40,  k41,   k42,   k43,   k44,   k45,        k48,     k49,   k4A,   k4B, k4C, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, XXX, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, XXX, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, XXX, k28, k29, k2A, k2B, k2C, k2D, k2E, XXX }, \
    { k30, k31, XXX, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3E }, \
    { k40, k41, k42, k43, k44, k45, XXX, XXX, k48, k49, k4A, k4B, k4C, k4E, XXX, XXX } \
}

#define LAYOUT_ansi_split_bs( \
          k00, k01, k02, k03, k04, k05, k06,    k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10,  k11,   k12, k13, k14, k15, k16,    k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F, \
    k20,    k21,  k22, k23, k24, k25, k26,    k28, k29, k2A, k2B, k2C, k2D,      k2E, \
    k30,     k31,   k33, k34, k35, k36, k37,    k38, k39, k3A, k3B, k3C,     k3D, \
    k40,  k41,   k42,   k43,   k44,   k45,        k48,     k49,   k4A,   k4B, k4C, k4D \
) { \
    { k00, k01, k02, k03, k04, k05, k06, XXX, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, XXX, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, XXX, k28, k29, k2A, k2B, k2C, k2D, k2E, XXX }, \
    { k30, k31, XXX, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, XXX, XXX }, \
    { k40, k41, k42, k43, k44, k45, XXX, XXX, k48, k49, k4A, k4B, k4C, k4D, XXX, XXX } \
}

#define LAYOUT_ansi_split_rshift( \
         k00, k01, k02, k03, k04, k05, k06,    k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,  k11,   k12, k13, k14, k15, k16,    k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F, \
    k20,    k21,  k22, k23, k24, k25, k26,    k28, k29, k2A, k2B, k2C, k2D,      k2E, \
    k30,     k31,   k33, k34, k35, k36, k37,    k38, k39, k3A, k3B, k3C,   k3D,    k3E, \
    k40,  k41,   k42,   k43,   k44,   k45,        k48,     k49,   k4A,   k4B, k4C, k4D \
) { \
    { k00, k01, k02, k03, k04, k05, k06, XXX, k08, k09, k0A, k0B, k0C, k0D, k0E, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, XXX, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, XXX, k28, k29, k2A, k2B, k2C, k2D, k2E, XXX }, \
    { k30, k31, XXX, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3E }, \
    { k40, k41, k42, k43, k44, k45, XXX, XXX, k48, k49, k4A, k4B, k4C, k4D, XXX, XXX } \
}
