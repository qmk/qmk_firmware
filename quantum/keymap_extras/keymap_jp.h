/* Copyright 2016 h-youhei
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
 *
 * JP106-layout (Japanese Standard)
 *
 * For more information, see
 * http://www2d.biglobe.ne.jp/~msyk/keyboard/layout/usbkeycode.html
 * note: This website is written in Japanese.
 */

#pragma once

#include "keymap.h"

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │Z↔︎H│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ ^ │ ¥ │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ @ │ [ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │ Eisū │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ : │ ] │    │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
 * │        │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ \ │      │
 * ├─────┬──┴┬──┴──┬┴───┴┬──┴───┴──┬┴───┴┬──┴┬──┴┬──┴┬──┴┬─────┤
 * │     │   │     │Muhen│         │ Hen │K↔H│   │   │   │     │
 * └─────┴───┴─────┴─────┴─────────┴─────┴───┴───┴───┴───┴─────┘
 */
// Row 1
#define JP_ZKHK KC_GRV  // Zenkaku ↔︎ Hankaku ↔ Kanji (半角 ↔ 全角 ↔ 漢字)
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
// Row 2
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
// Row 3
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
// Row 4
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
// Row 5
#define JP_MHEN KC_INT5 // Muhenkan (無変換)
#define JP_HENK KC_INT4 // Henkan (変換)
#define JP_KANA KC_INT2 // Katakana ↔ Hiragana ↔ Rōmaji (カタカナ ↔ ひらがな ↔ ローマ字)

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │ ! │ " │ # │ $ │ % │ & │ ' │ ( │ ) │   │ = │ ~ │ | │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ` │ { │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │ Caps │   │   │   │   │   │   │   │   │   │ + │ * │ } │    │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │ _ │      │
 * ├─────┬──┴┬──┴──┬┴───┴┬──┴───┴──┬┴───┴┬──┴┬──┴┬──┴┬──┴┬─────┤
 * │     │   │     │     │         │     │   │   │   │   │     │
 * └─────┴───┴─────┴─────┴─────────┴─────┴───┴───┴───┴───┴─────┘
 */
// Row 1
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
// Row 2
#define JP_GRV  S(JP_AT)   // `
#define JP_LCBR S(JP_LBRC) // {
// Row 3
#define JP_CAPS S(JP_EISU) // Caps Lock
#define JP_PLUS S(JP_SCLN) // +
#define JP_ASTR S(JP_COLN) // *
#define JP_RCBR S(JP_RBRC) // }
// Row 4
#define JP_LABK S(JP_COMM) // <
#define JP_RABK S(JP_DOT)  // >
#define JP_QUES S(JP_SLSH) // ?
#define JP_UNDS S(JP_BSLS) // _

// DEPRECATED
#define JP_ZHTG JP_ZKHK
#define JP_DQT  JP_DQUO
#define JP_LT   JP_LABK
#define JP_GT   JP_RABK

#define JP_MEISU KC_LANG2 // Eisū (英数) on macOS
#define JP_MKANA KC_LANG1 // Kana (かな) on macOS
