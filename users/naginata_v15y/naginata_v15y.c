/* Copyright eswai <@eswai> / Satoru NAKAYA <@tor-nky>
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

#include QMK_KEYBOARD_H
#include "nglist.h"
#include "nglistarray.h"
#include "naginata.h"

#include <string.h>

#define NGBUFFER 10 // キー入力バッファのサイズ

// static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ
static bool is_naginata = false; // 薙刀式がオンかオフか
static uint8_t naginata_layer = 0; // NG_*を配置しているレイヤー番号
static uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。
static uint16_t ngon_keys[2]; // 薙刀式をオンにするキー(通常HJ)
static uint16_t ngoff_keys[2]; // 薙刀式をオフにするキー(通常FG)
static NGListArray nginput;
uint32_t pressed_keys;

// 31キーを32bitの各ビットに割り当てる
#define B_Q    (1UL<<0)
#define B_W    (1UL<<1)
#define B_E    (1UL<<2)
#define B_R    (1UL<<3)
#define B_T    (1UL<<4)

#define B_Y    (1UL<<5)
#define B_U    (1UL<<6)
#define B_I    (1UL<<7)
#define B_O    (1UL<<8)
#define B_P    (1UL<<9)

#define B_A    (1UL<<10)
#define B_S    (1UL<<11)
#define B_D    (1UL<<12)
#define B_F    (1UL<<13)
#define B_G    (1UL<<14)

#define B_H    (1UL<<15)
#define B_J    (1UL<<16)
#define B_K    (1UL<<17)
#define B_L    (1UL<<18)
#define B_SCLN (1UL<<19)

#define B_Z    (1UL<<20)
#define B_X    (1UL<<21)
#define B_C    (1UL<<22)
#define B_V    (1UL<<23)
#define B_B    (1UL<<24)

#define B_N    (1UL<<25)
#define B_M    (1UL<<26)
#define B_COMM (1UL<<27)
#define B_DOT  (1UL<<28)
#define B_SLSH (1UL<<29)

#define B_SHFT (1UL<<30)

// キーコードとキービットの対応
// メモリ削減のため配列はNG_Qを0にしている
const uint32_t ng_key[] = {
  [NG_Q    - NG_Q]  = B_Q,
  [NG_W    - NG_Q]  = B_W,
  [NG_E    - NG_Q]  = B_E,
  [NG_R    - NG_Q]  = B_R,
  [NG_T    - NG_Q]  = B_T,

  [NG_Y    - NG_Q]  = B_Y,
  [NG_U    - NG_Q]  = B_U,
  [NG_I    - NG_Q]  = B_I,
  [NG_O    - NG_Q]  = B_O,
  [NG_P    - NG_Q]  = B_P,

  [NG_A    - NG_Q]  = B_A,
  [NG_S    - NG_Q]  = B_S,
  [NG_D    - NG_Q]  = B_D,
  [NG_F    - NG_Q]  = B_F,
  [NG_G    - NG_Q]  = B_G,

  [NG_H    - NG_Q]  = B_H,
  [NG_J    - NG_Q]  = B_J,
  [NG_K    - NG_Q]  = B_K,
  [NG_L    - NG_Q]  = B_L,
  [NG_SCLN - NG_Q]  = B_SCLN,

  [NG_Z    - NG_Q]  = B_Z,
  [NG_X    - NG_Q]  = B_X,
  [NG_C    - NG_Q]  = B_C,
  [NG_V    - NG_Q]  = B_V,
  [NG_B    - NG_Q]  = B_B,

  [NG_N    - NG_Q]  = B_N,
  [NG_M    - NG_Q]  = B_M,
  [NG_COMM - NG_Q]  = B_COMM,
  [NG_DOT  - NG_Q]  = B_DOT,
  [NG_SLSH - NG_Q]  = B_SLSH,

  [NG_SHFT - NG_Q]  = B_SHFT,
  [NG_SHFT2 - NG_Q] = B_SHFT,
};

// カナ変換テーブル
typedef struct {
  uint32_t shift;
  uint32_t douji;
  char kana[6];
} naginata_keymap;

const PROGMEM naginata_keymap ngdickana[] = {
  // 清音
  {.shift = 0UL    , .douji = B_J               , .kana = "a"       }, // あ
  {.shift = 0UL    , .douji = B_K               , .kana = "i"       }, // い
  {.shift = 0UL    , .douji = B_L               , .kana = "u"       }, // う
  {.shift = B_SHFT , .douji = B_O               , .kana = "e"       }, // え
  {.shift = B_SHFT , .douji = B_N               , .kana = "o"       }, // お
  {.shift = 0UL    , .douji = B_F               , .kana = "ka"      }, // か
  {.shift = 0UL    , .douji = B_W               , .kana = "ki"      }, // き
  {.shift = 0UL    , .douji = B_H               , .kana = "ku"      }, // く
  {.shift = 0UL    , .douji = B_S               , .kana = "ke"      }, // け
  {.shift = 0UL    , .douji = B_V               , .kana = "ko"      }, // こ
  {.shift = B_SHFT , .douji = B_U               , .kana = "sa"      }, // さ
  {.shift = 0UL    , .douji = B_R               , .kana = "si"      }, // し
  {.shift = 0UL    , .douji = B_O               , .kana = "su"      }, // す
  {.shift = B_SHFT , .douji = B_A               , .kana = "se"      }, // せ
  {.shift = 0UL    , .douji = B_B               , .kana = "so"      }, // そ
  {.shift = 0UL    , .douji = B_N               , .kana = "ta"      }, // た
  {.shift = B_SHFT , .douji = B_G               , .kana = "ti"      }, // ち
  {.shift = B_SHFT , .douji = B_L               , .kana = "tu"      }, // つ
  {.shift = 0UL    , .douji = B_E               , .kana = "te"      }, // て
  {.shift = 0UL    , .douji = B_D               , .kana = "to"      }, // と
  {.shift = 0UL    , .douji = B_M               , .kana = "na"      }, // な
  {.shift = B_SHFT , .douji = B_D               , .kana = "ni"      }, // に
  {.shift = B_SHFT , .douji = B_W               , .kana = "nu"      }, // ぬ
  {.shift = B_SHFT , .douji = B_R               , .kana = "ne"      }, // ね
  {.shift = B_SHFT , .douji = B_J               , .kana = "no"      }, // の
  {.shift = 0UL    , .douji = B_C               , .kana = "ha"      }, // は
  {.shift = 0UL    , .douji = B_X               , .kana = "hi"      }, // ひ
  {.shift = B_SHFT , .douji = B_X               , .kana = "hi"      }, // ひ
  {.shift = B_SHFT , .douji = B_SCLN            , .kana = "hu"      }, // ふ
  {.shift = 0UL    , .douji = B_P               , .kana = "he"      }, // へ
  {.shift = 0UL    , .douji = B_Z               , .kana = "ho"      }, // ほ
  {.shift = B_SHFT , .douji = B_Z               , .kana = "ho"      }, // ほ
  {.shift = B_SHFT , .douji = B_F               , .kana = "ma"      }, // ま
  {.shift = B_SHFT , .douji = B_B               , .kana = "mi"      }, // み
  {.shift = B_SHFT , .douji = B_COMM            , .kana = "mu"      }, // む
  {.shift = B_SHFT , .douji = B_S               , .kana = "me"      }, // め
  {.shift = B_SHFT , .douji = B_K               , .kana = "mo"      }, // も
  {.shift = B_SHFT , .douji = B_H               , .kana = "ya"      }, // や
  {.shift = B_SHFT , .douji = B_P               , .kana = "yu"      }, // ゆ
  {.shift = B_SHFT , .douji = B_I               , .kana = "yo"      }, // よ
  {.shift = 0UL    , .douji = B_DOT             , .kana = "ra"      }, // ら
  {.shift = B_SHFT , .douji = B_E               , .kana = "ri"      }, // り
  {.shift = 0UL    , .douji = B_I               , .kana = "ru"      }, // る
  {.shift = 0UL    , .douji = B_SLSH            , .kana = "re"      }, // れ
  {.shift = B_SHFT , .douji = B_SLSH            , .kana = "re"      }, // れ
  {.shift = 0UL    , .douji = B_A               , .kana = "ro"      }, // ろ
  {.shift = B_SHFT , .douji = B_DOT             , .kana = "wa"      }, // わ
  {.shift = B_SHFT , .douji = B_C               , .kana = "wo"      }, // を
  {.shift = 0UL    , .douji = B_COMM            , .kana = "nn"      }, // ん
  {.shift = 0UL    , .douji = B_SCLN            , .kana = "-"       }, // ー

  // 濁音
  {.shift = 0UL    , .douji = B_J|B_F           , .kana = "ga"      }, // が
  {.shift = 0UL    , .douji = B_J|B_W           , .kana = "gi"      }, // ぎ
  {.shift = 0UL    , .douji = B_F|B_H           , .kana = "gu"      }, // ぐ
  {.shift = 0UL    , .douji = B_J|B_S           , .kana = "ge"      }, // げ
  {.shift = 0UL    , .douji = B_J|B_V           , .kana = "go"      }, // ご
  {.shift = 0UL    , .douji = B_F|B_U           , .kana = "za"      }, // ざ
  {.shift = 0UL    , .douji = B_J|B_R           , .kana = "zi"      }, // じ
  {.shift = 0UL    , .douji = B_F|B_O           , .kana = "zu"      }, // ず
  {.shift = 0UL    , .douji = B_J|B_A           , .kana = "ze"      }, // ぜ
  {.shift = 0UL    , .douji = B_J|B_B           , .kana = "zo"      }, // ぞ
  {.shift = 0UL    , .douji = B_F|B_N           , .kana = "da"      }, // だ
  {.shift = 0UL    , .douji = B_J|B_G           , .kana = "di"      }, // ぢ
  {.shift = 0UL    , .douji = B_F|B_L           , .kana = "du"      }, // づ
  {.shift = 0UL    , .douji = B_J|B_E           , .kana = "de"      }, // で
  {.shift = 0UL    , .douji = B_J|B_D           , .kana = "do"      }, // ど
  {.shift = 0UL    , .douji = B_J|B_C           , .kana = "ba"      }, // ば
  {.shift = 0UL    , .douji = B_J|B_X           , .kana = "bi"      }, // び
  {.shift = 0UL    , .douji = B_F|B_SCLN        , .kana = "bu"      }, // ぶ
  {.shift = 0UL    , .douji = B_F|B_P           , .kana = "be"      }, // べ
  {.shift = 0UL    , .douji = B_J|B_Z           , .kana = "bo"      }, // ぼ
  {.shift = 0UL    , .douji = B_Q               , .kana = "vu"      }, // ゔ
  {.shift = B_SHFT , .douji = B_Q               , .kana = "vu"      }, // ゔ

  // 半濁音
  {.shift = 0UL    , .douji = B_M|B_C           , .kana = "pa"      }, // ぱ
  {.shift = 0UL    , .douji = B_M|B_X           , .kana = "pi"      }, // ぴ
  {.shift = 0UL    , .douji = B_V|B_SCLN        , .kana = "pu"      }, // ぷ
  {.shift = 0UL    , .douji = B_V|B_P           , .kana = "pe"      }, // ぺ
  {.shift = 0UL    , .douji = B_M|B_Z           , .kana = "po"      }, // ぽ

  // 小書き
  {.shift = 0UL    , .douji = B_Q|B_H           , .kana = "xya"     }, // ゃ
  {.shift = 0UL    , .douji = B_Q|B_P           , .kana = "xyu"     }, // ゅ
  {.shift = 0UL    , .douji = B_Q|B_I           , .kana = "xyo"     }, // ょ
  {.shift = 0UL    , .douji = B_Q|B_J           , .kana = "xa"      }, // ぁ
  {.shift = 0UL    , .douji = B_Q|B_K           , .kana = "xi"      }, // ぃ
  {.shift = 0UL    , .douji = B_Q|B_L           , .kana = "xu"      }, // ぅ
  {.shift = 0UL    , .douji = B_Q|B_O           , .kana = "xe"      }, // ぇ
  {.shift = 0UL    , .douji = B_Q|B_N           , .kana = "xo"      }, // ぉ
  {.shift = 0UL    , .douji = B_Q|B_DOT         , .kana = "xwa"     }, // ゎ
  {.shift = 0UL    , .douji = B_G               , .kana = "xtu"     }, // っ
  {.shift = 0UL    , .douji = B_Q|B_S           , .kana = "xke"     }, // ヶ
  {.shift = 0UL    , .douji = B_Q|B_F           , .kana = "xka"     }, // ヵ

  // 清音拗音 濁音拗音 半濁拗音
  {.shift = 0UL    , .douji = B_R|B_H           , .kana = "sya"     }, // しゃ
  {.shift = 0UL    , .douji = B_R|B_P           , .kana = "syu"     }, // しゅ
  {.shift = 0UL    , .douji = B_R|B_I           , .kana = "syo"     }, // しょ
  {.shift = 0UL    , .douji = B_J|B_R|B_H       , .kana = "zya"     }, // じゃ
  {.shift = 0UL    , .douji = B_J|B_R|B_P       , .kana = "zyu"     }, // じゅ
  {.shift = 0UL    , .douji = B_J|B_R|B_I       , .kana = "zyo"     }, // じょ
  {.shift = 0UL    , .douji = B_W|B_H           , .kana = "kya"     }, // きゃ
  {.shift = 0UL    , .douji = B_W|B_P           , .kana = "kyu"     }, // きゅ
  {.shift = 0UL    , .douji = B_W|B_I           , .kana = "kyo"     }, // きょ
  {.shift = 0UL    , .douji = B_J|B_W|B_H       , .kana = "gya"     }, // ぎゃ
  {.shift = 0UL    , .douji = B_J|B_W|B_P       , .kana = "gyu"     }, // ぎゅ
  {.shift = 0UL    , .douji = B_J|B_W|B_I       , .kana = "gyo"     }, // ぎょ
  {.shift = 0UL    , .douji = B_G|B_H           , .kana = "tya"     }, // ちゃ
  {.shift = 0UL    , .douji = B_G|B_P           , .kana = "tyu"     }, // ちゅ
  {.shift = 0UL    , .douji = B_G|B_I           , .kana = "tyo"     }, // ちょ
  {.shift = 0UL    , .douji = B_J|B_G|B_H       , .kana = "dya"     }, // ぢゃ
  {.shift = 0UL    , .douji = B_J|B_G|B_P       , .kana = "dyu"     }, // ぢゅ
  {.shift = 0UL    , .douji = B_J|B_G|B_I       , .kana = "dyo"     }, // ぢょ
  {.shift = 0UL    , .douji = B_D|B_H           , .kana = "nya"     }, // にゃ
  {.shift = 0UL    , .douji = B_D|B_P           , .kana = "nyu"     }, // にゅ
  {.shift = 0UL    , .douji = B_D|B_I           , .kana = "nyo"     }, // にょ
  {.shift = 0UL    , .douji = B_X|B_H           , .kana = "hya"     }, // ひゃ
  {.shift = 0UL    , .douji = B_X|B_P           , .kana = "hyu"     }, // ひゅ
  {.shift = 0UL    , .douji = B_X|B_I           , .kana = "hyo"     }, // ひょ
  {.shift = 0UL    , .douji = B_J|B_X|B_H       , .kana = "bya"     }, // びゃ
  {.shift = 0UL    , .douji = B_J|B_X|B_P       , .kana = "byu"     }, // びゅ
  {.shift = 0UL    , .douji = B_J|B_X|B_I       , .kana = "byo"     }, // びょ
  {.shift = 0UL    , .douji = B_M|B_X|B_H       , .kana = "pya"     }, // ぴゃ
  {.shift = 0UL    , .douji = B_M|B_X|B_P       , .kana = "pyu"     }, // ぴゅ
  {.shift = 0UL    , .douji = B_M|B_X|B_I       , .kana = "pyo"     }, // ぴょ
  {.shift = 0UL    , .douji = B_B|B_H           , .kana = "mya"     }, // みゃ
  {.shift = 0UL    , .douji = B_B|B_P           , .kana = "myu"     }, // みゅ
  {.shift = 0UL    , .douji = B_B|B_I           , .kana = "myo"     }, // みょ
  {.shift = 0UL    , .douji = B_E|B_H           , .kana = "rya"     }, // りゃ
  {.shift = 0UL    , .douji = B_E|B_P           , .kana = "ryu"     }, // りゅ
  {.shift = 0UL    , .douji = B_E|B_I           , .kana = "ryo"     }, // りょ

  // 清音外来音 濁音外来音
  {.shift = 0UL    , .douji = B_M|B_E|B_K       , .kana = "thi"     }, // てぃ
  {.shift = 0UL    , .douji = B_M|B_E|B_P       , .kana = "thu"     }, // てゅ
  {.shift = 0UL    , .douji = B_J|B_E|B_K       , .kana = "dhi"     }, // でぃ
  {.shift = 0UL    , .douji = B_J|B_E|B_P       , .kana = "dhu"     }, // でゅ
  {.shift = 0UL    , .douji = B_M|B_D|B_L       , .kana = "toxu"    }, // とぅ
  {.shift = 0UL    , .douji = B_J|B_D|B_L       , .kana = "doxu"    }, // どぅ
  {.shift = 0UL    , .douji = B_M|B_R|B_O       , .kana = "sye"     }, // しぇ
  {.shift = 0UL    , .douji = B_M|B_G|B_O       , .kana = "tye"     }, // ちぇ
  {.shift = 0UL    , .douji = B_J|B_R|B_O       , .kana = "zye"     }, // じぇ
  {.shift = 0UL    , .douji = B_J|B_G|B_O       , .kana = "dye"     }, // ぢぇ
  {.shift = 0UL    , .douji = B_V|B_SCLN|B_J    , .kana = "fa"      }, // ふぁ
  {.shift = 0UL    , .douji = B_V|B_SCLN|B_K    , .kana = "fi"      }, // ふぃ
  {.shift = 0UL    , .douji = B_V|B_SCLN|B_O    , .kana = "fe"      }, // ふぇ
  {.shift = 0UL    , .douji = B_V|B_SCLN|B_N    , .kana = "fo"      }, // ふぉ
  {.shift = 0UL    , .douji = B_V|B_SCLN|B_P    , .kana = "fyu"     }, // ふゅ
  {.shift = 0UL    , .douji = B_V|B_K|B_O       , .kana = "ixe"     }, // いぇ
  {.shift = 0UL    , .douji = B_V|B_L|B_K       , .kana = "wi"      }, // うぃ
  {.shift = 0UL    , .douji = B_V|B_L|B_O       , .kana = "we"      }, // うぇ
  {.shift = 0UL    , .douji = B_V|B_L|B_N       , .kana = "uxo"     }, // うぉ
  {.shift = 0UL    , .douji = B_M|B_Q|B_J       , .kana = "va"      }, // ゔぁ
  {.shift = 0UL    , .douji = B_M|B_Q|B_K       , .kana = "vi"      }, // ゔぃ
  {.shift = 0UL    , .douji = B_M|B_Q|B_O       , .kana = "ve"      }, // ゔぇ
  {.shift = 0UL    , .douji = B_M|B_Q|B_N       , .kana = "vo"      }, // ゔぉ
  {.shift = 0UL    , .douji = B_M|B_Q|B_P       , .kana = "vuxyu"   }, // ゔゅ
  {.shift = 0UL    , .douji = B_V|B_H|B_J       , .kana = "kuxa"    }, // くぁ
  {.shift = 0UL    , .douji = B_V|B_H|B_K       , .kana = "kuxi"    }, // くぃ
  {.shift = 0UL    , .douji = B_V|B_H|B_O       , .kana = "kuxe"    }, // くぇ
  {.shift = 0UL    , .douji = B_V|B_H|B_N       , .kana = "kuxo"    }, // くぉ
  {.shift = 0UL    , .douji = B_V|B_H|B_DOT     , .kana = "kuxwa"   }, // くゎ
  {.shift = 0UL    , .douji = B_F|B_H|B_J       , .kana = "guxa"    }, // ぐぁ
  {.shift = 0UL    , .douji = B_F|B_H|B_K       , .kana = "guxi"    }, // ぐぃ
  {.shift = 0UL    , .douji = B_F|B_H|B_O       , .kana = "guxe"    }, // ぐぇ
  {.shift = 0UL    , .douji = B_F|B_H|B_N       , .kana = "guxo"    }, // ぐぉ
  {.shift = 0UL    , .douji = B_F|B_H|B_DOT     , .kana = "guxwa"   }, // ぐゎ
  {.shift = 0UL    , .douji = B_V|B_L|B_J       , .kana = "tsa"     }, // つぁ

  // 追加
  {.shift = 0UL    , .douji = B_SHFT            , .kana = " "},
  {.shift = B_SHFT , .douji = B_V               , .kana = ","SS_TAP(X_ENTER)},
  {.shift = B_SHFT , .douji = B_M               , .kana = "."SS_TAP(X_ENTER)},
  {.shift = 0UL    , .douji = B_U               , .kana = SS_TAP(X_BACKSPACE)},

  // enter
  {.shift = 0UL    , .douji = B_V|B_M           , .kana = SS_TAP(X_ENTER)},
  // enter+シフト(連続シフト)
  {.shift = B_SHFT , .douji = B_V|B_M           , .kana = SS_TAP(X_ENTER)},

};

typedef struct {
  uint32_t shift;
  uint32_t douji;
  void (*func)(void);
} naginata_henshumap;

const PROGMEM naginata_henshumap ngdichenshu[] = {
  {.shift = 0UL        , .shift = B_T     , .func = ng_T}, //
  {.shift = 0UL        , .shift = B_Y     , .func = ng_Y}, //
  {.shift = B_SHFT     , .shift = B_T     , .func = ng_ST}, //
  {.shift = B_SHFT     , .shift = B_Y     , .func = ng_SY}, //
  // {.shift = 0UL        , .shift = B_H|B_J , .func = ng_kanaon}, //　かなオン
  // {.shift = 0UL        , .shift = B_F|B_G , .func = ng_kanaoff}, //　かなオフ

  // 編集モード
  {.shift = B_D|B_F    , .douji = B_Y     , .func = ngh_DFY}, // {Home}
  {.shift = B_D|B_F    , .douji = B_U     , .func = ngh_DFU}, // +{End}{BS}
  {.shift = B_D|B_F    , .douji = B_I     , .func = ngh_DFI}, // {vk1Csc079}
  {.shift = B_D|B_F    , .douji = B_O     , .func = ngh_DFO}, // {Del}
  {.shift = B_D|B_F    , .douji = B_P     , .func = ngh_DFP}, // {Esc 3}
  {.shift = B_D|B_F    , .douji = B_H     , .func = ngh_DFH}, // {Enter}{End}
  {.shift = B_D|B_F    , .douji = B_J     , .func = ngh_DFJ}, // {↑}
  {.shift = B_D|B_F    , .douji = B_K     , .func = ngh_DFK}, // +{↑}
  {.shift = B_D|B_F    , .douji = B_L     , .func = ngh_DFL}, // +{↑ 7}
  {.shift = B_D|B_F    , .douji = B_SCLN  , .func = ngh_DFSCLN}, // ^i
  {.shift = B_D|B_F    , .douji = B_N     , .func = ngh_DFN}, // {End}
  {.shift = B_D|B_F    , .douji = B_M     , .func = ngh_DFM}, // {↓}
  {.shift = B_D|B_F    , .douji = B_COMM  , .func = ngh_DFCOMM}, // +{↓}
  {.shift = B_D|B_F    , .douji = B_DOT   , .func = ngh_DFDOT}, // +{↓ 7}
  {.shift = B_D|B_F    , .douji = B_SLSH  , .func = ngh_DFSLSH}, // ^u

  {.shift = B_J|B_K    , .douji = B_Q     , .func = ngh_JKQ}, // ^{End}
  {.shift = B_J|B_K    , .douji = B_W     , .func = ngh_JKW}, // 『』{改行}{↑}
  {.shift = B_J|B_K    , .douji = B_E     , .func = ngh_JKE}, // ディ
  {.shift = B_J|B_K    , .douji = B_R     , .func = ngh_JKR}, // ^s
  {.shift = B_J|B_K    , .douji = B_T     , .func = ngh_JKT}, // ・
  {.shift = B_J|B_K    , .douji = B_A     , .func = ngh_JKA}, // ……{改行}
  {.shift = B_J|B_K    , .douji = B_S     , .func = ngh_JKS}, // (){改行}{↑}
  {.shift = B_J|B_K    , .douji = B_D     , .func = ngh_JKD}, // ？{改行}
  {.shift = B_J|B_K    , .douji = B_F     , .func = ngh_JKF}, // 「」{改行}{↑}
  {.shift = B_J|B_K    , .douji = B_G     , .func = ngh_JKG}, // 《》{改行}{↑}
  {.shift = B_J|B_K    , .douji = B_Z     , .func = ngh_JKZ}, // ――{改行}
  {.shift = B_J|B_K    , .douji = B_X     , .func = ngh_JKX}, // 【】{改行}{↑}
  {.shift = B_J|B_K    , .douji = B_C     , .func = ngh_JKC}, // ！{改行}
  {.shift = B_J|B_K    , .douji = B_V     , .func = ngh_JKV}, // {改行}{↓}
  {.shift = B_J|B_K    , .douji = B_B     , .func = ngh_JKB}, // {改行}{←}

  {.shift = B_C|B_V    , .douji = B_Y     , .func = ngh_CVY}, // +{Home}
  {.shift = B_C|B_V    , .douji = B_U     , .func = ngh_CVU}, // ^x
  {.shift = B_C|B_V    , .douji = B_I     , .func = ngh_CVI}, // ^v
  {.shift = B_C|B_V    , .douji = B_O     , .func = ngh_CVO}, // ^y
  {.shift = B_C|B_V    , .douji = B_P     , .func = ngh_CVP}, // ^z
  {.shift = B_C|B_V    , .douji = B_H     , .func = ngh_CVH}, // ^c
  {.shift = B_C|B_V    , .douji = B_J     , .func = ngh_CVJ}, // {→}
  {.shift = B_C|B_V    , .douji = B_K     , .func = ngh_CVK}, // +{→}
  {.shift = B_C|B_V    , .douji = B_L     , .func = ngh_CVL}, // +{→ 5}
  {.shift = B_C|B_V    , .douji = B_SCLN  , .func = ngh_CVSCLN}, // +{→ 20}
  {.shift = B_C|B_V    , .douji = B_N     , .func = ngh_CVN}, // +{End}
  {.shift = B_C|B_V    , .douji = B_M     , .func = ngh_CVM}, // {←}
  {.shift = B_C|B_V    , .douji = B_COMM  , .func = ngh_CVCOMM}, // +{←}
  {.shift = B_C|B_V    , .douji = B_DOT   , .func = ngh_CVDOT}, // +{← 5}
  {.shift = B_C|B_V    , .douji = B_SLSH  , .func = ngh_CVSLSH}, // +{← 20}

  {.shift = B_M|B_COMM , .douji = B_Q     , .func = ngh_MCQ}, // {Home}{→}{End}{Del 4}{←}
  {.shift = B_M|B_COMM , .douji = B_W     , .func = ngh_MCW}, // ^x『^v』{改行}{Space}+{↑}^x
  {.shift = B_M|B_COMM , .douji = B_E     , .func = ngh_MCE}, // {Home}{改行}{Space 3}{←}
  {.shift = B_M|B_COMM , .douji = B_R     , .func = ngh_MCR}, // {Space 3}
  {.shift = B_M|B_COMM , .douji = B_T     , .func = ngh_MCT}, // 〇{改行}
  {.shift = B_M|B_COMM , .douji = B_A     , .func = ngh_MCA}, // {Home}{→}{End}{Del 2}{←}
  {.shift = B_M|B_COMM , .douji = B_S     , .func = ngh_MCS}, // ^x(^v){改行}{Space}+{↑}^x
  {.shift = B_M|B_COMM , .douji = B_D     , .func = ngh_MCD}, // {Home}{改行}{Space 1}{←}
  {.shift = B_M|B_COMM , .douji = B_F     , .func = ngh_MCF}, // ^x「^v」{改行}{Space}+{↑}^x
  {.shift = B_M|B_COMM , .douji = B_G     , .func = ngh_MCG}, // ^x｜{改行}^v《》{改行}{↑}{Space}+{↑}^x
  {.shift = B_M|B_COMM , .douji = B_Z     , .func = ngh_MCZ}, // 　　　×　　　×　　　×{改行 2}
  {.shift = B_M|B_COMM , .douji = B_X     , .func = ngh_MCX}, // ^x【^v】{改行}{Space}+{↑}^x
  {.shift = B_M|B_COMM , .douji = B_C     , .func = ngh_MCC}, // ／{改行}
  {.shift = B_M|B_COMM , .douji = B_V     , .func = ngh_MCV}, // {改行}{End}{改行}「」{改行}{↑}
  {.shift = B_M|B_COMM , .douji = B_B     , .func = ngh_MCB}, // {改行}{End}{改行}{Space}

};

// 薙刀式のレイヤー、オンオフするキー
void set_naginata(uint8_t layer, uint16_t *onk, uint16_t *offk) {
  naginata_layer = layer;
  ngon_keys[0] = *onk;
  ngon_keys[1] = *(onk+1);
  ngoff_keys[0] = *offk;
  ngoff_keys[1] = *(offk+1);

  initializeListArray(&nginput);

  naginata_config.raw = eeconfig_read_user();
  if (naginata_config.os != NG_WIN && naginata_config.os != NG_MAC && naginata_config.os != NG_LINUX) {
    naginata_config.os = NG_WIN;
    naginata_config.live_conv = 1;
    naginata_config.tategaki = 1;
    naginata_config.kouchi_shift = 0;
    eeconfig_update_user(naginata_config.raw);
  }
  ng_set_unicode_mode(naginata_config.os);
}

// 薙刀式をオン
void naginata_on(void) {
  is_naginata = true;
  keycomb = 0UL;
  naginata_clear();
  layer_on(naginata_layer);

  tap_code(KC_LANGUAGE_1); // Mac
  tap_code(KC_INTERNATIONAL_4); // Win
}

// 薙刀式をオフ
void naginata_off(void) {
  is_naginata = false;
  keycomb = 0UL;
  naginata_clear();
  layer_off(naginata_layer);

  tap_code(KC_LANGUAGE_2); // Mac
  tap_code(KC_INTERNATIONAL_5); // Win
}

// 薙刀式のon/off状態を返す
bool naginata_state(void) {
  return is_naginata;
}

void switchOS(uint8_t os) {
  naginata_config.os = os;
  eeconfig_update_user(naginata_config.raw);
  ng_set_unicode_mode(naginata_config.os);
}

void ng_set_unicode_mode(uint8_t os) {
  switch (os) {
    case NG_WIN:
      set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
      break;
    case NG_MAC:
      set_unicode_input_mode(UNICODE_MODE_MACOS);
      break;
    case NG_LINUX:
      set_unicode_input_mode(UNICODE_MODE_LINUX);
      break;
  }
}

void mac_live_conversion_toggle() {
  naginata_config.live_conv ^= 1;
  eeconfig_update_user(naginata_config.raw);
}

void tategaki_toggle() {
  naginata_config.tategaki ^= 1;
  eeconfig_update_user(naginata_config.raw);
}

void kouchi_shift_toggle() {
  naginata_config.kouchi_shift ^= 1;
  eeconfig_update_user(naginata_config.raw);
}

void ng_show_os(void) {
  switch (naginata_config.os) {
    case NG_WIN:
      send_string("win");
      break;
    case NG_MAC:
      send_string("mac");
      if (naginata_config.live_conv) {
        send_string("/:lc");
      } else {
        send_string("/-lc");
      }
      break;
    case NG_LINUX:
      send_string("linux");
      break;
  }
  if (naginata_config.tategaki) {
    send_string("/tate");
  } else {
    send_string("/yoko");
  }
  if (naginata_config.kouchi_shift) {
    send_string("/:kouchi");
  } else {
    send_string("/-kouchi");
  }
}

#define MAX_STRLEN 40
void ng_send_unicode_string_P(const char *pstr) {
  if (strlen_P(pstr) > MAX_STRLEN) return;
  char str[MAX_STRLEN];
  strcpy_P(str, pstr);

  switch (naginata_config.os) {
    case NG_LINUX:
      tap_code(KC_INTERNATIONAL_5);
      send_unicode_string(str);
      tap_code(KC_INTERNATIONAL_4);
      break;
    case NG_WIN:
      send_unicode_string(str);
      tap_code(KC_ENT);
      break;
    case NG_MAC: // Karabiner-Elementsが必要
      tap_code(KC_LANGUAGE_2); // 未確定文字を確定する
      wait_ms(50);
      register_code(KC_LCTL); // Unicode HEX Inputへ切り替え
      wait_ms(50);
      tap_code(KC_F20);
      wait_ms(50);
      unregister_code(KC_LCTL);
      wait_ms(50);
      send_unicode_string(str);
      wait_ms(50);
      register_code(KC_LSFT); // 日本語入力へ切り替え。再変換にならないように「shift+かな」「かな」の2打にする。
      wait_ms(50);
      tap_code(KC_LANGUAGE_1);
      wait_ms(50);
      unregister_code(KC_LSFT);
      wait_ms(50);
      tap_code(KC_LANGUAGE_1);
      break;
  }
}

// modifierが押されたら薙刀式レイヤーをオフしてベースレイヤーに戻す
// get_mods()がうまく動かない
static int n_modifier = 0;

bool process_modifier(uint16_t keycode, keyrecord_t *record) {
  if (IS_MODIFIER_KEYCODE(keycode) || IS_QK_MOD_TAP(keycode)) {
    if (record->event.pressed) {
      n_modifier++;
      layer_off(naginata_layer);
    } else {
      n_modifier--;
      if (n_modifier <= 0) {
        n_modifier = 0;
        layer_on(naginata_layer);
      }
    }
    return true;
  }
  return false;
}

static uint16_t fghj_buf = 0; // 押しているJかKのキーコード
static uint8_t nkeypress = 0; // 同時にキーを押している数

// 薙刀式の起動処理(容量が大きいCOMBOを使わない)
bool enable_naginata(uint16_t keycode, keyrecord_t *record) {
  // キープレス
  if (record->event.pressed) {
    nkeypress++;
    // 1キー目、JKの前に他のキーを押していないこと
    if (fghj_buf == 0 && nkeypress == 1) {
      // かなオンキーの場合
      if (keycode == ngon_keys[0] || keycode == ngon_keys[1] || keycode == ngoff_keys[0] || keycode == ngoff_keys[1]) {
        fghj_buf = keycode;
        return false;
      }
    // ２キー目
    } else {
      // ２キー目、１キー目、両方ともかなオンキー
      if ((keycode == ngon_keys[0] && fghj_buf == ngon_keys[1]) ||
          (keycode == ngon_keys[1] && fghj_buf == ngon_keys[0])) {
        naginata_on();
        fghj_buf = 0;
        nkeypress = 0;
        return false;
      } else if ((keycode == ngoff_keys[0] && fghj_buf == ngoff_keys[1]) ||
          (keycode == ngoff_keys[1] && fghj_buf == ngoff_keys[0])) {
        naginata_off();
        fghj_buf = 0;
        nkeypress = 0;
        return false;
      // ２キー目はかなオンキーではない
      } else {
        tap_code(fghj_buf); // 1キー目を出力
        fghj_buf = 0;
        nkeypress = 0;
        return true; // 2キー目はQMKにまかせる
      }
    }
  } else {
    nkeypress = 0;
    // J/K単押しだった
    if (fghj_buf > 0) {
      tap_code(fghj_buf);
      fghj_buf = 0;

      // Shift + Jで、先にShiftを外した場合にShiftがリリースされない不具合対策
      if (IS_MODIFIER_KEYCODE(keycode)) {
        unregister_code(keycode);
      } else if (IS_QK_MOD_TAP(keycode)) {
        if (keycode & (MOD_LCTL << 8))
          unregister_code(KC_LEFT_CTRL);
        if (keycode & (MOD_LSFT << 8))
          unregister_code(KC_LEFT_SHIFT);
        if (keycode & (MOD_LALT << 8))
          unregister_code(KC_LEFT_ALT);
        if (keycode & (MOD_LGUI << 8))
          unregister_code(KC_LEFT_GUI);
        if (keycode & (MOD_RCTL << 8))
          unregister_code(KC_RIGHT_CTRL);
        if (keycode & (MOD_RSFT << 8))
          unregister_code(KC_RIGHT_SHIFT);
        if (keycode & (MOD_RALT << 8))
          unregister_code(KC_RIGHT_ALT);
        if (keycode & (MOD_RGUI << 8))
          unregister_code(KC_RIGHT_GUI);
      }
      return false;
    }
  }

  fghj_buf = 0;
  return true;
}

// バッファをクリアする
void naginata_clear(void) {
  // for (int i = 0; i < NGBUFFER; i++) {
  //   ninputs[i] = 0;
  // }
  // ng_chrcount = 0;
  initializeListArray(&nginput);
  n_modifier = 0;
  nkeypress = 0;
  fghj_buf = 0;
}

// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {

  // まれに薙刀モードオンのまま、レイヤーがオフになることがあるので、対策
  if (n_modifier == 0 && is_naginata && !layer_state_is(naginata_layer))
    layer_on(naginata_layer);
  if (n_modifier == 0 && !is_naginata && layer_state_is(naginata_layer))
    layer_off(naginata_layer);
  if (n_modifier > 0 && layer_state_is(naginata_layer))
    layer_off(naginata_layer);

  // OS切り替え(UNICODE出力)
  if (record->event.pressed) {
    switch (keycode) {
      case NG_ON:
        naginata_on();
        return false;
        break;
      case NG_OFF:
        naginata_off();
        return false;
        break;
      case NG_CLR:
        naginata_clear();
        return false;
        break;
      case NGSW_WIN:
        switchOS(NG_WIN);
        return false;
        break;
      case NGSW_MAC:
        switchOS(NG_MAC);
        return false;
        break;
      case NGSW_LNX:
        switchOS(NG_LINUX);
        return false;
        break;
      case NG_MLV:
        mac_live_conversion_toggle();
        return false;
        break;
      case NG_SHOS:
        ng_show_os();
        return false;
        break;
      case NG_TAYO:
        tategaki_toggle();
        return false;
        break;
      case NG_KOTI:
        kouchi_shift_toggle();
        return false;
        break;
    }
  }

  if (!is_naginata)
    // return true;
    return enable_naginata(keycode, record);

  if (process_modifier(keycode, record))
    return true;

  if (record->event.pressed) {
    #if defined(CONSOLE_ENABLE)
        uprintf(">process_naginata pressed=%u nginput.size=%u\n", keycode, nginput.size);
    #endif
    if (keycode >= NG_Q && keycode <= NG_SHFT2) {

      pressed_keys |= ng_key[keycode - NG_Q]; // キーの重ね合わせ

      if (keycode == NG_SHFT || keycode == NG_SHFT2) {
        NGList a;
        initializeList(&a);
        addToList(&a, keycode);
        addToListArray(&nginput, &a);
      } else {
        NGList a;
        copyList(&(nginput.elements[nginput.size - 1]), &a);
        NGList b;
        copyList(&a, &b);
        addToList(&b, keycode);

        // 前のキーとの同時押しの可能性があるなら前に足す
        // 同じキー連打を除外
        if (nginput.size > 0 && a.elements[a.size - 1] != keycode && number_of_candidates(&b, false) > 0) {
          removeFromListArrayAt(&nginput, nginput.size - 1);
          addToListArray(&nginput, &b);
        // 前のキーと同時押しはない
        } else {
          // 連続シフト
          uint16_t rs[4][2] = {{NG_D, NG_F}, {NG_C, NG_V}, {NG_J, NG_K}, {NG_M, NG_COMM}};
          NGList df;
          bool f = false;

          if (nginput.size > 0) {
            for (int i = 0; i < 4; i++) {
              initializeList(&df);
              addToList(&df, rs[i][0]);
              addToList(&df, rs[i][1]);
              addToList(&df, keycode);
              uint32_t brs = 0UL;
              for (int j = 0; j < 2; j++) {
                brs |=  ng_key[rs[i][j] - NG_Q];
              }
              if (keycode != rs[i][0] && keycode != rs[i][1] && ((brs & pressed_keys) == brs) && number_of_candidates(&df, false) >  0) {
                addToListArray(&nginput, &df);
                f = true;
                break;
              }
            }
          }

          // 連続シフトではない
          if (!f) { 
            NGList e;
            initializeList(&e);
            addToList(&e, keycode);
            addToListArray(&nginput, &e);
          }
        }

        if (nginput.size > 1 && number_of_candidates(&(nginput.elements[0]), false) == 1) {
          ng_type(&(nginput.elements[0]));
          removeFromListArrayAt(&nginput, 0);
        }
      }
      #if defined(CONSOLE_ENABLE)
        uprintf("<process_naginata pressed=%u nginput.size=%u\n", keycode, nginput.size);
      #endif
      return false;
    }

  } else { // key release
    #if defined(CONSOLE_ENABLE)
        uprintf(">process_naginata released=%u nginput.size=%u\n", keycode, nginput.size);
    #endif
    if (keycode >= NG_Q && keycode <= NG_SHFT2) {
      pressed_keys &= ~ng_key[keycode - NG_Q]; // キーの重ね合わせ

      if (pressed_keys == 0UL) {
        while (nginput.size > 0) {
          ng_type(&(nginput.elements[0]));
          removeFromListArrayAt(&nginput, 0);
        }
      }

      #if defined(CONSOLE_ENABLE)
          uprintf("<process_naginata released=%u nginput.size=%u\n", keycode, nginput.size);
      #endif
      return false;
    }
  }

  return true;
}

// キー入力を文字に変換して出力する
void ng_type(NGList *keys) {
  #if defined(CONSOLE_ENABLE)
    uprintf(">ng_type size=%u\n", keys->size);
  #endif
  if (keys->size == 0) return;

  naginata_keymap bngdickana;

  if (keys->size == 1 && keys->elements[0] == NG_SHFT2) {
    tap_code16(KC_ENT);
  }

  bool ftype = false;
  uint32_t keyset = 0UL;
  for (int i = 0; i < keys->size; i++) {
    keyset |= ng_key[keys->elements[i] - NG_Q];
  }
  for (int i = 0; i < sizeof ngdickana / sizeof bngdickana; i++) {
    memcpy_P(&bngdickana, &ngdickana[i], sizeof(bngdickana));
    if ((bngdickana.shift | bngdickana.douji) == keyset) {
      send_string(bngdickana.kana);
      ftype = true;
      break;
    }
  }
  // JIみたいにJIを含む同時押しはたくさんあるが、JIのみの同時押しがないとき
  // 最後の１キーを別に分けて変換する
  if (!ftype) {
    NGList a, b;
    initializeList(&a);
    initializeList(&b);
    for (int i = 0; i < keys->size - 1; i++) {
      addToList(&a, keys->elements[i]);
    }
    addToList(&b, keys->elements[keys->size - 1]);
    ng_type(&a);
    ng_type(&b);
  }

  #if defined(CONSOLE_ENABLE)
    uprintf("<ng_type\n");
  #endif
}

int number_of_candidates(NGList *keys, bool strict) {
  #if defined(CONSOLE_ENABLE)
    uprintf(">number_of_candidates\n");
  #endif
  if (keys->size == 0) return 0;

  naginata_keymap bngdickana; // PROGMEM buffer
  naginata_henshumap bngdichenshu;
  int noc = 0;

  if (strict) { // 完全一致
    if (keys->size == 1 && (compareList0(keys, NG_SHFT) || compareList0(keys, NG_SHFT2))) {
      noc = 1;
    } else if (keys->size > 1 && (compareList0(keys, NG_SHFT) || compareList0(keys, NG_SHFT2))) {
      uint32_t keyset = 0UL;
      for (int i = 1; i < keys->size; i++) {
        keyset |= ng_key[keys->elements[i] - NG_Q];
      }
      for (int i = 0; i < sizeof ngdickana / sizeof bngdickana; i++) {
        memcpy_P(&bngdickana, &ngdickana[i], sizeof(bngdickana));
        if (bngdickana.shift == B_SHFT && bngdickana.douji == keyset) {
          noc++;
        }
      }
    } else {
      if (keys->size == 3 && compareList01(keys, NG_D, NG_F)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_D|B_F) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else if (keys->size == 3 && compareList01(keys, NG_C, NG_V)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_C|B_V) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else if (keys->size == 3 && compareList01(keys, NG_J, NG_K)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_J|B_K) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else if (keys->size == 3 && compareList01(keys, NG_M, NG_COMM)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_M|B_COMM) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else {
        uint32_t keyset = 0UL;
        for (int i = 0; i < keys->size; i++) {
          keyset |= ng_key[keys->elements[i] - NG_Q];
        }
        for (int i = 0; i < sizeof ngdickana / sizeof bngdickana; i++) {
          memcpy_P(&bngdickana, &ngdickana[i], sizeof(bngdickana));
          if (bngdickana.shift == 0UL && bngdickana.douji == keyset) {
            noc++;
          }
        }
      }
    }

  } else { // 部分一致
    if (keys->size == 1 && (compareList0(keys, NG_SHFT) || compareList0(keys, NG_SHFT2))) {
      noc = 2;
    } else if (keys->size == 2 && (compareList01(keys, NG_D, NG_F) || compareList01(keys, NG_C, NG_V) || compareList01(keys, NG_J, NG_K) || compareList01(keys, NG_M, NG_COMM))) {
      noc = 2;
    } else if (keys->size > 1 && (compareList0(keys, NG_SHFT) || compareList0(keys, NG_SHFT2))) {
      uint32_t keyset = 0UL;
      for (int i = 1; i < keys->size; i++) {
        keyset |= ng_key[keys->elements[i] - NG_Q];
      }
      for (int i = 0; i < sizeof ngdickana / sizeof bngdickana; i++) {
        memcpy_P(&bngdickana, &ngdickana[i], sizeof(bngdickana));
        if (bngdickana.shift == B_SHFT && ((bngdickana.douji & keyset) == keyset)) {
          noc++;
        }
      }
    } else {
      if (keys->size == 3 && compareList01(keys, NG_D, NG_F)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_D|B_F) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else if (keys->size == 3 && compareList01(keys, NG_C, NG_V)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_C|B_V) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else if (keys->size == 3 && compareList01(keys, NG_J, NG_K)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_J|B_K) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else if (keys->size == 3 && compareList01(keys, NG_M, NG_COMM)) {
        for (int i = 0; i < sizeof ngdichenshu / sizeof bngdichenshu; i++) {
          memcpy_P(&bngdichenshu, &ngdichenshu[i], sizeof(bngdichenshu));
          if (bngdichenshu.shift == (B_M|B_COMM) && bngdichenshu.douji == ng_key[keys->elements[2] - NG_Q]) {
            noc = 1;
            break;
          }
        }
      } else {
        uint32_t keyset = 0UL;
        for (int i = 0; i < keys->size; i++) {
          keyset |= ng_key[keys->elements[i] - NG_Q];
        }
        for (int i = 0; i < sizeof ngdickana / sizeof bngdickana; i++) {
          memcpy_P(&bngdickana, &ngdickana[i], sizeof(bngdickana));
          if (bngdickana.shift == 0UL && ((bngdickana.douji & keyset) == keyset)) {
            noc++;
          }
        }
      }
    }
  }

  #if defined(CONSOLE_ENABLE)
    uprintf("<number_of_candidates noc=%u\n", noc);
  #endif

  return noc;
}


// 押すキーの数
int count_bit(uint32_t b) {
  int c = 0;
  while (b > 0) {
    if ((b & 1UL) == 1UL) c++;
    b = b >> 1;
  }
  return c;
}

void ng_T() {
  ng_left(1);
}

void ng_Y() {
  ng_right(1);
}

void ng_ST() {
  register_code(KC_LSFT);
  ng_left(1);
  unregister_code(KC_LSFT);
}

void ng_SY() {
  register_code(KC_LSFT);
  ng_right(1);
  unregister_code(KC_LSFT);
}

void ngh_JKQ() { // ^{End}
  ng_eof();
}

void ngh_JKW() { // 『』{改行}{↑}
  ng_send_unicode_string_P(PSTR("『』"));
  ng_up(1);
}

void ngh_JKE() { // ディ
  send_string("dhi");
}

void ngh_JKR() { // ^s
  ng_save();
}

void ngh_JKT() { // ・
  ng_send_unicode_string_P(PSTR("・"));
}

void ngh_JKA() { // ……{改行}
  ng_send_unicode_string_P(PSTR("……"));
}

void ngh_JKS() { // (){改行}{↑}
  ng_send_unicode_string_P(PSTR("()"));
  ng_up(1);
}

void ngh_JKD() { // ？{改行}
  ng_send_unicode_string_P(PSTR("？"));
}

void ngh_JKF() { // 「」{改行}{↑}
  ng_send_unicode_string_P(PSTR("「」"));
  ng_up(1);
}

void ngh_JKG() { // 《》{改行}{↑}
  ng_send_unicode_string_P(PSTR("《》"));
  ng_up(1);
}

void ngh_JKZ() { // ――{改行}
  ng_send_unicode_string_P(PSTR("――"));
}

void ngh_JKX() { // 【】{改行}{↑}
  ng_send_unicode_string_P(PSTR("【】"));
  ng_up(1);
}

void ngh_JKC() { // ！{改行}
  ng_send_unicode_string_P(PSTR("！"));
}

void ngh_JKV() { // {改行}{↓}
  tap_code(KC_ENT);
  ng_down(1);
}

void ngh_JKB() { // {改行}{←}
  tap_code(KC_ENT);
  ng_left(1);
}

void ngh_DFY() { // {Home}
  ng_home();
}

void ngh_DFU() { // +{End}{BS}
  register_code(KC_LSFT);
  ng_end();
  unregister_code(KC_LSFT);
  tap_code(KC_BSPC);
}

void ngh_DFI() { // {vk1Csc079}
  ng_saihenkan();
}

void ngh_DFO() { // {Del}
  tap_code(KC_DEL);
}

void ngh_DFP() { // {Esc 3}
  tap_code(KC_ESC);
  tap_code(KC_ESC);
  tap_code(KC_ESC);
}

void ngh_DFH() { // {Enter}{End}
  tap_code(KC_ENT);
  ng_end();
}

void ngh_DFJ() { // {↑}
  ng_up(1);
}

void ngh_DFK() { // +{↑}
  register_code(KC_LSFT);
  ng_up(1);
  unregister_code(KC_LSFT);
}

void ngh_DFL() { // +{↑ 7}
  register_code(KC_LSFT);
  ng_up(7);
  unregister_code(KC_LSFT);
}

void ngh_DFSCLN() { // ^i
  ng_katakana();
}

void ngh_DFN() { // {End}
  ng_end();
}

void ngh_DFM() { // {↓}
  ng_down(1);
}

void ngh_DFCOMM() { // +{↓}
  register_code(KC_LSFT);
  ng_down(1);
  unregister_code(KC_LSFT);
}

void ngh_DFDOT() { // +{↓ 7}
  register_code(KC_LSFT);
  ng_down(7);
  unregister_code(KC_LSFT);
}

void ngh_DFSLSH() { // ^u
  ng_hiragana();
}

void ngh_MCQ() { // {Home}{→}{End}{Del 4}{←}
  ng_home();
  ng_right(1);
  ng_end();
  tap_code(KC_DEL);
  tap_code(KC_DEL);
  tap_code(KC_DEL);
  tap_code(KC_DEL);
  ng_left(1);
}

void ngh_MCW() { // ^x『^v』{改行}{Space}+{↑}^x
  ng_cut();
  ng_send_unicode_string_P(PSTR("『"));
  ng_paste();
  ng_send_unicode_string_P(PSTR("』"));
  tap_code(KC_SPC);
  register_code(KC_LSFT);
  ng_up(1);
  unregister_code(KC_LSFT);
  ng_cut();
}

void ngh_MCE() { // {Home}{改行}{Space 3}{←}
  ng_home();
  tap_code(KC_ENT);
  tap_code(KC_SPC);
  tap_code(KC_SPC);
  tap_code(KC_SPC);
  ng_left(1);
}

void ngh_MCR() { // {Space 3}
  tap_code(KC_SPC);
  tap_code(KC_SPC);
  tap_code(KC_SPC);
}

void ngh_MCT() { // 〇{改行}
  ng_send_unicode_string_P(PSTR("〇"));
}

void ngh_MCA() { // {Home}{→}{End}{Del 2}{←}
  ng_home();
  ng_right(1);
  ng_end();
  tap_code(KC_DEL);
  tap_code(KC_DEL);
  ng_left(1);
}

void ngh_MCS() { // ^x(^v){改行}{Space}+{↑}^x
  ng_cut();
  ng_send_unicode_string_P(PSTR("("));
  ng_paste();
  ng_send_unicode_string_P(PSTR(")"));
  tap_code(KC_SPC);
  register_code(KC_LSFT);
  ng_up(1);
  unregister_code(KC_LSFT);
  ng_cut();
}

void ngh_MCD() { // {Home}{改行}{Space 1}{←}
  ng_home();
  tap_code(KC_ENT);
  tap_code(KC_SPC);
  ng_left(1);
}

void ngh_MCF() { // ^x「^v」{改行}{Space}+{↑}^x
  ng_cut();
  ng_send_unicode_string_P(PSTR("「"));
  ng_paste();
  ng_send_unicode_string_P(PSTR("」"));
  tap_code(KC_SPC);
  register_code(KC_LSFT);
  ng_up(1);
  unregister_code(KC_LSFT);
  ng_cut();
}

void ngh_MCG() { // ^x｜{改行}^v《》{改行}{↑}{Space}+{↑}^x
  ng_cut();
  ng_send_unicode_string_P(PSTR("｜"));
  ng_paste();
  tap_code(KC_SPC);
  register_code(KC_LSFT);
  ng_up(1);
  unregister_code(KC_LSFT);
  ng_cut();
  ng_send_unicode_string_P(PSTR("《》"));
  ng_up(1);
}

void ngh_MCZ() { // 　　　×　　　×　　　×{改行 2}
  ng_send_unicode_string_P(PSTR("　　　×　　　×　　　×"));
  tap_code(KC_ENT);
  tap_code(KC_ENT);
}

void ngh_MCX() { // ^x【^v】{改行}{Space}+{↑}^x
  ng_cut();
  ng_send_unicode_string_P(PSTR("【"));
  ng_paste();
  ng_send_unicode_string_P(PSTR("】"));
  tap_code(KC_SPC);
  register_code(KC_LSFT);
  ng_up(1);
  unregister_code(KC_LSFT);
  ng_cut();
}

void ngh_MCC() { // ／{改行}
  ng_send_unicode_string_P(PSTR("／"));
}

void ngh_MCV() { // {改行}{End}{改行}「」{改行}{↑}
  tap_code(KC_ENT);
  ng_end();
  tap_code(KC_ENT);
  ng_send_unicode_string_P(PSTR("「」"));
  ng_up(1);
}

void ngh_MCB() { // {改行}{End}{改行}{Space}
  tap_code(KC_ENT);
  ng_end();
  tap_code(KC_ENT);
  tap_code(KC_SPC);
}

void ngh_CVY() { // +{Home}
  register_code(KC_LSFT);
  ng_home();
  unregister_code(KC_LSFT);
}

void ngh_CVU() { // ^x
  ng_cut();
}

void ngh_CVI() { // ^v
  ng_paste();
}

void ngh_CVO() { // ^y
  ng_redo();
}

void ngh_CVP() { // ^z
  ng_undo();
}

void ngh_CVH() { // ^c
  ng_copy();
}

void ngh_CVJ() { // {→}
  ng_right(1);
}

void ngh_CVK() { // +{→}
  register_code(KC_LSFT);
  ng_right(1);
  unregister_code(KC_LSFT);
}

void ngh_CVL() { // +{→ 5}
  register_code(KC_LSFT);
  ng_right(5);
  unregister_code(KC_LSFT);
}

void ngh_CVSCLN() { // +{→ 20}
  register_code(KC_LSFT);
  ng_right(20);
  unregister_code(KC_LSFT);
}

void ngh_CVN() { // +{End}
  register_code(KC_LSFT);
  ng_end();
  unregister_code(KC_LSFT);
}

void ngh_CVM() { // {←}
  ng_left(1);
}

void ngh_CVCOMM() { // +{←}
  register_code(KC_LSFT);
  ng_left(1);
  unregister_code(KC_LSFT);
}

void ngh_CVDOT() { // +{← 5}
  register_code(KC_LSFT);
  ng_left(5);
  unregister_code(KC_LSFT);
}

void ngh_CVSLSH() { // +{← 20}
  register_code(KC_LSFT);
  ng_left(20);
  unregister_code(KC_LSFT);
}

// 固有名詞

// void ngh_UIW() { // 臨兵闘者皆陣烈在前
//   ng_send_unicode_string_P(PSTR("臨兵闘者皆陣烈在前"));
// }

// void ngh_UIE() { // 天狗
//   ng_send_unicode_string_P(PSTR("天狗"));
// }

// void ngh_UIR() { // シンイチ
//   ng_send_unicode_string_P(PSTR("シンイチ"));
// }

// void ngh_UIT() { // ネムカケ
//   ng_send_unicode_string_P(PSTR("ネムカケ"));
// }

// void ngh_UIA() { // 三神
//   ng_send_unicode_string_P(PSTR("三神"));
// }

// void ngh_UIS() { // 峯
//   ng_send_unicode_string_P(PSTR("峯"));
// }

// void ngh_UID() { // 小鴉
//   ng_send_unicode_string_P(PSTR("小鴉"));
// }

// void ngh_UIF() { // 光太郎
//   ng_send_unicode_string_P(PSTR("光太郎"));
// }

// void ngh_UIZ() { // 火よ、在れ
//   ng_send_unicode_string_P(PSTR("火よ、在れ"));
// }

// void ngh_UIX() { // 火の剣
//   ng_send_unicode_string_P(PSTR("火の剣"));
// }

// void ngh_UIC() { // 罵詈雑
//   ng_send_unicode_string_P(PSTR("罵詈雑"));
// }

// void ngh_UIV() { // 心の闇
//   ng_send_unicode_string_P(PSTR("心の闇"));
// }

// void ngh_ERY() { // 才一
//   ng_send_unicode_string_P(PSTR("才一"));
// }

// void ngh_ERU() { // さくら
//   ng_send_unicode_string_P(PSTR("さくら"));
// }

// void ngh_ERI() { // 酒田
//   ng_send_unicode_string_P(PSTR("酒田"));
// }

// void ngh_ERH() { // 鞍馬
//   ng_send_unicode_string_P(PSTR("鞍馬"));
// }

// void ngh_ERJ() { // 青鬼
//   ng_send_unicode_string_P(PSTR("青鬼"));
// }

// void ngh_ERK() { // 百地
//   ng_send_unicode_string_P(PSTR("百地"));
// }

// void ngh_ERSCLN() { // 不動金縛りの術
//   ng_send_unicode_string_P(PSTR("不動金縛りの術"));
// }

// void ngh_ERB() { // 鬼塚
//   ng_send_unicode_string_P(PSTR("鬼塚"));
// }

// void ngh_ERN() { // 赤石
//   ng_send_unicode_string_P(PSTR("赤石"));
// }

// void ngh_ERM() { // 八幡
//   ng_send_unicode_string_P(PSTR("八幡"));
// }

// void ngh_ERDOT() { // 霊槍
//   ng_send_unicode_string_P(PSTR("霊槍"));
// }

void ng_cut() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_X));
      break;
    case NG_MAC:
      tap_code16(LCMD(KC_X));
      break;
  }
}

void ng_copy() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_C));
      break;
    case NG_MAC:
      tap_code16(LCMD(KC_C));
      break;
  }
}

void ng_paste() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_V));
      break;
    case NG_MAC:
      register_code(KC_LCMD);
      wait_ms(100);
      tap_code(KC_V);
      wait_ms(100);
      unregister_code(KC_LCMD);
      wait_ms(100);
      break;
  }
}

void ng_up(uint8_t c) {
  for (uint8_t i = 0; i < c; i++) { // サイズ削減
    if (naginata_config.tategaki) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_LEFT);
    }
  }
}

void ng_down(uint8_t c) {
  for (uint8_t i = 0; i < c; i++) {
    if (naginata_config.tategaki) {
      tap_code(KC_DOWN);
    } else {
      tap_code(KC_RIGHT);
    }
  }
}

void ng_left(uint8_t c) {
  for (uint8_t i = 0; i < c; i++) {
    if (naginata_config.tategaki) {
      tap_code(KC_LEFT);
    } else {
      tap_code(KC_DOWN);
    }
  }
}

void ng_right(uint8_t c) {
  for (uint8_t i = 0; i < c; i++) {
    if (naginata_config.tategaki) {
      tap_code(KC_RIGHT);
    } else {
      tap_code(KC_UP);
    }
  }
}

void ng_home() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code(KC_HOME);
      break;
    case NG_MAC:
      tap_code16(LCTL(KC_A));
      break;
  }
}

void ng_end() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code(KC_END);
      break;
    case NG_MAC:
      tap_code16(LCTL(KC_E));
      break;
  }
}

void ng_katakana() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_I));
      break;
    case NG_MAC:
      tap_code16(LCTL(KC_K));
      break;
  }
}

void ng_save() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_S));
      break;
    case NG_MAC:
      tap_code16(LCMD(KC_S));
      break;
  }
}

void ng_hiragana() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_U));
      break;
    case NG_MAC:
      tap_code16(LCTL(KC_J));
      break;
  }
}

void ng_redo() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_Y));
      break;
    case NG_MAC:
      tap_code16(LSFT(LCMD(KC_Z)));
      break;
  }
}

void ng_undo() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_Z));
      break;
    case NG_MAC:
      tap_code16(LCMD(KC_Z));
      break;
  }
}

void ng_saihenkan() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code(KC_INT4);
      break;
    case NG_MAC:
      tap_code(KC_LANGUAGE_1);
      tap_code(KC_LANGUAGE_1);
      break;
  }
}

void ng_eof() {
  switch (naginata_config.os) {
    case NG_WIN:
    case NG_LINUX:
      tap_code16(LCTL(KC_END));
      break;
    case NG_MAC:
      tap_code16(LCMD(KC_DOWN));
      break;
  }
}