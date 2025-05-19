// Copyright 2025 QMK
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
#define LT_GRV  KC_GRV  // `
#define LT_EXLM KC_1    // !
#define LT_MINS KC_2    // -
#define LT_SLSH KC_3    // /
#define LT_SCLN KC_4    // ;
#define LT_COLN KC_5    // :
#define LT_COMM KC_6    // ,
#define LT_DOT  KC_7    // .
#define LT_EQL  KC_8    // =
#define LT_LPRN KC_9    // (
#define LT_RPRN KC_0    // )
#define LT_QUES KC_MINS // ?
#define LT_X    KC_EQL  // X
#define LT_AOGO KC_Q    // Ą
#define LT_ZCAR KC_W    // Ž
#define LT_E    KC_E    // E
#define LT_R    KC_R    // R
#define LT_T    KC_T    // T
#define LT_Y    KC_Y    // Y
#define LT_U    KC_U    // U
#define LT_I    KC_I    // I
#define LT_O    KC_O    // O
#define LT_P    KC_P    // P
#define LT_IOGO KC_LBRC // Į
#define LT_W    KC_RBRC // W
#define LT_A    KC_A    // A
#define LT_S    KC_S    // S
#define LT_D    KC_D    // D
#define LT_SCAR KC_F    // Š
#define LT_G    KC_G    // G
#define LT_H    KC_H    // H
#define LT_J    KC_J    // J
#define LT_K    KC_K    // K
#define LT_L    KC_L    // L
#define LT_UOGO KC_SCLN // Ų
#define LT_EDOT KC_QUOT // Ė
#define LT_Q    KC_NUHS // Q
#define LT_LABK KC_NUBS // <
#define LT_Z    KC_Z    // Z
#define LT_UMAC KC_X    // Ū
#define LT_C    KC_C    // C
#define LT_V    KC_V    // V
#define LT_B    KC_B    // B
#define LT_N    KC_N    // N
#define LT_M    KC_M    // M
#define LT_CCAR KC_COMM // Č
#define LT_F    KC_DOT  // F
#define LT_EOGO KC_SLSH // Ę
#define LT_TILD S(LT_GRV)  // ~
#define LT_1    S(LT_EXLM) // 1
#define LT_2    S(LT_MINS) // 2
#define LT_3    S(LT_SLSH) // 3
#define LT_4    S(LT_SCLN) // 4
#define LT_5    S(LT_COLN) // 5
#define LT_6    S(LT_COMM) // 6
#define LT_7    S(LT_DOT)  // 7
#define LT_8    S(LT_EQL)  // 8
#define LT_9    S(LT_LPRN) // 9
#define LT_0    S(LT_RPRN) // 0
#define LT_PLUS S(LT_QUES) // +
#define LT_RABK S(LT_LABK) // >
#define LT_ACUT ALGR(LT_GRV)  // ´
#define LT_AT   ALGR(LT_EXLM) // @
#define LT_UNDS ALGR(LT_MINS) // _
#define LT_HASH ALGR(LT_SLSH) // #
#define LT_DLR  ALGR(LT_SCLN) // $
#define LT_SECT ALGR(LT_COLN) // §
#define LT_CIRC ALGR(LT_COMM) // ^
#define LT_AMPR ALGR(LT_DOT)  // &
#define LT_ASTR ALGR(LT_EQL)  // *
#define LT_LBRC ALGR(LT_LPRN) // [
#define LT_RBRC ALGR(LT_RPRN) // ]
#define LT_QUOT ALGR(LT_QUES) // '
#define LT_PERC ALGR(LT_X)    // %
#define LT_EURO ALGR(LT_E)    // €
#define LT_LCBR ALGR(LT_IOGO) // {
#define LT_RCBR ALGR(LT_W)    // }
#define LT_DQUO ALGR(LT_EDOT) // "
#define LT_PIPE ALGR(LT_Q)    // |
#define LT_NDSH ALGR(LT_LABK) // –
#define LT_DLQU ALGR(LT_CCAR) // „
#define LT_LDQU ALGR(LT_F)    // “
#define LT_BSLS ALGR(LT_EOGO) // (backslash)

