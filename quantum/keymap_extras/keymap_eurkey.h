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
#define EU_GRV  KC_GRV  // `
#define EU_1    KC_1    // 1
#define EU_2    KC_2    // 2
#define EU_3    KC_3    // 3
#define EU_4    KC_4    // 4
#define EU_5    KC_5    // 5
#define EU_6    KC_6    // 6
#define EU_7    KC_7    // 7
#define EU_8    KC_8    // 8
#define EU_9    KC_9    // 9
#define EU_0    KC_0    // 0
#define EU_MINS KC_MINS // -
#define EU_EQL  KC_EQL  // =
#define EU_Q    KC_Q    // Q
#define EU_W    KC_W    // W
#define EU_E    KC_E    // E
#define EU_R    KC_R    // R
#define EU_T    KC_T    // T
#define EU_Y    KC_Y    // Y
#define EU_U    KC_U    // U
#define EU_I    KC_I    // I
#define EU_O    KC_O    // O
#define EU_P    KC_P    // P
#define EU_LBRC KC_LBRC // [
#define EU_RBRC KC_RBRC // ]
#define EU_BSLS KC_BSLS // (backslash)
#define EU_A    KC_A    // A
#define EU_S    KC_S    // S
#define EU_D    KC_D    // D
#define EU_F    KC_F    // F
#define EU_G    KC_G    // G
#define EU_H    KC_H    // H
#define EU_J    KC_J    // J
#define EU_K    KC_K    // K
#define EU_L    KC_L    // L
#define EU_SCLN KC_SCLN // ;
#define EU_QUOT KC_QUOT // '
#define EU_Z    KC_Z    // Z
#define EU_X    KC_X    // X
#define EU_C    KC_C    // C
#define EU_V    KC_V    // V
#define EU_B    KC_B    // B
#define EU_N    KC_N    // N
#define EU_M    KC_M    // M
#define EU_COMM KC_COMM // ,
#define EU_DOT  KC_DOT  // .
#define EU_SLSH KC_SLSH // /
#define EU_TILD S(EU_GRV)  // ~
#define EU_EXLM S(EU_1)    // !
#define EU_AT   S(EU_2)    // @
#define EU_HASH S(EU_3)    // #
#define EU_DLR  S(EU_4)    // $
#define EU_PERC S(EU_5)    // %
#define EU_CIRC S(EU_6)    // ^
#define EU_AMPR S(EU_7)    // &
#define EU_ASTR S(EU_8)    // *
#define EU_LPRN S(EU_9)    // (
#define EU_RPRN S(EU_0)    // )
#define EU_UNDS S(EU_MINS) // _
#define EU_PLUS S(EU_EQL)  // +
#define EU_LCBR S(EU_LBRC) // {
#define EU_RCBR S(EU_RBRC) // }
#define EU_PIPE S(EU_BSLS) // |
#define EU_COLN S(EU_SCLN) // :
#define EU_DQUO S(EU_QUOT) // "
#define EU_LABK S(EU_COMM) // <
#define EU_RABK S(EU_DOT)  // >
#define EU_QUES S(EU_SLSH) // ?
#define EU_DGRV ALGR(EU_GRV)  // ` (dead)
#define EU_IEXL ALGR(EU_1)    // ¡
#define EU_FORD ALGR(EU_2)    // ª
#define EU_MORD ALGR(EU_3)    // º
#define EU_PND  ALGR(EU_4)    // £
#define EU_EURO ALGR(EU_5)    // €
#define EU_DCIR ALGR(EU_6)    // ^ (dead)
#define EU_RNGA ALGR(EU_7)    // ˚ (dead)
#define EU_DLQU ALGR(EU_8)    // „
#define EU_LDQU ALGR(EU_9)    // “
#define EU_RDQU ALGR(EU_0)    // ”
#define EU_NDSH ALGR(EU_MINS) // –
#define EU_MUL  ALGR(EU_EQL)  // ×
#define EU_AE   ALGR(EU_Q)    // æ
#define EU_ARNG ALGR(EU_W)    // Å
#define EU_EDIA ALGR(EU_E)    // Ë
#define EU_YACU ALGR(EU_R)    // Ý
#define EU_THRN ALGR(EU_T)    // Þ
#define EU_YDIA ALGR(EU_Y)    // Ÿ
#define EU_UDIA ALGR(EU_U)    // Ü
#define EU_IDIA ALGR(EU_I)    // Ï
#define EU_ODIA ALGR(EU_O)    // Ö
#define EU_OE   ALGR(EU_P)    // Œ
#define EU_LDAQ ALGR(EU_LBRC) // «
#define EU_RDAQ ALGR(EU_RBRC) // »
#define EU_NOT  ALGR(EU_BSLS) // ¬
#define EU_ADIA ALGR(EU_A)    // Ä
#define EU_SS   ALGR(EU_S)    // ß
#define EU_ETH  ALGR(EU_D)    // Ð
#define EU_EGRV ALGR(EU_F)    // È
#define EU_EACU ALGR(EU_G)    // É
#define EU_UGRV ALGR(EU_H)    // Ù
#define EU_UACU ALGR(EU_J)    // Ú
#define EU_IJ   ALGR(EU_K)    // Ĳ
#define EU_OSTR ALGR(EU_L)    // Ø
#define EU_DEG  ALGR(EU_SCLN) // °
#define EU_ACUT ALGR(EU_QUOT) // ´ (dead)
#define EU_AGRV ALGR(EU_Z)    // À
#define EU_AACU ALGR(EU_X)    // Á
#define EU_CCED ALGR(EU_C)    // Ç
#define EU_IGRV ALGR(EU_V)    // Ì
#define EU_IACU ALGR(EU_B)    // Í
#define EU_NTIL ALGR(EU_N)    // Ñ
#define EU_DGRK ALGR(EU_M)    // μ (dead Greek key)
#define EU_OGRV ALGR(EU_COMM) // Ò
#define EU_OACU ALGR(EU_DOT)  // Ó
#define EU_IQUE ALGR(EU_SLSH) // ¿
#define EU_DTIL ALGR(EU_TILD) // ~ (dead)
#define EU_SUP1 S(ALGR(EU_1))    // ¹
#define EU_SUP2 S(ALGR(EU_2))    // ²
#define EU_SUP3 S(ALGR(EU_3))    // ³
#define EU_YEN  ALGR(EU_DLR)  // ¥
#define EU_CENT S(EU_EURO) // ¢
#define EU_CARN S(EU_DCIR) // ˇ (dead)
#define EU_MACR S(ALGR(EU_7))    // ¯ (dead)
#define EU_SLQU S(EU_DLQU) // ‚
#define EU_LSQU S(EU_LDQU) // ‘
#define EU_RSQU S(EU_RDQU) // ’
#define EU_MDSH S(EU_NDSH) // —
#define EU_DIV  S(EU_MUL)  // ÷
#define EU_LSAQ S(EU_LDAQ) // ‹
#define EU_RSAQ S(EU_RDAQ) // ›
#define EU_BRKP S(ALGR(EU_BSLS)) // ¦
#define EU_SECT S(ALGR(EU_S))    // §
#define EU_MDDT S(ALGR(EU_SCLN)) // ·
#define EU_DIAE ALGR(EU_DQUO) // ¨ (dead)
#define EU_ELLP ALGR(EU_QUES) // …

