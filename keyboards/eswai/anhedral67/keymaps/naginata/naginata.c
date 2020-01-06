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

#define NGBUFFER 10 // キー入力バッファのサイズ

#ifdef NAGINATA_TATEGAKI
  #define NGUP X_UP
  #define NGDN X_DOWN
  #define NGLT X_LEFT
  #define NGRT X_RGHT
  #define NGKUP KC_UP
  #define NGKDN KC_DOWN
  #define NGKLT KC_LEFT
  #define NGKRT KC_RGHT
#endif
#ifdef NAGINATA_YOKOGAKI
  #define NGUP X_LEFT
  #define NGDN X_RGHT
  #define NGLT X_UP
  #define NGRT X_DOWN
  #define NGKUP KC_LEFT
  #define NGKDN KC_RGHT
  #define NGKLT KC_UP
  #define NGKRT KC_DOWN
#endif

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ
static bool is_naginata = false; // 薙刀式がオンかオフか
static uint8_t naginata_layer = 0; // NG_*を配置しているレイヤー番号
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

const PROGMEM naginata_keymap ngmap[] = {
  // 単独
  {.key = B_Q               , .kana = "vu"},
  {.key = B_W               , .kana = "ha"},
  {.key = B_E               , .kana = "te"},
  {.key = B_R               , .kana = "si"},
  {.key = B_T               , .kana = SS_TAP(NGLT)},
  {.key = B_Y               , .kana = SS_TAP(NGRT)},
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
  {.key = B_J|B_G           , .kana = "di"},
  {.key = B_F|B_H           , .kana = "gu"},
  {.key = B_F|B_L           , .kana = "du"},
  {.key = B_J|B_Z           , .kana = "bo"},
  {.key = B_J|B_X           , .kana = "bi"},
  {.key = B_J|B_C           , .kana = "ge"},
  {.key = B_J|B_V           , .kana = "go"},
  {.key = B_J|B_B           , .kana = "zo"},
  {.key = B_F|B_N           , .kana = "da"},
  {.key = B_F|B_DOT         , .kana = "bu"},

  // 濁音+シフト(連続シフト)
  {.key = B_SHFT|B_J|B_W    , .kana = "ba"},
  {.key = B_SHFT|B_J|B_E    , .kana = "de"},
  {.key = B_SHFT|B_J|B_R    , .kana = "ji"},
  {.key = B_SHFT|B_F|B_U    , .kana = "za"},
  {.key = B_SHFT|B_F|B_O    , .kana = "zu"},
  {.key = B_SHFT|B_F|B_P    , .kana = "be"},
  {.key = B_SHFT|B_J|B_A    , .kana = "ze"},
  {.key = B_SHFT|B_J|B_S    , .kana = "gi"},
  {.key = B_SHFT|B_J|B_D    , .kana = "do"},
  {.key = B_SHFT|B_J|B_F    , .kana = "ga"},
  {.key = B_SHFT|B_J|B_G    , .kana = "di"},
  {.key = B_SHFT|B_F|B_H    , .kana = "gu"},
  {.key = B_SHFT|B_F|B_L    , .kana = "du"},
  {.key = B_SHFT|B_J|B_Z    , .kana = "bo"},
  {.key = B_SHFT|B_J|B_X    , .kana = "bi"},
  {.key = B_SHFT|B_J|B_C    , .kana = "ge"},
  // {.key = B_SHFT|B_J|B_V    , .kana = "go"},
  {.key = B_SHFT|B_J|B_B    , .kana = "zo"},
  {.key = B_SHFT|B_F|B_N    , .kana = "da"},
  {.key = B_SHFT|B_F|B_DOT  , .kana = "bu"},

  // 半濁音
  {.key = B_M|B_W           , .kana = "pa"},
  {.key = B_M|B_X           , .kana = "pi"},
  {.key = B_V|B_DOT         , .kana = "pu"},
  {.key = B_V|B_P           , .kana = "pe"},
  {.key = B_M|B_Z           , .kana = "po"},

  // 半濁音+シフト(連続シフト)
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

  // 拗音同時+シフト(連続シフト)
  {.key = B_SHFT|B_S|B_SCLN , .kana = "kya"},
  {.key = B_SHFT|B_S|B_O    , .kana = "kyu"},
  {.key = B_SHFT|B_S|B_I    , .kana = "kyo"},
  {.key = B_SHFT|B_R|B_SCLN , .kana = "sya"},
  {.key = B_SHFT|B_R|B_O    , .kana = "syu"},
  {.key = B_SHFT|B_R|B_I    , .kana = "syo"},
  {.key = B_SHFT|B_G|B_SCLN , .kana = "tya"},
  {.key = B_SHFT|B_G|B_O    , .kana = "tyu"},
  {.key = B_SHFT|B_G|B_I    , .kana = "tyo"},
  {.key = B_SHFT|B_D|B_SCLN , .kana = "nya"},
  {.key = B_SHFT|B_D|B_O    , .kana = "nyu"},
  {.key = B_SHFT|B_D|B_I    , .kana = "nyo"},
  {.key = B_SHFT|B_X|B_SCLN , .kana = "hya"},
  {.key = B_SHFT|B_X|B_O    , .kana = "hyu"},
  {.key = B_SHFT|B_X|B_I    , .kana = "hyo"},
  {.key = B_SHFT|B_W|B_SCLN , .kana = "mya"},
  {.key = B_SHFT|B_W|B_O    , .kana = "myu"},
  {.key = B_SHFT|B_W|B_I    , .kana = "myo"},
  {.key = B_SHFT|B_E|B_SCLN , .kana = "rya"},
  {.key = B_SHFT|B_E|B_O    , .kana = "ryu"},
  {.key = B_SHFT|B_E|B_I    , .kana = "ryo"},

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

  // 濁音拗音同時+シフト(連続シフト)
  {.key = B_SHFT|B_J|B_S|B_SCLN, .kana = "gya"},
  {.key = B_SHFT|B_J|B_S|B_O   , .kana = "gyu"},
  {.key = B_SHFT|B_J|B_S|B_I   , .kana = "gyo"},
  {.key = B_SHFT|B_J|B_R|B_SCLN, .kana = "jya"},
  {.key = B_SHFT|B_J|B_R|B_O   , .kana = "jyu"},
  {.key = B_SHFT|B_J|B_R|B_I   , .kana = "jyo"},
  {.key = B_SHFT|B_J|B_G|B_SCLN, .kana = "dya"},
  {.key = B_SHFT|B_J|B_G|B_O   , .kana = "dyu"},
  {.key = B_SHFT|B_J|B_G|B_I   , .kana = "dyo"},
  {.key = B_SHFT|B_J|B_X|B_SCLN, .kana = "bya"},
  {.key = B_SHFT|B_J|B_X|B_O   , .kana = "byu"},
  {.key = B_SHFT|B_J|B_X|B_I   , .kana = "byo"},

  // 半濁音拗音同時
  {.key = B_M|B_X|B_SCLN    , .kana = "pya"},
  {.key = B_M|B_X|B_O       , .kana = "pyu"},
  {.key = B_M|B_X|B_I       , .kana = "pyo"},

  // 半濁音拗音同時+シフト(連続シフト)
  {.key = B_SHFT|B_M|B_X|B_SCLN, .kana = "pya"},
  {.key = B_SHFT|B_M|B_X|B_O   , .kana = "pyu"},
  {.key = B_SHFT|B_M|B_X|B_I   , .kana = "pyo"},

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

  // 外来音+シフト(連続シフト)
  {.key = B_SHFT|B_Q|B_J    , .kana = "va"},
  {.key = B_SHFT|B_Q|B_K    , .kana = "vi"},
  {.key = B_SHFT|B_Q|B_L    , .kana = "vyu"},
  {.key = B_SHFT|B_Q|B_P    , .kana = "ve"},
  {.key = B_SHFT|B_Q|B_N    , .kana = "vo"},
  {.key = B_SHFT|B_E|B_K    , .kana = "teli"},
  {.key = B_SHFT|B_E|B_L    , .kana = "telu"},
  {.key = B_SHFT|B_R|B_P    , .kana = "sye"},
  {.key = B_SHFT|B_D|B_L    , .kana = "tolu"},
  {.key = B_SHFT|B_G|B_P    , .kana = "tile"},
  {.key = B_SHFT|B_L|B_K    , .kana = "uli"},
  {.key = B_SHFT|B_L|B_P    , .kana = "ule"},
  {.key = B_SHFT|B_L|B_N    , .kana = "ulo"},
  {.key = B_SHFT|B_DOT|B_J  , .kana = "fa"},
  {.key = B_SHFT|B_DOT|B_K  , .kana = "fi"},
  {.key = B_SHFT|B_DOT|B_L  , .kana = "fyu"},
  {.key = B_SHFT|B_DOT|B_P  , .kana = "fe"},
  {.key = B_SHFT|B_DOT|B_N  , .kana = "fo"},

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

  // 濁音外来音+シフト(連続シフト)
  {.key = B_SHFT|B_E|B_J|B_K, .kana = "deli"},
  {.key = B_SHFT|B_E|B_J|B_L, .kana = "delu"},
  {.key = B_SHFT|B_R|B_J|B_P, .kana = "je"},
  {.key = B_SHFT|B_D|B_J|B_L, .kana = "dolu"},
  {.key = B_SHFT|B_G|B_J|B_P, .kana = "dile"},

  // enter
  {.key = B_V|B_M           , .kana = SS_TAP(X_ENTER)},
  // enter+シフト(連続シフト)
  {.key = B_SHFT|B_V|B_M    , .kana = SS_TAP(X_ENTER)},

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

  {.key = B_D|B_F|B_J       , .kana = SS_TAP(NGUP)},
  {.key = B_D|B_F|B_M       , .kana = SS_TAP(NGDN)},

  // 編集モード2
  {.key = B_M|B_COMM|B_D    , .kana = "!"SS_TAP(X_ENTER)},
  {.key = B_M|B_COMM|B_F    , .kana = "?"SS_TAP(X_ENTER)},
  {.key = B_M|B_COMM|B_B    , .kana = "   "},

};

