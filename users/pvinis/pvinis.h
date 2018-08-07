#pragma once

#include "quantum.h"


// my own keycodes
enum userspace_custom_keycodes {
  PV_ = SAFE_RANGE,

  PV_VRSN, // prints firmware version
  PV_MAKE, // prints the make command of the keyboard
  PV_FLSH, // resets keyboard
  PV_KTMR, // play katamari music

  // tap dance
  TD_FLSH, // flash keyboard (as if the physical flash key was pressed)

  PV_SAFE_RANGE, // used for extra keycodes in the individual keymaps
};

#define ALLM(kc) LCAG(kc)           // easier name for left ctrl-alt-gui
#define PV_ESCC  CTL_T(KC_ESC)      // esc on tap, ctrl on hold
#define PV_LOCK  LCTL(LSFT(KC_PWR)) // lock computer
#define TD_3FLS  TD(TD_FLSH)        // tap dance 3 times for flash


// layers
enum {
  LR_BASE = 0, // used for basic keys like the surrounding ctrl, cmd, etc

  LR_QWERTY,
  LR_CARPALX,

  LR_SYMBOL, // symbol input (!, @, #, etc)
  LR_SYSCTL, // system control (music, volume, keyboard flash, etc)
  LR_KBCTL,  // keyboard control (version, make, flash, etc)
};


// layer switchers
#define BASE    TO(LR_BASE)
#define QWERTY  TO(LR_QWERTY)
#define CARPALX TO(LR_CARPALX)

#define SYMBOL  MO(LR_SYMBOL)
#define SYSCTL  MO(LR_SYSCTL)
#define KBCTL   MO(LR_KBCTL)


// layout parts for easy reuse between keyboard keymaps

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  1  |  2  |  3  |  4  |  5  |   |  6  |  7  |  8  |  9  |  0  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define ________________NUMBERS_L__________________  KC_1, KC_2, KC_3, KC_4, KC_5
#define ________________NUMBERS_R__________________  KC_6, KC_7, KC_8, KC_9, KC_0

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  Q  |  W  |  E  |  R  |  T  |   |  Y  |  U  |  I  |  O  |  P  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  A  |  S  |  D  |  F  |  G  |   |  H  |  J  |  K  |  L  |  ;  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  Z  |  X  |  C  |  V  |  B  |   |  N  |  M  |  ,  |  .  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define _________________QWERTY_L1_________________  KC_Q   , KC_W   , KC_E   , KC_R   , KC_T
#define _________________QWERTY_L2_________________  KC_A   , KC_S   , KC_D   , KC_F   , KC_G
#define _________________QWERTY_L3_________________  KC_1   , KC_X   , KC_C   , KC_V   , KC_B

#define _________________QWERTY_R1_________________  KC_Y   , KC_U   , KC_I   , KC_O   , KC_P
#define _________________QWERTY_R2_________________  KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN
#define _________________QWERTY_R3_________________  KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  Q  |  G  |  M  |  L  |  W  |   |  Y  |  F  |  I  |  O  |  P  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  D  |  S  |  T  |  N  |  R  |   |  I  |  A  |  K  |  L  |  ;  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  Z  |  X  |  C  |  V  |  J  |   |  K  |  P  |  ,  |  .  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define ________________CARPALX_L1_________________  KC_Q   , KC_G   , KC_M   , KC_L   , KC_W
#define ________________CARPALX_L2_________________  KC_D   , KC_S   , KC_T   , KC_N   , KC_R
#define ________________CARPALX_L3_________________  KC_Z   , KC_X   , KC_C   , KC_V   , KC_J

#define ________________CARPALX_R1_________________  KC_Y   , KC_F   , KC_U   , KC_B   , KC_SCLN
#define ________________CARPALX_R2_________________  KC_I   , KC_A   , KC_E   , KC_O   , KC_H
#define ________________CARPALX_R3_________________  KC_K   , KC_P   , KC_COMM, KC_DOT , KC_SLSH

#define _________________SYSCTL_L1_________________
#define _________________SYSCTL_L2_________________
#define _________________SYSCTL_L3_________________

//                                                    vol v                                                 ctl v
#define _________________SYSCTL_R1_________________  KC_MUTE , KC_HOME , KC_UP   , KC_END                 , PV_LOCK
#define _________________SYSCTL_R2_________________  KC_VOLU , KC_LEFT , KC_DOWN , KC_RGHT /* < arrows */ , KC_SLEP
#define _________________SYSCTL_R3_________________  KC_VOLD , KC_MPRV , KC_MPLY , KC_MNXT /* < music */  , KC_PWR


// we need wrappers in order for these definitions, because they need to be expanded before being used as arguments to the LAYOUT_xxx macro
#define LAYOUT_ergodox_pretty_wrapper(...)  LAYOUT_ergodox_pretty(__VA_ARGS__)
#define LAYOUT_wrapper(...)                 LAYOUT(__VA_ARGS__)
