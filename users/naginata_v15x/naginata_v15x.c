/* Copyright eswai <@eswai>
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

/*

TODO

x 親指エンター
x 英数字に戻る
x 前置シフト
x 編集モードの追加 (編集モードはかな変換と異なる処理にする)
x AVRで動くようにする (固有名詞をオフにする)
x もも　が出ない
x ５キー以上打鍵した時の処理
x シフトしたまま入力し続けると暴走する
x 前置シフトだと連続シフトにならない
x 「もみもみ」などの連続シフトで5キー以上
x ガブガブ、FJ両方ともキャリーオーバーするのでうまくいかない
x じょじょの連続シフト
x 5キーの組み合わせへの拡張

編集モードを英字モードでも使いたい --> v15xxで試す
グローバル変数を減らす
単打の時は評価関数を飛ばす
「なんと」が編集モードに入る
エクストリームな入力に対しても暴走しないようにする(シフトしたまま連打とか)

*/

#include QMK_KEYBOARD_H
#include "naginata.h"
#include "set.h"
#include "nglist.h"
#include <string.h>

// static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ
static bool is_naginata = false; // 薙刀式がオンかオフか
static uint8_t naginata_layer = 0; // NG_*を配置しているレイヤー番号
static uint16_t ngon_keys[2]; // 薙刀式をオンにするキー(通常HJ)
static uint16_t ngoff_keys[2]; // 薙刀式をオフにするキー(通常FG)
static uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。
static bool is_henshu = false; // 編集モードかどうか
static bool henshu_done = false; // 編集モードを実行したか、編集モード空打ちだったか

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
  [NG_Q    - NG_Q] = B_Q,
  [NG_W    - NG_Q] = B_W,
  [NG_E    - NG_Q] = B_E,
  [NG_R    - NG_Q] = B_R,
  [NG_T    - NG_Q] = B_T,

  [NG_Y    - NG_Q] = B_Y,
  [NG_U    - NG_Q] = B_U,
  [NG_I    - NG_Q] = B_I,
  [NG_O    - NG_Q] = B_O,
  [NG_P    - NG_Q] = B_P,

  [NG_A    - NG_Q] = B_A,
  [NG_S    - NG_Q] = B_S,
  [NG_D    - NG_Q] = B_D,
  [NG_F    - NG_Q] = B_F,
  [NG_G    - NG_Q] = B_G,

  [NG_H    - NG_Q] = B_H,
  [NG_J    - NG_Q] = B_J,
  [NG_K    - NG_Q] = B_K,
  [NG_L    - NG_Q] = B_L,
  [NG_SCLN - NG_Q] = B_SCLN,

  [NG_Z    - NG_Q] = B_Z,
  [NG_X    - NG_Q] = B_X,
  [NG_C    - NG_Q] = B_C,
  [NG_V    - NG_Q] = B_V,
  [NG_B    - NG_Q] = B_B,

  [NG_N    - NG_Q] = B_N,
  [NG_M    - NG_Q] = B_M,
  [NG_COMM - NG_Q] = B_COMM,
  [NG_DOT  - NG_Q] = B_DOT,
  [NG_SLSH - NG_Q] = B_SLSH,

  [NG_SHFT - NG_Q] = B_SHFT,
  [NG_SHFT2 - NG_Q] = B_SHFT,
};

#define NKEYS 3 // 最大何キーまでバッファに貯めるか
#define NDOUJI 3 // 組み合わせにある同時押しするキーの数、薙刀式なら3

// 文字入力バッファ
static Set ngpressd; // 押しているキー
static NGList nginput; // 未変換のキー
static Keystroke ngingroup[NKEYS][NDOUJI]; // 入力バッファを同時押しの組み合わせでグループ化

static uint8_t doujiSize[NKEYS] = {0}; // ngingroupの配列のサイズ

#define NCOMBI 9 // COMBI配列の大きさ
const uint8_t COMBINDEX[] = {0, 1, 3, NCOMBI}; // COMBI配列の各キー数の最初の位置

