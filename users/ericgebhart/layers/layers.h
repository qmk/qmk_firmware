#pragma once
/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "keycodes.h"
/*********************************************************************/
/* Non-Base Layer Definitions.                                       */
/*                                                                   */
/* Keypads, sympads, funcpads, symbols, RGB, Layers, Controls, etc.  */
/* Qwerty and Bepo versions exist as needed.                         */
/*                                                                   */
/* This file defines every auxillary layer I use on every keyboard   */
/* Ergodox, keebio/viterbi, xd75, rebound, crkbd, morpho, dactyl,..  */
/*********************************************************************/
/********************************************************************************/
/* The following Transient/Non-Base Layers are provided within.                 */
/* Each layer is named with the size of Keymatrix it has entries for.           */
/* 3x10 are usual for these.  I had 3x12's but I didn't need the edges really.  */
/* It was an attempt to accommodate Bepo which is 13 columns wide.              */
/* Even in a 3x12 Bepo is wonky. So I gave up on it. I also gave up on 4 row    */
/* layers, I really want my keys in that 3x5 space. Everything on the edges can */
/* stay as it is.  Splitting is managed in the macros as                        */
/* needed. BP indicates the Bepo equivalent to the Qwerty layer when needed.    */
/********************************************************************************/
/*                                                                              */
/* Explore below to see what they all are.                                      */
/* Naming gives the sizes of things, a prefix number is the length.             */
/* BP is the bepo version of things.                                            */
/* BKL is the beakl 15 version of a layout or chunk.                            */
/* C on the end of a name means its a compact version of something.             */
/* Compact meaning for use on a 3 row layout.                                   */
/*                                                                              */
/* TOPROWS - numbers, symbols, functions, all on one layer.                     */
/* ___TOPROWS_3x10___                                                           */
/* ___TOPROWS_BP_3x10___                                                        */
/*                                                                              */
/* KEYPADS/FUNCPADS.                                                            */
/* ___KP_C_3x10___                                                              */
/* ___KP_C_BP_3x10___                                                           */
/* ___KP_C_BKL_FUNC_3x10___  -- BEAKL key/func pads.                            */
/* ___KP_C_BKL_FUNC_BP_3x10___                                                  */
/*                                                                              */
/* SYMBOLS   -Beakl or Beakl extended                                           */
/* ___SYMB_BEAKL_3x10___                                                        */
/* ___SYMB_BEAKL_BP_3x10___                                                     */
/*                                                                              */
/* Beakl extended symbol layer with additional corner symbols.                  */
/* For use with non-beakl base layers.                                          */
/* ___SYMB_BEAKLA_3x10___                                                       */
/* ___SYMB_BEAKLA_BP_3x10___                                                    */
/* For use with vi bindings optimized                                           */
/* ___SYMB_BEAKLB_3x10___                                                       */
/* ___SYMB_BEAKLB_BP_3x10___                                                    */
/*                                                                              */
/* NAVIGATION                                                                   */
/* ___NAV_3x10___                                                               */
/*                                                                              */
/* CONTROLS                                                                     */
/* ___RGB_3x10___                                                               */
/* ___ADJUST_3x10___                                                            */
 /* ___LAYERS_3x10___                                                            */
 /********************************************************************************/
 /*********************************************************************/
 /* XXXXXX Layer chunk  -- These are the final layers.                */
 /*                                                                   */
/* Each section defines the necessary pieces to create a layer.      */
/* It builds them up into consistently shaped lists for the layout   */
/* wrapper.                                                          */
/*                                                                   */
/* Each Section ends with a _Layer Chunk_. This is so the            */
/* layer can be easily given to the Layout Wrapper macros which      */
/* takes a list of keys in lengths of 2x3x5, 2x3x6, 2x4x5, or 2x4x6. */
/*                                                                   */
/* All of my keyboard definitions use these same chunks with similar */
/* macros. The differences between keyboards are all managed in the  */
/* macro. Here we just have nice rectangular sets of keys to         */
/* complete a layout.                                                */
/*********************************************************************/

// these are needed so that groups of defined keys will unravel
// into their values. The Base layers don't need them becuse the
// keys are explicit in their passing. Here, chunks are made for
// convenience and reuse. They don't unravel unless we wrap these
// in var args.
#define CHUNK_LANG_MAP(...) LANG_MAP(__VA_ARGS__)
#define CHUNK_LANG_ROW(...) LANG_ROW(__VA_ARGS__)

// 5 wide, with the two shot control.
#define ___OS_MODS_L___   OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, TS_LCTL
#define ___OS_MODS_R___   TS_RCTL, OS_RSFT, OS_RCTL, OS_RALT, OS_RGUI
// 4 wide.
#define ___SML_MODS_L___  SMLM_LGUI, SMLM_LALT, SMLM_LCTL, SMLM_LSFT
#define ___SML_MODS_R___  SMLM_RSFT, SMLM_RCTL, SMLM_RALT, SMLM_RGUI

#include "keypads.h"
#include "nav.h"
#include "symbols.h"
#include "toprows.h"
#include "utility.h"
