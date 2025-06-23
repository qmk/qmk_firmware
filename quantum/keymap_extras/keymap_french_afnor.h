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
#define FR_AT   KC_GRV  // @
#define FR_AGRV KC_1    // à
#define FR_EACU KC_2    // é
#define FR_EGRV KC_3    // è
#define FR_ECIR KC_4    // ê
#define FR_LPRN KC_5    // (
#define FR_RPRN KC_6    // )
#define FR_LSQU KC_7    // ‘
#define FR_RSQU KC_8    // ’
#define FR_LDAQ KC_9    // «
#define FR_RDAQ KC_0    // »
#define FR_QUOT KC_MINS // '
#define FR_DCIR KC_EQL  // ^ (dead)
#define FR_A    KC_Q    // A
#define FR_Z    KC_W    // Z
#define FR_E    KC_E    // E
#define FR_R    KC_R    // R
#define FR_T    KC_T    // T
#define FR_Y    KC_Y    // Y
#define FR_U    KC_U    // U
#define FR_I    KC_I    // I
#define FR_O    KC_O    // O
#define FR_P    KC_P    // P
#define FR_MINS KC_LBRC // -
#define FR_PLUS KC_RBRC // +
#define FR_Q    KC_A    // Q
#define FR_S    KC_S    // S
#define FR_D    KC_D    // D
#define FR_F    KC_F    // F
#define FR_G    KC_G    // G
#define FR_H    KC_H    // H
#define FR_J    KC_J    // J
#define FR_K    KC_K    // K
#define FR_L    KC_L    // L
#define FR_M    KC_SCLN // M
#define FR_SLSH KC_QUOT // /
#define FR_ASTR KC_NUHS // *
#define FR_LABK KC_NUBS // <
#define FR_W    KC_Z    // W
#define FR_X    KC_X    // X
#define FR_C    KC_C    // C
#define FR_V    KC_V    // V
#define FR_B    KC_B    // B
#define FR_N    KC_N    // N
#define FR_DOT  KC_M    // .
#define FR_COMM KC_COMM // ,
#define FR_COLN KC_DOT  // :
#define FR_SCLN KC_SLSH // ;
#define FR_HASH S(FR_AT)   // #
#define FR_1    S(FR_AGRV) // 1
#define FR_2    S(FR_EACU) // 2
#define FR_3    S(FR_EGRV) // 3
#define FR_4    S(FR_ECIR) // 4
#define FR_5    S(FR_LPRN) // 5
#define FR_6    S(FR_RPRN) // 6
#define FR_7    S(FR_LSQU) // 7
#define FR_8    S(FR_RSQU) // 8
#define FR_9    S(FR_LDAQ) // 9
#define FR_0    S(FR_RDAQ) // 0
#define FR_DQUO S(FR_QUOT) // "
#define FR_DIAE S(FR_DCIR) // ¨ (dead)
#define FR_NDSH S(FR_MINS) // –
#define FR_PLMN S(FR_PLUS) // ±
#define FR_BSLS S(FR_SLSH) // (backslash)
#define FR_HALF S(FR_ASTR) // ½
#define FR_RABK S(FR_LABK) // >
#define FR_QUES S(FR_DOT)  // ?
#define FR_EXLM S(FR_COMM) // !
#define FR_ELLP S(FR_COLN) // …
#define FR_EQL  S(FR_SCLN) // =
#define FR_BREV ALGR(FR_AT)   // ˘ (dead)
#define FR_SECT ALGR(FR_AGRV) // §
#define FR_ACUT ALGR(FR_EACU) // ´ (dead)
#define FR_GRV  ALGR(FR_EGRV) // ` (dead)
#define FR_AMPR ALGR(FR_ECIR) // &
#define FR_LBRC ALGR(FR_LPRN) // [
#define FR_RBRC ALGR(FR_RPRN) // ]
#define FR_MACR ALGR(FR_LSQU) // ¯ (dead)
#define FR_UNDS ALGR(FR_RSQU) // _
#define FR_LDQU ALGR(FR_LDAQ) // “
#define FR_RDQU ALGR(FR_RDAQ) // ”
#define FR_DEG  ALGR(FR_QUOT) // °
#define FR_CARN ALGR(FR_DCIR) // ˇ (dead)
#define FR_AE   ALGR(FR_A)    // æ
#define FR_PND  ALGR(FR_Z)    // £
#define FR_EURO ALGR(FR_E)    // €
#define FR_REGD ALGR(FR_R)    // ®
#define FR_LCBR ALGR(FR_T)    // {
#define FR_RCBR ALGR(FR_Y)    // }
#define FR_UGRV ALGR(FR_U)    // ù
#define FR_DOTA ALGR(FR_I)    // ˙ (dead)
#define FR_OE   ALGR(FR_O)    // œ
#define FR_PERC ALGR(FR_P)    // %
#define FR_MMNS ALGR(FR_MINS) // −
#define FR_DAGG ALGR(FR_PLUS) // †
#define FR_THET ALGR(FR_Q)    // θ
#define FR_SS   ALGR(FR_S)    // ß
#define FR_DLR  ALGR(FR_D)    // $
#define FR_CURR ALGR(FR_F)    // ¤ (dead monetary key)
#define FR_DGRK ALGR(FR_G)    // µ (dead Greek key)
#define FR_EU   ALGR(FR_H)    // Eu (dead European symbol key)
#define FR_DSLS ALGR(FR_K)    // ∕ (dead)
#define FR_PIPE ALGR(FR_L)    // |
#define FR_INFN ALGR(FR_M)    // ∞
#define FR_DIV  ALGR(FR_SLSH) // ÷
#define FR_MUL  ALGR(FR_ASTR) // ×
#define FR_LEQL ALGR(FR_LABK) // ≤
#define FR_EZH  ALGR(FR_W)    // ʒ
#define FR_COPY ALGR(FR_X)    // ©
#define FR_CCED ALGR(FR_C)    // ç
#define FR_CEDL ALGR(FR_V)    // ¸ (dead)
#define FR_DMNS ALGR(FR_B)    // − (dead)
#define FR_DTIL ALGR(FR_N)    // ~ (dead)
#define FR_IQUE ALGR(FR_DOT)  // ¿
#define FR_IEXL ALGR(FR_COMM) // ¡
#define FR_MDDT ALGR(FR_COLN) // ·
#define FR_AEQL ALGR(FR_SCLN) // ≃
#define FR_IBRV S(ALGR(FR_AT))   // ̑ (dead)
#define FR_DACU S(ALGR(FR_LPRN)) // ˝ (dead)
#define FR_DGRV S(ALGR(FR_RPRN)) // ̏ (dead)
#define FR_MDSH S(ALGR(FR_RSQU)) // —
#define FR_LSAQ S(ALGR(FR_LDAQ)) // ‹
#define FR_RSAQ S(ALGR(FR_RDAQ)) // ›
#define FR_RNGA S(ALGR(FR_QUOT)) // ˚ (dead)
#define FR_TM   S(ALGR(FR_T))    // ™
#define FR_DOTB S(ALGR(FR_I))    // ̣ (dead)
#define FR_PERM S(ALGR(FR_P))    // ‰
#define FR_NBHY S(ALGR(FR_MINS)) // ‑ (non-breaking hyphen)
#define FR_DDAG S(ALGR(FR_PLUS)) // ‡
#define FR_MACB S(ALGR(FR_H))    // ˍ (dead)
#define FR_SQRT S(ALGR(FR_SLSH)) // √
#define FR_QRTR S(ALGR(FR_ASTR)) // ¼
#define FR_GEQL S(ALGR(FR_LABK)) // ≥
#define FR_OGON S(ALGR(FR_V))    // ˛ (dead)
#define FR_DCMM S(ALGR(FR_COMM)) // ̦ (dead)
#define FR_NEQL S(ALGR(FR_SCLN)) // ≠

