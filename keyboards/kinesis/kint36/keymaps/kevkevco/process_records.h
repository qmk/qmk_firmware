// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include "version.h"
#include "keycodes.h"
#include "layers.h"
#include "tap_dances.h"
#include "features/caps_word.h"
#include "features/num_word.h"
#include "features/select_word.h"
#include "print.h" // For debugging purposes

// For more readable LED control code
#define LED_KEYPAD E26

// Initialize variable holding the binary representation of active modifiers.
uint8_t mod_state;

// Super cmd↯TAB initializations
bool     is_cmd_tab_active;
uint16_t cmd_tab_timer;

// Aliases for longer keycodes
// clang-format off

// Layer keycodes
#define QWERTY  TO(_QWERTY)
#define NUMSHFT TG(_NUMSHIFT)
#define SYMBOL  TG(_SYMBOLS)
#define VIM     TG(_VIM)
#define NAV     TG(_NAV)
#define R_KEYPD TG(_RKEYPAD)
#define L_KEYPD TG(_LKEYPAD)
#define FUNCTN  TG(_FUNCTION)

// Tapdances
#define T_SPOT  TD(SPOT)
#define T_CMAG  TD(CMAG)
#define T_PDAG  TD(PDAG)
#define T_NVUD  TD(NVUD)
#define T_WIND  TD(WIND)
#define T_ISPT  TD(ISPT)
#define T_GVES  TD(GVES)
#define T_ENTR  TD(ENTR)
#define T_SLSH  TD(SLSH)
#define T_LPNKY TD(LPINKY)
#define T_RPNKY TD(RPINKY)
#define T_COLON TD(COLON)

// Hold shortcut functions
#define Q_HOLD  LT(0,KC_Q)
#define W_HOLD  LT(0,KC_W)
#define C_HOLD  LT(0,KC_C)
#define V_HOLD  LT(0,KC_V)
#define Z_HOLD  LT(0,KC_Z)
#define A_HOLD  LT(0,KC_A)
#define X_HOLD  LT(0,KC_X)
#define T_HOLD  LT(0,KC_T)
#define B_HOLD  LT(0,KC_B)
#define N_HOLD  LT(0,KC_N)
#define Y_HOLD  LT(0,KC_Y)
#define R_HOLD  LT(0,KC_R)

// Home Row Mods
#define A_CTL   LCTL_T(KC_A)
#define S_OPT   LOPT_T(KC_S)
#define D_GUI   LGUI_T(KC_D)
#define F_SFT   LSFT_T(KC_F)
#define J_SFT   RSFT_T(KC_J)
#define K_GUI   RGUI_T(KC_K)
#define L_OPT   ROPT_T(KC_L)

// LKeypad Home Row Mods
#define KP4_OPT LOPT_T(KC_4)
#define KP5_LGU LGUI_T(KC_5)
#define KP6_SFT LSFT_T(KC_6)

// RKeypad Home Row Mods
#define KP4_SFT RSFT_T(KC_4)
#define KP5_GUI RGUI_T(KC_5)
#define KP6_OPT ROPT_T(KC_6)
#define PLS_CTL RCTL_T(KC_PPLS)

// Misc.
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_MEH  OSM(MOD_MEH)
#define BSP_GUI LGUI_T(KC_BSPC)
#define DEL_SFT SFT_T(KC_DEL)
#define SPC_GUI RGUI_T(KC_SPC)
#define COM_NAV LT(_NAV, S(KC_COMM))
#define BSP_HYP HYPR_T(KC_BSPC)
#define ENT_CAG LCAG_T(KC_ENT)
#define MEH_TAB MEH_T(KC_TAB)
// clang-format on

