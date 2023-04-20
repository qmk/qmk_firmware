// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include "quantum.h"


#define TD_BRC   TD(T_BRC)
#define TD_ATH   TD(T_ATH)
#define TD_CSPC  TD(T_CSPC)
#define TD_DSPC  TD(T_DSPC)
#define TD_CP    TD(T_CP)
#define TD_DENT  TD(T_DENT)
#define TD_IENT  TD(T_IENT)
#define TD_MIN   TD(T_MIN)
#define TD_UMIN  TD(T_UMIN)
#define TD_GESC  TD(T_GESC)
#define TD_QESC  TD(T_QESC)
#define TD_QEXC  TD(T_QEXC)
#define TD_PRAM  TD(T_PRAM)
#define TD_SE    TD(T_SE)
#define TD_MD    TD(T_MULTDIV)
#define TD_UR    TD(T_UR)
#define TD_DL    TD(T_DL)
#define TD_TE    TD(T_TE)
#define TD_20    TD(T_20)
#define TD_SL    TD(T_SL)
#define TD_XX    TD(T_XX)
#define TD_YY    TD(T_YY)



// Tap Dance
enum tapdance_id{
  T_BRC = 0,
  T_ATH,
  T_CSPC,
  T_DSPC,
  T_CP,
  T_DENT,
  T_IENT,
  T_MIN,
  T_UMIN,
  T_GESC,
  T_QESC,
  T_QEXC,
  T_SE,
  T_MULTDIV,
  T_UR,
  T_DL,
  T_TE,
  T_20,
  T_SL,
  T_XX,
  T_YY,
  T_PRAM
};