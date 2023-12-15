// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "wrappers.h"
#include "action.h"
#include "version.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
#    include "tapdances.h"
#endif

enum layer_names {
  _WM,
  _QW,
  _LOWER,
  _RAISE,
  _EX,
  _FN,
  _SYMB
};


// Layer macros
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE) 
#define FN MO(_FN)
#define EX MO(_EX)
#define TEX     LT(_EX, KC_T)           // Tap for "T", hold for Extras layer
#define BSYM    LT(_SYMB, KC_B)         // Tap for "B", hold for Symbols layer
#define JSYM    LT(_SYMB, KC_J)         // Tap for "J", hold for Symbols layer
#define FNZ     LT(_FN, KC_Z)           // Tap for "Z", hold for FN layer
#define VLOWER  LT(_LOWER, KC_V)        // Tap for "V", hold for Lower layer
#define KRAISE  LT(_RAISE, KC_K)        // Tap for "K", hold for Raise layer

// Mod Tap
//#define ASFT    MT(MOD_LSFT, KC_A)      // Tap for "A", hold for Shift
#define ASFT    SFT_T(KC_A)             // Tap for "A", hold for Shift
#define GGUI    MT(MOD_LGUI, KC_G)      // Tap for "G", hold for OS Key
#define MGUI    MT(MOD_LGUI, KC_M)      // Tap for "M", hold for OS Key
#define CTRLX   MT(MOD_LCTL, KC_X)      // Tap for "X", hold for Ctrl
#define CALT    MT(MOD_LALT, KC_C)      // Tap for "C", hold for Alt
#define L_ALT   MT(MOD_RALT, KC_L)      // Tap for "L", hold for Alt
#define TBSHFT  MT(MOD_LSFT, KC_TAB)    // Tap for Tab, hold for Shift
#define SLSHFT  MT(MOD_RSFT, KC_SLSH)   // Tap for Slash, hold for Shift
#define SFT_ENT RSFT_T(KC_ENT)          // Tap for Enter, hold for Shift
#define OSSFT   OSM(MOD_LSFT)           // One shot left Shift

// MISC
#define CALTDEL LCTL(LALT(KC_DEL))	    // Ctrl Alt Del
#define TSKMGR  LCTL(LSFT(KC_ESC))	    // Task Manager
#define CLIP    LCTL(LALT(KC_Q))	    	// Clipboard (Ditto)
#define SS      LCTL(LALT(KC_G))		    // Greenshot region
#define NUM     LSFT(KC_3)
#define AT      LSFT(KC_2)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define ____    KC_TRNS
#define XXXX    KC_NO
#define XXXXXXX KC_NO
