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
#define IE_GRV  KC_GRV  // `
#define IE_1    KC_1    // 1
#define IE_2    KC_2    // 2
#define IE_3    KC_3    // 3
#define IE_4    KC_4    // 4
#define IE_5    KC_5    // 5
#define IE_6    KC_6    // 6
#define IE_7    KC_7    // 7
#define IE_8    KC_8    // 8
#define IE_9    KC_9    // 9
#define IE_0    KC_0    // 0
#define IE_MINS KC_MINS // -
#define IE_EQL  KC_EQL  // =
#define IE_Q    KC_Q    // Q
#define IE_W    KC_W    // W
#define IE_E    KC_E    // E
#define IE_R    KC_R    // R
#define IE_T    KC_T    // T
#define IE_Y    KC_Y    // Y
#define IE_U    KC_U    // U
#define IE_I    KC_I    // I
#define IE_O    KC_O    // O
#define IE_P    KC_P    // P
#define IE_LBRC KC_LBRC // [
#define IE_RBRC KC_RBRC // ]
#define IE_A    KC_A    // A
#define IE_S    KC_S    // S
#define IE_D    KC_D    // D
#define IE_F    KC_F    // F
#define IE_G    KC_G    // G
#define IE_H    KC_H    // H
#define IE_J    KC_J    // J
#define IE_K    KC_K    // K
#define IE_L    KC_L    // L
#define IE_SCLN KC_SCLN // ;
#define IE_QUOT KC_QUOT // '
#define IE_HASH KC_NUHS // #
#define IE_BSLS KC_NUBS // (backslash)
#define IE_Z    KC_Z    // Z
#define IE_X    KC_X    // X
#define IE_C    KC_C    // C
#define IE_V    KC_V    // V
#define IE_B    KC_B    // B
#define IE_N    KC_N    // N
#define IE_M    KC_M    // M
#define IE_COMM KC_COMM // ,
#define IE_DOT  KC_DOT  // .
#define IE_SLSH KC_SLSH // /
#define IE_NOT  S(IE_GRV)  // ¬
#define IE_EXLM S(IE_1)    // !
#define IE_DQUO S(IE_2)    // "
#define IE_PND  S(IE_3)    // £
#define IE_DLR  S(IE_4)    // $
#define IE_PERC S(IE_5)    // %
#define IE_CIRC S(IE_6)    // ^
#define IE_AMPR S(IE_7)    // &
#define IE_ASTR S(IE_8)    // *
#define IE_LPRN S(IE_9)    // (
#define IE_RPRN S(IE_0)    // )
#define IE_UNDS S(IE_MINS) // _
#define IE_PLUS S(IE_EQL)  // +
#define IE_LCBR S(IE_LBRC) // {
#define IE_RCBR S(IE_RBRC) // }
#define IE_COLN S(IE_SCLN) // :
#define IE_AT   S(IE_QUOT) // @
#define IE_TILD S(IE_HASH) // ~
#define IE_PIPE S(IE_BSLS) // |
#define IE_LABK S(IE_COMM) // <
#define IE_RABK S(IE_DOT)  // >
#define IE_QUES S(IE_SLSH) // ?
#define IE_BRKP ALGR(IE_GRV)  // ¦
#define IE_EURO ALGR(IE_4)    // €
#define IE_EACU ALGR(IE_E)    // É
#define IE_UACU ALGR(IE_U)    // Ú
#define IE_IACU ALGR(IE_I)    // Í
#define IE_OACU ALGR(IE_O)    // Ó
#define IE_AACU ALGR(IE_A)    // Á
#define IE_ACUT ALGR(IE_QUOT) // ´ (dead)

