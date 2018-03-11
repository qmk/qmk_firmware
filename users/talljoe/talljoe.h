#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum layers {
    _BASE = 0,
    _WORKMAN,
    _NORMAN,
    _DVORAK,
    _COLMAK,
    _GAME,
    _NAV,
    _ADJUST,
    _RESET,
};

#define KM_(...) KM(__VA_ARGS__)

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define NV_SPC  LT(_NAV, KC_SPC)
#define NV_ENT  LT(_NAV, KC_ENT)
#define AD_GRV  LT(_ADJUST, KC_GRV)

#define MO_NAV    MO(_NAV)
#define MO_ADJ    MO(_ADJUST)
#define MO_RST    MO(_RESET)
#define TG_ADJ    TG(_ADJUST)
#define TG_GAME   TG(_GAME)
#define LY_QWER   DF(_BASE)
#define LY_WORK   DF(_WORKMAN)
#define LY_NRMN   DF(_NORMAN)
#define LY_DVRK   DF(_DVORAK)
#define LY_CLMK   DF(_COLMAK)
#define TG_NKRO   MAGIC_TOGGLE_NKRO
#define KC_PTT    KC_F24
#define MS_MID    KC_MS_BTN3


#ifndef SPACE_COUNT
  #define SPACE_COUNT 1
#endif
#if (SPACE_COUNT == 1)
  #define KC_SPC1   NV_SPC
#elif (SPACE_COUNT == 3)
  #define KC_SPC1   KC_ENT
  #define KC_SPC2   TT(_NAV)
  #define KC_SPC3   KC_SPC
#else
  #error "Unsupported space count:" SPACE_COUNT
#endif

enum userspace_custom_keycodes {
  KC_MAKE = SAFE_RANGE, // can always be here
  NEW_SAFE_RANGE //use "NEWPLACEHOLDER for keymap specific codes
};

#define SAFE_RANGE NEW_SAFE_RANGE

#define _________________QWERTY_L1_________________  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________  KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________COLEMAK_L1________________  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________  KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________  KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________DVORAK_L1_________________  KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________  KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________  KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________  KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________  KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define _________________WORKMAN_L1________________  KC_Q   , KC_D   , KC_R   , KC_W   , KC_B
#define _________________WORKMAN_L2________________  KC_A   , KC_S   , KC_H   , KC_T   , KC_G
#define _________________WORKMAN_L3________________  KC_Z   , KC_X   , KC_M   , KC_C   , KC_V

#define _________________WORKMAN_R1________________  KC_J   , KC_F   , KC_U   , KC_P   , KC_SCLN
#define _________________WORKMAN_R2________________  KC_Y   , KC_N   , KC_E   , KC_O   , KC_I
#define _________________WORKMAN_R3________________  KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH

#define _________________NORMAN_L1_________________  KC_Q   , KC_W   , KC_D   , KC_F   , KC_K
#define _________________NORMAN_L2_________________  KC_A   , KC_S   , KC_E   , KC_T   , KC_G
#define _________________NORMAN_L3_________________  KC_Z   , KC_X   , KC_C   , KC_V   , KC_B

#define _________________NORMAN_R1_________________  KC_J   , KC_U   , KC_R   , KC_L   , KC_SCLN
#define _________________NORMAN_R2_________________  KC_Y   , KC_N   , KC_I   , KC_O   , KC_H
#define _________________NORMAN_R3_________________  KC_P   , KC_M   , KC_COMM, KC_DOT , KC_SLSH

#define ________________NAVLAYER_L1________________  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_VOLU
#define ________________NAVLAYER_L2________________  KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_MUTE
#define ________________NAVLAYER_L3________________  KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_VOLD

#define ________________NAVLAYER_R1________________  KC_INS , KC_PGUP, KC_UP  , KC_PGDN, XXXXXXX
#define ________________NAVLAYER_R2________________  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END
#define ________________NAVLAYER_R3________________  KC_END , KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX

#define ________________ADJLAYER_L1________________  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________ADJLAYER_L2________________  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________ADJLAYER_L3________________  LY_QWER, LY_WORK, LY_NRMN, LY_DVRK, LY_CLMK

#define ________________ADJLAYER_R1________________  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________ADJLAYER_R2________________  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________ADJLAYER_R3________________  XXXXXXX, XXXXXXX, XXXXXXX, KC_MAKE, TG_GAME

#endif
