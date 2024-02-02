
#pragma once
#include "../__init__.h"

// GENERAL
#define OS_LGUI OSM(MOD_LGUI)
#define OS_LALT OSM(MOD_LALT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LSFT OSM(MOD_LSFT)

#define TG_NUM  TG(NUM)
#define TG_NAV  TG(NAV)
#define TG_GAME TG(GAME)
#define TG_LOCK TG(LOCK)

#define MO_PAD  MO(NUMPAD)

// HOTKEYS
#define HK_TMCF S(KC_ENT)
#define HK_TMOP S(KC_ESC)
#define HK_STAB S(KC_TAB)

#define HK_COPY C(KC_C)
#define HK_PSTE C(KC_V)
#define HK_CUT  C(KC_X)
#define HK_UNDO C(KC_Z)
#define HK_SALL C(KC_A)
#define HK_RMLN C(KC_W)
#define HK_CPLN C(KC_D)
#define HK_SRCH C(KC_F)
#define HK_SAVE C(KC_S)
#define HK_NWTB C(KC_T)
#define HK_RLD  C(KC_R)
#define HK_RFCT C(KC_F6)
#define HK_RPLY C(KC_UP)
#define HK_NXTB C(KC_TAB)
#define HK_RMWR C(KC_BSPC)
#define HK_COMM C(KC_SLSH)

#define HK_ALTB A(KC_TAB)

#define HK_WNLK G(KC_L)

#define HK_RSTB C(S(KC_T))
#define HK_REDO C(S(KC_Z))
#define HK_GSRC C(S(KC_F))
#define HK_SLXT C(S(KC_A))
#define HK_PRTB C(S(KC_TAB))

#define HK_SWAP C(A(KC_TAB))
#define HK_SLSR C(A(KC_F))

#define HK_RFAL MEH(KC_J)

// TAP DANCES
#define TD_NONE TD(TDI_NONE)
#define TD_LOCK TD(TDI_LOCK)
#define TD_NUM  TD(TDI_NUM)
#define TD_LGSW TD(TDI_LGSW)
#define TD_PASS TD(TDI_PASS)
#define TD_EXLM TD(TDI_EXLM)
#define TD_EQL  TD(TDI_EQL)
#define TD_DQT  TD(TDI_DQT)
#define TD_BSLS TD(TDI_BSLS)
#define TD_UNDS TD(TDI_UNDS)
#define TD_COLN TD(TDI_COLN)
#define TD_ARR  TD(TDI_ARR)
#define TD_ECLP TD(TDI_ECLP)
#define TD_SALL TD(TDI_SALL)
#define TD_MD   TD(TDI_MD)

// THUMB
#define TH_LNAV LT(NAV_LEFT, KC_BSPC)
#define TH_NUM  LT(NUM, KC_SPC)
#define TH_LNUM LT(QWERTY, KC_SPC)

#define TH_NAV  LT(NAV, KC_BSPC)
#define TH_FUNC LT(FUNCTION, KC_DEL)

// STURDY
#define GLT_S LT(QWERTY, KC_S)
#define ALT_T LT(QWERTY, KC_T)
#define CLT_R LT(QWERTY, KC_R)
#define SMT_D LSFT_T(KC_D)

#define SMT_N LSFT_T(KC_N)
#define CLT_A LT(QWERTY, KC_A)
#define ALT_E LT(QWERTY, KC_E)
#define LT_I LT(MEDIA, KC_I)

// QWERTY
#define GMT_A LGUI_T(KC_A)
#define AMT_S LALT_T(KC_S)
#define CMT_D LCTL_T(KC_D)
#define SMT_F LSFT_T(KC_F)

#define SMT_J LSFT_T(KC_J)
#define CMT_K LCTL_T(KC_K)
#define AMT_L LALT_T(KC_L)
#define LT_SCLN LT(MEDIA, KC_SCLN)

// GAME
#define HR_F5 LT(MEDIA, KC_F5)

// NUM
#define HR_RMLN LGUI_T(KC_NO)
#define HR_SAVE LALT_T(KC_NO)
#define HR_CPLN LCTL_T(KC_NO)
#define HR_SRCH LSFT_T(KC_NO)

// NAV
#define HR_DEL LT(ALT_NAV, KC_DEL)
