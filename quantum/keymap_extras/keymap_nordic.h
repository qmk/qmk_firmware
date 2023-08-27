// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once
#include "keycodes.h"
// clang-format off

// Aliases
#define NO_HALF KC_GRV 
#define NO_PLUS KC_MINS
#define NO_ACUT KC_EQL 
#define NO_AM   KC_LBRC
#define NO_QUOT KC_RBRC // this is the "umlaut" char on Nordic keyboards, Apple layout
#define NO_AE   KC_SCLN
#define NO_OSLH KC_QUOT
#define NO_APOS KC_NUHS
#define NO_LESS KC_NUBS
#define NO_MINS KC_SLSH
#define NO_SECT LSFT(NO_HALF)
#define NO_QUO2 LSFT(KC_2)
#define NO_BULT LSFT(KC_4)
#define NO_AMPR LSFT(KC_6)
#define NO_SLSH LSFT(KC_7)
#define NO_LPRN LSFT(KC_8)
#define NO_RPRN LSFT(KC_9)
#define NO_EQL  LSFT(KC_0)
#define NO_QUES LSFT(NO_PLUS)
#define NO_GRV  LSFT(NO_ACUT)
#define NO_CIRC LSFT(NO_QUOT)
#define NO_GRTR LSFT(NO_LESS)
#define NO_SCLN LSFT(KC_COMM)
#define NO_COLN LSFT(KC_DOT)
#define NO_UNDS LSFT(NO_MINS)
#define NO_AT   ALGR(KC_2)   
#define NO_PND  ALGR(KC_3)   
#define NO_DLR  ALGR(KC_4)   
#define NO_LCBR ALGR(KC_7)   
#define NO_LBRC ALGR(KC_8)   
#define NO_RBRC ALGR(KC_9)   
#define NO_RCBR ALGR(KC_0)   
#define NO_PIPE ALGR(KC_NUBS)
#define NO_EURO ALGR(KC_E)   
#define NO_TILD ALGR(NO_QUOT)
#define NO_BSLS ALGR(KC_MINS)
#define NO_MU   ALGR(KC_M)   

