#ifndef SX60_H
#define SX60_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses (see "mcp23018.md")
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

extern uint8_t mcp23018_status;

uint8_t init_mcp23018(void);

#define KEYMAP( \
	K00, K01, K02, K03, K04, K05, K06,          K08, K09, K010, K011, K012, K013, K014, K015, \
	K10, K11, K12, K13, K14, K15, K16,          K18, K19, K110, K111, K112, K113, K114, K115, \
	K20, K21, K22, K23, K24, K25, K26,          K28, K29, K210, K211, K212, K213, K214, \
	K30, K31,      K33, K34, K35, K36, K37,     K38, K39, K310, K311, K312, K313, K314, K315, \
	K40, K41, K42, K43, K44, K45,               K48, K49, K410, K411, K412, K413 \
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO,  K08, K09, K010, K011, K012, K013, K014,  K015  }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO,  K18, K19, K110, K111, K112, K113, K114,  K115  }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO,  K28, K29, K210, K211, K212, K213, K214,  KC_NO }, \
	{ K30,   K31,   KC_NO, K33,   K34,   K35,   K36,   K37,    K38, K39, K310, K311, K312, K313, K314,  K315  }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   KC_NO, KC_NO,  K48, K49, K410, K411, K412, K413, KC_NO, KC_NO }  \
}

#endif
/*#define KEYMAP( \
	K00, K01, K02, K03, K04, K05, K06,      \
	K10, K11, K12, K13, K14, K15, K16,      \
	K20, K21, K22, K23, K24, K25, K26,      \
	K30, K31,      K33, K34, K35, K36, K37, \
	K40, K41, K42, K43, K44, K45  \
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO }, \
	{ K30,   K31,   KC_NO, K33,   K34,   K35,   K36,   K37 }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   KC_NO, KC_NO }  \
}

#endif*/
