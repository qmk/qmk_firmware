#ifndef PTERODACTYL_H
#define PTERODACTYL_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

#define I2C_ADDR        0b0100000
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

extern uint8_t expander_status;
extern uint8_t expander_input_pin_mask;
extern bool i2c_initialized;

void init_pterodactyl(void);
void init_expander(void);

/*
 *   LEFT HAND: LINES 38-45
 *  RIGHT HAND: LINES 47-54
 */
#define LAYOUT_pterodactyl(                                                       \
                                                                                  \
    k00,k01,k02,k03,k04,k05,k06,                                                  \
    k10,k11,k12,k13,k14,k15,k16,                                                  \
    k20,k21,k22,k23,k24,k25,k26,                                                  \
    k30,k31,k32,k33,k34,k35,k36,                                                  \
    k40,k41,k42,k43,k44,k45,k46,                                                  \
                                                                                  \
          k07,k08,k09,k0A,k0B,k0C,k0D,                                            \
          k17,k18,k19,k1A,k1B,k1C,k1D,                                            \
          k27,k28,k29,k2A,k2B,k2C,k2D,                                            \
          k37,k38,k39,k3A,k3B,k3C,k3D,                                            \
          k47,k48,k49,k4A,k4B,k4C,k4D,KC_NO                                       \
   )                                                                              \
                                                                                  \
   /* matrix positions */                                                         \
   {                                                                              \
    { k00, k01, k02, k03, k04, k05, k06,     k07, k08, k09, k0A, k0B, k0C, k0D }, \
    { k10, k11, k12, k13, k14, k15, k16,     k17, k18, k19, k1A, k1B, k1C, k1D }, \
    { k20, k21, k22, k23, k24, k25, k26,     k27, k28, k29, k2A, k2B, k2C, k2D }, \
    { k30, k31, k32, k33, k34, k35, k36,     k37, k38, k39, k3A, k3B, k3C, k3D }, \
    { k40, k41, k42, k43, k44, k45, k46,     k47, k48, k49, k4A, k4B, k4C, k4D }, \
   }


#endif
