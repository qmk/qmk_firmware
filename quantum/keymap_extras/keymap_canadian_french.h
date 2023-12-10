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
#define FR_HASH KC_GRV  // #
#define FR_1    KC_1    // 1
#define FR_2    KC_2    // 2
#define FR_3    KC_3    // 3
#define FR_4    KC_4    // 4
#define FR_5    KC_5    // 5
#define FR_6    KC_6    // 6
#define FR_7    KC_7    // 7
#define FR_8    KC_8    // 8
#define FR_9    KC_9    // 9
#define FR_0    KC_0    // 0
#define FR_MINS KC_MINS // -
#define FR_EQL  KC_EQL  // =
#define FR_Q    KC_Q    // Q
#define FR_W    KC_W    // W
#define FR_E    KC_E    // E
#define FR_R    KC_R    // R
#define FR_T    KC_T    // T
#define FR_Y    KC_Y    // Y
#define FR_U    KC_U    // U
#define FR_I    KC_I    // I
#define FR_O    KC_O    // O
#define FR_P    KC_P    // P
#define FR_DCIR KC_LBRC // ^ (dead)
#define FR_CEDL KC_RBRC // ¸ (dead)
#define FR_A    KC_A    // A
#define FR_S    KC_S    // S
#define FR_D    KC_D    // D
#define FR_F    KC_F    // F
#define FR_G    KC_G    // G
#define FR_H    KC_H    // H
#define FR_J    KC_J    // J
#define FR_K    KC_K    // K
#define FR_L    KC_L    // L
#define FR_SCLN KC_SCLN // ;
#define FR_DGRV KC_QUOT // ` (dead)
#define FR_LABK KC_NUHS // <
#define FR_LDAQ KC_NUBS // «
#define FR_Z    KC_Z    // Z
#define FR_X    KC_X    // X
#define FR_C    KC_C    // C
#define FR_V    KC_V    // V
#define FR_B    KC_B    // B
#define FR_N    KC_N    // N
#define FR_M    KC_M    // M
#define FR_COMM KC_COMM // ,
#define FR_DOT  KC_DOT  // .
#define FR_EACU KC_SLSH // É
#define FR_PIPE S(FR_HASH) // |
#define FR_EXLM S(FR_1)    // !
#define FR_DQUO S(FR_2)    // "
#define FR_SLSH S(FR_3)    // /
#define FR_DLR  S(FR_4)    // $
#define FR_PERC S(FR_5)    // %
#define FR_QUES S(FR_6)    // ?
#define FR_AMPR S(FR_7)    // &
#define FR_ASTR S(FR_8)    // *
#define FR_LPRN S(FR_9)    // (
#define FR_RPRN S(FR_0)    // )
#define FR_UNDS S(FR_MINS) // _
#define FR_PLUS S(FR_EQL)  // +
#define FR_DIAE S(FR_CEDL) // ¨ (dead)
#define FR_COLN S(FR_SCLN) // :
#define FR_RABK S(FR_LABK) // >
#define FR_RDAQ S(FR_LDAQ) // »
#define FR_QUOT S(FR_COMM) // '
#define FR_BSLS ALGR(FR_HASH) // (backslash)
#define FR_PLMN ALGR(FR_1)    // ±
#define FR_AT   ALGR(FR_2)    // @
#define FR_PND  ALGR(FR_3)    // £
#define FR_CENT ALGR(FR_4)    // ¢
#define FR_CURR ALGR(FR_5)    // ¤
#define FR_NOT  ALGR(FR_6)    // ¬
#define FR_BRKP ALGR(FR_7)    // ¦
#define FR_SUP2 ALGR(FR_8)    // ²
#define FR_SUP3 ALGR(FR_9)    // ³
#define FR_QRTR ALGR(FR_0)    // ¼
#define FR_HALF ALGR(FR_MINS) // ½
#define FR_TQTR ALGR(FR_EQL)  // ¾
#define FR_SECT ALGR(FR_O)    // §
#define FR_PARA ALGR(FR_P)    // ¶
#define FR_LBRC ALGR(FR_DCIR) // [
#define FR_RBRC ALGR(FR_CEDL) // ]
#define FR_TILD ALGR(FR_SCLN) // ~
#define FR_LCBR ALGR(FR_DGRV) // {
#define FR_RCBR ALGR(FR_LABK) // }
#define FR_DEG  ALGR(FR_LDAQ) // °
#define FR_MICR ALGR(FR_M)    // µ
#define FR_MACR ALGR(FR_COMM) // ¯
#define FR_SHYP ALGR(FR_DOT)  // ­ (soft hyphen)
#define FR_ACUT ALGR(FR_EACU) // ´ (dead)

