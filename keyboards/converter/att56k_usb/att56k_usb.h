#pragma once

#include "quantum.h"
#include "att56k_if.h"

void matrix_init_user(void);

/*
 * ATT 56K 460 ACW
 *
 * Keymap array: 8x16
 *    0  ...  F
 *   +---------+
 *  0|         |
 *  :|         | 0x00-0x7f
 *  :|         |
 *  7|         |
 *   +---------+
 */


enum custom_keycodes {
  CLCK_CYC = SAFE_RANGE,
  NEW_SAFE_RANGE //use "NEW_SAFE_RANGE" for keymap specific codes
};

#define LAYOUT( \
                        K3C, K08, K56, K03, K24, K06, K04, K30, K7C, K3D, K49, K74, \
                        K0E, K38, K1D, K5F, K79, K6C, K53, K7A, K1F, K3F, K2F, K2B, \
  K1A, K2C,   K20, K58, K09, K3E, K7E, K10, K2E, K3A, K4C, K5E, K0F, K27, K2D,   K4B,     K57, K7B, K4E,   K12, K14, K07, K7F, \
  K26, K37,     K46,  K3B, K23, K33, K76, K16, K34, K40, K6B, K48, K66, K75, K69,         K39, K42, K68,   K64, K0A, K5C, K4A, \
  K43, K44,      K19,  K35, K29, K63, K70, K22, K28, K05, K65, K73, K60, K5A, K6F, K21,        K2A,        K4D, K6D, K50, K0C, \
  K32, K52,    K61, K17, K11, K5D, K6A, K1C, K0B, K7D, K77, K5B, K55, K4F,      K54,      K45, K67, K71,   K36, K6E, K1E, K00, \
  K31, K78,    K47,       K59,                       K41,                K62,      K25,        K13,           K18,   K02      \
) { \
    { K00  , KC_NO, K02  , K03  , K04  , K05  , K06  , K07  , K08   , K09  , K0A  , K0B  , K0C  , KC_NO, K0E  , K0F  , }, \
    { K10  , K11  , K12  , K13  , K14  , KC_NO, K16  , K17  , K18   , K19  , K1A  , KC_NO, K1C  , K1D  , K1E  , K1F  , }, \
    { K20  , K21  , K22  , K23  , K24  , K25  , K26  , K27  , K28   , K29  , K2A  , K2B  , K2C  , K2D  , K2E  , K2F  , }, \
    { K30  , K31  , K32  , K33  , K34  , K35  , K36  , K37  , K38   , K39  , K3A  , K3B  , K3C  , K3D  , K3E  , K3F  , }, \
    { K40  , K41  , K42  , K43  , K44  , K45  , K46  , K47  , K48   , K49  , K4A  , K4B  , K4C  , K4D  , K4E  , K4F  , }, \
    { K50  , KC_NO, K52  , K53  , K54  , K55  , K56  , K57  , K58   , K59  , K5A  , K5B  , K5C  , K5D  , K5E  , K5F  , }, \
    { K60  , K61  , K62  , K63  , K64  , K65  , K66  , K67  , K68   , K69  , K6A  , K6B  , K6C  , K6D  , K6E  , K6F  , }, \
    { K70  , K71  , KC_NO, K73  , K74  , K75  , K76  , K77  , K78   , K79  , K7A  , K7B  , K7C  , K7D  , K7E  , K7F  , }  \
}

void on_scan(void);

