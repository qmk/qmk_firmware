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

#define QMK_TURKISH_F_KEYCODES_VERSION "0.0.1"
#define QMK_TURKISH_F_KEYCODES_VERSION_BCD 0x00000001
#define QMK_TURKISH_F_KEYCODES_VERSION_MAJOR 0
#define QMK_TURKISH_F_KEYCODES_VERSION_MINOR 0
#define QMK_TURKISH_F_KEYCODES_VERSION_PATCH 1

// Aliases
#define TR_PLUS KC_GRV  // +
#define TR_1    KC_1    // 1
#define TR_2    KC_2    // 2
#define TR_3    KC_3    // 3
#define TR_4    KC_4    // 4
#define TR_5    KC_5    // 5
#define TR_6    KC_6    // 6
#define TR_7    KC_7    // 7
#define TR_8    KC_8    // 8
#define TR_9    KC_9    // 9
#define TR_0    KC_0    // 0
#define TR_SLSH KC_MINS // /
#define TR_MINS KC_EQL  // -
#define TR_F    KC_Q    // F
#define TR_G    KC_W    // G
#define TR_GBRV KC_E    // Ğ
#define TR_I    KC_R    // I
#define TR_O    KC_T    // O
#define TR_D    KC_Y    // D
#define TR_R    KC_U    // R
#define TR_N    KC_I    // N
#define TR_H    KC_O    // H
#define TR_P    KC_P    // P
#define TR_Q    KC_LBRC // Q
#define TR_W    KC_RBRC // W
#define TR_U    KC_A    // U
#define TR_IDOT KC_S    // İ
#define TR_E    KC_D    // E
#define TR_A    KC_F    // A
#define TR_UDIA KC_G    // Ü
#define TR_T    KC_H    // T
#define TR_K    KC_J    // K
#define TR_M    KC_K    // M
#define TR_L    KC_L    // L
#define TR_Y    KC_SCLN // Y
#define TR_SCED KC_QUOT // Ş
#define TR_X    KC_NUHS // X
#define TR_LABK KC_NUBS // <
#define TR_J    KC_Z    // J
#define TR_ODIA KC_X    // Ö
#define TR_V    KC_C    // V
#define TR_C    KC_V    // C
#define TR_CCED KC_B    // Ç
#define TR_Z    KC_N    // Z
#define TR_S    KC_M    // S
#define TR_B    KC_COMM // B
#define TR_DOT  KC_DOT  // .
#define TR_COMM KC_SLSH // ,
#define TR_ASTR S(TR_PLUS) // *
#define TR_EXLM S(TR_1)    // !
#define TR_DQUO S(TR_2)    // "
#define TR_CIRC S(TR_3)    // ^ (dead)
#define TR_DLR  S(TR_4)    // $
#define TR_PERC S(TR_5)    // %
#define TR_AMPR S(TR_6)    // &
#define TR_QUOT S(TR_7)    // '
#define TR_LPRN S(TR_8)    // (
#define TR_RPRN S(TR_9)    // )
#define TR_EQL  S(TR_0)    // =
#define TR_QUES S(TR_SLSH) // ?
#define TR_UNDS S(TR_MINS) // _
#define TR_RABK S(TR_LABK) // >
#define TR_COLN S(TR_DOT)  // :
#define TR_SCLN S(TR_COMM) // ;
#define TR_NOT  ALGR(TR_PLUS) // ¬
#define TR_SUP1 ALGR(TR_1)    // ¹
#define TR_SUP2 ALGR(TR_2)    // ²
#define TR_HASH ALGR(TR_3)    // #
#define TR_QRTR ALGR(TR_4)    // ¼
#define TR_HALF ALGR(TR_5)    // ½
#define TR_TQTR ALGR(TR_6)    // ¾
#define TR_LCBR ALGR(TR_7)    // {
#define TR_LBRC ALGR(TR_8)    // [
#define TR_RBRC ALGR(TR_9)    // ]
#define TR_RCBR ALGR(TR_0)    // }
#define TR_BSLS ALGR(TR_SLSH) // (backslash)
#define TR_PIPE ALGR(TR_MINS) // |
#define TR_AT   ALGR(TR_F)    // @
#define TR_PILC ALGR(TR_I)    // ¶
#define TR_YEN  ALGR(TR_D)    // ¥
#define TR_OSTR ALGR(TR_H)    // Ø
#define TR_PND  ALGR(TR_P)    // £
#define TR_DIAE ALGR(TR_Q)    // ¨ (dead)
#define TR_TILD ALGR(TR_W)    // ~ (dead)
#define TR_AE   ALGR(TR_U)    // Æ
#define TR_SS   ALGR(TR_IDOT) // ß
#define TR_EURO ALGR(TR_E)    // €
#define TR_LIRA ALGR(TR_T)    // ₺
#define TR_ACUT ALGR(TR_Y)    // ´ (dead)
#define TR_GRV  ALGR(TR_X)    // ` (dead)
#define TR_LDAQ ALGR(TR_J)    // «
#define TR_RDAQ ALGR(TR_ODIA) // »
#define TR_CENT ALGR(TR_V)    // ¢
#define TR_MICR ALGR(TR_S)    // µ
#define TR_MUL  ALGR(TR_B)    // ×
#define TR_DIV  ALGR(TR_DOT)  // ÷
#define TR_SHYP ALGR(TR_COMM) // ­ (soft hyphen)
#define TR_SUP3 S(ALGR(TR_3))    // ³
#define TR_CURR S(ALGR(TR_4))    // ¤
#define TR_IQUE S(ALGR(TR_SLSH)) // ¿
#define TR_REGD S(ALGR(TR_I))    // ®
#define TR_SECT S(ALGR(TR_IDOT)) // §
#define TR_FORD S(ALGR(TR_A))    // ª
#define TR_BRKP S(ALGR(TR_LABK)) // ¦
#define TR_COPY S(ALGR(TR_V))    // ©
#define TR_MORD S(ALGR(TR_S))    // º

