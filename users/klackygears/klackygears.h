#ifndef USERSPACE
#define USERSPACE
#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

//#include "wrappers.h"



#ifndef PERMISSIVE_HOLD
#define PERMISSIVE_HOLD
#endif
#ifndef TAPPING_TERM
#define TAPPING_TERM 200
#endif
#ifndef IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT
#endif
//#ifndef TAPPING_FORCE_HOLD
//#define TAPPING_FORCE_HOLD
//#endif
#if defined(KEYBOARD_helix)
#undef MASTER_LEFT
#define EE_HANDS
//#undef TAPPING_FORCE_HOLD
#endif


/*
#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE



typedef struct {
  bool is_press_action;
  int state;
} tap;
*/
enum layer_number {
    _DVRK = 0,
    _QUER,
    _MDVK,
    _NUMB,
    _MNMB,
    _SYMB,
    _MDIA
};

#define _DVRK 0
#define _QUER 1
#define _MDVK 2
#define _NUMB 3
#define _MNMB 4
#define _SYMB 5
#define _MDIA 6

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum custom_keycodes {
  DVRK = SAFE_RANGE,
  MDVK,
  NUMB,
  MNMB,
  SYMB,
  MDIA,
  RGBRST,
  //ADJUST,
  KC_MAKE,
  DYNAMIC_MACRO_RANGE,
};



//Tap dance enums
enum {
  //SSWAP,
  TD_MCROTOG = 0,
  TD_MCROTG2,
  TD_BTK,
  TD_TDE,
  TD_LPRN,
  TD_RPRN,
  TD_MIN,
  TD_USC,
  TD_CMWN,
  TD_ATSH,
  TD_PSTI,
  TD_PTSP,
  TD_FNDR,
  TD_CCPY,
  TD_DDEL,
  TD_ACCW,
  TD_CAPESC,
  TD_DTEX,
  TD_COMQUES,
  TD_MINPLS,
  TD_DIVMLT,
  TD_DOTEQL,
  TD_LSHSYM,
  TD_RSHSYM,
  TD_SCNSP,
  TD_MCCCPY,
  TD_MCPSTIN,
  SOME_OTHER_DANCE,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
//void sftswap (qk_tap_dance_state_t *state, void *user_data);
//void reset_sftswap (qk_tap_dance_state_t *state, void *user_data);



// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
//   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
     #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
//     #define RGBLIGHT_EFFECT_BEAM
#endif

#endif
