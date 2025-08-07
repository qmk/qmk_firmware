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

#define QMK_ITALIAN_MAC_ANSI_KEYCODES_VERSION "0.0.1"
#define QMK_ITALIAN_MAC_ANSI_KEYCODES_VERSION_BCD 0x00000001
#define QMK_ITALIAN_MAC_ANSI_KEYCODES_VERSION_MAJOR 0
#define QMK_ITALIAN_MAC_ANSI_KEYCODES_VERSION_MINOR 0
#define QMK_ITALIAN_MAC_ANSI_KEYCODES_VERSION_PATCH 1

// Aliases
#define IT_LABK KC_GRV  // <
#define IT_1    KC_1    // 1
#define IT_2    KC_2    // 2
#define IT_3    KC_3    // 3
#define IT_4    KC_4    // 4
#define IT_5    KC_5    // 5
#define IT_6    KC_6    // 6
#define IT_7    KC_7    // 7
#define IT_8    KC_8    // 8
#define IT_9    KC_9    // 9
#define IT_0    KC_0    // 0
#define IT_QUOT KC_MINS // '
#define IT_IGRV KC_EQL  // ì
#define IT_Q    KC_Q    // Q
#define IT_W    KC_W    // W
#define IT_E    KC_E    // E
#define IT_R    KC_R    // R
#define IT_T    KC_T    // T
#define IT_Y    KC_Y    // Y
#define IT_U    KC_U    // U
#define IT_I    KC_I    // I
#define IT_O    KC_O    // O
#define IT_P    KC_P    // P
#define IT_EGRV KC_LBRC // è
#define IT_PLUS KC_RBRC // +
#define IT_UGRV KC_BSLS // ù
#define IT_A    KC_A    // A
#define IT_S    KC_S    // S
#define IT_D    KC_D    // D
#define IT_F    KC_F    // F
#define IT_G    KC_G    // G
#define IT_H    KC_H    // H
#define IT_J    KC_J    // J
#define IT_K    KC_K    // K
#define IT_L    KC_L    // L
#define IT_OGRV KC_SCLN // ò
#define IT_AGRV KC_QUOT // à
#define IT_BSLS KC_NUBS // (backslash, not physically present)
#define IT_Z    KC_Z    // Z
#define IT_X    KC_X    // X
#define IT_C    KC_C    // C
#define IT_V    KC_V    // V
#define IT_B    KC_B    // B
#define IT_N    KC_N    // N
#define IT_M    KC_M    // M
#define IT_COMM KC_COMM // ,
#define IT_DOT  KC_DOT  // .
#define IT_MINS KC_SLSH // -
#define IT_RABK S(IT_LABK) // >
#define IT_EXLM S(IT_1)    // !
#define IT_DQUO S(IT_2)    // "
#define IT_PND  S(IT_3)    // £
#define IT_DLR  S(IT_4)    // $
#define IT_PERC S(IT_5)    // %
#define IT_AMPR S(IT_6)    // &
#define IT_SLSH S(IT_7)    // /
#define IT_LPRN S(IT_8)    // (
#define IT_RPRN S(IT_9)    // )
#define IT_EQL  S(IT_0)    // =
#define IT_QUES S(IT_QUOT) // ?
#define IT_CIRC S(IT_IGRV) // ^
#define IT_EACU S(IT_EGRV) // é
#define IT_ASTR S(IT_PLUS) // *
#define IT_SECT S(IT_UGRV) // §
#define IT_LCCE S(IT_OGRV) // ç
#define IT_DEG  S(IT_AGRV) // °
#define IT_PIPE S(IT_BSLS) // | (not physically present)
#define IT_SCLN S(IT_COMM) // ;
#define IT_COLN S(IT_DOT)  // :
#define IT_UNDS S(IT_MINS) // _
#define IT_LTEQ A(IT_LABK) // ≤
#define IT_LDAQ A(IT_1)    // «
#define IT_LDQU A(IT_2)    // “
#define IT_LSQU A(IT_3)    // ‘
#define IT_YEN  A(IT_4)    // ¥
#define IT_TILD A(IT_5)    // ~
#define IT_LSAQ A(IT_6)    // ‹
#define IT_DIV  A(IT_7)    // ÷
#define IT_ACUT A(IT_8)    // ´ (dead)
#define IT_DGRV A(IT_9)    // ` (dead)
#define IT_NEQL A(IT_0)    // ≠
#define IT_IEXL A(IT_QUOT) // ¡
#define IT_DCIR A(IT_IGRV) // ˆ (dead)
#define IT_DLQU A(IT_Q)    // „
#define IT_OMEG A(IT_W)    // Ω
#define IT_EURO A(IT_E)    // €
#define IT_REGD A(IT_R)    // ®
#define IT_TM   A(IT_T)    // ™
#define IT_AE   A(IT_Y)    // Æ
#define IT_DIAE A(IT_U)    // ¨ (dead)
#define IT_OE   A(IT_I)    // Œ
#define IT_OSTR A(IT_O)    // Ø
#define IT_PI   A(IT_P)    // π
#define IT_LBRC A(IT_EGRV) // [
#define IT_RBRC A(IT_PLUS) // ]
#define IT_ARNG A(IT_A)    // Å
#define IT_SS   A(IT_S)    // ß
#define IT_PDIF A(IT_D)    // ∂
#define IT_FHK  A(IT_F)    // ƒ
#define IT_INFN A(IT_G)    // ∞
#define IT_INCR A(IT_H)    // ∆
#define IT_FORD A(IT_J)    // ª
#define IT_MORD A(IT_K)    // º
#define IT_NOT  A(IT_L)    // ¬
#define IT_AT   A(IT_OGRV) // @
#define IT_HASH A(IT_AGRV) // #
#define IT_PILC A(IT_UGRV) // ¶
#define IT_GRV  A(IT_BSLS) // ` (not physically present)
#define IT_NARS A(IT_Z)    // ∑
#define IT_DAGG A(IT_X)    // †
#define IT_COPY A(IT_C)    // ©
#define IT_SQRT A(IT_V)    // √
#define IT_INTG A(IT_B)    // ∫
#define IT_STIL A(IT_N)    // ˜ (dead)
#define IT_MICR A(IT_M)    // µ
#define IT_ELLP A(IT_COMM) // …
#define IT_BULT A(IT_DOT)  // •
#define IT_NDSH A(IT_MINS) // –
#define IT_GTEQ S(A(IT_LABK)) // ≥
#define IT_RDAQ S(A(IT_1))    // »
#define IT_RDQU S(A(IT_2))    // ”
#define IT_RSQU S(A(IT_3))    // ’
#define IT_CENT S(A(IT_4))    // ¢
#define IT_PERM S(A(IT_5))    // ‰
#define IT_RSAQ S(A(IT_6))    // ›
#define IT_FRSL S(A(IT_7))    // ⁄
#define IT_APPL S(A(IT_8))    //  (Apple logo)
#define IT_AEQL S(A(IT_0))    // ≈
#define IT_IQUE S(A(IT_QUOT)) // ¿
#define IT_PLMN S(A(IT_IGRV)) // ±
#define IT_SLQU S(A(IT_Q))    // ‚
#define IT_CAGR S(A(IT_W))    // À
#define IT_CEGR S(A(IT_E))    // È
#define IT_CIGR S(A(IT_R))    // Ì
#define IT_COGR S(A(IT_T))    // Ò
#define IT_CUGR S(A(IT_U))    // Ù
#define IT_NARP S(A(IT_P))    // ∏
#define IT_LCBR S(A(IT_EGRV)) // {
#define IT_RCBR S(A(IT_PLUS)) // }
#define IT_LOZN S(A(IT_UGRV)) // ◊
#define IT_MACR S(A(IT_S))    // ¯
#define IT_BREV S(A(IT_D))    // ˘
#define IT_DOTA S(A(IT_F))    // ˙
#define IT_RGNA S(A(IT_G))    // ˚
#define IT_CEDL S(A(IT_H))    // ¸
#define IT_DACU S(A(IT_J))    // ˝
#define IT_OGON S(A(IT_K))    // ˛
#define IT_CARN S(A(IT_L))    // ˇ
#define IT_CCCE S(A(IT_OGRV)) // Ç
#define IT_DDAG S(A(IT_X))    // ‡
#define IT_CAAC S(A(IT_C))    // Á
#define IT_CEAC S(A(IT_V))    // É
#define IT_CIAC S(A(IT_B))    // Í
#define IT_COAC S(A(IT_N))    // Ó
#define IT_CUAC S(A(IT_M))    // Ú
#define IT_MDDT S(A(IT_DOT))  // ·
#define IT_MDSH S(A(IT_MINS)) // —

