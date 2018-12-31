#ifndef USERSPACE
#define USERSPACE
#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

#include "wrappers.h"

#ifndef PERMISSIVE_HOLD
#define PERMISSIVE_HOLD
#endif
#ifndef TAPPING_TERM
#define TAPPING_TERM 200
#endif
#ifndef IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT
#endif

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum layer_number {
    _DVRK = 0,
    _MDVK,
    _QUER,
    _SYMB,
    _NUMB,
    _MNMB,
    _MDIA
};
/*
#define _DVRK 0
#define _NUMB 1
#define _MDVK 2
#define _MNMB 3
#define _SYMB 4
#define _MDIA 5
*/
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
  ADJUST,
  KC_MAKE,
  DYNAMIC_MACRO_RANGE,
};



//Tap dance enums
enum {
  SSWAP = 0,
  TD_MCROTOG,
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
#define KC_KANJI KC_GRV


#define KC_SYMB SYMB
#define KC_NUMB NUMB
#define KC_MNMB MNMB
#define KC_DVRK TO(_DVRK)
#define KC_QUER TO(_QUER)
#define KC_MACD TO(_MDVK)
#define KC_MCNB TO(_MNMB)
#define KC_ADJS ADJUST

#define KC_RST   RESET

#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LRMOD RGB_RMOD

#define KC_SPSY LT(_SYMB,KC_SPC)
#define KC_BSNB LT(_NUMB,KC_BSPC)
#define KC_TBNB LT(_NUMB,KC_TAB)
#define KC_ENSY LT(_SYMB,KC_ENT)
#define KC_MBNB LT(_MNMB,KC_BSPC)
#define KC_MTNB LT(_MNMB,KC_TAB)


#define KC_MCRTG   TD(TD_MCROTOG)
#define KC_MCRT2   TD(TD_MCROTG2)
#define KC_CMWN    TD(TD_CMWN)
#define KC_ATSH    TD(TD_ATSH)
#define KC_PSTI    TD(TD_PSTI)
#define KC_PTSP    TD(TD_PTSP)
#define KC_FNDR    TD(TD_FNDR)
#define KC_CCPY    TD(TD_CCPY)
#define KC_DDEL    TD(TD_DDEL)
#define KC_ACCW    TD(TD_ACCW)
#define KC_CAPES   TD(TD_CAPES)
#define KC_DTEX    TD(TD_DTEX)
#define KC_COMQUES TD(TD_COMQUES)
#define KC_MINPLS  TD(TD_MINPLS)
#define KC_DIVMLT  TD(TD_DIVMLT)
#define KC_DOTEQL  TD(TD_DOTEQL)
#define KC_LSHSYM  TD(TD_LSHSYM)
#define KC_RSHSYM  TD(TD_RSHSYM)
#define KC_SCNSP   TD(TD_SCNSP)
#define KC_MCCPY   TD(TD_MCCCPY)
#define KC_MCPIN   TD(TD_MCPSTIN)

#define KC_QUAD TD(SSWAP)

#define KC_WNL  LGUI(KC_L)
#define KC_MCL  LCTL(LALT(KC_Q))
#define KC_WNSC MT(MOD_LGUI,KC_SCLN)
#define KC_CSCN MT(MOD_LCTL,KC_SCLN)
#define KC_ALTQ MT(MOD_LALT,KC_Q)
#define KC_CTLJ MT(MOD_LCTL,KC_J)
#define KC_GUIJ MT(MOD_LGUI,KC_J)
#define KC_SHFK MT(MOD_LSFT,KC_K)
#define KC_SHFM MT(MOD_LSFT,KC_M)
#define KC_CTLW MT(MOD_LCTL,KC_W)
#define KC_GUIW MT(MOD_LGUI,KC_W)
#define KC_ALTV MT(MOD_LALT,KC_V)
#define KC_MDAZ LT(_MDIA,KC_Z)
#define KC_CTLA LCTL(KC_A)
#define KC_CTL2 MT(MOD_LCTL,KC_2)
#define KC_ALT3 MT(MOD_LALT,KC_3)
#define KC_CSTC C_S_T(KC_COLN)
//#define KC_SWP  SH_TT
#define KC_MRC1 DYN_REC_START1
#define KC_MPL1 DYN_MACRO_PLAY1
#define KC_MSP  DYN_REC_STOP

#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LMOD  RGB_MOD
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSPI  RGB_SPI
#define KC_LSPD  RGB_SPD
#define KC_LRMOD RGB_RMOD

#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP
#define KC_GUAP  LALT_T(KC_APP)

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void sftswap (qk_tap_dance_state_t *state, void *user_data);
void reset_sftswap (qk_tap_dance_state_t *state, void *user_data);

#endif
