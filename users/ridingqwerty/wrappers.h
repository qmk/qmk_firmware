#pragma once
#include "ridingqwerty.h"

// clang-format off
#define LAYOUT_atreus_wrapper(...)  LAYOUT_atreus(__VA_ARGS__)
#define LAYOUT_minorca_wrapper(...) LAYOUT_minorca(__VA_ARGS__)

#define ___________VI_ARROWS______________                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT

//      1......__2......__3......__4......__5......        1......__2......__3......__4......__5......
#define ________________QWERTY_L1__________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define ________________QWERTY_L2__________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define ________________QWERTY_L3__________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define ________________QWERTY_R1__________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define ________________QWERTY_R2__________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define ________________QWERTY_R3__________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH


#define ________________ATREUS_L1__________________        ________________QWERTY_L1__________________
#define ________________ATREUS_L2__________________        ED(A),   KC_S,    KC_D,    KC_F,    KC_G
#define ________________ATREUS_L3__________________        LS(Z),   KC_X,    KC_C,    KC_V,    KC_B

#define ________________ATREUS_R1__________________        ________________QWERTY_R1__________________
#define ________________ATREUS_R2__________________        KC_H,    KC_J,    KC_K,    KC_L,    NM(SCLN)
#define ________________ATREUS_R3__________________        KC_N,    KC_M,    KC_COMM, FK(DOT), RS(SLSH)

#define ________________FNHOMEROW_L2_______________        C(KC_A), G(KC_S), A(KC_D), S(KC_F), KC_G
#define ________________FNHOMEROW_R2_______________        KC_H,    S(KC_J), A(KC_K), G(KC_L), C(SCLN)

#define ____THUMBS_R4___        ED(ESC), DB(TAB)
#define _____BLANK_R4___        _______, _______
#define ________________        _______, _______


#define ________________COLEMAK_L1_________________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define ________________COLEMAK_L2_________________        ED(A),   KC_R,    KC_S,    KC_T,    KC_D
#define ________________COLEMAK_L3_________________        LS(Z),   KC_X,    KC_C,    KC_V,    KC_B

#define ________________COLEMAK_R1_________________        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ________________COLEMAK_R2_________________        KC_H,    KC_N,    KC_E,    KC_I,    NM(O)
#define ________________COLEMAK_R3_________________        KC_K,    KC_M,    KC_COMM, FK(DOT), RS(SLSH)


#define ________________DVORAK_L1__________________        KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define ________________DVORAK_L2__________________        ED(A),   KC_O,    KC_E,   KC_U,     KC_I
#define ________________DVORAK_L3__________________        LS(SCLN),KC_Q,    KC_J,   KC_K,     KC_X

#define ________________DVORAK_R1__________________        KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define ________________DVORAK_R2__________________        KC_D,    KC_H,    KC_T,    KC_N,    NM(S)
#define ________________DVORAK_R3__________________        KC_B,    KC_M,    KC_W,    FK(V),   RS(Z)

#define ________________BOTTOM_L4__________________        LC(ESC), LG(TAB),  LA(LBRC), LS(RBRC), NM(BSPC)
#define ________________BOTTOM_R4__________________        SM(SPC), RS(MINS), RA(EQL),  RG_QUOT,  RC(ENT)


#define ________________NUMROW_L1__________________        KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMROW_R1__________________        KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define ________________NUMPAD_R1__________________        _______, KC_7,    KC_8,    KC_9,    KC_0
#define ________________NUMPAD_R2__________________        _______, KC_4,    KC_5,    KC_6,    _______
#define ________________NUMPAD_R3__________________        _______, KC_1,    KC_2,    KC_3,    KC_BSLS
#define ________________NUMPAD_R4__________________        KC_0,    KC_0,    KC_DOT,  KC_3,    _______


#define ________________SYMROW_L1__________________        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define ________________SYMROW_R1__________________        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN


#define ________________                                   _______, _______
#define _________________________                          _______, _______, _______
#define __________________________________                 _______, _______, _______, _______
#define ___________________________________________        _______, _______, _______, _______, _______
#define ___________________________________________        _______, _______, _______, _______, _______
#define ___________________________________________        _______, _______, _______, _______, _______
#define ________________BLANK______________________        ___________________________________________
#define ________________BLOCK______________________        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX        ________________BLOCK______________________

#define ________________FKEYROW_L1_________________        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ________________FKEYROW_R1_________________        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ________________EDITOR_L1__________________        KC_GRV,  _______, KC_END,  _______, KC_F5  
#define ________________EDITOR_L2__________________        KC_HOME, _______, KC_DELT, _______, _______
#if defined(TAP_DANCE_ENABLE)
#define ________________EDITOR_L3__________________        _______, KC_VOLD, KC_VOLU, CCCV,    TD_BRC
#else
#define ________________EDITOR_L3__________________        _______, KC_VOLD, KC_VOLU, CCCV,    _______
#endif