const PROGMEM naginata_keymap_long ngmapl[] = {
  {.key = B_SHFT|B_T        , .kana = SS_LSFT(SS_TAP(NGLT))},
  {.key = B_SHFT|B_Y        , .kana = SS_LSFT(SS_TAP(NGRT))},

  // 編集モード1
  {.key = B_D|B_F|B_P       , .kana = SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)},

  {.key = B_D|B_F|B_K       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(NGUP)SS_UP(X_LSHIFT)},
  {.key = B_D|B_F|B_L       , .kana = SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)},

  {.key = B_D|B_F|B_COMM    , .kana = SS_LSFT(SS_TAP(NGDN))},
  {.key = B_D|B_F|B_DOT     , .kana = SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)},

#ifdef NAGINATA_EDIT_WIN
  {.key = B_J|B_K|B_Q       , .kana = SS_LCTRL(SS_TAP(X_END))},
  {.key = B_J|B_K|B_W       , .kana = SS_LCTRL(SS_TAP(X_HOME))},
  {.key = B_D|B_F|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_END)SS_UP(X_LSHIFT)SS_TAP(X_BSPACE)},
  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_TAP(X_END)},
  {.key = B_D|B_F|B_Y       , .kana = SS_TAP(X_HOME)},
  {.key = B_D|B_F|B_N       , .kana = SS_TAP(X_END)},
