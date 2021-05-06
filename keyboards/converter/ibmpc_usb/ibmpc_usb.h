#ifndef IBMPC_USB_H
#define IBMPC_USB_H

#include "quantum.h"

void matrix_init_user(void);

#define LAYOUT_101( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,     KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,K5D,K5A,               K6B,K73,K74,K79, \
    K12,    K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K59,     KF5,      K69,K72,K7A,     \
    K14,    K11,        K29,                K91,        K94, KEB,KF2,KF4,  K70,    K71,KDA  \
) { \
    { KC_NO, K01,   KC_NO, K03,   K04,   K05,   K06,   K07   }, \
    { KC_NO, K09,   K0A,   K0B,   K0C,   K0D,   K0E,   KC_NO }, \
    { KC_NO, K11,   K12,   KC_NO, K14,   K15,   K16,   KC_NO }, \
    { KC_NO, KC_NO, K1A,   K1B,   K1C,   K1D,   K1E,   KC_NO }, \
    { KC_NO, K21,   K22,   K23,   K24,   K25,   K26,   KC_NO }, \
    { KC_NO, K29,   K2A,   K2B,   K2C,   K2D,   K2E,   KC_NO }, \
    { KC_NO, K31,   K32,   K33,   K34,   K35,   K36,   KC_NO }, \
    { KC_NO, KC_NO, K3A,   K3B,   K3C,   K3D,   K3E,   KC_NO }, \
    { KC_NO, K41,   K42,   K43,   K44,   K45,   K46,   KC_NO }, \
    { KC_NO, K49,   K4A,   K4B,   K4C,   K4D,   K4E,   KC_NO }, \
    { KC_NO, KC_NO, K52,   KC_NO, K54,   K55,   KC_NO, KC_NO }, \
    { K58,   K59,   K5A,   K5B,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K66,   KC_NO }, \
    { KC_NO, K69,   KC_NO, K6B,   K6C,   KC_NO, KC_NO, KC_NO }, \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77   }, \
    { K78,   K79,   K7A,   KC_NO, K7C,   K7D,   K7E,   KC_NO }  \
}

typedef enum { NONE, PC_XT, PC_AT, PC_TERMINAL, PC_AT_Z150 } keyboard_kind_t;
#define KEYBOARD_KIND_STR(kind) \
    (kind == PC_XT ? "XT" :   \
     kind == PC_AT ? "AT" :   \
     kind == PC_TERMINAL ? "TERMINAL" :   \
     kind == PC_AT_Z150 ? "AT_Z150" :  \
     "NONE")

extern uint16_t keyboard_id;
extern keyboard_kind_t keyboard_kind;

#endif
