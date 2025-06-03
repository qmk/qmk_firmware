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

#define QMK_HUNGARIAN_KEYCODES_VERSION "0.0.1"
#define QMK_HUNGARIAN_KEYCODES_VERSION_BCD 0x00000001
#define QMK_HUNGARIAN_KEYCODES_VERSION_MAJOR 0
#define QMK_HUNGARIAN_KEYCODES_VERSION_MINOR 0
#define QMK_HUNGARIAN_KEYCODES_VERSION_PATCH 1

// Aliases
#define HU_0    KC_GRV  // 0
#define HU_1    KC_1    // 1
#define HU_2    KC_2    // 2
#define HU_3    KC_3    // 3
#define HU_4    KC_4    // 4
#define HU_5    KC_5    // 5
#define HU_6    KC_6    // 6
#define HU_7    KC_7    // 7
#define HU_8    KC_8    // 8
#define HU_9    KC_9    // 9
#define HU_ODIA KC_0    // Ö
#define HU_UDIA KC_MINS // Ü
#define HU_OACU KC_EQL  // Ó
#define HU_Q    KC_Q    // Q
#define HU_W    KC_W    // W
#define HU_E    KC_E    // E
#define HU_R    KC_R    // R
#define HU_T    KC_T    // T
#define HU_Z    KC_Y    // Z
#define HU_U    KC_U    // U
#define HU_I    KC_I    // I
#define HU_O    KC_O    // O
#define HU_P    KC_P    // P
#define HU_ODAC KC_LBRC // Ő
#define HU_UACU KC_RBRC // Ú
#define HU_A    KC_A    // A
#define HU_S    KC_S    // S
#define HU_D    KC_D    // D
#define HU_F    KC_F    // F
#define HU_G    KC_G    // G
#define HU_H    KC_H    // H
#define HU_J    KC_J    // J
#define HU_K    KC_K    // K
#define HU_L    KC_L    // L
#define HU_EACU KC_SCLN // É
#define HU_AACU KC_QUOT // Á
#define HU_UDAC KC_NUHS // Ű
#define HU_IACU KC_NUBS // Í
#define HU_Y    KC_Z    // Y
#define HU_X    KC_X    // X
#define HU_C    KC_C    // C
#define HU_V    KC_V    // V
#define HU_B    KC_B    // B
#define HU_N    KC_N    // N
#define HU_M    KC_M    // M
#define HU_COMM KC_COMM // ,
#define HU_DOT  KC_DOT  // .
#define HU_MINS KC_SLSH // -
#define HU_SECT S(HU_0)    // §
#define HU_QUOT S(HU_1)    // '
#define HU_DQUO S(HU_2)    // "
#define HU_PLUS S(HU_3)    // +
#define HU_EXLM S(HU_4)    // !
#define HU_PERC S(HU_5)    // %
#define HU_SLSH S(HU_6)    // /
#define HU_EQL  S(HU_7)    // =
#define HU_LPRN S(HU_8)    // (
#define HU_RPRN S(HU_9)    // )
#define HU_QUES S(HU_COMM) // ?
#define HU_COLN S(HU_DOT)  // :
#define HU_UNDS S(HU_MINS) // _
#define HU_TILD ALGR(HU_1)    // ~
#define HU_CARN ALGR(HU_2)    // ˇ (dead)
#define HU_CIRC ALGR(HU_3)    // ^ (dead)
#define HU_BREV ALGR(HU_4)    // ˘ (dead)
#define HU_RNGA ALGR(HU_5)    // ° (dead)
#define HU_OGON ALGR(HU_6)    // ˛ (dead)
#define HU_GRV  ALGR(HU_7)    // `
#define HU_DOTA ALGR(HU_8)    // ˙ (dead)
#define HU_ACUT ALGR(HU_9)    // ´ (dead)
#define HU_DACU ALGR(HU_ODIA) // ˝ (dead)
#define HU_DIAE ALGR(HU_UDIA) // ¨ (dead)
#define HU_CEDL ALGR(HU_OACU) // ¸ (dead)
#define HU_BSLS ALGR(HU_Q)    // (backslash)
#define HU_PIPE ALGR(HU_W)    // |
#define HU_CADI ALGR(HU_E)    // Ä
#define HU_EURO ALGR(HU_U)    // €
#define HU_DIV  ALGR(HU_ODAC) // ÷
#define HU_MUL  ALGR(HU_UACU) // ×
#define HU_LADI ALGR(HU_A)    // ä
#define HU_LDST ALGR(HU_S)    // đ
#define HU_CDST ALGR(HU_D)    // Đ
#define HU_LBRC ALGR(HU_F)    // [
#define HU_RBRC ALGR(HU_G)    // ]
#define HU_LLST ALGR(HU_K)    // ł
#define HU_CLST ALGR(HU_L)    // Ł
#define HU_DLR  ALGR(HU_EACU) // $
#define HU_SS   ALGR(HU_AACU) // ß
#define HU_CURR ALGR(HU_UDAC) // ¤
#define HU_LABK ALGR(HU_IACU) // <
#define HU_RABK ALGR(HU_Y)    // >
#define HU_HASH ALGR(HU_X)    // #
#define HU_AMPR ALGR(HU_C)    // &
#define HU_AT   ALGR(HU_V)    // @
#define HU_LCBR ALGR(HU_B)    // {
#define HU_RCBR ALGR(HU_N)    // }
#define HU_SCLN ALGR(HU_COMM) // ;
#define HU_ASTR ALGR(HU_MINS) // *

