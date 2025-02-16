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
#define JP_ZKHK KC_GRV  // Zenkaku ↔ Hankaku ↔ Kanji (半角 ↔ 全角 ↔ 漢字)
#define JK_NU   KC_1    // ぬ
#define JK_FU   KC_2    // ふ
#define JK_A    KC_3    // あ
#define JK_U    KC_4    // う
#define JK_E    KC_5    // え
#define JK_O    KC_6    // お
#define JK_YA   KC_7    // や
#define JK_YU   KC_8    // ゆ
#define JK_YO   KC_9    // よ
#define JK_WA   KC_0    // わ
#define JK_HO   KC_MINS // ほ
#define JK_HE   KC_EQL  // へ
#define JK_LONG KC_INT3 // ー
#define JK_TA   KC_Q    // た
#define JK_TE   KC_W    // て
#define JK_I    KC_E    // い
#define JK_SU   KC_R    // す
#define JK_KA   KC_T    // か
#define JK_N    KC_Y    // ん
#define JK_NA   KC_U    // な
#define JK_NI   KC_I    // に
#define JK_RA   KC_O    // ら
#define JK_SE   KC_P    // せ
#define JK_VOICE KC_LBRC // ゛(濁点)
#define JK_SEMI_VOICE KC_RBRC // ゜(半濁点)
#define JK_EISU KC_CAPS // Eisū (英数)
#define JK_CHI  KC_A    // ち
#define JK_TO   KC_S    // と
#define JK_SHI  KC_D    // し
#define JK_HA   KC_F    // は
#define JK_KI   KC_G    // き
#define JK_KU   KC_H    // く
#define JK_MA   KC_J    // ま
#define JK_NO   KC_K    // の
#define JK_RI   KC_L    // り
#define JK_RE   KC_SCLN // れ
#define JK_KE   KC_QUOT // け
#define JK_MU   KC_NUHS // む
#define JK_TSU  KC_Z    // つ
#define JK_SA   KC_X    // さ
#define JK_SO   KC_C    // そ
#define JK_HI   KC_V    // ひ
#define JK_KO   KC_B    // こ
#define JK_MI   KC_N    // み
#define JK_MO   KC_M    // も
#define JK_NE   KC_COMM // ね
#define JK_RU   KC_DOT  // る
#define JK_ME   KC_SLSH // め
#define JK_RO   KC_INT1 // ろ
#define JK_MHEN KC_INT5 // Muhenkan (無変換)
#define JK_HENK KC_INT4 // Henkan (変換)
#define JK_KANA KC_INT2 // Katakana ↔ Hiragana ↔ Rōmaji (カタカナ ↔ ひらがな ↔ ローマ字)
#define JK_LA   S(KC_3)    // ぁ
#define JK_LU   S(KC_4)    // ぅ
#define JK_LE   S(KC_5)    // ぇ
#define JK_LO   S(KC_6)    // ぉ
#define JK_LYA  S(KC_7)    // ゃ
#define JK_LYU  S(KC_8)    // ゅ
#define JK_LYO  S(KC_9)    // ょ
#define JK_WO   S(KC_0)    // を
#define JK_LI   S(KC_E)    // ぃ
#define JK_LEFT_KAGI S(KC_RBRC) // 「
#define JK_RIGHT_KAGI S(KC_NUHS) // 」
#define JK_TEN  S(KC_COMM) // 、
#define JK_MARU S(KC_DOT)  // 。

#define JK_HU JK_FU
#define JK_NN JK_N
#define JK_DAKU JK_VOICE
#define JK_DAKUTEN JK_VOICE
#define JK_HANDAKU JK_SEMI_VOICE
#define JK_HANDAKUTEN JK_SEMI_VOICE
#define JK_TI JK_CHI
#define JK_SI JK_SHI
#define JK_TU JK_TSU
#define JK_MUHENKAN JK_MHEN
#define JK_HENKAN JK_HENK
#define JK_XA JK_LA
#define JK_SMALL_A JK_LA
#define JK_XU JK_LU
#define JK_SMALL_U JK_LU
#define JK_XE JK_LE
#define JK_SMALL_E JK_LE
#define JK_XO JK_LO
#define JK_SMALL_O JK_LO
#define JK_XYA JK_LYA
#define JK_SMALL_YA JK_LYA
#define JK_XYU JK_LYU
#define JK_SMALL_YU JK_LYU
#define JK_XYO JK_LYO
#define JK_SMALL_YO JK_LYO
#define JK_XI JK_LI
#define JK_SMALL_I JK_LI
#define JK_LKAG JK_LEFT_KAGI
#define JK_RKAG JK_RIGHT_KAGI
#define JK_COMMA JK_TEN
#define JK_COMM JK_TEN
#define JK_DOT JK_MARU
#define JK_PERIOD JK_MARU
#define JK_PROD JK_MARU
