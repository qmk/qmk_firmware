#ifndef IBM_TERMINAL_H
#define IBM_TERMINAL_H

#include "quantum.h"

void matrix_init_user(void);

/*
 * IBM Terminal keyboard 6110345(122keys)/1392595(102keys)
 * http://geekhack.org/showthread.php?10737-What-Can-I-Do-With-a-Terminal-Model-M
 * http://www.seasip.info/VintagePC/ibm_1391406.html
 *
 * Keymap array:
 *     8 bytes
 *   +---------+
 *  0|         |
 *  :|         | 0x00-0x87
 *  ;|         |
 * 17|         |
 *   +---------+
 */
#define KEYMAP( \
                  K08,K10,K18,K20,K28,K30,K38,K40,K48,K50,K57,K5F,                                         \
                  K07,K0F,K17,K1F,K27,K2F,K37,K3F,K47,K4F,K56,K5E,                                         \
                                                                                                           \
    K05,K06,  K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K5D,K66,  K67,K6E,K6F,  K76,K77,K7E,K84, \
    K04,K0C,  K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,    K5C,  K64,K65,K6D,  K6C,K75,K7D,K7C, \
    K03,K0B,  K14,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K53,K5A,      K63,      K6B,K73,K74,K7B, \
    K83,K0A,  K12,K13,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K51,K59,  K61,K62,K6A,  K69,K72,K7A,K79, \
    K01,K09,  K11,    K19,            K29,                    K39,    K58,      K60,      K68,K70,K71,K78  \
) { \
    { KC_NO, K01,   KC_NO, K03,   K04,   K05,   K06,   K07   }, \
    { K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17   }, \
    { K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27   }, \
    { K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37   }, \
    { K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F   }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47   }, \
    { K48,   K49,   K4A,   K4B,   K4C,   K4D,   K4E,   K4F   }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57   }, \
    { K58,   K59,   K5A,   K5B,   K5C,   K5D,   K5E,   K5F   }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67   }, \
    { K68,   K69,   K6A,   K6B,   K6C,   K6D,   K6E,   K6F   }, \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77   }, \
    { K78,   K79,   K7A,   K7B,   K7C,   K7D,   K7E,   KC_NO }, \
    { KC_NO, KC_NO, KC_NO, K83,   K84,   KC_NO, KC_NO, KC_NO,}, \
}

/*
 * IBM Terminal keyboard 1399625, 101-key
 */
#define KEYMAP_101( \
    K08,    K07,K0F,K17,K1F,K27,K2F,K37,K3F,K47,K4F,K56,K5E,  K57,K5F,K62,                   \
                                                                                             \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66,  K67,K6E,K6F,  K76,K77,K7E,K84, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5C,  K64,K65,K6D,  K6C,K75,K7D,     \
    K14,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,                K6B,K73,K74,K7C, \
    K12,    K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K59,      K63,      K69,K72,K7A,     \
    K11,    K19,            K29,                K39,    K58,  K61,K60,K6A,  K70,    K71,K79  \
) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K07   }, \
    { K08,   KC_NO, KC_NO, KC_NO, KC_NO, K0D,   K0E,   K0F   }, \
    { KC_NO, K11,   K12,   KC_NO, K14,   K15,   K16,   K17   }, \
    { KC_NO, K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { KC_NO, K21,   K22,   K23,   K24,   K25,   K26,   K27   }, \
    { KC_NO, K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F   }, \
    { KC_NO, K31,   K32,   K33,   K34,   K35,   K36,   K37   }, \
    { KC_NO, K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F   }, \
    { KC_NO, K41,   K42,   K43,   K44,   K45,   K46,   K47   }, \
    { KC_NO, K49,   K4A,   K4B,   K4C,   K4D,   K4E,   K4F   }, \
    { KC_NO, KC_NO, K52,   KC_NO, K54,   K55,   K56,   K57   }, \
    { K58,   K59,   K5A,   K5B,   K5C,   KC_NO, K5E,   K5F   }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67   }, \
    { KC_NO, K69,   K6A,   K6B,   K6C,   K6D,   K6E,   K6F   }, \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77   }, \
    { KC_NO, K79,   K7A,   KC_NO, K7C,   K7D,   K7E,   KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, K84,   KC_NO, KC_NO, KC_NO,}, \
}

#endif