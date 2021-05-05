#ifndef IBMPC_USB_H
#define IBMPC_USB_H

#include "quantum.h"

void matrix_init_user(void);

/*
 * IBM Terminal keyboard 1399625, 101-key
 */
#define KEYMAP_ALL( \
        K08,K10,K18,K20,K28,K30,K38,K40,K48,K50,K57,K5F,                                        \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,         KFC,K7E,KFE,      KA1,KB2,KA3, \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K6A,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,    K5D, KF1,KE9,KFA,  K6C,K75,K7D,K79, \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,        K5A,               K6B,K73,K74,K6D, \
    K12,K61,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K51,K59,     KF5,      K69,K72,K7A,KDA, \
    K14,K9F,K11,K67,    K29,            K64,K13,K91,KA7,KAF,K94, KEB,KF2,KF4,  K68,K70,K71,K63, \
                                                                                            \
    KB7, KBF, KDE,           /* System Power, Sleep, Wake */                                \
    KCD, K95, KBB, KB4, KD0, /* Next, Previous, Stop, Pause, Media Select */                \
    KC8, KAB, KC0,           /* Mail, Calculator, My Computer */                            \
    K90, KBA, KB8, KB0,      /* WWW Search, Home, Back, Forward */                          \
    KA8, KA0, K98            /* WWW Stop, Refresh, Favorites */                             \
) { \
    { KC_NO,         K01, KC_NO,         K03,      K04,      K05,      K06,      K07 }, \
    {      K08,      K09,      K0A,      K0B,      K0C,      K0D,      K0E, KC_NO    }, \
    {      K10,      K11,      K12,      K13,      K14,      K15,      K16, KC_NO    }, \
    {      K18, KC_NO,         K1A,      K1B,      K1C,      K1D,      K1E, KC_NO    }, \
    {      K20,      K21,      K22,      K23,      K24,      K25,      K26, KC_NO    }, \
    {      K28,      K29,      K2A,      K2B,      K2C,      K2D,      K2E, KC_NO    }, \
    {      K30,      K31,      K32,      K33,      K34,      K35,      K36, KC_NO    }, \
    {      K38, KC_NO,         K3A,      K3B,      K3C,      K3D,      K3E, KC_NO    }, \
    {      K40,      K41,      K42,      K43,      K44,      K45,      K46, KC_NO    }, \
    {      K48,      K49,      K4A,      K4B,      K4C,      K4D,      K4E, KC_NO    }, \
    {      K50,      K51,      K52, KC_NO,         K54,      K55, KC_NO,         K57 }, \
    {      K58,      K59,      K5A,      K5B, KC_NO,         K5D, KC_NO,         K5F }, \
    { KC_NO,         K61, KC_NO,         K63,      K64, KC_NO,         K66,      K67 }, \
    {      K68,      K69,      K6A,      K6B,      K6C,      K6D, KC_NO,    KC_NO    }, \
    {      K70,      K71,      K72,      K73,      K74,      K75,      K76,      K77 }, \
    {      K78,      K79,      K7A,      K7B,      K7C,      K7D,      K7E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,         K83, KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    {      K90,      K91, KC_NO,    KC_NO,         K94,      K95, KC_NO,    KC_NO    }, \
    {      K98, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         K9F }, \
    {      KA0,      KA1, KC_NO,         KA3, KC_NO,    KC_NO,    KC_NO,         KA7 }, \
    {      KA8, KC_NO,    KC_NO,         KAB, KC_NO,    KC_NO,    KC_NO,         KAF }, \
    {      KB0, KC_NO,         KB2, KC_NO,         KB4, KC_NO,    KC_NO,         KB7 }, \
    {      KB8, KC_NO,         KBA,      KBB, KC_NO,    KC_NO,    KC_NO,         KBF }, \
    {      KC0, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    {      KC8, KC_NO,         KCA, KC_NO,    KC_NO,         KCD, KC_NO,    KC_NO    }, \
    {      KD0, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,         KDA, KC_NO,    KC_NO,    KC_NO,         KDE, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,         KE9, KC_NO,         KEB,      KEC, KC_NO,    KC_NO,    KC_NO    }, \
    {      KF0,      KF1,      KF2, KC_NO,         KF4,      KF5, KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,         KFA, KC_NO,         KFC,      KFD,      KFE, KC_NO    }, \
}

#define LAYOUT_ISO( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,     KF1,KE9,KFA,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,K5D,K5A,               K6B,K73,K74,K79, \
    K12,K61,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K59,     KF5,      K69,K72,K7A,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KF4,  K70,    K71,KDA  \
)

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