#endif
#ifdef NAGINATA_EDIT_MAC
  {.key = B_J|B_K|B_Q       , .kana = SS_LCMD(SS_TAP(X_DOWN))},
  {.key = B_J|B_K|B_W       , .kana = SS_LCMD(SS_TAP(X_UP))},
  {.key = B_D|B_F|B_U       , .kana = SS_LSFT(SS_LCMD(SS_TAP(NGDN)))SS_LGUI("x")},
  {.key = B_D|B_F|B_H       , .kana = SS_TAP(X_ENTER)SS_LCMD(SS_TAP(NGDN))},
  {.key = B_D|B_F|B_Y       , .kana = SS_LCMD(SS_TAP(NGUP))},
  {.key = B_D|B_F|B_N       , .kana = SS_LCMD(SS_TAP(NGDN))},
#endif

  // 編集モード2
#ifdef NAGINATA_EDIT_WIN
  {.key = B_M|B_COMM|B_T    , .kana = SS_TAP(X_HOME)" "SS_TAP(X_END)},
  {.key = B_M|B_COMM|B_G    , .kana = SS_TAP(X_HOME)"   "SS_TAP(X_END)},
  {.key = B_C|B_V|B_U       , .kana = SS_DOWN(X_LSHIFT)SS_TAP(X_HOME)SS_UP(X_LSHIFT)SS_LCTRL("x")},
  {.key = B_C|B_V|B_I       , .kana = SS_LCTRL(SS_TAP(X_BSPACE))},
#endif
#ifdef NAGINATA_EDIT_MAC
  {.key = B_M|B_COMM|B_T    , .kana = SS_LCMD(SS_TAP(NGUP))" "SS_LCMD(SS_TAP(X_RIGHT))},
  {.key = B_M|B_COMM|B_G    , .kana = SS_LCMD(SS_TAP(NGUP))"   "SS_LCMD(SS_TAP(X_RIGHT))},
  {.key = B_C|B_V|B_U       , .kana = SS_LSFT(SS_LCMD(SS_TAP(NGUP)))SS_LGUI("x")},
  {.key = B_C|B_V|B_I       , .kana = ""},
