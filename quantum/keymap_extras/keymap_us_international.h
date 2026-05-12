// Copyright 2026 QMK
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

#define QMK_US_INTERNATIONAL_KEYCODES_VERSION "0.0.1"
#define QMK_US_INTERNATIONAL_KEYCODES_VERSION_BCD 0x00000001
#define QMK_US_INTERNATIONAL_KEYCODES_VERSION_MAJOR 0
#define QMK_US_INTERNATIONAL_KEYCODES_VERSION_MINOR 0
#define QMK_US_INTERNATIONAL_KEYCODES_VERSION_PATCH 1

// Aliases
#define US_DGRV KC_GRV  // ` (dead)
#define US_1    KC_1    // 1
#define US_2    KC_2    // 2
#define US_3    KC_3    // 3
#define US_4    KC_4    // 4
#define US_5    KC_5    // 5
#define US_6    KC_6    // 6
#define US_7    KC_7    // 7
#define US_8    KC_8    // 8
#define US_9    KC_9    // 9
#define US_0    KC_0    // 0
#define US_MINS KC_MINS // -
#define US_EQL  KC_EQL  // =
#define US_Q    KC_Q    // Q
#define US_W    KC_W    // W
#define US_E    KC_E    // E
#define US_R    KC_R    // R
#define US_T    KC_T    // T
#define US_Y    KC_Y    // Y
#define US_U    KC_U    // U
#define US_I    KC_I    // I
#define US_O    KC_O    // O
#define US_P    KC_P    // P
#define US_LBRC KC_LBRC // [
#define US_RBRC KC_RBRC // ]
#define US_BSLS KC_BSLS // (backslash)
#define US_A    KC_A    // A
#define US_S    KC_S    // S
#define US_D    KC_D    // D
#define US_F    KC_F    // F
#define US_G    KC_G    // G
#define US_H    KC_H    // H
#define US_J    KC_J    // J
#define US_K    KC_K    // K
#define US_L    KC_L    // L
#define US_SCLN KC_SCLN // ;
#define US_ACUT KC_QUOT // ´ (dead)
#define US_Z    KC_Z    // Z
#define US_X    KC_X    // X
#define US_C    KC_C    // C
#define US_V    KC_V    // V
#define US_B    KC_B    // B
#define US_N    KC_N    // N
#define US_M    KC_M    // M
#define US_COMM KC_COMM // ,
#define US_DOT  KC_DOT  // .
#define US_SLSH KC_SLSH // /
#define US_DTIL S(US_DGRV) // ~ (dead)
#define US_EXLM S(US_1)    // !
#define US_AT   S(US_2)    // @
#define US_HASH S(US_3)    // #
#define US_DLR  S(US_4)    // $
#define US_PERC S(US_5)    // %
#define US_DCIR S(US_6)    // ^ (dead)
#define US_AMPR S(US_7)    // &
#define US_ASTR S(US_8)    // *
#define US_LPRN S(US_9)    // (
#define US_RPRN S(US_0)    // )
#define US_UNDS S(US_MINS) // _
#define US_PLUS S(US_EQL)  // +
#define US_LCBR S(US_LBRC) // {
#define US_RCBR S(US_RBRC) // }
#define US_PIPE S(US_BSLS) // |
#define US_COLN S(US_SCLN) // :
#define US_DIAE S(US_ACUT) // ¨ (dead)
#define US_LABK S(US_COMM) // <
#define US_RABK S(US_DOT)  // >
#define US_QUES S(US_SLSH) // ?
#define US_IEXL ALGR(US_1)    // ¡
#define US_SUP2 ALGR(US_2)    // ²
#define US_SUP3 ALGR(US_3)    // ³
#define US_CURR ALGR(US_4)    // ¤
#define US_EURO ALGR(US_5)    // €
#define US_QRTR ALGR(US_6)    // ¼
#define US_HALF ALGR(US_7)    // ½
#define US_TQTR ALGR(US_8)    // ¾
#define US_LSQU ALGR(US_9)    // ‘
#define US_RSQU ALGR(US_0)    // ’
#define US_YEN  ALGR(US_MINS) // ¥
#define US_MUL  ALGR(US_EQL)  // ×
#define US_ADIA ALGR(US_Q)    // Ä
#define US_ARNG ALGR(US_W)    // Å
#define US_EACU ALGR(US_E)    // É
#define US_REGD ALGR(US_R)    // ®
#define US_THRN ALGR(US_T)    // Þ
#define US_UDIA ALGR(US_Y)    // Ü
#define US_UACU ALGR(US_U)    // Ú
#define US_IACU ALGR(US_I)    // Í
#define US_OACU ALGR(US_O)    // Ó
#define US_ODIA ALGR(US_P)    // Ö
#define US_LDAQ ALGR(US_LBRC) // «
#define US_RDAQ ALGR(US_RBRC) // »
#define US_NOT  ALGR(US_BSLS) // ¬
#define US_AACU ALGR(US_A)    // Á
#define US_SS   ALGR(US_S)    // ß
#define US_ETH  ALGR(US_D)    // Ð
#define US_OSTR ALGR(US_L)    // Ø
#define US_PILC ALGR(US_SCLN) // ¶
#define US_NDAC ALGR(US_ACUT) // ´
#define US_AE   ALGR(US_Z)    // Æ
#define US_COPY ALGR(US_C)    // ©
#define US_NTIL ALGR(US_N)    // Ñ
#define US_MICR ALGR(US_M)    // µ
#define US_CCED ALGR(US_COMM) // Ç
#define US_IQUE ALGR(US_SLSH) // ¿
#define US_SUP1 S(ALGR(US_1))    // ¹
#define US_PND  S(ALGR(US_4))    // £
#define US_DIV  S(ALGR(US_EQL))  // ÷
#define US_BRKP S(ALGR(US_BSLS)) // ¦
#define US_SECT S(ALGR(US_S))    // §
#define US_DEG  S(ALGR(US_SCLN)) // °
#define US_NDDR S(ALGR(US_ACUT)) // ¨
#define US_CENT S(ALGR(US_C))    // ¢

