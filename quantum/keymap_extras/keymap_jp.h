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


#ifndef KEYMAP_JP_H
#define KEYMAP_JP_H


#include "keymap.h"


#define JP_ZHTG KC_GRV  // hankaku/zenkaku|kanzi
#define JP_YEN  KC_INT3 // yen, |
#define JP_CIRC KC_EQL  // ^, ~
#define JP_AT   KC_LBRC // @, `
#define JP_LBRC KC_RBRC // [, {
#define JP_COLN KC_QUOT // :, *
#define JP_RBRC KC_NUHS // ], }
#define JP_BSLS KC_INT1 // \, _
#define JP_MHEN KC_INT5 // muhenkan
#define JP_HENK KC_INT4 // henkan
#define JP_KANA KC_INT2 // katakana/hiragana|ro-mazi

#define JP_MKANA KC_LANG1 //kana on MacOSX
#define JP_MEISU KC_LANG2 //eisu on MacOSX


//Aliases for shifted symbols
#define JP_DQT  LSFT(KC_2)    // "
#define JP_AMPR LSFT(KC_6)    // &
#define JP_QUOT LSFT(KC_7)    // '
#define JP_LPRN LSFT(KC_8)    // (
#define JP_RPRN LSFT(KC_9)    // )
#define JP_EQL  LSFT(KC_MINS) // =
#define JP_TILD LSFT(JP_CIRC) // ~
#define JP_PIPE LSFT(JP_YEN)  // |
#define JP_GRV  LSFT(JP_AT)   // `
#define JP_LCBR LSFT(JP_LBRC) // {
#define JP_PLUS LSFT(KC_SCLN) // +
#define JP_ASTR LSFT(JP_COLN) // *
#define JP_RCBR LSFT(JP_RBRC) // }
#define JP_UNDS LSFT(JP_BSLS) // _


// These symbols are correspond to US101-layout.
#define JP_MINS KC_MINS // -
#define JP_SCLN KC_SCLN // ;
#define JP_COMM KC_COMM // ,
#define JP_DOT  KC_DOT  // .
#define JP_SLSH KC_SLSH // /
// shifted
#define JP_EXLM KC_EXLM // !
#define JP_HASH KC_HASH // #
#define JP_DLR  KC_DLR  // $
#define JP_PERC KC_PERC // %
#define JP_LT   KC_LT   // <
#define JP_GT   KC_GT   // >
#define JP_QUES KC_QUES // ?


#endif