#endif

};

const PROGMEM naginata_keymap_unicode ngmapu[] = {
  // 編集モード2
#ifdef NAGINATA_EDIT_WIN
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

  {.key = B_C|B_V|B_O       , .kana = "FF5C"},
  {.key = B_C|B_V|B_J       , .kana = "300C"},
  {.key = B_C|B_V|B_M       , .kana = "300D"},
  {.key = B_C|B_V|B_K       , .kana = "300E"},
  {.key = B_C|B_V|B_COMM    , .kana = "300F"},
  {.key = B_C|B_V|B_L       , .kana = "300A"},
  {.key = B_C|B_V|B_DOT     , .kana = "300B"},
  {.key = B_C|B_V|B_SCLN    , .kana = "FF08"},
  {.key = B_C|B_V|B_SLSH    , .kana = "FF09"},
#endif
};

// 薙刀式のレイヤー、シフトキーを設定
void set_naginata(uint8_t layer) {
  naginata_layer = layer;
}

// 薙刀式をオン
void naginata_on(void) {
  is_naginata = true;
  keycomb = 0UL;
  naginata_clear();
  layer_on(naginata_layer);

  tap_code(KC_LANG1); // Mac
  tap_code(KC_HENK); // Win
}

// 薙刀式をオフ
void naginata_off(void) {
  is_naginata = false;
  keycomb = 0UL;
  naginata_clear();
  layer_off(naginata_layer);

  tap_code(KC_LANG2); // Mac
  tap_code(KC_MHEN); // Win
}

// 薙刀式のon/off状態を返す
bool naginata_state(void) {
  return is_naginata;
}

// OSのかな/英数モードをキーボードに合わせる
void makesure_mode(void) {
  if (is_naginata) {
    tap_code(KC_LANG1); // Mac
    tap_code(KC_HENK); // Win
  } else {
    tap_code(KC_LANG2); // Mac
    tap_code(KC_MHEN); // Win
  }
}

// バッファをクリアする
void naginata_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
}

// バッファから先頭n文字を削除する
void compress_buffer(int n) {
  for (int j = 0; j < NGBUFFER; j++) {
    if (j + n < NGBUFFER) {
      ninputs[j] = ninputs[j + n];
    } else {
      ninputs[j] = 0;
    }
  }
  ng_chrcount -= n;
}


// modifierが押されたら薙刀式レイヤーをオフしてベースレイヤーに戻す
// get_mods()がうまく動かない
static int n_modifier = 0;

bool process_modifier(uint16_t keycode, keyrecord_t *record) {
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
      return true;
      break;
  }
  return false;
}

// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {
  if (!is_naginata) return true;

  if (process_modifier(keycode, record))
    return true;

  if (record->event.pressed) {
    switch (keycode) {
      case NG_Q ... NG_SHFT:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        // バッファが一杯になったら処理を開始
        if (ng_chrcount >= NGBUFFER) {
          naginata_type();
        }
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case NG_Q ... NG_SHFT:
        // どれかキーを離したら処理を開始する
        keycomb &= ~ng_key[keycode - NG_Q]; // キーの重ね合わせ
        if (ng_chrcount > 0) {
          naginata_type();
        }
        return false;
        break;
    }
  }
  return true;
}

// キー入力を文字に変換して出力する
void naginata_type(void) {
  // バッファの最初からnt文字目までを検索キーにする。
  // 一致する組み合わせがなければntを減らして=最後の1文字を除いて再度検索する。
  int nt = ng_chrcount;

  while (nt > 0) {
    if (naginata_lookup(nt)) return;
    nt--; // 最後の1キーを除いて、もう一度仮名テーブルを検索する
  }
  compress_buffer(1);
}