/* 
  nginputをngingroupへ変換する
  同時押しの組み合わせを列挙している
  数字はninputの配列添字、-1はnull 
*/
const PROGMEM int8_t COMBI[NCOMBI][NKEYS][NDOUJI] = { 
  // 1 key
  {{ 0, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 0
  // 2 keys
  {{ 0, -1, -1}, { 1, -1, -1}, {-1, -1, -1}}, // 0 1
  {{ 0,  1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 01
  // 3 keys
  {{ 0, -1, -1}, { 1, -1, -1}, { 2, -1, -1}}, // 0   1   2
  {{ 0,  1, -1}, { 2, -1, -1}, {-1, -1, -1}}, // 01  2
  {{ 0, -1, -1}, { 1,  2, -1}, {-1, -1, -1}}, // 0   12
  {{ 0,  1,  2}, {-1, -1, -1}, {-1, -1, -1}}, // 012
  {{ 0,  1, -1}, { 0,  2, -1}, {-1, -1, -1}}, // 01  02 : 0が連続シフト (0に当てはまるのはfvjm space)
  {{ 0,  1, -1}, { 1,  2, -1}, {-1, -1, -1}}, // 01  12 : 1が連続シフト spaceはこれなしで
  // fvjm space以外でも連続シフトしている

  // // 1 key
  // {{ 0, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 0
  // // 2 keys
  // {{ 0, -1, -1}, { 1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 0 1
  // {{ 0,  1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 01
  // // 3 keys
  // {{ 0, -1, -1}, { 1, -1, -1}, { 2, -1, -1}, {-1, -1, -1}}, // 0   1   2
  // {{ 0,  1, -1}, { 2, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 01  2
  // {{ 0, -1, -1}, { 1,  2, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 0   12
  // {{ 0,  1,  2}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 012
  // {{ 0,  1, -1}, { 0,  2, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 01  02 : 0が連続シフト
  // {{ 0,  1, -1}, { 1,  2, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 01  12 : 1が連続シフト
  // // 4 keys
  // {{ 0, -1, -1}, { 1, -1, -1}, { 2, -1, -1}, { 3, -1, -1}}, // 0   1   2   3
  // {{ 0,  1, -1}, { 2, -1, -1}, { 3, -1, -1}, {-1, -1, -1}}, // 01  2   3
  // {{ 0, -1, -1}, { 1,  2, -1}, { 3, -1, -1}, {-1, -1, -1}}, // 0   12  3
  // {{ 0, -1, -1}, { 1, -1, -1}, { 2,  3, -1}, {-1, -1, -1}}, // 0   1   23
  // {{ 0,  1,  2}, { 3, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 012 3
  // {{ 0,  1, -1}, { 2,  3, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 01  23
  // {{ 0, -1, -1}, { 1,  2,  3}, {-1, -1, -1}, {-1, -1, -1}}, // 0   123
  // // 0連続シフト
  // {{ 0,  1, -1}, { 0,  2, -1}, { 0,  3, -1}, {-1, -1, -1}}, // 01  02  03
  // {{ 0,  1, -1}, { 0,  2, -1}, { 3, -1, -1}, {-1, -1, -1}}, // 01  02  3
  // {{ 0,  1,  2}, { 0,  3, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 012 03
  // {{ 0,  1, -1}, { 0,  2,  3}, {-1, -1, -1}, {-1, -1, -1}}, // 01  023
  // // 1連続シフト
  // {{ 0,  1, -1}, { 1,  2, -1}, { 3, -1, -1}, {-1, -1, -1}}, // 01  12  3
  // {{ 0,  1, -1}, { 1,  2, -1}, { 1,  3, -1}, {-1, -1, -1}}, // 01  12  13
  // {{ 0, -1, -1}, { 1,  2, -1}, { 1,  3, -1}, {-1, -1, -1}}, // 0   12  13
  // {{ 0,  1, -1}, { 1,  2,  3}, {-1, -1, -1}, {-1, -1, -1}}, // 01  123
  // {{ 0,  1,  2}, { 1,  3, -1}, {-1, -1, -1}, {-1, -1, -1}}, // 012 13
  // // 2連続シフト
  // {{ 0, -1, -1}, { 1,  2, -1}, { 2,  3, -1}, {-1, -1, -1}}, // 0   12  23
  // {{ 0,  1,  2}, { 2,  3, -1}, {-1, -1, -1}, {-1, -1, -1}}  // 012 23
};

// カナ変換テーブル
typedef struct {
  uint32_t key;
  char kana[6];
} naginata_keymap;

const PROGMEM naginata_keymap ngmap[] = {
  // 清音
  {.key = B_J                      , .kana = "a"       }, // あ
  {.key = B_K                      , .kana = "i"       }, // い
  {.key = B_L                      , .kana = "u"       }, // う
  {.key = B_SHFT|B_O               , .kana = "e"       }, // え
  {.key = B_SHFT|B_N               , .kana = "o"       }, // お
  {.key = B_F                      , .kana = "ka"      }, // か
  {.key = B_W                      , .kana = "ki"      }, // き
  {.key = B_H                      , .kana = "ku"      }, // く
  {.key = B_S                      , .kana = "ke"      }, // け
  {.key = B_V                      , .kana = "ko"      }, // こ
  {.key = B_SHFT|B_U               , .kana = "sa"      }, // さ
  {.key = B_R                      , .kana = "si"      }, // し
  {.key = B_O                      , .kana = "su"      }, // す
  {.key = B_SHFT|B_A               , .kana = "se"      }, // せ
  {.key = B_B                      , .kana = "so"      }, // そ
  {.key = B_N                      , .kana = "ta"      }, // た
  {.key = B_SHFT|B_G               , .kana = "ti"      }, // ち
  {.key = B_SHFT|B_L               , .kana = "tu"      }, // つ
  {.key = B_E                      , .kana = "te"      }, // て
  {.key = B_D                      , .kana = "to"      }, // と
  {.key = B_M                      , .kana = "na"      }, // な
  {.key = B_SHFT|B_D               , .kana = "ni"      }, // に
  {.key = B_SHFT|B_W               , .kana = "nu"      }, // ぬ
  {.key = B_SHFT|B_R               , .kana = "ne"      }, // ね
  {.key = B_SHFT|B_J               , .kana = "no"      }, // の
  {.key = B_C                      , .kana = "ha"      }, // は
  {.key = B_X                      , .kana = "hi"      }, // ひ
  {.key = B_SHFT|B_X               , .kana = "hi"      }, // ひ
  {.key = B_SHFT|B_SCLN            , .kana = "hu"      }, // ふ
  {.key = B_P                      , .kana = "he"      }, // へ
  {.key = B_Z                      , .kana = "ho"      }, // ほ
  {.key = B_SHFT|B_Z               , .kana = "ho"      }, // ほ
  {.key = B_SHFT|B_F               , .kana = "ma"      }, // ま
  {.key = B_SHFT|B_B               , .kana = "mi"      }, // み
  {.key = B_SHFT|B_COMM            , .kana = "mu"      }, // む
  {.key = B_SHFT|B_S               , .kana = "me"      }, // め
  {.key = B_SHFT|B_K               , .kana = "mo"      }, // も
  {.key = B_SHFT|B_H               , .kana = "ya"      }, // や
  {.key = B_SHFT|B_P               , .kana = "yu"      }, // ゆ
  {.key = B_SHFT|B_I               , .kana = "yo"      }, // よ
  {.key = B_DOT                    , .kana = "ra"      }, // ら
  {.key = B_SHFT|B_E               , .kana = "ri"      }, // り
  {.key = B_I                      , .kana = "ru"      }, // る
  {.key = B_SLSH                   , .kana = "re"      }, // れ
  {.key = B_SHFT|B_SLSH            , .kana = "re"      }, // れ
  {.key = B_A                      , .kana = "ro"      }, // ろ
  {.key = B_SHFT|B_DOT             , .kana = "wa"      }, // わ
  {.key = B_SHFT|B_C               , .kana = "wo"      }, // を
  {.key = B_COMM                   , .kana = "nn"      }, // ん
  {.key = B_SCLN                   , .kana = "-"       }, // ー

  // 濁音
  {.key = B_J|B_F                  , .kana = "ga"      }, // が
  {.key = B_J|B_W                  , .kana = "gi"      }, // ぎ
  {.key = B_F|B_H                  , .kana = "gu"      }, // ぐ
  {.key = B_J|B_S                  , .kana = "ge"      }, // げ
  {.key = B_J|B_V                  , .kana = "go"      }, // ご
  {.key = B_F|B_U                  , .kana = "za"      }, // ざ
  {.key = B_J|B_R                  , .kana = "zi"      }, // じ
  {.key = B_F|B_O                  , .kana = "zu"      }, // ず
  {.key = B_J|B_A                  , .kana = "ze"      }, // ぜ
  {.key = B_J|B_B                  , .kana = "zo"      }, // ぞ
  {.key = B_F|B_N                  , .kana = "da"      }, // だ
  {.key = B_J|B_G                  , .kana = "di"      }, // ぢ
  {.key = B_F|B_L                  , .kana = "du"      }, // づ
  {.key = B_J|B_E                  , .kana = "de"      }, // で
  {.key = B_J|B_D                  , .kana = "do"      }, // ど
  {.key = B_J|B_C                  , .kana = "ba"      }, // ば
  {.key = B_J|B_X                  , .kana = "bi"      }, // び
  {.key = B_F|B_SCLN               , .kana = "bu"      }, // ぶ
  {.key = B_F|B_P                  , .kana = "be"      }, // べ
  {.key = B_J|B_Z                  , .kana = "bo"      }, // ぼ
  {.key = B_Q                      , .kana = "vu"      }, // ゔ
  {.key = B_SHFT|B_Q               , .kana = "vu"      }, // ゔ

  // 半濁音
  {.key = B_M|B_C                  , .kana = "pa"      }, // ぱ
  {.key = B_M|B_X                  , .kana = "pi"      }, // ぴ
  {.key = B_V|B_SCLN               , .kana = "pu"      }, // ぷ
  {.key = B_V|B_P                  , .kana = "pe"      }, // ぺ
  {.key = B_M|B_Z                  , .kana = "po"      }, // ぽ

  // 小書き
  {.key = B_Q|B_H                  , .kana = "xya"     }, // ゃ
  {.key = B_Q|B_P                  , .kana = "xyu"     }, // ゅ
  {.key = B_Q|B_I                  , .kana = "xyo"     }, // ょ
  {.key = B_Q|B_J                  , .kana = "xa"      }, // ぁ
  {.key = B_Q|B_K                  , .kana = "xi"      }, // ぃ
  {.key = B_Q|B_L                  , .kana = "xu"      }, // ぅ
  {.key = B_Q|B_O                  , .kana = "xe"      }, // ぇ
  {.key = B_Q|B_N                  , .kana = "xo"      }, // ぉ
  {.key = B_Q|B_DOT                , .kana = "xwa"     }, // ゎ
  {.key = B_G                      , .kana = "xtu"     }, // っ
  {.key = B_Q|B_S                  , .kana = "xke"     }, // ヶ
  {.key = B_Q|B_F                  , .kana = "xka"     }, // ヵ

  // 清音拗音 濁音拗音 半濁拗音
  {.key = B_R|B_H                  , .kana = "sya"     }, // しゃ
  {.key = B_R|B_P                  , .kana = "syu"     }, // しゅ
  {.key = B_R|B_I                  , .kana = "syo"     }, // しょ
  {.key = B_J|B_R|B_H              , .kana = "zya"     }, // じゃ
  {.key = B_J|B_R|B_P              , .kana = "zyu"     }, // じゅ
  {.key = B_J|B_R|B_I              , .kana = "zyo"     }, // じょ
  {.key = B_W|B_H                  , .kana = "kya"     }, // きゃ
  {.key = B_W|B_P                  , .kana = "kyu"     }, // きゅ
  {.key = B_W|B_I                  , .kana = "kyo"     }, // きょ
  {.key = B_J|B_W|B_H              , .kana = "gya"     }, // ぎゃ
  {.key = B_J|B_W|B_P              , .kana = "gyu"     }, // ぎゅ
  {.key = B_J|B_W|B_I              , .kana = "gyo"     }, // ぎょ
  {.key = B_G|B_H                  , .kana = "tya"     }, // ちゃ
  {.key = B_G|B_P                  , .kana = "tyu"     }, // ちゅ
  {.key = B_G|B_I                  , .kana = "tyo"     }, // ちょ
  {.key = B_J|B_G|B_H              , .kana = "dya"     }, // ぢゃ
  {.key = B_J|B_G|B_P              , .kana = "dyu"     }, // ぢゅ
  {.key = B_J|B_G|B_I              , .kana = "dyo"     }, // ぢょ
  {.key = B_D|B_H                  , .kana = "nya"     }, // にゃ
  {.key = B_D|B_P                  , .kana = "nyu"     }, // にゅ
  {.key = B_D|B_I                  , .kana = "nyo"     }, // にょ
  {.key = B_X|B_H                  , .kana = "hya"     }, // ひゃ
  {.key = B_X|B_P                  , .kana = "hyu"     }, // ひゅ
  {.key = B_X|B_I                  , .kana = "hyo"     }, // ひょ
  {.key = B_J|B_X|B_H              , .kana = "bya"     }, // びゃ
  {.key = B_J|B_X|B_P              , .kana = "byu"     }, // びゅ
  {.key = B_J|B_X|B_I              , .kana = "byo"     }, // びょ
  {.key = B_M|B_X|B_H              , .kana = "pya"     }, // ぴゃ
  {.key = B_M|B_X|B_P              , .kana = "pyu"     }, // ぴゅ
  {.key = B_M|B_X|B_I              , .kana = "pyo"     }, // ぴょ
  {.key = B_B|B_H                  , .kana = "mya"     }, // みゃ
  {.key = B_B|B_P                  , .kana = "myu"     }, // みゅ
  {.key = B_B|B_I                  , .kana = "myo"     }, // みょ
  {.key = B_E|B_H                  , .kana = "rya"     }, // りゃ
  {.key = B_E|B_P                  , .kana = "ryu"     }, // りゅ
  {.key = B_E|B_I                  , .kana = "ryo"     }, // りょ

  // 清音外来音 濁音外来音
  {.key = B_M|B_E|B_K              , .kana = "thi"     }, // てぃ
  {.key = B_M|B_E|B_P              , .kana = "thu"     }, // てゅ
  {.key = B_J|B_E|B_K              , .kana = "dhi"     }, // でぃ
  {.key = B_J|B_E|B_P              , .kana = "dhu"     }, // でゅ
  {.key = B_M|B_D|B_L              , .kana = "toxu"    }, // とぅ
  {.key = B_J|B_D|B_L              , .kana = "doxu"    }, // どぅ
  {.key = B_M|B_R|B_O              , .kana = "sye"     }, // しぇ
  {.key = B_M|B_G|B_O              , .kana = "tye"     }, // ちぇ
  {.key = B_J|B_R|B_O              , .kana = "zye"     }, // じぇ
  {.key = B_J|B_G|B_O              , .kana = "dye"     }, // ぢぇ
  {.key = B_V|B_SCLN|B_J           , .kana = "fa"      }, // ふぁ
  {.key = B_V|B_SCLN|B_K           , .kana = "fi"      }, // ふぃ
  {.key = B_V|B_SCLN|B_O           , .kana = "fe"      }, // ふぇ
  {.key = B_V|B_SCLN|B_N           , .kana = "fo"      }, // ふぉ
  {.key = B_V|B_SCLN|B_P           , .kana = "fyu"     }, // ふゅ
  {.key = B_V|B_K|B_O              , .kana = "ixe"     }, // いぇ
  {.key = B_V|B_L|B_K              , .kana = "wi"      }, // うぃ
  {.key = B_V|B_L|B_O              , .kana = "we"      }, // うぇ
  {.key = B_V|B_L|B_N              , .kana = "uxo"     }, // うぉ
  {.key = B_M|B_Q|B_J              , .kana = "va"      }, // ゔぁ
  {.key = B_M|B_Q|B_K              , .kana = "vi"      }, // ゔぃ
  {.key = B_M|B_Q|B_O              , .kana = "ve"      }, // ゔぇ
  {.key = B_M|B_Q|B_N              , .kana = "vo"      }, // ゔぉ
  {.key = B_M|B_Q|B_P              , .kana = "vuxyu"   }, // ゔゅ
  {.key = B_V|B_H|B_J              , .kana = "kuxa"    }, // くぁ
  {.key = B_V|B_H|B_K              , .kana = "kuxi"    }, // くぃ
  {.key = B_V|B_H|B_O              , .kana = "kuxe"    }, // くぇ
  {.key = B_V|B_H|B_N              , .kana = "kuxo"    }, // くぉ
  {.key = B_V|B_H|B_DOT            , .kana = "kuxwa"   }, // くゎ
  {.key = B_F|B_H|B_J              , .kana = "guxa"    }, // ぐぁ
  {.key = B_F|B_H|B_K              , .kana = "guxi"    }, // ぐぃ
  {.key = B_F|B_H|B_O              , .kana = "guxe"    }, // ぐぇ
  {.key = B_F|B_H|B_N              , .kana = "guxo"    }, // ぐぉ
  {.key = B_F|B_H|B_DOT            , .kana = "guxwa"   }, // ぐゎ
  {.key = B_V|B_L|B_J              , .kana = "tsa"     }, // つぁ

  // 追加
  {.key = B_SHFT            , .kana = " "},
  {.key = B_V|B_SHFT        , .kana = ","SS_TAP(X_ENTER)},
  {.key = B_M|B_SHFT        , .kana = "."SS_TAP(X_ENTER)},
  {.key = B_U               , .kana = SS_TAP(X_BACKSPACE)},

  // enter
  {.key = B_V|B_M           , .kana = SS_TAP(X_ENTER)},
  // enter+シフト(連続シフト)
  {.key = B_SHFT|B_V|B_M    , .kana = SS_TAP(X_ENTER)},

  // 非標準の変換
  {.key = B_X|B_C|B_M       , .kana = "pyu"     }, // ピュ

  // 別途処理しないといけない変換
  {.key = B_T               , .kana = ""}, //
  {.key = B_Y               , .kana = ""}, //
  {.key = B_SHFT|B_T        , .kana = ""}, //
  {.key = B_SHFT|B_Y        , .kana = ""}, //
  {.key = B_H|B_J           , .kana = ""}, //　かなオン
  {.key = B_F|B_G           , .kana = ""}, //　かなオフ

};

// 薙刀式のレイヤー、オンオフするキー
void set_naginata(uint8_t layer, uint16_t *onk, uint16_t *offk) {
  naginata_layer = layer;
  ngon_keys[0] = *onk;
  ngon_keys[1] = *(onk+1);
  ngoff_keys[0] = *offk;
  ngoff_keys[1] = *(offk+1);

  naginata_config.raw = eeconfig_read_user();
  if (naginata_config.os != NG_WIN && naginata_config.os != NG_MAC && naginata_config.os != NG_LINUX) {
    naginata_config.os = NG_WIN;
    naginata_config.live_conv = 1;
    naginata_config.tategaki = 1;
    naginata_config.kouchi_shift = 0;
    eeconfig_update_user(naginata_config.raw);
  }
  ng_set_unicode_mode(naginata_config.os);

  initializeSet(&ngpressd);
  initializeList(&nginput);
}

// 薙刀式をオン
void naginata_on(void) {
  is_naginata = true;
  naginata_clear();
  layer_on(naginata_layer);

  tap_code(KC_LANGUAGE_1); // Mac
  tap_code(KC_INTERNATIONAL_4); // Win
}

// 薙刀式をオフ
void naginata_off(void) {
  is_naginata = false;
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
static int8_t n_modifier = 0;

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
  n_modifier = 0;
  nkeypress = 0;
  fghj_buf = 0;
  initializeSet(&ngpressd);
  initializeList(&nginput);
}

// 編集モードの判定
bool check_henshu() {
  bool h = false;
  if (keycomb == (B_D | B_F) ||
      keycomb == (B_J | B_K) ||
      keycomb == (B_C | B_V) ||
      keycomb == (B_M | B_COMM) ||
      keycomb == (B_U | B_I) ||
      keycomb == (B_E | B_R))
    h = true;
  if ((keycomb & (B_D | B_F)) != (B_D | B_F) &&
      (keycomb & (B_J | B_K)) != (B_J | B_K) &&
      (keycomb & (B_C | B_V)) != (B_C | B_V) &&
      (keycomb & (B_M | B_COMM)) != (B_M | B_COMM) &&
      (keycomb & (B_U | B_I)) != (B_U | B_I) &&
      (keycomb & (B_E | B_R)) != (B_E | B_R))
    h = false;

  return h;
}

// #define LOG_PROCESS_NAGINATA
// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {
  #if defined(CONSOLE_ENABLE) && defined(LOG_PROCESS_NAGINATA)
  uprintf(">process_naginata, is_naginata=%u, keycode=%u, press=%u\n", is_naginata, keycode, record->event.pressed);
  #endif

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
    return enable_naginata(keycode, record);

  if (process_modifier(keycode, record))
    return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_SHFT ... NG_SHFT2:
      case NG_Q ... NG_SLSH:
        addToSet(&ngpressd, keycode);

        // 4文字目の入力
        if (ngpressd.size > NKEYS || nginput.size >= NKEYS) {
          int ntyped = naginata_type(true);

          for (int i = 0; i < ntyped; i++) {
            removeFromListAt(&nginput, 0);
          }
          // 連続シフト
          // 組み合わせがないかもしれないのに連続シフトしている
          // バッファ内のキーを組み合わせる
          uint32_t keycomb_buf = 0UL;
          for (uint8_t k = 0; k < nginput.size; k++) {
            keycomb_buf |= ng_key[nginput.elements[k].keycode - NG_Q];
          }
          keycomb_buf ||= ng_key[keycode - NG_Q];
          if (includeSet(&ngpressd, NG_SHFT) >= 0 && includeList(&nginput, NG_SHFT) < 0) {            
            bool isExist = false;
            for (uint16_t k = 0; k < sizeof ngmap / sizeof bngmap; k++) {
              memcpy_P(&bngmap, &ngmap[k], sizeof(bngmap));
              if (keycomb_buf == (bngmap.key & keycomb_buf)) {
                isExist = true;
                break;
              }
            }
            if (isExist) {
              Keystroke ks = (Keystroke){.keycode = NG_SHFT, .pressTime = record->event.time, .releaseTime = 0};
              addToListAt(&nginput, &ks, 0);
            }
          } else if (includeSet(&ngpressd, NG_SHFT2) >= 0 && includeList(&nginput, NG_SHFT2) < 0) {
            Keystroke ks = (Keystroke){.keycode = NG_SHFT2, .pressTime = record->event.time, .releaseTime = 0};
            addToListAt(&nginput, &ks, 0);
          } else if (includeSet(&ngpressd, NG_F) >= 0 && includeList(&nginput, NG_F) < 0) {
            Keystroke ks = (Keystroke){.keycode = NG_F, .pressTime = record->event.time, .releaseTime = 0};
            addToListAt(&nginput, &ks, 0);
          } else if (includeSet(&ngpressd, NG_V) >= 0 && includeList(&nginput, NG_V) < 0) {
            Keystroke ks = (Keystroke){.keycode = NG_V, .pressTime = record->event.time, .releaseTime = 0};
            addToListAt(&nginput, &ks, 0);
          } else if (includeSet(&ngpressd, NG_J) >= 0 && includeList(&nginput, NG_J) < 0) {
            Keystroke ks = (Keystroke){.keycode = NG_J, .pressTime = record->event.time, .releaseTime = 0};
            addToListAt(&nginput, &ks, 0);
          } else if (includeSet(&ngpressd, NG_M) >= 0 && includeList(&nginput, NG_M) < 0) {
            Keystroke ks = (Keystroke){.keycode = NG_M, .pressTime = record->event.time, .releaseTime = 0};
            addToListAt(&nginput, &ks, 0);
          }

          keycomb = 0UL;
          for (uint8_t i = 0; i < nginput.size; i++) {
            keycomb |= ng_key[nginput.elements[i].keycode - NG_Q];
          }
        }

        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        if (is_henshu) {
          if (exec_henshu(keycomb))
            return true;
        }

        is_henshu = check_henshu();
        
        Keystroke ks = (Keystroke){.keycode = keycode, .pressTime = record->event.time, .releaseTime = 0};
        addToList(&nginput, &ks);

        /*
        press時の早期確定
        1キー押す、絞り込めないので何もしない
        2キー目
          0 1の場合(3キーの可能性)
            0 1 2 なら、0 1は確定していい
            0 12  なら、0は確定していい
          01なら確定できない
            01 2
            01 02
            01 12
            012
        3キー目
          確定していいが、シフトを残すかどうかを別途検討しないといけない
        */
        // check_eager_input() == 1でも確定していいはずなんだけど、プレス時は押している時間が0なので、0 1 2で変換される。
        // if (nginput.size > 1 && check_eager_input() < 1) {
        //   int ntyped = naginata_type(true);
        //   for (int i = 0; i < ntyped; i++) {
        //     removeFromListAt(&nginput, 0);
        //   }

        //   // 連続シフト

        //   keycomb = 0UL;
        //   for (uint8_t i = 0; i < nginput.size; i++) {
        //     keycomb |= ng_key[nginput.elements[i].keycode - NG_Q];
        //   }
        // }
  
        #if defined(CONSOLE_ENABLE) && defined(LOG_PROCESS_NAGINATA)
        uprintf("<process_naginata return=false, ngpressd.size=%u\n", ngpressd.size);
        #endif
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case NG_Q ... NG_SHFT2:  
        removeFromSet(&ngpressd, keycode);        
        keycomb &= ~ng_key[keycode - NG_Q]; // キーの重ね合わせ
        is_henshu = check_henshu();

        for (uint8_t i = 0; i < nginput.size; i++) { //　連続シフト　もも
          if (keycode == nginput.elements[i].keycode && nginput.elements[i].releaseTime == 0) {
            nginput.elements[i].releaseTime = record->event.time;
            break;
          }
        }
        // 全部キーを離したら
        if (ngpressd.size == 0 && nginput.size > 0) {
          if (henshu_done) { // 編集モードを実行した後のDF等は変換しない
            henshu_done = false;
            initializeList(&nginput);
            keycomb = 0UL;
            return false;
          }
          naginata_type(false);
          initializeList(&nginput);
          keycomb = 0UL;
        }
        #if defined(CONSOLE_ENABLE) && defined(LOG_PROCESS_NAGINATA)
        uprintf("<process_naginata return=false, ngpressd.size=%u\n", ngpressd.size);
        #endif
        return false;
        break;
    }
  }
  #if defined(CONSOLE_ENABLE) && defined(LOG_PROCESS_NAGINATA)
  uprintf("<process_naginata return=true\n");
  #endif

  return true;
}

// #define LOG_NAGINATA_TYPE
// キー入力を文字に変換して出力する
// partial 部分変換するかどうか
// 戻り値 変換処理したキーの数
uint8_t naginata_type(bool partial) {
  #if defined(CONSOLE_ENABLE) && defined(LOG_NAGINATA_TYPE)
  uprintf(">naginata_type nginput.sze=%u\n", nginput.sze);
  for (uint8_t i = 0; i < nginput.size; i++)
    uprintf(" naginata_type key=%lu, pressTime=%lu, releaseTime=%lu\n",  nginput.elements[i].keycode,  nginput.elements[i].pressTime,  nginput.elements[i].releaseTime);
  #endif

  if (nginput.size == 1 && nginput.elements[0].keycode == NG_SHFT2) {
    tap_code(KC_ENT);
    return 1;
  }

  naginata_keymap bngmap; // PROGMEM buffer

  uint8_t keySize = evaluate();

  // かなへ変換する
  if (partial) keySize = 1; // partialの時は、最初の組み合わせだけ出力する
  
  for (uint8_t i = 0; i < keySize; i++) {
    // バッファ内のキーを組み合わせる
    uint32_t keycomb_buf = 0UL;
    for (uint8_t j = 0; j < doujiSize[i]; j++) {
      keycomb_buf |= ng_key[ngingroup[i][j].keycode - NG_Q];
    }
    switch (keycomb_buf) {
      case B_T:
        ng_left(1);
        break;
      case B_Y:
        ng_right(1);
        break;
      case B_SHFT|B_T:
        register_code(KC_LSFT);
        ng_left(1);
        unregister_code(KC_LSFT);
        break;
      case B_SHFT|B_Y:
        register_code(KC_LSFT);
        ng_right(1);
        unregister_code(KC_LSFT);
        break;
      case B_H|B_J:
        naginata_on();
        break;
      case B_F|B_G:
        naginata_off();
        break;
      default:
        for (uint16_t j = 0; j < sizeof ngmap / sizeof bngmap; j++) {
          memcpy_P(&bngmap, &ngmap[j], sizeof(bngmap));
          if (keycomb_buf == bngmap.key) {
            send_string(bngmap.kana);
            #if defined(CONSOLE_ENABLE) && defined(LOG_NAGINATA_TYPE)
            uprintf(" send_string %s\n", bngmap.kana);
            #endif
          }
        }
        break;
    }
  }

  if (partial) {
    return doujiSize[0];
  } else {
    return nginput.size;
  }

  #if defined(CONSOLE_ENABLE) && defined(LOG_NAGINATA_TYPE)
  uprintf("<naginata_type\n");
  #endif
}

// 早期確定できるかどうか判定する
// 同時押しがありえるかどうか
uint8_t check_eager_input() {
  naginata_keymap bngmap; // PROGMEM buffer
  uint8_t noc = 0;

  // バッファ内のキーを組み合わせる
  uint32_t keycomb_buf = 0UL;
  for (uint8_t k = 0; k < nginput.size; k++) {
    keycomb_buf |= ng_key[nginput.elements[k].keycode - NG_Q];
  }
  // 辞書に存在するかチェック
  for (uint16_t k = 0; k < sizeof ngmap / sizeof bngmap; k++) {
    memcpy_P(&bngmap, &ngmap[k], sizeof(bngmap));
    if (keycomb_buf == (bngmap.key & keycomb_buf)) {
      noc++;
    }
  }

  return noc;
}

// #define LOG_EVALUATE
// ngingroupを作って中で一番評価値が高い組み合わせngingroupに入れる
uint8_t evaluate() {
  #if defined(CONSOLE_ENABLE) && defined(LOG_EVALUATE)
  uprintf(">evaluate nginput.size=%u\n", nginput.size);
  #endif

  Keystroke tmpgroup[NKEYS][NDOUJI]; // 入力バッファを同時押しの組み合わせでグループ化
  uint32_t score = 0;
  uint32_t maxScore = 0;
  uint8_t tdoujiSize[NKEYS] = {0}; // ngingroupの配列のサイズ

  naginata_keymap bngmap; // PROGMEM buffer
  int8_t bcombi = 0; // PROGMEM buffer
  bool isExist = false;
  uint8_t keySize = 0;

  for (uint8_t i = COMBINDEX[nginput.size - 1]; i < COMBINDEX[nginput.size]; i++) { // 組み合わせごとに
    #if defined(CONSOLE_ENABLE) && defined(LOG_EVALUATE)
    uprintf(" evaluate COMBI[%u]\n", i);
    #endif
    uint8_t tkeySize = 0;
    for (uint8_t j = 0; j < NKEYS; j++) { // 組み合わせの順番に
      #if defined(CONSOLE_ENABLE) && defined(LOG_EVALUATE)
      uprintf(" evaluate   j=%u\n", j);
      #endif
      memcpy_P(&bcombi, &COMBI[i][j][0], sizeof(bcombi));
      if (bcombi == -1) {
        #if defined(CONSOLE_ENABLE) && defined(LOG_EVALUATE)
        uprintf(" evaluate   j=%u, break\n", j);
        #endif
        break;
      }

      // ngingroupを作る
      uint8_t tdouji = 0;
      for (uint8_t k = 0; k < NDOUJI; k++) { // 同時に押しているキー
        #if defined(CONSOLE_ENABLE) && defined(LOG_EVALUATE)
        uprintf(" evaluate     k=%u\n", k);
        #endif
        memcpy_P(&bcombi, &COMBI[i][j][k], sizeof(bcombi));
        if (bcombi == -1) {
          break;
        } else {
          tmpgroup[j][k] = nginput.elements[bcombi];
          tdouji++;
        }
      }
      tdoujiSize[j] = tdouji; //あとで辞書にない可能性もあるけど、オーバーライトされるか
      #if defined(CONSOLE_ENABLE) && defined(LOG_EVALUATE)
      uprintf(" evaluate   tdouji=%u\n", tdouji);
      for (uint8_t k = 0; k < tdoujiSize[j]; k++) {
        uprintf(" evaluate   tmpgroup %u,%u key=%lu, pressTime=%lu, releaseTime=%lu\n", j, k, tmpgroup[j][k].keycode,  tmpgroup[j][k].pressTime,  tmpgroup[j][k].releaseTime);
      }
      #endif

      // バッファ内のキーを組み合わせる
      uint32_t keycomb_buf = 0UL;
      for (uint8_t k = 0; k < tdouji; k++) {
        keycomb_buf |= ng_key[tmpgroup[j][k].keycode - NG_Q];
      }
      // 辞書に存在するかチェック
      isExist = false;
      for (uint16_t k = 0; k < sizeof ngmap / sizeof bngmap; k++) {
        memcpy_P(&bngmap, &ngmap[k], sizeof(bngmap));
        if (keycomb_buf == bngmap.key) {
          isExist = true;
          break;
        }
      }
      #if defined(CONSOLE_ENABLE) && defined(LOG_EVALUATE)
      uprintf(" evaluate   isExist=%u\n", isExist);
      #endif
      if (!isExist) {
        break; // 辞書になければ追加しない
      }
      tkeySize++;
    } // j

    if (!isExist) {
      continue; // 辞書になければ追加しない
    }

    uint32_t s = 0;
    for (uint8_t j = 0; j < tkeySize; j++) {
      s += scoring(tmpgroup[j], tdoujiSize[j]);
    }
    score = s / tkeySize;

    #if defined(CONSOLE_ENABLE)
    uprintf(" evaluate combi=%u, score=%lu\n", i, score);
    for (uint8_t j = 0; j < tkeySize; j++) {
      uprintf(" evaluate   douji=%u\n", tdoujiSize[j]);
      for (uint8_t k = 0; k < tdoujiSize[j]; k++) {
        uprintf(" evaluate     tmpgroup %u,%u,%u key=%lu, pressTime=%lu, releaseTime=%lu\n", i, j, k, tmpgroup[j][k].keycode,  tmpgroup[j][k].pressTime,  tmpgroup[j][k].releaseTime);
      }
    }
    #endif

    if (score >= maxScore) {
      maxScore = score;
      keySize = tkeySize;
      for (uint8_t j = 0; j < keySize; j++) {
        doujiSize[j] = tdoujiSize[j];
        for (uint8_t k = 0; k < doujiSize[j]; k++) {
          ngingroup[j][k] = tmpgroup[j][k];
        }
      }
    }
  }
  
  #if defined(CONSOLE_ENABLE)
  uprintf("<evaluate return score=%lu\n", maxScore);
  #endif

  return keySize;

}

// #define LOG_SCORING
uint32_t scoring(Keystroke ks[], uint8_t size) {
  uint16_t now = timer_read();
  #if defined(CONSOLE_ENABLE) && defined(LOG_SCORING)
  uprintf(">scoring size=%u\n", size);
  for (uint8_t i = 0; i < size; i++) {
    uprintf(" scoring key=%lu, pressTime=%lu, releaseTime=%lu\n", ks[i].keycode, ks[i].pressTime, ks[i].releaseTime);
  }
  #endif

  if (size == 1) { // 単打の重み
    #if defined(CONSOLE_ENABLE) && defined(LOG_SCORING)
    uprintf("<scoring return=%u\n", 100);
    #endif
    return 100; // 単打を優先するか、同時押しを優先するかをチューニングする
  }

  // 前置シフト
  if (!naginata_config.kouchi_shift && (ks[1].keycode == NG_SHFT || ks[1].keycode == NG_SHFT2)) {
    return 0;
  }

  // 点数=キー同士が重なる時間を、それぞれのキーを押している時間で割る
  uint16_t s2 = ks[0].pressTime;
  uint16_t e2 = ks[0].releaseTime > 0 ? ks[0].releaseTime : now;
  for (uint8_t i = 1; i < size; i++) {
    if (ks[i].pressTime > s2) {
      s2 = ks[i].pressTime;
    }
    if (ks[i].releaseTime > 0 && ks[i].releaseTime < e2) {
      e2 = ks[i].releaseTime;
    }
  }
  #if defined(CONSOLE_ENABLE) && defined(LOG_SCORING)
  uprintf(" scoring s2=%lu, e2=%lu\n", s2, e2);
  #endif
  uint32_t w = e2 - s2; // キーが重なっている時間、uint16_tにするとおかしくなる？
  uint32_t s = 0;
  if (s2 < e2) {
    for (uint8_t i = 0; i < size; i++) {
      s += w * 1000 / ((ks[i].releaseTime > 0 ? ks[i].releaseTime : now) - ks[i].pressTime);
    }
  }

  #if defined(CONSOLE_ENABLE) && defined(LOG_SCORING)
  uprintf("<scoring return=%lu, w=%lu\n", s, w);
  #endif

  return s;
}

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
      if (naginata_config.tategaki)
        tap_code16(LCMD(KC_LEFT));
      else
        tap_code16(LCMD(KC_DOWN));
      break;
  }
}

