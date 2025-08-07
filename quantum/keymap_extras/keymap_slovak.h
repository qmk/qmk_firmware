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

#define QMK_SLOVAK_KEYCODES_VERSION "0.0.1"
#define QMK_SLOVAK_KEYCODES_VERSION_BCD 0x00000001
#define QMK_SLOVAK_KEYCODES_VERSION_MAJOR 0
#define QMK_SLOVAK_KEYCODES_VERSION_MINOR 0
#define QMK_SLOVAK_KEYCODES_VERSION_PATCH 1

// Aliases
#define SK_SCLN KC_GRV  // ;
#define SK_PLUS KC_1    // +
#define SK_LCAR KC_2    // ľ
#define SK_SCAR KC_3    // š
#define SK_CCAR KC_4    // č
#define SK_TCAR KC_5    // ť
#define SK_ZCAR KC_6    // ž
#define SK_YACU KC_7    // ý
#define SK_AACU KC_8    // á
#define SK_IACU KC_9    // í
#define SK_EACU KC_0    // é
#define SK_EQL  KC_MINS // =
#define SK_ACUT KC_EQL  // ´ (dead)
#define SK_Q    KC_Q    // Q
#define SK_W    KC_W    // W
#define SK_E    KC_E    // E
#define SK_R    KC_R    // R
#define SK_T    KC_T    // T
#define SK_Z    KC_Y    // Z
#define SK_U    KC_U    // U
#define SK_I    KC_I    // I
#define SK_O    KC_O    // O
#define SK_P    KC_P    // P
#define SK_UACU KC_LBRC // ú
#define SK_ADIA KC_RBRC // ä
#define SK_A    KC_A    // A
#define SK_S    KC_S    // S
#define SK_D    KC_D    // D
#define SK_F    KC_F    // F
#define SK_G    KC_G    // G
#define SK_H    KC_H    // H
#define SK_J    KC_J    // J
#define SK_K    KC_K    // K
#define SK_L    KC_L    // L
#define SK_OCIR KC_SCLN // ô
#define SK_SECT KC_QUOT // §
#define SK_NCAR KC_NUHS // ň
#define SK_AMPR KC_NUBS // &
#define SK_Y    KC_Z    // Y
#define SK_X    KC_X    // X
#define SK_C    KC_C    // C
#define SK_V    KC_V    // V
#define SK_B    KC_B    // B
#define SK_N    KC_N    // N
#define SK_M    KC_M    // M
#define SK_COMM KC_COMM // ,
#define SK_DOT  KC_DOT  // .
#define SK_MINS KC_SLSH // -
#define SK_RNGA S(SK_SCLN) // ° (dead)
#define SK_1    S(SK_PLUS) // 1
#define SK_2    S(SK_LCAR) // 2
#define SK_3    S(SK_SCAR) // 3
#define SK_4    S(SK_CCAR) // 4
#define SK_5    S(SK_TCAR) // 5
#define SK_6    S(SK_ZCAR) // 6
#define SK_7    S(SK_YACU) // 7
#define SK_8    S(SK_AACU) // 8
#define SK_9    S(SK_IACU) // 9
#define SK_0    S(SK_EACU) // 0
#define SK_PERC S(SK_EQL)  // %
#define SK_CARN S(SK_ACUT) // ˇ (dead)
#define SK_SLSH S(SK_UACU) // /
#define SK_LPRN S(SK_ADIA) // (
#define SK_DQUO S(SK_OCIR) // "
#define SK_EXLM S(SK_SECT) // !
#define SK_RPRN S(SK_NCAR) // )
#define SK_ASTR S(SK_AMPR) // *
#define SK_QUES S(SK_COMM) // ?
#define SK_COLN S(SK_DOT)  // :
#define SK_UNDS S(SK_MINS) // _
#define SK_TILD ALGR(SK_PLUS) // ~
#define SK_CIRC ALGR(SK_SCAR) // ^ (dead)
#define SK_BREV ALGR(SK_CCAR) // ˘ (dead)
#define SK_OGON ALGR(SK_TCAR) // ˛ (dead)
#define SK_GRV  ALGR(SK_ZCAR) // `
#define SK_DOTA ALGR(SK_YACU) // ˙ (dead)
#define SK_DACU ALGR(SK_EACU) // ˝ (dead)
#define SK_DIAE ALGR(SK_EQL)  // ¨ (dead)
#define SK_CEDL ALGR(SK_ACUT) // ¸ (dead)
#define SK_BSLS ALGR(SK_Q)    // (backslash)
#define SK_PIPE ALGR(SK_W)    // |
#define SK_EURO ALGR(SK_E)    // €
#define SK_QUOT ALGR(SK_P)    // '
#define SK_DIV  ALGR(SK_UACU) // ÷
#define SK_MUL  ALGR(SK_ADIA) // ×
#define SK_LDST ALGR(SK_S)    // đ
#define SK_CDST ALGR(SK_D)    // Đ
#define SK_LBRC ALGR(SK_F)    // [
#define SK_RBRC ALGR(SK_G)    // ]
#define SK_LLST ALGR(SK_K)    // ł
#define SK_CLST ALGR(SK_L)    // Ł
#define SK_DLR  ALGR(SK_OCIR) // $
#define SK_SS   ALGR(SK_SECT) // ß
#define SK_CURR ALGR(SK_NCAR) // ¤
#define SK_LABK ALGR(SK_AMPR) // <
#define SK_RABK ALGR(SK_Y)    // >
#define SK_HASH ALGR(SK_X)    // #
#define SK_AT   ALGR(SK_V)    // @
#define SK_LCBR ALGR(SK_B)    // {
#define SK_RCBR ALGR(SK_N)    // }

