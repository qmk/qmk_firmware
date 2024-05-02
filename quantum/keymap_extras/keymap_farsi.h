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
#define FA_JSPC KC_GRV  // ‍
#define FA_1    KC_1    // ۱
#define FA_2    KC_2    // ۲
#define FA_3    KC_3    // ۳
#define FA_4    KC_4    // ۴
#define FA_5    KC_5    // ۵
#define FA_6    KC_6    // ۶
#define FA_7    KC_7    // ۷
#define FA_8    KC_8    // ۸
#define FA_9    KC_9    // ۹
#define FA_0    KC_0    // ۰
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
#define FA_VAV  KC_COMM // و
#define FA_DOT  KC_DOT  // .
#define FA_SLSH KC_SLSH // /
#define FA_SPC  KC_SPC  //  
#define FA_TAGH S(FA_JSPC) // ÷
#define FA_EXLM S(FA_1)    // !
#define FA_THS  S(FA_2)    // ٬
#define FA_DECS S(FA_3)    // ٫
#define FA_RIAL S(FA_4)    // ﷼
#define FA_PERC S(FA_5)    // ٪
#define FA_MUL  S(FA_6)    // ×
#define FA_COMM S(FA_7)    // ،
#define FA_ASTR S(FA_8)    // *
#define FA_LPRN S(FA_9)    // )
#define FA_RPRN S(FA_0)    // (
#define FA_TATW S(FA_MINS) // ـ
#define FA_PLUS S(FA_EQL)  // +
#define FA_SUK  S(FA_ZAD)  // ْ
#define FA_DMTN S(FA_SAD)  // ٌ
#define FA_KSTN S(FA_SE)   // ٍ
#define FA_FTHN S(FA_QAF)  // ً
#define FA_DMM  S(FA_FE)   // ُ
#define FA_KAS  S(FA_GHYN) // ِ
#define FA_FAT  S(FA_EYN)  // َ
#define FA_TSDD S(FA_HE)   // ّ
#define FA_LBRC S(FA_KHE)  // ]
#define FA_RBRC S(FA_HEJ)  // [
#define FA_LCBR S(FA_JIM)  // }
#define FA_RCBR S(FA_CHE)  // {
#define FA_HMZV S(FA_SHIN) // ؤ
#define FA_HMZY S(FA_SIN)  // ئ
#define FA_AYE  S(FA_YE)   // ي
#define FA_HMZU S(FA_BE)   // إ
#define FA_HMZO S(FA_LAM)  // أ
#define FA_MALF S(FA_ALEF) // آ
#define FA_TEHM S(FA_TE)   // ة
#define FA_LQOT S(FA_NOON) // »
#define FA_RQOT S(FA_MIM)  // «
#define FA_COLN S(FA_KAF)  // :
#define FA_SCLN S(FA_GAF)  // ؛
#define FA_GT   S(FA_LT)   // >
#define FA_AKAF S(FA_ZA)   // ك
#define FA_MADO S(FA_TA)   // ٓ
#define FA_ZHE  S(FA_ZE)   // ژ
#define FA_SUPA S(FA_RE)   // ٰ
#define FA_NSPC S(FA_ZAL)  // ‌
#define FA_HMZA S(FA_DAL)  // ٔ
#define FA_HMZ  S(FA_PE)   // ء
#define FA_GTA  S(FA_VAV)  // >
#define FA_LTA  S(FA_DOT)  // <
#define FA_QUES S(FA_SLSH) // ؟
#define FA_NSPA S(FA_SPC)  // ‌
#define FA_TILD ALGR(FA_JSPC) // ~
#define FA_GRV  ALGR(FA_1)    // `
#define FA_AT   ALGR(FA_2)    // @
#define FA_HASH ALGR(FA_3)    // #
#define FA_DLR  ALGR(FA_4)    // $
#define FA_EPRC ALGR(FA_5)    // %
#define FA_CIRC ALGR(FA_6)    // ^
#define FA_AMPR ALGR(FA_7)    // &
#define FA_BSC  ALGR(FA_8)    // •
#define FA_LTRM ALGR(FA_9)    // ‎
#define FA_RTLM ALGR(FA_0)    // ‏
#define FA_UNDS ALGR(FA_MINS) // _
#define FA_MMNS ALGR(FA_EQL)  // −
#define FA_DEG  ALGR(FA_ZAD)  // °
#define FA_EURO ALGR(FA_SE)   // €
#define FA_LTRO ALGR(FA_HE)   // ‭
#define FA_RTLO ALGR(FA_KHE)  // ‮
#define FA_PDIR ALGR(FA_HEJ)  // ‬
#define FA_LTRE ALGR(FA_JIM)  // ‪
#define FA_RTLE ALGR(FA_CHE)  // ‫
#define FA_ALFM ALGR(FA_YE)   // ى
#define FA_ALFW ALGR(FA_ALEF) // ٱ
#define FA_LORP ALGR(FA_NOON) // ﴾
#define FA_RORP ALGR(FA_MIM)  // ﴿
#define FA_ESCN ALGR(FA_KAF)  // ;
#define FA_DQT  ALGR(FA_GAF)  // "
#define FA_MNSA ALGR(FA_BSLS) // -
#define FA_PIPE ALGR(FA_ZA)   // |
#define FA_SUBA ALGR(FA_RA)   // ٖ
#define FA_JSPA ALGR(FA_ZAL)  // ‍
#define FA_HMZB ALGR(FA_DAL)  // ء
#define FA_ELLP ALGR(FA_PE)   // …
#define FA_ECOM ALGR(FA_VAV)  // ,
#define FA_EQOT ALGR(FA_DOT)  // '
#define FA_EQUS ALGR(FA_SLSH) // ?
#define FA_1E   S(ALGR(FA_1))    // 1
#define FA_2E   S(ALGR(FA_2))    // 2
#define FA_3E   S(ALGR(FA_3))    // 3
#define FA_4E   S(ALGR(FA_4))    // 4
#define FA_5E   S(ALGR(FA_5))    // 5
#define FA_6E   S(ALGR(FA_6))    // 6
#define FA_7E   S(ALGR(FA_7))    // 7
#define FA_8E   S(ALGR(FA_8))    // 8
#define FA_9E   S(ALGR(FA_9))    // 9
#define FA_0E   S(ALGR(FA_0))    // 0
#define FA_BRKP S(ALGR(FA_LT))   // ¦
#define FA_NNBS S(ALGR(FA_SPC))  //  

