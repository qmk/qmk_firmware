#ifndef NUMNAVPAD_H
#define NUMNAVPAD_H

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
extern uint8_t expander_input_pin_masK;
extern bool i2c_initialized;

void init_numnavpad(void);
void init_expander(void);

/*
 *   LEFT HAND: LINES 38-45
 *  RIGHT HAND: LINES 47-54
 */
#define LAYOUT(                                                  \
    K00,K01,K02,     K03,K04,K05,K06, \
    K10,K11,K12,     K13,K14,K15,K16, \
    K20,K21,K22,     K23,K24,K25,K26, \
    K30,K31,K32,     K33,K34,K35,K36, \
    K40,K41,K42,     K43,K44,K45,K46  \
) \
   { \
    { K00, K01, K02,   K03, K04, K05, K06 }, \
    { K10, K11, K12,   K13, K14, K15, K16 }, \
    { K20, K21, K22,   K23, K24, K25, K26 }, \
    { K30, K31, K32,   K33, K34, K35, K36 }, \
    { K40, K41, K42,   K43, K44, K45, K46 }, \
   }


#endif
