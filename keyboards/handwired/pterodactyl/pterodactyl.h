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
#define LAYOUT_pterodactyl(                                                  \
                                                                        \
    k00,k01,k02,k03,k04,k05,                                            \
    k10,k11,k12,k13,k14,k15,                                            \
    k20,k21,k22,k23,k24,k25,                                            \
    k30,k31,k32,k33,k34,k35,                                            \
    k40,k41,k42,k43,k44,k53,                                            \
                            k55,k50,                                    \
                                k54,                                    \
                            k52,k51,                                    \
                                                                        \
            k06,k07,k08,k09,k0A,k0B,                                    \
            k16,k17,k18,k19,k1A,k1B,                                    \
            k26,k27,k28,k29,k2A,k2B,                                    \
            k36,k37,k38,k39,k3A,k3B,                                    \
            k58,k47,k48,k49,k4A,k4B,                                    \
    k5B,k56,                                                            \
    k57,                                                                \
    k5A,k59 )                                                       \
                                                                        \
   /* matrix positions */                                               \
   {                                                                    \
    { k0B, k0A, k09, k08, k07, k06,      k05, k04, k03, k02, k01, k00 }, \
    { k1B, k1A, k19, k18, k17, k16,      k15, k14, k13, k12, k11, k10 }, \
    { k2B, k2A, k29, k28, k27, k26,      k25, k24, k23, k22, k21, k20 }, \
    { k3B, k3A, k39, k38, k37, k36,      k35, k34, k33, k32, k31, k30 }, \
    { k4B, k4A, k49, k48, k47, k58,      k53, k44, k43, k42, k41, k40 }, \
    { k56, k5B, k57, k5A, k59, KC_NO,  KC_NO, k52, k51, k54, k50, k55 }, \
   }
#endif
  /* for future comers:
   * the weird ass ordering here is because the dactyl/ergo/etc are wired for the
   * chip to be in the right side, mine is not built that way.
   * that last line is not obvious but its due to the way my columns are wired
   * and are different than the dactyl guide.
   * this is to compensate for my build.
   */
