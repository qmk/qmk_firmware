#ifndef USERSPACE_PVINIS_PVINIS_H
#define USERSPACE_PVINIS_PVINIS_H

#include "quantum.h"


// my own keycodes
enum userspace_custom_keycodes {
  PV_ = SAFE_RANGE,

  PV_VERSION, // prints firmware version
  PV_KATAMARI, // play katamari music

  PV_SAFE_RANGE, // used for extra keycodes in the individual keymaps
};


// layouts
enum {
  LR_QWERTY = 0,
  LR_SYSCTL, // system control (music, volume, keyboard flash, etc)
};

// layout parts for easy reuse between keyboard keymaps

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  1  |  2  |  3  |  4  |  5  |   |  6  |  7  |  8  |  9  |  0  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define _________NUMBERS_L__________  KC_1 , KC_2 , KC_3 , KC_4 , KC_5
#define _________NUMBERS_R__________  KC_6 , KC_7 , KC_8 , KC_9 , KC_0

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  Q  |  W  |  E  |  R  |  T  |   |  Y  |  U  |  I  |  O  |  P  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  A  |  S  |  D  |  F  |  G  |   |  H  |  J  |  K  |  L  |  ;  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  Z  |  X  |  C  |  V  |  B  |   |  N  |  M  |  ,  |  .  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define _________QWERTY_L1__________  KC_Q , KC_W , KC_E , KC_R , KC_T
#define _________QWERTY_L2__________  KC_A , KC_S , KC_D , KC_F , KC_G
#define _________QWERTY_L3__________  KC_1 , KC_X , KC_C , KC_V , KC_B

#define _________QWERTY_R1__________  KC_Y , KC_U , KC_I    , KC_O   , KC_P
#define _________QWERTY_R2__________  KC_H , KC_J , KC_K    , KC_L   , KC_SCLN
#define _________QWERTY_R3__________  KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  Q  |  G  |  M  |  L  |  W  |   |  Y  |  F  |  I  |  O  |  P  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  D  |  S  |  T  |  N  |  R  |   |  I  |  A  |  K  |  L  |  ;  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  Z  |  X  |  C  |  V  |  J  |   |  K  |  P  |  ,  |  .  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define ________CARPALX_L1__________ KC_Q , KC_G , KC_M , KC_L , KC_W
#define ________CARPALX_L2__________ KC_D , KC_S , KC_T , KC_N , KC_R
#define ________CARPALX_L3__________ KC_Z , KC_X , KC_C , KC_V , KC_J

#define ________CARPALX_R1__________ KC_Y  , KC_F  , KC_U    , KC_B   , KC_SCLN
#define ________CARPALX_R2__________ KC_I  , KC_A  , KC_E    , KC_O   , KC_H
#define ________CARPALX_R3__________ KC_K  , KC_P  , KC_COMM , KC_DOT , KC_SLSH

#define _________SYSCTL_L1__________         ,         ,         ,         ,
#define _________SYSCTL_L2__________         ,         ,         ,         ,
#define _________SYSCTL_L3__________         ,         ,         ,         ,

//                                    vol v
#define _________SYSCTL_R1__________ KC_MUTE , KC_HOME , KC_UP   , KC_END  ,
#define _________SYSCTL_R2__________ KC_VOLU , KC_LEFT , KC_DOWN , KC_RGHT , // < arrows
#define _________SYSCTL_R3__________ KC_VOLD , KC_MPRV , KC_MPLY , KC_MNXT , // < music


// we need wrappers in order for these definitions, because they need to be expanded before being used as arguments to the LAYOUT_xxx macro
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)


#endif // !USERSPACE_PVINIS_PVINIS_H