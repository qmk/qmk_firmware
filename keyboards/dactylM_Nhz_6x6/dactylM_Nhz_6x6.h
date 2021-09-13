/* Copyright 2020 NeohertzParts
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include "i2c_master.h"

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

#define DACTYL_I2C_TIMEOUT 100

extern i2c_status_t mcp23018_status;
uint8_t init_mcp23018(void);



#define LAYOUT_6x6( \
		K05, K04, K03, K02, K01, K00, 	  K07, K08, K09, K0A, K0B, K0C, \
		K15, K14, K13, K12, K11, K10, 	  K17, K18, K19, K1A, K1B, K1C, \
		K25, K24, K23, K22, K21, K20, 	  K27, K28, K29, K2A, K2B, K2C, \
		K35, K34, K33, K32, K31, K30, 	  K37, K38, K39, K3A, K3B, K3C, \
		K45, K44, K43, K42, K41, K40, 	  K47, K48, K49, K4A, K4B, K4C, \
				  K53, K52,            	  			K59, K5A,       \
				       K51, K50,  	           K57, K58,               \
							K36, K06,  	  K0D, K3D,               \
				            K26, K16,     K1D, K2D             \
									   								  \
) { \
		{ K00,   K01,   K02, K03, K04,   K05,  K06 }, \
		{ K10,   K11,   K12, K13, K14,   K15,  K16 }, \
		{ K20,   K21,   K22, K23, K24,   K25,  K26 }, \
		{ K30,   K31,   K32, K33, K34,   K35,  K36 }, \
		{ K40,   K41, 	K42, K43, K44,   K45,  KC_NO }, \
		{ K50,   K51, 	K52, K53, KC_NO, KC_NO,KC_NO }, \
		\
		{ K07,   K08,   K09, K0A, K0B,   K0C,  K0D }, \
		{ K17,   K18,   K19, K1A, K1B,   K1C,  K1D }, \
		{ K27,   K28,   K29, K2A, K2B,   K2C,  K2D }, \
		{ K37,   K38,   K39, K3A, K3B,   K3C,  K3D }, \
		{ K47,   K48,   K49, K4A, K4B,   K4C,  KC_NO }, \
		{ K57,   K58, 	K59, K5A, KC_NO, KC_NO,KC_NO} \
}

/*
#define LAYOUT( \
		K05, K04, K03, K02, K01, K00, 	  K07, K08, K09, K0A, K0B, K0C, \
		K15, K14, K13, K12, K11, K10, 	  K17, K18, K19, K1A, K1B, K1C, \
		K25, K24, K23, K22, K21, K20, 	  K27, K28, K29, K2A, K2B, K2C, \
				  K33, K32,            	          K39, K3A,           \
							K31, K30,  	  K37, K38,                     \
							K36, K06,  	  K0D, K3D,                     \
				  K26, K16,            	          K1D, K2D           \
									   								  \
) { \
		{ K00,   K01,   K02, K03, K04,   K05,  K06 }, \
		{ K10,   K11,   K12, K13, K14,   K15,  K16 }, \
		{ K20,   K21,   K22, K23, K24,   K25,  K26 }, \
		{ K30, K31, 	K32, K33, KC_NO, KC_NO,K36 }, \
		\
		{ K07,   K08,   K09, K0A, K0B,   K0C,  K0D }, \
		{ K17,   K18,   K19, K1A, K1B,   K1C,  K1D }, \
		{ K27,   K28,   K29, K2A, K2B,   K2C,  K2D }, \
		{ K37,   K38, 	K39, K3A, KC_NO, KC_NO,K3D} \
} */

/*
#define LAYOUT_ergodox(                                         \
                                                                \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                                k54,                            \
                        k53,k52,k51,                            \
                                                                \
        k07,k08,k09,k0A,k0B,k0C,k0D,                            \
        k17,k18,k19,k1A,k1B,k1C,k1D,                            \
            k28,k29,k2A,k2B,k2C,k2D,                            \
        k37,k38,k39,k3A,k3B,k3C,k3D,                            \
                k49,k4A,k4B,k4C,k4D,                            \
    k57,k58,                                                    \
    k59,                                                        \
    k5C,k5B,k5A )                                               \
                                                                \
    matrix positions                                        \
   {                                                            \
    { k00, k10, k20, k30, k40, KC_NO },   \
    { k01, k11, k21, k31, k41, k51 },   \
    { k02, k12, k22, k32, k42, k52 },   \
    { k03, k13, k23, k33, k43, k53 },   \
    { k04, k14, k24, k34, k44, k54 },   \
    { k05, k15, k25, k35, KC_NO, k55 },   \
    { k06, k16, KC_NO, k36, KC_NO, k56 },   \
                                                                 \
    { k07, k17, KC_NO, k37,KC_NO, k57 },   \
    { k08, k18, k28, k38,KC_NO, k58 },   \
    { k09, k19, k29, k39, k49, k59 },   \
    { k0A, k1A, k2A, k3A, k4A, k5A },   \
    { k0B, k1B, k2B, k3B, k4B, k5B },   \
    { k0C, k1C, k2C, k3C, k4C, k5C },   \
    { k0D, k1D, k2D, k3D, k4D, KC_NO }    \
   }

#define LAYOUT(\
    L00, L01, L02, L03, L04, L05,                    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                    R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                    R20, R21, R22, R23, R24, R25, \
              L32, L33,                                        R32, R33,           \
                        L34, L35,                    R30, R31,                     \
                        L44, L45,                    R40, R41,                     \
              L42, L43,                                        R42, R43            \
    ) \
    { \
        { L00,   L01,   L02, L03, L04, L05 }, \
        { L10,   L11,   L12, L13, L14, L15 }, \
        { L20,   L21,   L22, L23, L24, L25 }, \
        { KC_NO, KC_NO, L32, L33, L34, L35 }, \
        { KC_NO, KC_NO, L42, L43, L44, L45 }, \
\
        { R00, R01, R02, R03, R04,   R05   }, \
        { R10, R11, R12, R13, R14,   R15   }, \
        { R20, R21, R22, R23, R24,   R25   }, \
        { R30, R31, R32, R33, KC_NO, KC_NO }, \
        { R40, R41, R42, R43, KC_NO, KC_NO } \
\
   } */