bool exec_henshu(uint32_t keycomb) {
  switch (keycomb) {
    #ifndef NG_NO_HENSHU1
    case B_J|B_K|B_Q: // ^{End}
      ng_eof();
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_W: // 『』{改行}{↑}
      ng_send_unicode_string_P(PSTR("『』"));
      ng_up(1);
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_R: // ^s
      ng_save();
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_T: // ・
      ng_send_unicode_string_P(PSTR("・"));
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_A: // ……{改行}
      ng_send_unicode_string_P(PSTR("……"));
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_S: // (){改行}{↑}
      ng_send_unicode_string_P(PSTR("()"));
      ng_up(1);
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_D: // ？{改行}
      ng_send_unicode_string_P(PSTR("？"));
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_F: // 「」{改行}{↑}
      ng_send_unicode_string_P(PSTR("「」"));
      ng_up(1);
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_G: // 《》{改行}{↑}
      ng_send_unicode_string_P(PSTR("《》"));
      ng_up(1);
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_Z: // ――{改行}
      ng_send_unicode_string_P(PSTR("――"));
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_X: // 【】{改行}{↑}
      ng_send_unicode_string_P(PSTR("【】"));
      ng_up(1);
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_C: // ！{改行}
      ng_send_unicode_string_P(PSTR("！"));
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_V: // {改行}{↓}
      tap_code(KC_ENT);
      ng_down(1);
      henshu_done = true;
      return true;
      break;
    case B_J|B_K|B_B: // {改行}{←}
      tap_code(KC_ENT);
      ng_left(1);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_Y: // {Home}
      ng_home();
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_U: // +{End}{BS}
      register_code(KC_LSFT);
      ng_end();
      unregister_code(KC_LSFT);
      tap_code(KC_BSPC);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_I: // {vk1Csc079}
      ng_saihenkan();
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_O: // {Del}
      tap_code(KC_DEL);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_P: // {Esc 3}
      tap_code(KC_ESC);
      tap_code(KC_ESC);
      tap_code(KC_ESC);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_H: // {Enter}{End}
      tap_code(KC_ENT);
      ng_end();
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_J: // {↑}
      ng_up(1);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_K: // +{↑}
      register_code(KC_LSFT);
      ng_up(1);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_L: // +{↑ 7}
      register_code(KC_LSFT);
      ng_up(7);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_SCLN: // ^i
      ng_katakana();
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_N: // {End}
      ng_end();
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_M: // {↓}
      ng_down(1);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_COMM: // +{↓}
      register_code(KC_LSFT);
      ng_down(1);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_DOT: // +{↓ 7}
      register_code(KC_LSFT);
      ng_down(7);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_D|B_F|B_SLSH: // ^u
      ng_hiragana();
      henshu_done = true;
      return true;
      break;
    #endif
    #ifndef NG_NO_HENSHU2
    case B_M|B_COMM|B_Q: // {Home}{→}{End}{Del 4}{←}
      ng_home();
      ng_right(1);
      ng_end();
      tap_code(KC_DEL);
      tap_code(KC_DEL);
      tap_code(KC_DEL);
      tap_code(KC_DEL);
      ng_left(1);
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_W: // ^x『^v』{改行}{Space}+{↑}^x
      ng_cut();
      ng_send_unicode_string_P(PSTR("『"));
      ng_paste();
      ng_send_unicode_string_P(PSTR("』"));
      tap_code(KC_SPC);
      register_code(KC_LSFT);
      ng_up(1);
      unregister_code(KC_LSFT);
      ng_cut();
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_E: // {Home}{改行}{Space 3}{←}
      ng_home();
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      tap_code(KC_SPC);
      tap_code(KC_SPC);
      ng_left(1);
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_R: // {Space 3}
      tap_code(KC_SPC);
      tap_code(KC_SPC);
      tap_code(KC_SPC);
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_T: // 〇{改行}
      ng_send_unicode_string_P(PSTR("〇"));
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_A: // {Home}{→}{End}{Del 2}{←}
      ng_home();
      ng_right(1);
      ng_end();
      tap_code(KC_DEL);
      tap_code(KC_DEL);
      ng_left(1);
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_S: // ^x(^v){改行}{Space}+{↑}^x
      ng_cut();
      ng_send_unicode_string_P(PSTR("("));
      ng_paste();
      ng_send_unicode_string_P(PSTR(")"));
      tap_code(KC_SPC);
      register_code(KC_LSFT);
      ng_up(1);
      unregister_code(KC_LSFT);
      ng_cut();
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_D: // {Home}{改行}{Space 1}{←}
      ng_home();
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      ng_left(1);
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_F: // ^x「^v」{改行}{Space}+{↑}^x
      ng_cut();
      ng_send_unicode_string_P(PSTR("「"));
      ng_paste();
      ng_send_unicode_string_P(PSTR("」"));
      tap_code(KC_SPC);
      register_code(KC_LSFT);
      ng_up(1);
      unregister_code(KC_LSFT);
      ng_cut();
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_G: // ^x｜{改行}^v《》{改行}{↑}{Space}+{↑}^x
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
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_Z: // 　　　×　　　×　　　×{改行 2}
      ng_send_unicode_string_P(PSTR("　　　×　　　×　　　×"));
      tap_code(KC_ENT);
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_X: // ^x【^v】{改行}{Space}+{↑}^x
      ng_cut();
      ng_send_unicode_string_P(PSTR("【"));
      ng_paste();
      ng_send_unicode_string_P(PSTR("】"));
      tap_code(KC_SPC);
      register_code(KC_LSFT);
      ng_up(1);
      unregister_code(KC_LSFT);
      ng_cut();
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_C: // ／{改行}
      ng_send_unicode_string_P(PSTR("／"));
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_V: // {改行}{End}{改行}「」{改行}{↑}
      tap_code(KC_ENT);
      ng_end();
      tap_code(KC_ENT);
      ng_send_unicode_string_P(PSTR("「」"));
      ng_up(1);
      henshu_done = true;
      return true;
      break;
    case B_M|B_COMM|B_B: // {改行}{End}{改行}{Space}
      tap_code(KC_ENT);
      ng_end();
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_Y: // +{Home}
      register_code(KC_LSFT);
      ng_home();
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_U: // ^x
      ng_cut();
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_I: // ^v
      ng_paste();
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_O: // ^y
      ng_redo();
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_P: // ^z
      ng_undo();
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_H: // ^c
      ng_copy();
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_J: // {→}
      ng_right(1);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_K: // +{→}
      register_code(KC_LSFT);
      ng_right(1);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_L: // +{→ 5}
      register_code(KC_LSFT);
      ng_right(5);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_SCLN: // +{→ 20}
      register_code(KC_LSFT);
      ng_right(20);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_N: // +{End}
      register_code(KC_LSFT);
      ng_end();
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_M: // {←}
      ng_left(1);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_COMM: // +{←}
      register_code(KC_LSFT);
      ng_left(1);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_DOT: // +{← 5}
      register_code(KC_LSFT);
      ng_left(5);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    case B_C|B_V|B_SLSH: // +{← 20}
      register_code(KC_LSFT);
      ng_left(20);
      unregister_code(KC_LSFT);
      henshu_done = true;
      return true;
      break;
    #endif
  // 固有名詞
    #ifndef NG_NO_KOYUMEISHI
    case B_U|B_I|B_W: // 臨兵闘者皆陣烈在前
      ng_send_unicode_string_P(PSTR("臨兵闘者皆陣烈在前"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_E: // 天狗
      ng_send_unicode_string_P(PSTR("天狗"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_R: // シンイチ
      ng_send_unicode_string_P(PSTR("シンイチ"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_T: // ネムカケ
      ng_send_unicode_string_P(PSTR("ネムカケ"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_A: // 三神
      ng_send_unicode_string_P(PSTR("三神"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_S: // 峯
      ng_send_unicode_string_P(PSTR("峯"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_D: // 小鴉
      ng_send_unicode_string_P(PSTR("小鴉"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_F: // 光太郎
      ng_send_unicode_string_P(PSTR("光太郎"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_Z: // 火よ、在れ
      ng_send_unicode_string_P(PSTR("火よ、在れ"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_X: // 火の剣
      ng_send_unicode_string_P(PSTR("火の剣"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_C: // 罵詈雑
      ng_send_unicode_string_P(PSTR("罵詈雑"));
      henshu_done = true;
      return true;
      break;
    case B_U|B_I|B_V: // 心の闇
      ng_send_unicode_string_P(PSTR("心の闇"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_Y: // 才一
      ng_send_unicode_string_P(PSTR("才一"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_U: // さくら
      ng_send_unicode_string_P(PSTR("さくら"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_I: // 酒田
      ng_send_unicode_string_P(PSTR("酒田"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_H: // 鞍馬
      ng_send_unicode_string_P(PSTR("鞍馬"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_J: // 青鬼
      ng_send_unicode_string_P(PSTR("青鬼"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_K: // 百地
      ng_send_unicode_string_P(PSTR("百地"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_SCLN: // 不動金縛りの術
      ng_send_unicode_string_P(PSTR("不動金縛りの術"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_B: // 鬼塚
      ng_send_unicode_string_P(PSTR("鬼塚"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_N: // 赤石
      ng_send_unicode_string_P(PSTR("赤石"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_M: // 八幡
      ng_send_unicode_string_P(PSTR("八幡"));
      henshu_done = true;
      return true;
      break;
    case B_E|B_R|B_DOT: // 霊槍
      ng_send_unicode_string_P(PSTR("霊槍"));
      henshu_done = true;
      return true;
      break;
    #endif  
  }

  return false;
}