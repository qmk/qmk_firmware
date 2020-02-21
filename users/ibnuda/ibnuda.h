#pragma once
#include "quantum.h"

#include "tapdance.h"
#include "wrapper.h"
//#include "combo.h"

enum {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// thumb keys.
#define ALT_ENT   ALT_T(KC_ENT)
#define SFT_ESC   SFT_T(KC_ESC)

// home row mods.
#define CT_O LCTL_T(KC_O)
#define CT_N RCTL_T(KC_N)
#define SH_A LSFT_T(KC_A)
#define SH_S RSFT_T(KC_S)
#define AL_E LALT_T(KC_E)
#define AL_T RALT_T(KC_T)
#define GU_I LGUI_T(KC_I)
#define GU_D RGUI_T(KC_D)

// layer toggle.
#define LW_I     LT(_LOWER, KC_I)
#define LW_BSPC  LT(_LOWER, KC_BSPC)
#define RS_SPC   LT(_RAISE, KC_SPC)
#define RS_D     LT(_RAISE, KC_D)

// idk, man. not used, i guess.
#define ADDDD    MO(_ADJUST)

// common shortcuts for windows and linux that i use.
#define NXTTAB LCTL(KC_PGDN)
#define PRVTAB LCTL(KC_PGUP)
#define UPTAB  LCTL(LSFT(KC_PGUP))
#define DNTAB  LCTL(LSFT(KC_PGDN))
#define NXTWIN LALT(KC_TAB)
#define PRVWIN LALT(LSFT(KC_TAB))
#define CALDL  LCTL(LALT(KC_DELT))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define EXPLR  LGUI(KC_E)
#define LCKGUI LGUI(KC_L)
#define CONPST LSFT(KC_INS)
#define CLSGUI LALT(KC_F4)

// tap dances
#define CTL_DLT TD(TD_DLT_CTLDLT)
#define SM_CLN  TD(TD_SCLN_CLN)
#define LFT_TMB TD(TD_LEFT_THUMB)
