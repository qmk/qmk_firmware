#ifndef CLEAN60_H
#define CLEAN60_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLkPR = 0x80, CLkPR = (n))
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

void init_clean60(void);
void init_expander(void);

/*
 *   LEFT HAND: LINES 38-45
 *  RIGHT HAND: LINES 47-54
 */
#define LAYOUT_clean60( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,       k0E, \
	k10,       k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
	k20,       k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,       \
	      k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,       k3D,       \
	k40, k41,       k43,             k46,                   k4A, k4B,       k4D, k4E  \
) { \
	{ k00,  k01,  k02,  k03,  k04,  k05,  k06,  k07,  k08,  k09,  k0A,  k0B,  k0C,  KC_NO, k0E }, \
	{ k10,  KC_NO, k12,  k13,  k14,  k15,  k16,  k17,  k18,  k19,  k1A,  k1B,  k1C,  k1D,  k1E }, \
	{ k20,  KC_NO, k22,  k23,  k24,  k25,  k26,  k27,  k28,  k29,  k2A,  k2B,  k2C,  k2D,  KC_NO }, \
	{ KC_NO, k31,  k32,  k33,  k34,  k35,  k36,  k37,  k38,  k39,  k3A,  k3B,  KC_NO, k3D,  KC_NO }, \
	{ k40,  k41,  KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, k4A,  k4B,  KC_NO, k4D,  k4E }  \
}


#endif
