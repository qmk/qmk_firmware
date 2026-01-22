/* Copyright 2018-2019 eswai <@eswai>
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
#include "naginata.h"

#if !defined(__AVR__)
  #include <string.h>
  #define memcpy_P(des, src, len) memcpy(des, src, len)
#endif

#define NGBUFFER 5 // バッファのサイズ

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static bool is_naginata = false; // 薙刀式がオンかオフか
static uint8_t naginata_layer = 0; // レイヤー番号
static uint8_t n_modifier = 0; // 押しているmodifierキーの数
static uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。

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

// 文字入力バッファ
static uint16_t ninputs[NGBUFFER];

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
};

// 薙刀式カナ変換テーブル
// 順序つき
#ifdef NAGINATA_JDOUJI
typedef struct {
  uint32_t key[3];
  char kana[5];
} naginata_keymap_ordered;
#endif

// 順序なし
typedef struct {
  uint32_t key;
  char kana[5];
} naginata_keymap;

// 順序なしロング
typedef struct {
  uint32_t key;
  char kana[15];
} naginata_keymap_long;

// 順序なしUNICODE
typedef struct {
  uint32_t key;
  char kana[10];
} naginata_keymap_unicode;

#ifdef NAGINATA_JDOUJI
const PROGMEM naginata_keymap_ordered ngmapo[] = {
  {.key = {NG_K, NG_E, 0}   , .kana = "ite"},
  {.key = {NG_L, NG_D, 0}   , .kana = "uto"},
};
#endif

const PROGMEM naginata_keymap ngmap[] = {
  // 単独
  {.key = B_Q               , .kana = "vu"},
  {.key = B_W               , .kana = "ha"},
  {.key = B_E               , .kana = "te"},
  {.key = B_R               , .kana = "si"},
  {.key = B_T               , .kana = SS_TAP(X_LEFT)},
  {.key = B_Y               , .kana = SS_TAP(X_RIGHT)},
  {.key = B_U               , .kana = SS_TAP(X_BSPACE)},
  {.key = B_I               , .kana = "ru"},
  {.key = B_O               , .kana = "su"},
  {.key = B_P               , .kana = "he"},
  {.key = B_A               , .kana = "ro"},
  {.key = B_S               , .kana = "ki"},
  {.key = B_D               , .kana = "to"},
  {.key = B_F               , .kana = "ka"},
  {.key = B_G               , .kana = "ltu"},
  {.key = B_H               , .kana = "ku"},
  {.key = B_J               , .kana = "a"},
  {.key = B_K               , .kana = "i"},
  {.key = B_L               , .kana = "u"},
  {.key = B_SCLN            , .kana = "-"},
  {.key = B_Z               , .kana = "ho"},
  {.key = B_X               , .kana = "hi"},
  {.key = B_C               , .kana = "ke"},
  {.key = B_V               , .kana = "ko"},
  {.key = B_B               , .kana = "so"},
  {.key = B_N               , .kana = "ta"},
  {.key = B_M               , .kana = "na"},
  {.key = B_COMM            , .kana = "nn"},
  {.key = B_DOT             , .kana = "ra"},
  {.key = B_SLSH            , .kana = "re"},
  {.key = B_SHFT            , .kana = " "},

  // シフト
  {.key = B_SHFT|B_Q        , .kana = "vu"},
  {.key = B_SHFT|B_W        , .kana = "mi"},
  {.key = B_SHFT|B_E        , .kana = "ri"},
  {.key = B_SHFT|B_R        , .kana = "me"},
  {.key = B_SHFT|B_U        , .kana = "sa"},
  {.key = B_SHFT|B_I        , .kana = "yo"},
  {.key = B_SHFT|B_O        , .kana = "yu"},
  {.key = B_SHFT|B_P        , .kana = "e"},
  {.key = B_SHFT|B_A        , .kana = "se"},
  {.key = B_SHFT|B_S        , .kana = "ne"},
  {.key = B_SHFT|B_D        , .kana = "ni"},
  {.key = B_SHFT|B_F        , .kana = "ma"},
  {.key = B_SHFT|B_G        , .kana = "ti"},
  {.key = B_SHFT|B_H        , .kana = "wa"},
  {.key = B_SHFT|B_J        , .kana = "no"},
  {.key = B_SHFT|B_K        , .kana = "mo"},
  {.key = B_SHFT|B_L        , .kana = "tu"},
  {.key = B_SHFT|B_SCLN     , .kana = "ya"},
  {.key = B_SHFT|B_Z        , .kana = "ho"},
  {.key = B_SHFT|B_X        , .kana = "hi"},
  {.key = B_SHFT|B_C        , .kana = "wo"},
  {.key = B_SHFT|B_V        , .kana = ","},
  {.key = B_SHFT|B_B        , .kana = "nu"},
  {.key = B_SHFT|B_N        , .kana = "o"},
  {.key = B_SHFT|B_M        , .kana = "."SS_TAP(X_ENTER)},
  {.key = B_SHFT|B_COMM     , .kana = "mu"},
  {.key = B_SHFT|B_DOT      , .kana = "hu"},
  {.key = B_SHFT|B_SLSH     , .kana = "re"},

  // 濁音
  {.key = B_J|B_W           , .kana = "ba"},
  {.key = B_J|B_E           , .kana = "de"},
  {.key = B_J|B_R           , .kana = "ji"},
  {.key = B_F|B_U           , .kana = "za"},
  {.key = B_F|B_O           , .kana = "zu"},
  {.key = B_F|B_P           , .kana = "be"},
  {.key = B_J|B_A           , .kana = "ze"},
  {.key = B_J|B_S           , .kana = "gi"},
  {.key = B_J|B_D           , .kana = "do"},
  {.key = B_J|B_F           , .kana = "ga"},
  {.key = B_J|B_G           , .kana = "du"},
  {.key = B_F|B_H           , .kana = "gu"},
  {.key = B_F|B_L           , .kana = "du"},
  {.key = B_J|B_Z           , .kana = "bo"},
  {.key = B_J|B_X           , .kana = "bi"},
  {.key = B_J|B_C           , .kana = "ge"},
  {.key = B_J|B_V           , .kana = "go"},
  {.key = B_J|B_B           , .kana = "zo"},
  {.key = B_F|B_N           , .kana = "da"},
  {.key = B_F|B_DOT         , .kana = "bu"},

  // 半濁音
  {.key = B_M|B_W           , .kana = "pa"},
  {.key = B_M|B_X           , .kana = "pi"},
  {.key = B_V|B_DOT         , .kana = "pu"},
  {.key = B_V|B_P           , .kana = "pe"},
  {.key = B_M|B_Z           , .kana = "po"},

  // 小書き
  {.key = B_SHFT|B_V|B_J    , .kana = "la"},
  {.key = B_SHFT|B_V|B_K    , .kana = "li"},
  {.key = B_SHFT|B_V|B_L    , .kana = "lu"},
  {.key = B_SHFT|B_V|B_P    , .kana = "le"},
  {.key = B_SHFT|B_V|B_N    , .kana = "lo"},

  // 拗音
  {.key = B_SHFT|B_V|B_SCLN , .kana = "lya"},
  {.key = B_SHFT|B_V|B_O    , .kana = "lyu"},
  {.key = B_SHFT|B_V|B_I    , .kana = "lyo"},

  // 拗音同時
  {.key = B_S|B_SCLN        , .kana = "kya"},
  {.key = B_S|B_O           , .kana = "kyu"},
  {.key = B_S|B_I           , .kana = "kyo"},
  {.key = B_R|B_SCLN        , .kana = "sya"},
  {.key = B_R|B_O           , .kana = "syu"},
  {.key = B_R|B_I           , .kana = "syo"},
  {.key = B_G|B_SCLN        , .kana = "tya"},
  {.key = B_G|B_O           , .kana = "tyu"},
  {.key = B_G|B_I           , .kana = "tyo"},
  {.key = B_D|B_SCLN        , .kana = "nya"},
  {.key = B_D|B_O           , .kana = "nyu"},
  {.key = B_D|B_I           , .kana = "nyo"},
  {.key = B_X|B_SCLN        , .kana = "hya"},
  {.key = B_X|B_O           , .kana = "hyu"},
  {.key = B_X|B_I           , .kana = "hyo"},
  {.key = B_W|B_SCLN        , .kana = "mya"},
  {.key = B_W|B_O           , .kana = "myu"},
  {.key = B_W|B_I           , .kana = "myo"},
  {.key = B_E|B_SCLN        , .kana = "rya"},
  {.key = B_E|B_O           , .kana = "ryu"},
  {.key = B_E|B_I           , .kana = "ryo"},

  // 濁音拗音同時
  {.key = B_J|B_S|B_SCLN    , .kana = "gya"},
  {.key = B_J|B_S|B_O       , .kana = "gyu"},
  {.key = B_J|B_S|B_I       , .kana = "gyo"},
  {.key = B_J|B_R|B_SCLN    , .kana = "jya"},
  {.key = B_J|B_R|B_O       , .kana = "jyu"},
  {.key = B_J|B_R|B_I       , .kana = "jyo"},
  {.key = B_J|B_G|B_SCLN    , .kana = "dya"},
  {.key = B_J|B_G|B_O       , .kana = "dyu"},
  {.key = B_J|B_G|B_I       , .kana = "dyo"},
  {.key = B_J|B_X|B_SCLN    , .kana = "bya"},
  {.key = B_J|B_X|B_O       , .kana = "byu"},
  {.key = B_J|B_X|B_I       , .kana = "byo"},

  // 半濁音拗音同時
  {.key = B_M|B_X|B_SCLN    , .kana = "pya"},
  {.key = B_M|B_X|B_O       , .kana = "pyu"},
  {.key = B_M|B_X|B_I       , .kana = "pyo"},

  // 外来音
  {.key = B_Q|B_J           , .kana = "va"},
  {.key = B_Q|B_K           , .kana = "vi"},
  {.key = B_Q|B_L           , .kana = "vyu"},
  {.key = B_Q|B_P           , .kana = "ve"},
  {.key = B_Q|B_N           , .kana = "vo"},
  {.key = B_E|B_K           , .kana = "teli"},
  {.key = B_E|B_L           , .kana = "telu"},
  {.key = B_R|B_P           , .kana = "sye"},
  {.key = B_D|B_L           , .kana = "tolu"},
  {.key = B_G|B_P           , .kana = "tile"},
  {.key = B_L|B_K           , .kana = "uli"},
  {.key = B_L|B_P           , .kana = "ule"},
  {.key = B_L|B_N           , .kana = "ulo"},
  {.key = B_DOT|B_J         , .kana = "fa"},
  {.key = B_DOT|B_K         , .kana = "fi"},
  {.key = B_DOT|B_L         , .kana = "fyu"},
  {.key = B_DOT|B_P         , .kana = "fe"},
  {.key = B_DOT|B_N         , .kana = "fo"},

  // シフト外来音
  {.key = B_SHFT|B_L|B_J    , .kana = "tula"},
  {.key = B_SHFT|B_L|B_K    , .kana = "tuli"},
  {.key = B_SHFT|B_L|B_P    , .kana = "tule"},
  {.key = B_SHFT|B_L|B_N    , .kana = "tulo"},

  // 濁音外来音
  {.key = B_E|B_J|B_K       , .kana = "deli"},
  {.key = B_E|B_J|B_L       , .kana = "delu"},
  {.key = B_R|B_J|B_P       , .kana = "je"},
  {.key = B_D|B_J|B_L       , .kana = "dolu"},
  {.key = B_G|B_J|B_P       , .kana = "dile"},

  // enter
  {.key = B_V|B_M           , .kana = SS_TAP(X_ENTER)},

  // 編集モード1
  {.key = B_J|B_K|B_E       , .kana = "deli"},
  {.key = B_J|B_K|B_R       , .kana = ""},

#ifdef NAGINATA_EDIT_WIN
  {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_INT4)},
  {.key = B_J|B_K|B_A       , .kana = SS_LCTRL("y")},
  {.key = B_J|B_K|B_S       , .kana = SS_LCTRL("s")},
  {.key = B_J|B_K|B_Z       , .kana = SS_LCTRL("z")},
  {.key = B_J|B_K|B_X       , .kana = SS_LCTRL("x")},
  {.key = B_J|B_K|B_C       , .kana = SS_LCTRL("c")},
  {.key = B_J|B_K|B_V       , .kana = SS_LCTRL("v")},
  {.key = B_D|B_F|B_SCLN    , .kana = SS_LCTRL("i")},
  {.key = B_D|B_F|B_SLSH    , .kana = SS_LCTRL("u")},
#endif
#ifdef NAGINATA_EDIT_MAC
  {.key = B_D|B_F|B_I       , .kana = SS_TAP(X_LANG1)SS_TAP(X_LANG1)},
  {.key = B_J|B_K|B_A       , .kana = SS_LGUI("y")},
  {.key = B_J|B_K|B_S       , .kana = SS_LGUI("s")},
  {.key = B_J|B_K|B_Z       , .kana = SS_LGUI("z")},
  {.key = B_J|B_K|B_X       , .kana = SS_LGUI("x")},
  {.key = B_J|B_K|B_C       , .kana = SS_LGUI("c")},
  {.key = B_J|B_K|B_V       , .kana = SS_LGUI("v")},
  {.key = B_D|B_F|B_SCLN    , .kana = SS_LCTRL("k")},
  {.key = B_D|B_F|B_SLSH    , .kana = SS_LCTRL("j")},
#endif
  {.key = B_J|B_K|B_D       , .kana = SS_TAP(X_PGUP)},
  {.key = B_J|B_K|B_F       , .kana = SS_TAP(X_PGDOWN)},

  {.key = B_D|B_F|B_O       , .kana = SS_TAP(X_DELETE)},

  {.key = B_D|B_F|B_J       , .kana = SS_TAP(X_LEFT)},
  {.key = B_D|B_F|B_M       , .kana = SS_TAP(X_RIGHT)},

  // 編集モード2
  {.key = B_M|B_COMM|B_D    , .kana = "!"SS_TAP(X_ENTER)},
  {.key = B_M|B_COMM|B_F    , .kana = "?"SS_TAP(X_ENTER)},
  {.key = B_M|B_COMM|B_B    , .kana = "   "},

  {.key = B_C|B_V|B_O       , .kana = ""},
  {.key = B_C|B_V|B_P       , .kana = ""},

  {.key = B_C|B_V|B_N       , .kana = "]"SS_TAP(X_ENTER)SS_TAP(X_ENTER)},
};

const PROGMEM naginata_keymap_long ngmapl[] = {
  // 編集モード1
  {.key = B_D|B_F|B_P       , .kana = SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)},

  {.key = B_D|B_F|B_K       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_LEFT)SS_UP(X_LSHIFT)},
  {.key = B_D|B_F|B_L       , .kana = SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)},

  {.key = B_D|B_F|B_COMM    , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_RIGHT)SS_UP(X_LSHIFT)},
  {.key = B_D|B_F|B_DOT     , .kana = SS_TAP(X_RIGHT)SS_TAP(X_RIGHT)SS_TAP(X_RIGHT)SS_TAP(X_RIGHT)SS_TAP(X_RIGHT)},

#ifdef NAGINATA_EDIT_WIN
  {.key = B_J|B_K|B_Q       , .kana = SS_DOWN(X_LCTRL)SS_TAP(X_END)SS_UP(X_LCTRL)},
  {.key = B_J|B_K|B_W       , .kana = SS_DOWN(X_LCTRL)SS_TAP(X_HOME)SS_UP(X_LCTRL)},
  {.key = B_D|B_F|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_END)SS_UP(X_LSHIFT)SS_LCTRL("x")},
  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_TAP(X_END)},
  {.key = B_D|B_F|B_Y       , .kana = SS_TAP(X_HOME)},
  {.key = B_D|B_F|B_N       , .kana = SS_TAP(X_END)},
#endif
#ifdef NAGINATA_EDIT_MAC
  {.key = B_J|B_K|B_Q       , .kana = SS_DOWN(X_LGUI)SS_TAP(X_DOWN)SS_UP(X_LGUI)},
  {.key = B_J|B_K|B_W       , .kana = SS_DOWN(X_LGUI)SS_TAP(X_UP)SS_UP(X_LGUI)},
  {.key = B_D|B_F|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_DOWN(X_LGUI)SS_TAP(X_RIGHT)SS_UP(X_LGUI)SS_UP(X_LSHIFT)SS_LGUI("x")},
  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_DOWN(X_LGUI)SS_TAP(X_RIGHT)SS_UP(X_LGUI)},
  {.key = B_D|B_F|B_Y       , .kana = SS_DOWN(X_LGUI)SS_TAP(X_LEFT)SS_UP(X_LGUI)},
  {.key = B_D|B_F|B_N       , .kana = SS_DOWN(X_LGUI)SS_TAP(X_RIGHT)SS_UP(X_LGUI)},
#endif

  // 編集モード2
  {.key = B_C|B_V|B_Y       , .kana = "]"SS_TAP(X_ENTER)SS_TAP(X_ENTER)" "},
  {.key = B_C|B_V|B_H       , .kana = "]"SS_TAP(X_ENTER)SS_TAP(X_ENTER)"["},

#ifdef NAGINATA_EDIT_WIN
  {.key = B_M|B_COMM|B_T    , .kana = SS_TAP(X_HOME)" "SS_TAP(X_END)},
  {.key = B_M|B_COMM|B_G    , .kana = SS_TAP(X_HOME)"   "SS_TAP(X_END)},
  {.key = B_C|B_V|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_HOME)SS_UP(X_LSHIFT)SS_LCTRL("x")},
  {.key = B_C|B_V|B_I       , .kana = SS_DOWN(X_LCTRL)SS_TAP(X_BSPACE)SS_UP(X_LCTRL)},
#endif
#ifdef NAGINATA_EDIT_MAC
  {.key = B_M|B_COMM|B_T    , .kana = SS_DOWN(X_LGUI)SS_TAP(X_LEFT)SS_UP(X_LGUI)" "SS_DOWN(X_LGUI)SS_TAP(X_RIGHT)SS_UP(X_LGUI)},
  {.key = B_M|B_COMM|B_G    , .kana = SS_DOWN(X_LGUI)SS_TAP(X_LEFT)SS_UP(X_LGUI)"   "SS_DOWN(X_LGUI)SS_TAP(X_RIGHT)SS_UP(X_LGUI)},
  {.key = B_C|B_V|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_DOWN(X_LGUI)SS_TAP(X_LEFT)SS_UP(X_LGUI)SS_UP(X_LSHIFT)SS_LGUI("x")},
  {.key = B_C|B_V|B_I       , .kana = ""},
#endif

};

const PROGMEM naginata_keymap_unicode ngmapu[] = {
  // 編集モード2
  {.key = B_M|B_COMM|B_Q    , .kana = "FF0F"},
  {.key = B_M|B_COMM|B_W    , .kana = "FF1A"},
  {.key = B_M|B_COMM|B_E    , .kana = "30FB"},
  {.key = B_M|B_COMM|B_R    , .kana = "3007"},

  {.key = B_M|B_COMM|B_A    , .kana = "3010"},
  {.key = B_M|B_COMM|B_Z    , .kana = "3011"},
  {.key = B_M|B_COMM|B_S    , .kana = "3008"},
  {.key = B_M|B_COMM|B_X    , .kana = "3009"},

  {.key = B_M|B_COMM|B_C    , .kana = "2026 2026"},
  {.key = B_M|B_COMM|B_V    , .kana = "2500 2500"},

  {.key = B_C|B_V|B_J       , .kana = "300C"},
  {.key = B_C|B_V|B_M       , .kana = "300D"},
  {.key = B_C|B_V|B_K       , .kana = "300E"},
  {.key = B_C|B_V|B_COMM    , .kana = "300F"},
  {.key = B_C|B_V|B_L       , .kana = "300A"},
  {.key = B_C|B_V|B_DOT     , .kana = "300B"},
  {.key = B_C|B_V|B_SCLN    , .kana = "FF08"},
  {.key = B_C|B_V|B_SLSH    , .kana = "FF09"},
};

// 薙刀式のレイヤー、シフトキーを設定
void set_naginata(uint8_t layer) {
  naginata_layer = layer;
}

// 薙刀式をオンオフ
void naginata_on(void) {
  is_naginata = true;
  keycomb = 0UL;
  naginata_clear();
  layer_on(naginata_layer);

  tap_code(KC_LANG1); // Mac
  tap_code(KC_HENK); // Win
}

void naginata_off(void) {
  is_naginata = false;
  keycomb = 0UL;
  naginata_clear();
  layer_off(naginata_layer);

  tap_code(KC_LANG2); // Mac
  tap_code(KC_MHEN); // Win
}

// 薙刀式の状態
bool naginata_state(void) {
  return is_naginata;
}


// キー入力を文字に変換して出力する
void naginata_type(void) {
#ifdef NAGINATA_JDOUJI
  naginata_keymap_ordered bngmapo; // PROGMEM buffer
#endif
  naginata_keymap bngmap; // PROGMEM buffer
  naginata_keymap_long bngmapl; // PROGMEM buffer
  naginata_keymap_unicode bngmapu; // PROGMEM buffer

  uint32_t skey = 0; // 連続押しの場合のバッファ

  switch (keycomb) {
    // send_stringできないキー、長すぎるマクロはここで定義
    case B_F|B_G:
      naginata_off();
      break;
    case B_J|B_K|B_T:
#ifdef NAGINATA_EDIT_WIN
      register_code(KC_LCTRL);
      tap_code(KC_LEFT);
      unregister_code(KC_LCTRL);
      for (int i = 0; i < 10; i++) tap_code(KC_RGHT);
#endif
#ifdef NAGINATA_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 10; i++) tap_code(KC_RGHT);
#endif
      break;
    case B_J|B_K|B_G:
#ifdef NAGINATA_EDIT_WIN
      register_code(KC_LCTRL);
      tap_code(KC_LEFT);
      unregister_code(KC_LCTRL);
      for (int i = 0; i < 20; i++) tap_code(KC_RGHT);
#endif
#ifdef NAGINATA_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 20; i++) tap_code(KC_RGHT);
#endif
      break;
    case B_J|B_K|B_B:
#ifdef NAGINATA_EDIT_WIN
      register_code(KC_LCTRL);
      tap_code(KC_LEFT);
      unregister_code(KC_LCTRL);
      for (int i = 0; i < 30; i++) tap_code(KC_RGHT);
#endif
#ifdef NAGINATA_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 30; i++) tap_code(KC_RGHT);
#endif
      break;
    default:
      // キーから仮名に変換して出力する。
      // 同時押しの場合 ngmapに定義されている
      // 順序つき
      #ifdef NAGINATA_JDOUJI
      for (int i = 0; i < sizeof ngmapo / sizeof bngmapo; i++) {
        memcpy_P(&bngmapo, &ngmapo[i], sizeof(bngmapo));
        if (ninputs[0] == bngmapo.key[0] && ninputs[1] == bngmapo.key[1] && ninputs[2] == bngmapo.key[2]) {
          send_string(bngmapo.kana);
          naginata_clear();
          return;
        }
      }
      #endif
      // 順序なし
      for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
        memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
        if (keycomb == bngmap.key) {
          send_string(bngmap.kana);
          naginata_clear();
          return;
        }
      }
      // 順序なしロング
      for (int i = 0; i < sizeof ngmapl / sizeof bngmapl; i++) {
        memcpy_P(&bngmapl, &ngmapl[i], sizeof(bngmapl));
        if (keycomb == bngmapl.key) {
          send_string(bngmapl.kana);
          naginata_clear();
          return;
        }
      }
      // 順序なしUNICODE
      for (int i = 0; i < sizeof ngmapu / sizeof bngmapu; i++) {
        memcpy_P(&bngmapu, &ngmapu[i], sizeof(bngmapu));
        if (keycomb == bngmapu.key) {
          send_unicode_hex_string(bngmapu.kana);
          tap_code(KC_ENT);
          naginata_clear();
          return;
        }
      }
      // 連続押しの場合 ngmapに定義されていない
      for (int j = 0; j < ng_chrcount; j++) {
        skey = ng_key[ninputs[j] - NG_Q];
        if ((keycomb & B_SHFT) > 0) skey |= B_SHFT; // シフトキー状態を反映
        for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
          memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
          if (skey == bngmap.key) {
            send_string(bngmap.kana);
            break;
          }
        }
      }
  }

  naginata_clear(); // バッファを空にする
}

// バッファをクリアする
void naginata_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
}

// 入力モードか編集モードかを確認する
void naginata_mode(uint16_t keycode, keyrecord_t *record) {
  if (!is_naginata) return;

  // modifierが押されたらレイヤーをオフ
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
      if (record->event.pressed) {
        n_modifier++;
        layer_off(naginata_layer);
      } else {
        n_modifier--;
        if (n_modifier == 0) {
          layer_on(naginata_layer);
        }
      }
      break;
  }

}

// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {
  // if (!is_naginata || n_modifier > 0) return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_Q ... NG_SHFT:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        // 3文字押したら処理を開始
        if (ng_chrcount > 2) {
          naginata_type();
        }
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case NG_Q ... NG_SHFT:
        // 3文字入力していなくても、どれかキーを離したら処理を開始する
        if (ng_chrcount > 0) {
          naginata_type();
        }
        keycomb &= ~ng_key[keycode - NG_Q]; // キーの重ね合わせ
        return false;
        break;
    }
  }
  return true;
}

