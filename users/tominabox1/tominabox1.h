#pragma once
#include "quantum.h"
#include "action.h"
#include "version.h"
#include "wrappers.h"

extern keymap_config_t keymap_config;

enum layers {
  _BASE,
  _NUM_SYM,
  _RAISE,
  _MACRO,
  _NUMPAD,
  _NAV,
  _FKEY,
  _GAME,
  _NP,
  _ADJUST
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  RGBRST,
  SPONGEBOB,
  AESTHETIC,
};

enum tap_dance_indexes {
  TD_TAB_ESC=0,
  TD_Q_ESC,
  TD_QUES_ENT,
  TD_SPC_SHFT,
  TD_CTRL_Z,
  TD_CTRL_Y,
  TD_CTRL_C,
  TD_CTRL_V,
  TD_CTRL_A,
  TD_O_BSLS,
  TD_QUOTE,
  TD_QCOL,
  TD_WTAB
};
/* Tapdnce keycodes */
#define KC_TABESC TD(TD_TAB_ESC) // Single tap tab, double tap esc
#define KC_QESC   TD(TD_Q_ESC) // Single tap Q, double tap esc
#define KC_QESENT TD(TD_QUES_ENT) // Single tap slsh, double tap enter, hold rshift
#define KC_SPSHFT TD(TD_SPC_SHFT) // Single tap spce, hold shift
#define KC_CTLZ   TD(TD_CTRL_Z) // Single tap z, double tap ctrl+z (undo)
#define KC_CTLY   TD(TD_CTRL_Y) // Single tap y, double tap ctrl+y (redo)
#define KC_CTLC   TD(TD_CTRL_C) // Single tap c, double tap ctrl+c (copy)
#define KC_CTLV   TD(TD_CTRL_V) // Single tap v, double tap ctrl+v (paste)
#define KC_CTLA   TD(TD_CTRL_A) // Single tap a, hold ctrl, double tap ctrl*a (select all)
#define KC_OBSLS  TD(TD_O_BSLS) // Single tap o, double tap backslash
#define KC_DQOT   TD(TD_QUOTE) // Single tap quote, double tap double quote
#define KC_QCOL   TD(TD_QCOL) // Single tap quote, double tap semicolon
#define KC_WTAB   TD(TD_WTAB) // Single tap w, double tap tab

/* Basic mod-taps */
#define KC_CTLTB CTL_T(KC_TAB) // Tab on tap, ctrl on hold
#define KC_A_CT  LCTL_T(KC_A) // A on tap, ctrl on hold
#define KC_Z_SF  LSFT_T(KC_Z) // Z on tap, shift on hold
#define KC_C_AL  LALT_T(KC_C) // C on tap, GUI or Alt on hold
#define KC_K_GU  LGUI_T(KC_K) // K on tap, GUI or Alt on hold
#define KC_ENSF  LSFT_T(KC_ENT) // Return on tap, Shift on hold
#define KC_GENT  LALT_T(KC_ENT) // Return on tap, ALT or GUI on hold
#define KC_SSLSH RSFT_T(KC_SLSH) // Slash on tap, shift on hold

/* Layer taps */
#define KC_NUM_SPC LT(_NUM_SYM, KC_SPC) // Space on tap, num/symbol layer on hold
#define KC_FDOT  LT(_FKEY, KC_DOT) // period on tap, Fkey layer on hold
#define KC_NAV_ENT LT(_NAV, KC_ENT) // Return on tap, Nav layer on hold
#define KC_SPC_RSE LT(_RAISE, KC_SPC) // Space on tap, Raise on hold
#define KC_FKEY LT(_FKEY, KC_ENT) // Return on tap, Fkey on hold

/* RGB keycodes */
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
