#ifndef SX60_H
#define SX60_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

/* I2C aliases and register addresses (see "mcp23018.md") */
#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
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

#define LAYOUT( \
	      K00, K01, K02, K03, K04, K05, K06,    K07, K08, K09, K10, K11, K12, K13, K14, \
	K15,  K16,    K17, K18, K19, K20, K21,    K22, K23, K24, K25, K26, K27, K28,  K29, \
	K30,    K31,    K32, K33, K34, K35, K36,    K37, K38, K39, K40, K41, K42, K43, K44, \
	K45,   K46,  K47, K48, K49, K50, K51, K52,    K53, K54, K55, K56, K57,  K58,   K59, \
	K60,  K61,   K62,   K63,   K64,   K65,       K66,     K67,    K68,   K69, K70, K71 \
) { \
	{ K00, K01, K02, K03, K04, K05, K06,   KC_NO, K07, K08, K09, K10, K11, K12, K13,   K14   }, \
	{ K15, K16, K17, K18, K19, K20, K21,   KC_NO, K22, K23, K24, K25, K26, K27, K28,   K29   }, \
	{ K30, K31, K32, K33, K34, K35, K36,   KC_NO, K37, K38, K39, K40, K41, K42, K43,   K44   }, \
	{ K45, K46, K47, K48, K49, K50, K51,   K52,   K53, K54, K55, K56, K57, K58, K59,   K59   }, \
	{ K60, K61, K62, K63, K64, K65, KC_NO, KC_NO, K66, K67, K68, K69, K70, K71, KC_NO, KC_NO }  \
}

#define LAYOUT_ansi_split_bs_rshift( \
	      K00, K01, K02, K03, K04, K05, K06,    K07, K08, K09, K10, K11, K12, K13, K14, \
	K15,  K16,   K17, K18, K19, K20, K21,    K22, K23, K24, K25, K26, K27, K28,   K29, \
	K30,    K31,  K32, K33, K34, K35, K36,    K37, K38, K39, K40, K41, K42,      K43, \
	K44,     K45,   K46, K47, K48, K49, K50,    K51, K52, K53, K54, K55,   K56,    K57, \
	K58,  K59,   K60,   K61,   K62,   K63,        K64,     K65,   K66,   K67, K68, K69 \
) { \
	{ K00, K01, K02,   K03, K04, K05, K06,   KC_NO, K07, K08, K09, K10, K11, K12, K13,   K14   }, \
	{ K15, K16, K17,   K18, K19, K20, K21,   KC_NO, K22, K23, K24, K25, K26, K27, K28,   K29   }, \
	{ K30, K31, K32,   K33, K34, K35, K36,   KC_NO, K37, K38, K39, K40, K41, K42, K43,   KC_NO }, \
	{ K44, K45, KC_NO, K46, K47, K48, K49,   K50,   K51, K52, K53, K54, K55, K56, K57,   K57   }, \
	{ K58, K59, K60,   K61, K62, K63, KC_NO, KC_NO, K64, K65, K66, K67, K68, K69, KC_NO, KC_NO }  \
}

#define LAYOUT_ansi_split_bs( \
	      K00, K01, K02, K03, K04, K05, K06,    K07, K08, K09, K10, K11, K12, K13, K14, \
	K15,  K16,   K17, K18, K19, K20, K21,    K22, K23, K24, K25, K26, K27, K28,   K29, \
	K30,    K31,  K32, K33, K34, K35, K36,    K37, K38, K39, K40, K41, K42,      K43, \
	K44,     K45,   K46, K47, K48, K49, K50,    K51, K52, K53, K54, K55,     K56, \
 	K57,  K58,   K59,   K60,   K61,   K62,        K63,     K64,   K65,   K66, K67, K68 \
) { \
	{ K00, K01, K02,   K03, K04, K05, K06,   KC_NO, K07, K08, K09, K10, K11, K12, K13,   K14   }, \
	{ K15, K16, K17,   K18, K19, K20, K21,   KC_NO, K22, K23, K24, K25, K26, K27, K28,   K29   }, \
	{ K30, K31, K32,   K33, K34, K35, K36,   KC_NO, K37, K38, K39, K40, K41, K42, K43,   KC_NO }, \
	{ K44, K45, KC_NO, K46, K47, K48, K49,   K50,   K51, K52, K53, K54, K55, K56, KC_NO, KC_NO }, \
	{ K57, K58, K59,   K60, K61, K62, KC_NO, KC_NO, K63, K64, K65, K66, K67, K68, KC_NO, KC_NO }  \
}

#define LAYOUT_ansi_split_rshift( \
	      K00, K01, K02, K03, K04, K05, K06,    K07, K08, K09, K10, K11, K12, K13, \
	K14,  K15,   K16, K17, K18, K19, K20,    K21, K22, K23, K24, K25, K26, K27,   K28, \
	K29,    K30,  K31, K32, K33, K34, K35,    K36, K37, K38, K39, K40, K41,      K42, \
	K43,     K44,   K45, K46, K47, K48, K49,    K50, K51, K52, K53, K54,   K55,    K56, \
	K57,  K58,   K59,   K60,   K61,   K62,        K63,     K64,   K65,   K66, K67, K68 \
) { \
	{ K00, K01, K02,   K03, K04, K05, K06,   KC_NO, K07, K08, K09, K10, K11, K12, K13,   K13   }, \
	{ K14, K15, K16,   K17, K18, K19, K20,   KC_NO, K21, K22, K23, K24, K25, K26, K27,   K28   }, \
	{ K29, K30, K31,   K32, K33, K34, K35,   KC_NO, K36, K37, K38, K39, K40, K41, K42,   KC_NO }, \
	{ K43, K44, KC_NO, K45, K46, K47, K48,   K49,   K50, K51, K52, K53, K54, K55, K56,   K56   }, \
	{ K57, K58, K59,   K60, K61, K62, KC_NO, KC_NO, K63, K64, K65, K66, K67, K68, KC_NO, KC_NO }  \
}

#endif
