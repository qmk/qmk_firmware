// Copyright 2022 QMK
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
#include "keymap.h"
// clang-format off

// Aliases
#define IL_SCLN KC_GRV  // ;
#define IL_1    KC_1    // 1
#define IL_2    KC_2    // 2
#define IL_3    KC_3    // 3
#define IL_4    KC_4    // 4
#define IL_5    KC_5    // 5
#define IL_6    KC_6    // 6
#define IL_7    KC_7    // 7
#define IL_8    KC_8    // 8
#define IL_9    KC_9    // 9
#define IL_0    KC_0    // 0
#define IL_MINS KC_MINS // -
#define IL_EQL  KC_EQL  // =
#define IL_SLSH KC_Q    // /
#define IL_QUOT KC_W    // '
#define IL_QOF  KC_E    // ק
#define IL_RESH KC_R    // ר
#define IL_ALEF KC_T    // א
#define IL_TET  KC_Y    // ט
#define IL_VAV  KC_U    // ו
#define IL_FNUN KC_I    // ן
#define IL_FMEM KC_O    // ם
#define IL_PE   KC_P    // פ
#define IL_RBRC KC_LBRC // ]
#define IL_LBRC KC_RBRC // [
#define IL_SHIN KC_A    // ש
#define IL_DALT KC_S    // ד
#define IL_GIML KC_D    // ג
#define IL_KAF  KC_F    // כ
#define IL_AYIN KC_G    // ע
#define IL_YOD  KC_H    // י
#define IL_HET  KC_J    // ח
#define IL_LAMD KC_K    // ל
#define IL_FKAF KC_L    // ך
#define IL_FPE  KC_SCLN // ף
#define IL_COMM KC_QUOT // ,
#define IL_BSLS KC_NUHS // (backslash)
#define IL_ZAYN KC_Z    // ז
#define IL_SMKH KC_X    // ס
#define IL_BET  KC_C    // ב
#define IL_HE   KC_V    // ה
#define IL_NUN  KC_B    // נ
#define IL_MEM  KC_N    // מ
#define IL_TSDI KC_M    // צ
#define IL_TAV  KC_COMM // ת
#define IL_FTSD KC_DOT  // ץ
#define IL_DOT  KC_SLSH // .
#define IL_TILD S(IL_SCLN) // ~
#define IL_EXLM S(IL_1)    // !
#define IL_AT   S(IL_2)    // @
#define IL_PND  S(IL_3)    // #
#define IL_DLR  S(IL_4)    // $
#define IL_PERC S(IL_5)    // %
#define IL_CIRC S(IL_6)    // ^
#define IL_AMPR S(IL_7)    // &
#define IL_ASTR S(IL_8)    // *
#define IL_RPRN S(IL_9)    // )
#define IL_LPRN S(IL_0)    // (
#define IL_UNDS S(IL_MINS) // _
#define IL_PLUS S(IL_EQL)  // +
#define IL_RCBR S(IL_RBRC) // }
#define IL_LCBR S(IL_LBRC) // {
#define IL_COLN S(IL_FPE)  // :
#define IL_DQUO S(IL_COMM) // "
#define IL_PIPE S(IL_BSLS) // |
#define IL_RABK S(IL_TAV)  // >
#define IL_LABK S(IL_FTSD) // <
#define IL_QUES S(IL_DOT)  // ?
#define IL_EURO ALGR(IL_3)    // €
#define IL_SHKL ALGR(IL_4)    // ₪
#define IL_DEG  ALGR(IL_5)    // °
#define IL_MUL  ALGR(IL_8)    // ×
#define IL_DVAV ALGR(IL_TET)  // װ
#define IL_VYOD ALGR(IL_AYIN) // ױ
#define IL_DYOD ALGR(IL_YOD)  // ײ
#define IL_DIV  ALGR(IL_DOT)  // ÷
