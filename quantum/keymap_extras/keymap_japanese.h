// Copyright 2024 QMK
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
#define JP_ZKHK KC_GRV  // Zenkaku ↔ Hankaku ↔ Kanji (半角 ↔ 全角 ↔ 漢字)
#define JP_1    KC_1    // 1
#define JP_2    KC_2    // 2
#define JP_3    KC_3    // 3
#define JP_4    KC_4    // 4
#define JP_5    KC_5    // 5
#define JP_6    KC_6    // 6
#define JP_7    KC_7    // 7
#define JP_8    KC_8    // 8
#define JP_9    KC_9    // 9
#define JP_0    KC_0    // 0
#define JP_MINS KC_MINS // -
#define JP_CIRC KC_EQL  // ^
#define JP_YEN  KC_INT3 // ¥
#define JP_Q    KC_Q    // Q
#define JP_W    KC_W    // W
#define JP_E    KC_E    // E
#define JP_R    KC_R    // R
#define JP_T    KC_T    // T
#define JP_Y    KC_Y    // Y
#define JP_U    KC_U    // U
#define JP_I    KC_I    // I
#define JP_O    KC_O    // O
#define JP_P    KC_P    // P
#define JP_AT   KC_LBRC // @
#define JP_LBRC KC_RBRC // [
#define JP_EISU KC_CAPS // Eisū (英数)
#define JP_A    KC_A    // A
#define JP_S    KC_S    // S
#define JP_D    KC_D    // D
#define JP_F    KC_F    // F
#define JP_G    KC_G    // G
#define JP_H    KC_H    // H
#define JP_J    KC_J    // J
#define JP_K    KC_K    // K
#define JP_L    KC_L    // L
#define JP_SCLN KC_SCLN // ;
#define JP_COLN KC_QUOT // :
#define JP_RBRC KC_NUHS // ]
#define JP_Z    KC_Z    // Z
#define JP_X    KC_X    // X
#define JP_C    KC_C    // C
#define JP_V    KC_V    // V
#define JP_B    KC_B    // B
#define JP_N    KC_N    // N
#define JP_M    KC_M    // M
#define JP_COMM KC_COMM // ,
#define JP_DOT  KC_DOT  // .
#define JP_SLSH KC_SLSH // /
#define JP_BSLS KC_INT1 // (backslash)
#define JP_MHEN KC_INT5 // Muhenkan (無変換)
#define JP_HENK KC_INT4 // Henkan (変換)
#define JP_KANA KC_INT2 // Katakana ↔ Hiragana ↔ Rōmaji (カタカナ ↔ ひらがな ↔ ローマ字)
#define JP_EXLM S(JP_1)    // !
#define JP_DQUO S(JP_2)    // "
#define JP_HASH S(JP_3)    // #
#define JP_DLR  S(JP_4)    // $
#define JP_PERC S(JP_5)    // %
#define JP_AMPR S(JP_6)    // &
#define JP_QUOT S(JP_7)    // '
#define JP_LPRN S(JP_8)    // (
#define JP_RPRN S(JP_9)    // )
#define JP_EQL  S(JP_MINS) // =
#define JP_TILD S(JP_CIRC) // ~
#define JP_PIPE S(JP_YEN)  // |
#define JP_GRV  S(JP_AT)   // `
#define JP_LCBR S(JP_LBRC) // {
#define JP_CAPS S(JP_EISU) // Caps Lock
#define JP_PLUS S(JP_SCLN) // +
#define JP_ASTR S(JP_COLN) // *
#define JP_RCBR S(JP_RBRC) // }
#define JP_LABK S(JP_COMM) // <
#define JP_RABK S(JP_DOT)  // >
#define JP_QUES S(JP_SLSH) // ?
#define JP_UNDS S(JP_BSLS) // _