// バッファの頭からnt文字の範囲を検索キーにしてテーブル検索し、文字に変換して出力する
// 検索に成功したらtrue、失敗したらfalseを返す
bool naginata_lookup(int nt) {
  naginata_keymap bngmap; // PROGMEM buffer
  naginata_keymap_long bngmapl; // PROGMEM buffer
  naginata_keymap_unicode bngmapu; // PROGMEM buffer

  // keycomb_bufはバッファ内のキーの組み合わせ、keycombはリリースしたキーを含んでいない
  uint32_t keycomb_buf = 0UL;

  // バッファ内のキーを組み合わせる
  for (int i = 0; i < nt; i++) {
    keycomb_buf |= ng_key[ninputs[i] - NG_Q];
  }

  // 連続シフトを有効にする
  if ((keycomb & B_SHFT) == B_SHFT) keycomb_buf |= B_SHFT;

  // 編集モードを連続する
  if ((keycomb & (B_D | B_F))    == (B_D | B_F))    keycomb_buf |= (B_D | B_F);
  if ((keycomb & (B_C | B_V))    == (B_C | B_V))    keycomb_buf |= (B_C | B_V);
  if ((keycomb & (B_J | B_K))    == (B_J | B_K))    keycomb_buf |= (B_J | B_K);
  if ((keycomb & (B_M | B_COMM)) == (B_M | B_COMM)) keycomb_buf |= (B_M | B_COMM);

  // 濁音、半濁音を連続する
  if ((keycomb & B_F) == B_F) keycomb_buf |= B_F;
  if ((keycomb & B_J) == B_J) keycomb_buf |= B_J;
  if ((keycomb & B_V) == B_V) keycomb_buf |= B_V;
  if ((keycomb & B_M) == B_M) keycomb_buf |= B_M;

  switch (keycomb_buf) {
    // send_stringできないキー、長すぎるマクロはここで定義
    case B_F|B_G:
      naginata_off();
      compress_buffer(nt);
      return true;
      break;
    case B_J|B_K|B_T:
#ifdef NAGINATA_EDIT_WIN
      tap_code(KC_HOME);
      for (int i = 0; i < 10; i++) tap_code(NGKDN);
#endif
#ifdef NAGINATA_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 10; i++) tap_code(NGKDN);
#endif
      compress_buffer(nt);
      return true;
      break;
    case B_J|B_K|B_G:
#ifdef NAGINATA_EDIT_WIN
      tap_code(KC_HOME);
      for (int i = 0; i < 20; i++) tap_code(NGKDN);
#endif
#ifdef NAGINATA_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 20; i++) tap_code(NGKDN);
#endif
      compress_buffer(nt);
      return true;
      break;
    case B_J|B_K|B_B:
#ifdef NAGINATA_EDIT_WIN
      tap_code(KC_HOME);
      for (int i = 0; i < 30; i++) tap_code(NGKDN);
#endif
#ifdef NAGINATA_EDIT_MAC
      register_code(KC_LGUI);
      tap_code(KC_LEFT);
      unregister_code(KC_LGUI);
      for (int i = 0; i < 30; i++) tap_code(NGKDN);
#endif
      compress_buffer(nt);
      return true;
      break;
#ifdef NAGINATA_EDIT_WIN
    case B_C|B_V|B_P:
      send_unicode_hex_string("FF5C");
      tap_code(KC_ENT);
      tap_code(KC_END);
      send_unicode_hex_string("300A 300B");
      tap_code(KC_ENT);
      tap_code(KC_LEFT);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_Y:
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      tap_code(KC_SPC);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_H:
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      send_unicode_hex_string("300C");
      tap_code(KC_ENT);
      compress_buffer(nt);
      return true;
      break;
    case B_C|B_V|B_N:
      send_unicode_hex_string("300D");
      tap_code(KC_ENT);
      tap_code(KC_ENT);
      compress_buffer(nt);
      return true;
      break;
#endif
    default:
      // キーから仮名に変換して出力する

      // 通常の仮名
      for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
        memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
        if (keycomb_buf == bngmap.key) {
          send_string(bngmap.kana);
          compress_buffer(nt);
          return true;
        }
      }
      // 仮名ロング
      for (int i = 0; i < sizeof ngmapl / sizeof bngmapl; i++) {
        memcpy_P(&bngmapl, &ngmapl[i], sizeof(bngmapl));
        if (keycomb_buf == bngmapl.key) {
          send_string(bngmapl.kana);
          compress_buffer(nt);
          return true;
        }
      }
      // UNICODE文字
      for (int i = 0; i < sizeof ngmapu / sizeof bngmapu; i++) {
        memcpy_P(&bngmapu, &ngmapu[i], sizeof(bngmapu));
        if (keycomb_buf == bngmapu.key) {
          send_unicode_hex_string(bngmapu.kana);
          tap_code(KC_ENT);
          compress_buffer(nt);
          return true;
        }
      }
  }
  return false;
}

