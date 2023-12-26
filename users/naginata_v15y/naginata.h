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

#pragma once
#include "nglist.h"
#include "nglistarray.h"

void ng_type(NGList *);
void naginata_clear(void);
int number_of_candidates(NGList *, bool);
int count_bit(uint32_t);

bool process_modifier(uint16_t, keyrecord_t *);

void naginata_on(void);
void naginata_off(void);
bool naginata_state(void);

void switchOS(uint8_t);
void ng_set_unicode_mode(uint8_t);
void ng_show_os(void);
void mac_live_conversion_toggle(void);
void tategaki_toggle(void);
void kouchi_shift_toggle(void);

bool process_naginata(uint16_t, keyrecord_t *);
// void set_naginata(uint8_t);
void set_naginata(uint8_t, uint16_t *, uint16_t *);

void nofunc(void);

void ng_cut(void);
void ng_copy(void);
void ng_paste(void);
void ng_up(uint8_t);
void ng_down(uint8_t);
void ng_left(uint8_t);
void ng_right(uint8_t);
void ng_home(void);
void ng_end(void);
void ng_katakana(void);
void ng_save(void);
void ng_hiragana(void);
void ng_redo(void);
void ng_undo(void);
void ng_saihenkan(void);
void ng_eof(void);

void ng_T(void);
void ng_Y(void);
void ng_ST(void);
void ng_SY(void);

void ngh_DFY(void);
void ngh_DFU(void);
void ngh_DFI(void);
void ngh_DFO(void);
void ngh_DFP(void);
void ngh_DFH(void);
void ngh_DFJ(void);
void ngh_DFK(void);
void ngh_DFL(void);
void ngh_DFSCLN(void);
void ngh_DFN(void);
void ngh_DFM(void);
void ngh_DFCOMM(void);
void ngh_DFDOT(void);
void ngh_DFSLSH(void);
void ngh_JKQ(void);
void ngh_JKW(void);
void ngh_JKE(void);
void ngh_JKR(void);
void ngh_JKT(void);
void ngh_JKA(void);
void ngh_JKS(void);
void ngh_JKD(void);
void ngh_JKF(void);
void ngh_JKG(void);
void ngh_JKZ(void);
void ngh_JKX(void);
void ngh_JKC(void);
void ngh_JKV(void);
void ngh_JKB(void);
void ngh_CVY(void);
void ngh_CVU(void);
void ngh_CVI(void);
void ngh_CVO(void);
void ngh_CVP(void);
void ngh_CVH(void);
void ngh_CVJ(void);
void ngh_CVK(void);
void ngh_CVL(void);
void ngh_CVSCLN(void);
void ngh_CVN(void);
void ngh_CVM(void);
void ngh_CVCOMM(void);
void ngh_CVDOT(void);
void ngh_CVSLSH(void);
void ngh_MCQ(void);
void ngh_MCW(void);
void ngh_MCE(void);
void ngh_MCR(void);
void ngh_MCT(void);
void ngh_MCA(void);
void ngh_MCS(void);
void ngh_MCD(void);
void ngh_MCF(void);
void ngh_MCG(void);
void ngh_MCZ(void);
void ngh_MCX(void);
void ngh_MCC(void);
void ngh_MCV(void);
void ngh_MCB(void);

// bool enable_naginata(uint16_t, keyrecord_t *);

// なぜKC_キーコードを使わず、NG_キーコードを定義するのか
// 1. 英字レイアウトがQWERTYでない場合でもOK
// 2. 薙刀式レイヤーでもKC_を定義すれば、かな変換せず出力できる
typedef enum naginata_keycodes {
  NG_Q = SAFE_RANGE, // 薙刀式シフトキー
  NG_W,
  NG_E,
  NG_R,
  NG_T,
  NG_Y,
  NG_U,
  NG_I,
  NG_O,
  NG_P,

  NG_A,
  NG_S,
  NG_D,
  NG_F,
  NG_G,
  NG_H,
  NG_J,
  NG_K,
  NG_L,
  NG_SCLN,

  NG_Z,
  NG_X,
  NG_C,
  NG_V,
  NG_B,
  NG_N,
  NG_M,
  NG_COMM,
  NG_DOT,
  NG_SLSH,

  NG_SHFT,
  NG_SHFT2,

  NG_ON,
  NG_OFF,
  NG_CLR,
  NGSW_WIN,
  NGSW_MAC,
  NGSW_LNX,
  NG_MLV,
  NG_SHOS,
  NG_TAYO,
  NG_KOTI,
} NGKEYS;

// EEPROMに保存する設定
typedef union {
  uint32_t raw;
  struct {
    uint8_t os;
    bool live_conv :1;
    bool tategaki :1;
    bool kouchi_shift :1;
  };
} user_config_t;

user_config_t naginata_config;

#define NG_SAFE_RANGE SAFE_RANGE + 42

#define NG_WIN 1
#define NG_MAC 2
#define NG_LINUX 3

