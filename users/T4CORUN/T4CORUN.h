#pragma once
#include QMK_KEYBOARD_H

#include "wrappers.h"

enum layers {
  _QWERTY = 0,
  FIRST_DEFAULT_LAYER = 0,  
  _COLEMAK_DH,
  _GAMING,
  _NUMBER,
  _NAVIGATION,
  _FUNCTION,
  _MOUSE,
  _GAMENUMBER,
  _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  CLMAKDH,
  GAMING
};

#define _DEFAULT_LAYER_1 FIRST_DEFAULT_LAYER
#define _DEFAULT_LAYER_2 (FIRST_DEFAULT_LAYER + 1)
#define _DEFAULT_LAYER_3 (FIRST_DEFAULT_LAYER + 2)

#define ___x___ KC_NO

//momentary layer
#define ADJUST     MO(_ADJUST)
#define NAV        MO(_NAVIGATION)
#define NUMBER     MO(_NUMBER)
#define GAMENO     MO(_GAMENUMBER)

//layer taps
#define FUN_Z      LT(_FUNCTION, KC_Z)
#define AD_SLSH    LT(_ADJUST, KC_SLSH)

//Windows Shortcuts
#define SC_COPY    LCTL(KC_C)
#define SC_CUT     LCTL(KC_X)
#define SC_UNDO    LCTL(KC_Z)
#define SC_PAST    LCTL(KC_V)
#define SC_REDO    LCTL(KC_Y)
#define W_SNIP     LSG(KC_S)


/*
We will move all as many preprocessor directives here so the wrapper is easier to follow
- Any keycodes with prefix TR has behavior dependent on if the feature is enabled.
- We will only define things that are used across different layers. Entire layers are turned off in the keymap
*/

#if defined(ONESHOT_ENABLE)
#   define TR_OSTG OS_TOGG
#   define TR_LSFT OSM(MOD_LSFT)
#   define TR_LCTL OSM(MOD_LCTL)
#   define TR_LALT OSM(MOD_LALT)
#   define TR_LGUI OSM(MOD_LGUI)
#else
#   define TR_OSTG ___x___
#   define TR_LSFT KC_LSFT
#   define TR_LCTL KC_LCTL
#   define TR_LALT KC_LALT
#   define TR_LGUI KC_LGUI
#endif //ONESHOT_ENABLE




#if defined(MOUSELAYER_ENABLE)
#   define TR_MOUC LT(_MOUSE, KC_C)
#   define TR_MOUT TG(_MOUSE)
#   define TR_BTN1 KC_BTN1
#else
#   define TR_MOUC KC_C
#   define TR_MOUT ___x___
#   define TR_BTN1 ___x___
#endif //MOUSELAYER_ENABLE






#if defined(MOUSEKEY_ENABLE)
#   define TR_MOUU KC_MS_U
#   define TR_MOUD KC_MS_D
#   define TR_MOUL KC_MS_L
#   define TR_MOUR KC_MS_R
#   define TR_MWHU KC_WH_U
#   define TR_MWHD KC_WH_D
#else
#   define TR_MOUU ___x___
#   define TR_MOUD ___x___
#   define TR_MOUL ___x___
#   define TR_MOUR ___x___
#   define TR_MWHU ___x___
#   define TR_MWHD ___x___
#endif //MOUSEKEY_ENABLE




//these keycodes come from the cnano
#if defined(POINTING_DEVICE_ENABLE)
#   define TR_SNIP SNIPING
#   define TR_SNIT SNP_TOG
#   define TR_DRGS DRGSCRL
#   define TR_DRGT DRG_TOG
#   define TR_SDPI S_D_MOD
#   define TR_PDPI DPI_MOD
#else
#   define TR_SNIP ___x___
#   define TR_SNIT ___x___
#   define TR_DRGS ___x___
#   define TR_DRGT ___x___
#   define TR_SDPI ___x___
#   define TR_PDPI ___x___
#endif //POINTING_DEVICE_ENABLE





#if defined(GAMELAYER_ENABLE) 
#   define TR_GAME GAMING
#else
#   define TR_GAME ___x___
#endif //GAMELAYER_ENABLE




#if defined(HOMEROWMOD_ENABLE)
//Home Row Mods QWERTY
#   define TR_A  LGUI_T(KC_A)
#   define TR_S  LALT_T(KC_S)
#   define TR_D  LCTL_T(KC_D)
#   define TR_F  LSFT_T(KC_F)

#   define TR_J  LSFT_T(KC_J)
#   define TR_K  LCTL_T(KC_K)
#   define TR_L  LALT_T(KC_L)
#   define TR_QT LGUI_T(KC_QUOT)
//Home Row Mods COLEMAKDH
#   define TR_R  LALT_T(KC_R)
#   define TR_S  LCTL_T(KC_S)
#   define TR_T  LSFT_T(KC_T)

#   define TR_N  LSFT_T(KC_N)
#   define TR_E  LCTL_T(KC_E)
#   define TR_I  LALT_T(KC_I)
#   define TR_O  LGUI_T(KC_O)
#else
//Home Row Mods QWERTY
#   define TR_A  KC_A
#   define TR_S  KC_S
#   define TR_D  KC_D
#   define TR_F  KC_F

#   define TR_J  KC_J
#   define TR_K  KC_K
#   define TR_L  KC_L
#   define TR_QT KC_QUOT
//Home Row Mods COLEMAKDH
#   define TR_R  KC_R
#   define TR_S  KC_S
#   define TR_T  KC_T

#   define TR_N  KC_N
#   define TR_E  KC_E
#   define TR_I  KC_I
#   define TR_O  KC_O
#endif //HOMEROWMOD_ENABLE




#if defined(TAP_DANCE_ENABLE)
#   define TR_LBRC TD_LBKT
#   define TR_RBRC TD_RBKT
#else
#   define TR_LBRC KC_LBRC
#   define TR_RBRC KC_RBRC
#endif //TAP_DANCE_ENABLE





#if defined(DYNAMIC_MACRO_ENABLE)
#   define TR_DMR1 DM_REC1
#   define TR_DMP1 DM_PLY1
#   define TR_DMR2 DM_REC2
#   define TR_DMP2 DM_PLY2
#else
#   define TR_DMR1 ___x___
#   define TR_DMP1 ___x___
#   define TR_DMR2 ___x___
#   define TR_DMP2 ___x___
#endif //DYNAMIC_MACRO_ENABLE




#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#   define TR_RHUI RGB_HUI
#   define TR_RSAI RGB_SAI
#   define TR_RVAI RGB_VAI
#   define TR_RSPI RGB_SPI
#   define TR_RTOG RGB_TOG
#   define TR_RMOD RGB_MOD
#else
#   define TR_RHUI ___x___
#   define TR_RSAI ___x___
#   define TR_RVAI ___x___
#   define TR_RSPI ___x___
#   define TR_RTOG ___x___
#   define TR_RMOD ___x___
#endif //RGB_MATRIX_ENABLE or RGBLIGHT_ENABLE





#if defined(AUDIO_ENABLE)
#   define TR_ATOG AU_TOGG
#   define TR_MTOG MU_TOGG
#   define TR_CTOG CK_TOGG
#   define TR_CKUP CK_UP
#   define TR_CKDN CK_DOWN
#else
#   define TR_ATOG ___x___
#   define TR_MTOG ___x___
#   define TR_CTOG ___x___
#   define TR_CKUP ___x___
#   define TR_CKDN ___x___
#endif //AUDIO_ENABLE

