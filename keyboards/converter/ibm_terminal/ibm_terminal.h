#ifndef IBM_TERMINAL_H
#define IBM_TERMINAL_H

#include "quantum.h"

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
    { KC_NO,    KC_##K01, KC_NO,    KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_##K78, KC_##K79, KC_##K7A, KC_##K7B, KC_##K7C, KC_##K7D, KC_##K7E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K83, KC_##K84, KC_NO,    KC_NO,    KC_NO,   }, \
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
    { KC_NO,    KC_NO   , KC_NO,    KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##K07 }, \
    { KC_##K08, KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_NO   , KC_##K11, KC_##K12, KC_NO   , KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_NO   , KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_NO   , KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_NO   , KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_NO   , KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_NO   , KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_NO   , KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_NO   , KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_NO   , KC_NO   , KC_##K52, KC_NO   , KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_NO   , KC_##K5E, KC_##K5F }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_NO   , KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_NO   , KC_##K79, KC_##K7A, KC_NO   , KC_##K7C, KC_##K7D, KC_##K7E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO   , KC_##K84, KC_NO,    KC_NO,    KC_NO,   }, \
}

#endif