/* Copyright 2020
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "keymap.h"

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ; │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ / │ ' │ פ │ ם │ ן │ ו │ ט │ א │ ר │ ק │ ] │ [ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ ף │ ך │ ל │ ח │ י │ ע │ כ │ ג │ ד │ ש │ , │ \ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │ ץ │ ת │ צ │ מ │ נ │ ה │ ב │ ס │ ז │ . │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
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
// Row 2
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
// Row 3
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
// Row 4
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

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ) │ ( │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ } │ { │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ : │ " │ | │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │ > │ < │ ? │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
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
// Row 2
#define IL_RCBR S(IL_RBRC) // }
#define IL_LCBR S(IL_LBRC) // {
// Row 3
#define IL_COLN S(IL_FPE)  // :
#define IL_DQUO S(IL_COMM) // "
#define IL_PIPE S(IL_BSLS) // |
// Row 4
#define IL_RABK S(IL_TAV)  // >
#define IL_LABK S(IL_FTSD) // <
#define IL_QUES S(IL_DOT)  // ?

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │   │ € │ ₪ │ ° │   │   │ × │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │ װ │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │ ײ │ ױ │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │ ÷ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IL_EURO ALGR(IL_3)    // €
#define IL_SHKL ALGR(IL_4)    // ₪
#define IL_DEG  ALGR(IL_5)    // °
#define IL_MUL  ALGR(IL_8)    // ×
// Row 2
#define IL_DVAV ALGR(IL_TET)  // װ
// Row 3
#define IL_VYOD ALGR(IL_AYIN) // ױ
#define IL_DYOD ALGR(IL_YOD)  // ײ
// Row 4
#define IL_DIV  ALGR(IL_DOT)  // ÷
