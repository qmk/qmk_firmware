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

#define QMK_BEPO_KEYCODES_VERSION "0.0.1"
#define QMK_BEPO_KEYCODES_VERSION_BCD 0x00000001
#define QMK_BEPO_KEYCODES_VERSION_MAJOR 0
#define QMK_BEPO_KEYCODES_VERSION_MINOR 0
#define QMK_BEPO_KEYCODES_VERSION_PATCH 1

// Aliases
#define BP_DLR  KC_GRV  // $
#define BP_DQUO KC_1    // "
#define BP_LDAQ KC_2    // «
#define BP_RDAQ KC_3    // »
#define BP_LPRN KC_4    // (
#define BP_RPRN KC_5    // )
#define BP_AT   KC_6    // @
#define BP_PLUS KC_7    // +
#define BP_MINS KC_8    // -
#define BP_SLSH KC_9    // /
#define BP_ASTR KC_0    // *
#define BP_EQL  KC_MINS // =
#define BP_PERC KC_EQL  // %
#define BP_B    KC_Q    // B
#define BP_EACU KC_W    // É
#define BP_P    KC_E    // P
#define BP_O    KC_R    // O
#define BP_EGRV KC_T    // È
#define BP_DCIR KC_Y    // ^ (dead)
#define BP_V    KC_U    // V
#define BP_D    KC_I    // D
#define BP_L    KC_O    // L
#define BP_J    KC_P    // J
#define BP_Z    KC_LBRC // Z
#define BP_W    KC_RBRC // W
#define BP_A    KC_A    // A
#define BP_U    KC_S    // U
#define BP_I    KC_D    // I
#define BP_E    KC_F    // E
#define BP_COMM KC_G    // ,
#define BP_C    KC_H    // C
#define BP_T    KC_J    // T
#define BP_S    KC_K    // S
#define BP_R    KC_L    // R
#define BP_N    KC_SCLN // N
#define BP_M    KC_QUOT // M
#define BP_CCED KC_BSLS // Ç
#define BP_ECIR KC_NUBS // Ê
#define BP_AGRV KC_Z    // À
#define BP_Y    KC_X    // Y
#define BP_X    KC_C    // X
#define BP_DOT  KC_V    // .
#define BP_K    KC_B    // K
#define BP_QUOT KC_N    // '
#define BP_Q    KC_M    // Q
#define BP_G    KC_COMM // G
#define BP_H    KC_DOT  // H
#define BP_F    KC_SLSH // F
#define BP_HASH S(BP_DLR)  // #
#define BP_1    S(BP_DQUO) // 1
#define BP_2    S(BP_LDAQ) // 2
#define BP_3    S(BP_RDAQ) // 3
#define BP_4    S(BP_LPRN) // 4
#define BP_5    S(BP_RPRN) // 5
#define BP_6    S(BP_AT)   // 6
#define BP_7    S(BP_PLUS) // 7
#define BP_8    S(BP_MINS) // 8
#define BP_9    S(BP_SLSH) // 9
#define BP_0    S(BP_ASTR) // 0
#define BP_DEG  S(BP_EQL)  // °
#define BP_GRV  S(BP_PERC) // `
#define BP_EXLM S(BP_DCIR) // !
#define BP_SCLN S(BP_COMM) // ;
#define BP_COLN S(BP_DOT)  // :
#define BP_QUES S(BP_QUOT) // ?
#define BP_NBSP S(KC_SPC)  // (non-breaking space)
#define BP_NDSH ALGR(BP_DLR)  // –
#define BP_MDSH ALGR(BP_DQUO) // —
#define BP_LABK ALGR(BP_LDAQ) // <
#define BP_RABK ALGR(BP_RDAQ) // >
#define BP_LBRC ALGR(BP_LPRN) // [
#define BP_RBRC ALGR(BP_RPRN) // ]
#define BP_CIRC ALGR(BP_AT)   // ^
#define BP_PLMN ALGR(BP_PLUS) // ±
#define BP_MMNS ALGR(BP_MINS) // −
#define BP_DIV  ALGR(BP_SLSH) // ÷
#define BP_MUL  ALGR(BP_ASTR) // ×
#define BP_NEQL ALGR(BP_EQL)  // ≠
#define BP_PERM ALGR(BP_PERC) // ‰
#define BP_PIPE ALGR(BP_B)    // |
#define BP_ACUT ALGR(BP_EACU) // ´ (dead)
#define BP_AMPR ALGR(BP_P)    // &
#define BP_OE   ALGR(BP_O)    // Œ
#define BP_DGRV ALGR(BP_EGRV) // ` (dead)
#define BP_IEXL ALGR(BP_DCIR) // ¡
#define BP_CARN ALGR(BP_V)    // ˇ (dead)
#define BP_ETH  ALGR(BP_D)    // Ð
#define BP_DSLS ALGR(BP_L)    // / (dead)
#define BP_IJ   ALGR(BP_J)    // Ĳ
#define BP_SCHW ALGR(BP_Z)    // Ə
#define BP_BREV ALGR(BP_W)    // ˘ (dead)
#define BP_AE   ALGR(BP_A)    // Æ
#define BP_UGRV ALGR(BP_U)    // Ù
#define BP_DIAE ALGR(BP_I)    // ¨ (dead)
#define BP_EURO ALGR(BP_E)    // €
#define BP_COPY ALGR(BP_C)    // ©
#define BP_THRN ALGR(BP_T)    // Þ
#define BP_SS   ALGR(BP_S)    // ẞ
#define BP_REGD ALGR(BP_R)    // ®
#define BP_DTIL ALGR(BP_N)    // ~ (dead)
#define BP_MACR ALGR(BP_M)    // ¯ (dead)
#define BP_CEDL ALGR(BP_CCED) // ¸ (dead)
#define BP_BSLS ALGR(BP_AGRV) // (backslash)
#define BP_LCBR ALGR(BP_Y)    // {
#define BP_RCBR ALGR(BP_X)    // }
#define BP_ELLP ALGR(BP_DOT)  // …
#define BP_TILD ALGR(BP_K)    // ~
#define BP_IQUE ALGR(BP_QUES) // ¿
#define BP_RNGA ALGR(BP_Q)    // ° (dead)
#define BP_DGRK ALGR(BP_G)    // µ (dead Greek key)
#define BP_DAGG ALGR(BP_H)    // †
#define BP_OGON ALGR(BP_F)    // ˛ (dead)
#define BP_UNDS ALGR(KC_SPC)  // _
#define BP_PARA S(ALGR(BP_DLR))  // ¶
#define BP_DLQU S(ALGR(BP_DQUO)) // „
#define BP_LDQU S(ALGR(BP_LDAQ)) // “
#define BP_RDQU S(ALGR(BP_RDAQ)) // ”
#define BP_LEQL S(ALGR(BP_LPRN)) // ≤
#define BP_GEQL S(ALGR(BP_RPRN)) // ≥
#define BP_NOT  S(ALGR(BP_PLUS)) // ¬
#define BP_QRTR S(ALGR(BP_MINS)) // ¼
#define BP_HALF S(ALGR(BP_SLSH)) // ½
#define BP_TQTR S(ALGR(BP_ASTR)) // ¾
#define BP_PRIM S(ALGR(BP_EQL))  // ′
#define BP_DPRM S(ALGR(BP_PERC)) // ″
#define BP_BRKP S(ALGR(BP_B))    // ¦
#define BP_DACU S(ALGR(BP_EACU)) // ˝ (dead)
#define BP_SECT S(ALGR(BP_P))    // §
#define BP_DOTA S(ALGR(BP_I))    // ˙ (dead)
#define BP_CURR S(ALGR(BP_E))    // ¤ (dead)
#define BP_HORN S(ALGR(BP_COMM)) // ̛ (dead)
#define BP_LNGS S(ALGR(BP_C))    // ſ
#define BP_TM   S(ALGR(BP_R))    // ™
#define BP_MORD S(ALGR(BP_M))    // º
#define BP_DCMM S(ALGR(BP_CCED)) // , (dead)
#define BP_LSQU S(ALGR(BP_Y))    // ‘
#define BP_RSQU S(ALGR(BP_X))    // ’
#define BP_MDDT S(ALGR(BP_DOT))  // ·
#define BP_KEYB S(ALGR(BP_K))    // ⌨
#define BP_HOKA S(ALGR(BP_QUOT)) // ̉ (dead)
#define BP_DOTB S(ALGR(BP_Q))    // ̣ (dead)
#define BP_DDAG S(ALGR(BP_H))    // ‡
#define BP_FORD S(ALGR(BP_F))    // ª
#define BP_NNBS S(ALGR(KC_SPC))  // (narrow non-breaking space)

