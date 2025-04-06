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
#define FA_ZWJ  KC_GRV  // (zero-width joiner)
#define FA_1A   KC_1    // ۱
#define FA_2A   KC_2    // ۲
#define FA_3A   KC_3    // ۳
#define FA_4A   KC_4    // ۴
#define FA_5A   KC_5    // ۵
#define FA_6A   KC_6    // ۶
#define FA_7A   KC_7    // ۷
#define FA_8A   KC_8    // ۸
#define FA_9A   KC_9    // ۹
#define FA_0A   KC_0    // ۰
#define FA_MINS KC_MINS // -
#define FA_EQL  KC_EQL  // =
#define FA_ZAD  KC_Q    // ض
#define FA_SAD  KC_W    // ص
#define FA_SE   KC_E    // ث
#define FA_QAF  KC_R    // ق
#define FA_FE   KC_T    // ف
#define FA_GHYN KC_Y    // غ
#define FA_EYN  KC_U    // ع
#define FA_HE   KC_I    // ه
#define FA_KHE  KC_O    // خ
#define FA_HEJ  KC_P    // ح
#define FA_JIM  KC_LBRC // ج
#define FA_CHE  KC_RBRC // چ
#define FA_SHIN KC_A    // ش
#define FA_SIN  KC_S    // س
#define FA_YE   KC_D    // ی
#define FA_BE   KC_F    // ب
#define FA_LAM  KC_G    // ل
#define FA_ALEF KC_H    // ا
#define FA_TE   KC_J    // ت
#define FA_NOON KC_K    // ن
#define FA_MIM  KC_L    // م
#define FA_KAF  KC_SCLN // ک
#define FA_GAF  KC_QUOT // گ
#define FA_BSLS KC_BSLS // (backslash)
#define FA_LT   KC_LT   // <
#define FA_ZA   KC_Z    // ظ
#define FA_TA   KC_X    // ط
#define FA_ZE   KC_C    // ز
#define FA_RE   KC_V    // ر
#define FA_ZAL  KC_B    // ذ
#define FA_DAL  KC_N    // د
#define FA_PE   KC_M    // پ
#define FA_WAW  KC_COMM // و
#define FA_DOT  KC_DOT  // .
#define FA_SLSH KC_SLSH // /
#define FA_SPC  KC_SPC  //  
#define FA_DIV  S(FA_ZWJ)  // ÷
#define FA_EXLM S(FA_1A)   // !
#define FA_THS  S(FA_2A)   // ٬
#define FA_DECS S(FA_3A)   // ٫
#define FA_RIAL S(FA_4A)   // ﷼
#define FA_PRCA S(FA_5A)   // ٪
#define FA_MUL  S(FA_6A)   // ×
#define FA_COMA S(FA_7A)   // ،
#define FA_ASTR S(FA_8A)   // *
#define FA_RPRN S(FA_9A)   // )
#define FA_LPRN S(FA_0A)   // (
#define FA_TATW S(FA_MINS) // ـ
#define FA_PLUS S(FA_EQL)  // +
#define FA_SUK  S(FA_ZAD)  // ْ
#define FA_DMTN S(FA_SAD)  // ٌ
#define FA_KSTN S(FA_SE)   // ٍ
#define FA_FTHN S(FA_QAF)  // ً
#define FA_DMM  S(FA_FE)   // ُ
#define FA_KAS  S(FA_GHYN) // ِ
#define FA_FAT  S(FA_EYN)  // َ
#define FA_TSDD S(FA_HE)   // 
#define FA_RBRC S(FA_KHE)  // ]
#define FA_LBRC S(FA_HEJ)  // [
#define FA_RCBR S(FA_JIM)  // }
#define FA_LCBR S(FA_CHE)  // {
#define FA_HMZV S(FA_SHIN) // ؤ
#define FA_HMZY S(FA_SIN)  // ئ
#define FA_YEA  S(FA_YE)   // ي
#define FA_HMZU S(FA_BE)   // إ
#define FA_HMZO S(FA_LAM)  // أ
#define FA_MALF S(FA_ALEF) // آ
#define FA_TEHM S(FA_TE)   // ة
#define FA_RQOT S(FA_NOON) // »
#define FA_LQOT S(FA_MIM)  // «
#define FA_COLN S(FA_KAF)  // :
#define FA_SCLA S(FA_GAF)  // ؛
#define FA_GT   S(FA_LT)   // >
#define FA_KAFA S(FA_ZA)   // ك
#define FA_MADO S(FA_TA)   // ٓ
#define FA_JEH  S(FA_ZE)   // ژ
#define FA_SUPA S(FA_RE)   // ٰ
#define FA_ZWNJ S(FA_ZAL)  // (zero-width non-joiner)
#define FA_HMZA S(FA_DAL)  // ٔ
#define FA_HMZ  S(FA_PE)   // ء
#define FA_QSA  S(FA_SLSH) // ؟
#define FA_TILD ALGR(FA_ZWJ)  // ~
#define FA_GRV  ALGR(FA_1A)   // `
#define FA_AT   ALGR(FA_2A)   // @
#define FA_HASH ALGR(FA_3A)   // #
#define FA_DLR  ALGR(FA_4A)   // $
#define FA_PERC ALGR(FA_5A)   // %
#define FA_CIRC ALGR(FA_6A)   // ^
#define FA_AMPR ALGR(FA_7A)   // &
#define FA_BULT ALGR(FA_8A)   // •
#define FA_LRM  ALGR(FA_9A)   // (left-to-right mark)
#define FA_RLM  ALGR(FA_0A)   // (right-to-left mark)
#define FA_UNDS ALGR(FA_MINS) // _
#define FA_DMNS ALGR(FA_EQL)  // − (dead)
#define FA_DEG  ALGR(FA_ZAD)  // °
#define FA_EURO ALGR(FA_SE)   // €
#define FA_LRO  ALGR(FA_HE)   // (left-to-right override)
#define FA_RLO  ALGR(FA_KHE)  // (right-to-left override)
#define FA_PDF  ALGR(FA_HEJ)  // (pop directional formatting)
#define FA_LRE  ALGR(FA_JIM)  // (left-to-right embedding)
#define FA_RLE  ALGR(FA_CHE)  // (right-to-left embedding)
#define FA_ALFM ALGR(FA_YE)   // ى
#define FA_ALFW ALGR(FA_ALEF) // ٱ
#define FA_LORP ALGR(FA_NOON) // ﴾
#define FA_RORP ALGR(FA_MIM)  // ﴿
#define FA_SCLN ALGR(FA_KAF)  // ;
#define FA_DQT  ALGR(FA_GAF)  // "
#define FA_MINA ALGR(FA_BSLS) // -
#define FA_PIPE ALGR(FA_ZA)   // |
#define FA_SUBA ALGR(FA_RE)   // ٖ
#define FA_HMZB ALGR(FA_DAL)  // ء
#define FA_ELLP ALGR(FA_PE)   // …
#define FA_COMM ALGR(FA_WAW)  // ,
#define FA_QUOT ALGR(FA_DOT)  // '
#define FA_QUES ALGR(FA_SLSH) // ?
#define FA_1    S(ALGR(FA_1A))   // 1
#define FA_2    S(ALGR(FA_2A))   // 2
#define FA_3    S(ALGR(FA_3A))   // 3
#define FA_4    S(ALGR(FA_4A))   // 4
#define FA_5    S(ALGR(FA_5A))   // 5
#define FA_6    S(ALGR(FA_6A))   // 6
#define FA_7    S(ALGR(FA_7A))   // 7
#define FA_8    S(ALGR(FA_8A))   // 8
#define FA_9    S(ALGR(FA_9A))   // 9
#define FA_0    S(ALGR(FA_0A))   // 0
#define FA_BRKP S(ALGR(FA_LT))   // ¦
#define FA_NNBS S(ALGR(FA_SPC))  // (narrow non-breaking space)

