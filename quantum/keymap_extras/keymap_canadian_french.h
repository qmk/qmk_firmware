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
#define FC_HASH KC_GRV  // #
#define FC_1    KC_1    // 1
#define FC_2    KC_2    // 2
#define FC_3    KC_3    // 3
#define FC_4    KC_4    // 4
#define FC_5    KC_5    // 5
#define FC_6    KC_6    // 6
#define FC_7    KC_7    // 7
#define FC_8    KC_8    // 8
#define FC_9    KC_9    // 9
#define FC_0    KC_0    // 0
#define FC_MINS KC_MINS // -
#define FC_EQL  KC_EQL  // =
#define FC_Q    KC_Q    // Q
#define FC_W    KC_W    // W
#define FC_E    KC_E    // E
#define FC_R    KC_R    // R
#define FC_T    KC_T    // T
#define FC_Y    KC_Y    // Y
#define FC_U    KC_U    // U
#define FC_I    KC_I    // I
#define FC_O    KC_O    // O
#define FC_P    KC_P    // P
#define FC_DCIR KC_LBRC // ^ (dead)
#define FC_CEDL KC_RBRC // ¸ (dead)
#define FC_A    KC_A    // A
#define FC_S    KC_S    // S
#define FC_D    KC_D    // D
#define FC_F    KC_F    // F
#define FC_G    KC_G    // G
#define FC_H    KC_H    // H
#define FC_J    KC_J    // J
#define FC_K    KC_K    // K
#define FC_L    KC_L    // L
#define FC_SCLN KC_SCLN // ;
#define FC_DGRV KC_QUOT // ` (dead)
#define FC_LABK KC_NUHS // <
#define FC_LDAQ KC_NUBS // «
#define FC_Z    KC_Z    // Z
#define FC_X    KC_X    // X
#define FC_C    KC_C    // C
#define FC_V    KC_V    // V
#define FC_B    KC_B    // B
#define FC_N    KC_N    // N
#define FC_M    KC_M    // M
#define FC_COMM KC_COMM // ,
#define FC_DOT  KC_DOT  // .
#define FC_EACU KC_SLSH // É
#define FC_PIPE S(FC_HASH) // |
#define FC_EXLM S(FC_1)    // !
#define FC_DQUO S(FC_2)    // "
#define FC_SLSH S(FC_3)    // /
#define FC_DLR  S(FC_4)    // $
#define FC_PERC S(FC_5)    // %
#define FC_QUES S(FC_6)    // ?
#define FC_AMPR S(FC_7)    // &
#define FC_ASTR S(FC_8)    // *
#define FC_LPRN S(FC_9)    // (
#define FC_RPRN S(FC_0)    // )
#define FC_UNDS S(FC_MINS) // _
#define FC_PLUS S(FC_EQL)  // +
#define FC_DIAE S(FC_CEDL) // ¨ (dead)
#define FC_COLN S(FC_SCLN) // :
#define FC_RDAQ S(FC_LDAQ) // »
#define FC_QUOT S(FC_COMM) // '
#define FC_BSLS ALGR(FC_HASH) // (backslash)
#define FC_PLMN ALGR(FC_1)    // ±
#define FC_AT   ALGR(FC_2)    // @
#define FC_PND  ALGR(FC_3)    // £
#define FC_CENT ALGR(FC_4)    // ¢
#define FC_CURR ALGR(FC_5)    // ¤
#define FC_NOT  ALGR(FC_6)    // ¬
#define FC_BRKP ALGR(FC_7)    // ¦
#define FC_SUP2 ALGR(FC_8)    // ²
#define FC_SUP3 ALGR(FC_9)    // ³
#define FC_QRTR ALGR(FC_0)    // ¼
#define FC_HALF ALGR(FC_MINS) // ½
#define FC_TQTR ALGR(FC_EQL)  // ¾
#define FC_EURO ALGR(FC_E)    // €
#define FC_SECT ALGR(FC_O)    // §
#define FC_PARA ALGR(FC_P)    // ¶
#define FC_LBRC ALGR(FC_DCIR) // [
#define FC_RBRC ALGR(FC_CEDL) // ]
#define FC_TILD ALGR(FC_SCLN) // ~
#define FC_LCBR ALGR(FC_DGRV) // {
#define FC_RCBR ALGR(FC_LABK) // }
#define FC_DEG  ALGR(FC_LDAQ) // °
#define FC_MICR ALGR(FC_M)    // µ
#define FC_MACR ALGR(FC_COMM) // ¯
#define FC_SHYP ALGR(FC_DOT)  // ­ (soft hyphen)
#define FC_ACUT ALGR(FC_EACU) // ´ (dead)