#define ________________EDITOR_R1__________________        _______, _______, KC_INS,  _______, KC_PGUP
#define ________________EDITOR_R2__________________        ___________VI_ARROWS______________, _______
#define ________________EDITOR_R3__________________        KC_PGDN, _______, _______, _______, KC_BSLS


#define ________________DEBUG_L1___________________        DEBUG,   _______, _______, RNGWORD, SARCASM
#define ________________DEBUG_L2___________________        GREEK,   RUSSIAN, HIRAGAN, RUNES,   _______
#define ________________DEBUG_L3___________________        _______, _______, _______, VERSION, _______

#define ________________DEBUG_R1___________________        VPRWAVE, STRAYA,  _______, TESTING, _______
#define ________________DEBUG_R2___________________        _______, _______, EEP_RST, RESET,   MAKE
#define ________________DEBUG_R3___________________        QWERTY,  DVORAK,  COLEMAK, _______, _______


#define ________________SECRET_L1__________________        _______, _______, _______, SECRET0, SECRET1
#define ________________SECRET_L2__________________        SECRET4, SECRET8, _______, _______, _______
#define ________________SECRET_L3__________________        SECRET7, _______, SECRET2, SECRET5, _______

#define ________________SECRET_R1__________________        _______, _______, _______, _______, _______
#define ________________SECRET_R2__________________        _______, _______, _______, SECRET6, _______
#define ________________SECRET_R3__________________        _______, SECRET3, _______, _______, _______


#if defined(UNICODEMAP_ENABLE)
// Greek
#define ________________GREEK_L1___________________        THETA,   OMEGA,   EPSLN,   RHO,     TAU
#define ________________GREEK_L2___________________        ALPHA,   SIGMA,   DELTA,   PHI,     GAMMA
#define ________________GREEK_L3___________________        ZETA,    XI,      CHI,     PHI,     BETA
#define ________________GREEK_R1___________________        UPSLN,   UPSLN,   IOTA,    OMCRN,   PI
#define ________________GREEK_R2___________________        ETA,     PSI,     KAPPA,   LAMBD,   NM(SCLN)
#define ________________GREEK_R3___________________        NU,      GMU,     KC_COMM, FK(DOT), RS(SLSH)

// Elder Futhark
#define ________________FTHRK_L1___________________        INGWZ,   WUNJO,   EHWAZ,   RAIDO,   TIWAZ
#define ________________FTHRK_L2___________________        ANSUZ,   SOWIL,   DAGAZ,   FE,      GEBO
#define ________________FTHRK_L3___________________        ALGIZ,   THURS,   KAUNA,   WUNJO,   BEORC
#define ________________FTHRK_R1___________________        IWAZ,    UR,      ISAZ,    ETHEL,   PERTH
#define ________________FTHRK_R2___________________        HAGLZ,   JERAN,   KAUNA,   LAUKZ,   KC_SCLN
#define ________________FTHRK_R3___________________        NAUDZ,   MANNZ,   KC_COMM, KC_DOT,  KC_SLSH

// Russian Cyrillic
#define ________________CYRLC_L1___________________        YA,      SCHA,    IE,      ER,      TE
#define ________________CYRLC_L2___________________        AH,      ES,      DE,      EF,      GHE
#define ________________CYRLC_L3___________________        ZE,      HA,      TSE,     VE,      BE
#define ________________CYRLC_R1___________________        YERU,    UU,      IH,      OH,      PE
#define ________________CYRLC_R2___________________        CHE,     SIH,     KA,      EL,      SOFT
#define ________________CYRLC_R3___________________        EN,      EM,      YU,      SCHA,    EH
#define ________________CYRLC_R4___________________        SM(SPC), IO,      HARD,    ZHE,     RC(ENT)

// Hiragana
#define ________________JIS1_R1____________________        JTA,     JTE,     JI,      JSU,     JKA
#define ________________JIS1_R2____________________        JTI,     JTO,     JSI,     JHA,     JKI
#define ________________JIS1_R3____________________        JMI,     JMO,     KC_COMM, KC_DOT,  MO(_HIRA2)
#define ________________JIS1_L1____________________        JN,      JNA,     JNI,     JRA,     JSE
#define ________________JIS1_L2____________________        JKU,     JMA,     JNO,     JRI,     JRE
#define ________________JIS1_L3____________________        JTU,     JSA,     JSO,     JHI,     JKO

#define ________________JIS2_R1____________________        JRO,     JWA,     JNU,     JHU,     JA
#define ________________JIS2_R2____________________        JYO,     JHO,     JHE,     JMU,     JVV
#define ________________JIS2_R3____________________        JRU,     JME,     KC_COMM, KC_DOT,  _______
#define ________________JIS2_L1____________________        JU,      JE,      JO,      JYA,     JYU
#define ________________JIS2_L2____________________        JSV,     JKE,     JMI,     JMO,     JNE
#define ________________JIS2_L3____________________        JTU,     JSA,     JSO,     JHI,     JKO

#endif
// clang-format on
