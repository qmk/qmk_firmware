#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// beakl, balanced effort key layout.
// Beakl 15 and 19 are somewhat more related.
// Beakl-wi is the latest. It feels a little bit more like a system.


// Remember the - and ; outside pinky keys.
// Or use the 6 size.
// Both are on the symbol layer too. So you
// wont lose them at least.
// KC_BK_COMM, KC_BK_QUOT, KC_BK_DOT - Beakl->Qwerty
// BP_BK_COMM, BP_BK_QUOT, BP_BK_DOT - Beakl->Bepo
// take care of the different shifted chars.


/* BEAKL 27 (main layer): */
/* // altered shifted pairs: dot = .`  comma = ,?   dquot = !" */
/* Alt target is BK2 */

/* 32104 76598 */
/* qhoux gcmrv */
/* yiea. dstnb */
/* j",k' wflpz */

/* BEAKL 27 (shift layer): */
/*   !@$#% ^(*)& */
/*   QHOUX GCMRV */
/*   YIEA` DSTNB */
/*   J!?K' WFLPZ */


#define CARTE_BEAKL27                           \
  carte_de_map(" qhoux gcmrz ",                 \
               " yiea. dstnb ",                 \
               " j\",k' wflpv ")

// Alt target is BK
#define ___BEAKL27___                                                   \
  LANG_MAP(_Q, _H,      _O,      _U, _X,      _G, _C, _M, _R, _Z,       \
           _Y, _I,      _E,      _A, TL_DOT,  _D, _S, _T, _N, _B,       \
           _J, TL_EXLM, TL_COMM, _K, TL_QUOT, _W, _F, _L, _P, _V)

/* BEAKL 15 (main layer): */
// altered shifted pairs: quot = '`  comma = ,!   dot = .@
/*   40123 76598   */
#define CARTE_BEAKL15                           \
  carte_de_map(" qhoux gcrfz ",                 \
               " yiea. dstnb ",                 \
               " j/,k' wmlpv ")

// Alt target is BK
#define ___BEAKL15___                                           \
  LANG_MAP(_Q, _H,    _O,      _U, _X,      _G, _C, _R, _F, _Z, \
           _Y, _I,    _E,      _A, TL_DOT,  _D, _S, _T, _N, _B, \
           _J, _SLSH, TL_COMM, _K, TL_QUOT, _W, _M, _L, _P, _V)

/* BEAKL 19    */
// Beakl 19.  scores better than 15, better in french also.
// Both are lots better than dvorak or bepo.

/* same symbols and keypad as 15 */
/* number row is different */
/*  32104 76598  */

// Alt target is BK
#define CARTE_BEAKL19                           \
  carte_de_map(" q.ouj wdnm, ",                 \
               " haeik gsrtp ",                 \
               " z'/yx bclfv ")

#define ___BEAKL19___                                                   \
  LANG_MAP(_Q, _DOT,  _O,    _U, _J, _W,    _D, _N, _M, TL_COMM,        \
           _H, _A,    _E,    _I, _K, _G,    _S, _R, _T, _P,             \
           _Z, _QUOT, _SLSH, _Y, _X, _B,    _C, _L, _F, _V)

//BEAKL 19bis - original.
// the é and è were simply added for analysis not real use.
// even so, this layout scores well for french, better than
// bepo and mtgap
/*  qyouz  wdnck   */
/* -hiea,  gtrsp; */
/* èj'é.x  vmlfb   */

// A 3x12
//BEAKL 19bis mod z.
// French optimised with some english.
// This version rearranges things a little based on fequency.
// Since it needs 3x12, I filled in the corners and removed ;.
// Leaving y where it is. the o and the e might cause sfbs.
// Put é on a different finger from e.
// swap z, e's, add à, ^, and ê, swap ; for -.
// it might be beneficial to swap w and à, as à is much more frequent than w
#define CARTE_BEAKL19bis                        \
  carte_de_map(" àqyoué  wdnck^ ",              \
               " ;hiea,  gtrsp- ",              \
               " zj'è.x  vmlfbê  ")

#define ___BEAKL19bis_3x12___                                           \
  LANG_MAP6(                                                            \
            _AGRV, _Q, _Y,    _O,    _U,   _EACU,   _W, _D, _N, _C, _K, _DCIR, \
            _SCLN, _H, _I,    _E,    _A,   _COMM,   _G, _T, _R, _S, _P, _MINS, \
            _Z,    _J, _QUOT, _EGRV, _DOT, _X,      _V, _M, _L, _F, _B, _ECIR)


// Beakl Wi.   This is the most current beakl this size. 18/01/2022.
// Nothing on the 6th outer columns but layer toggle buttons. All 6.
// altered shifted pairs: dot = .` comma = ,~  colon = :;
// i is on the left thumb.
/* ;you- ctrsv */
/* qheaw gdnmz */
/* j,.k' bplfx */
/*    i        */

#define CARTE_BEAKLWI                           \
  carte_de_map(" ;you- ctrsv ",                 \
               " qheaw gdnmz ",                 \
               " j,.k' bplfx i")

#define ___BEAKLWI___                                                   \
  LANG_MAP(TL_COLN, _Y,      _O,     _U, _MINS,   _C, _T, _R, _S, _V,   \
           _Q,      _H,      _E,     _A, _W,      _G, _D, _N, _M, _Z,   \
           _J,      TL_COMM, TL_DOT, _K, _QUOT,   _B, _P, _L, _F, _X)

// Thumbs.
#define ___BEAKLWI_CRKBD_THUMBS___ LT_ESC, LT_I, LT_TAB,  LT_ENT, LT_SPC, LT_BSPC

// My version, loses KC_mins, because it's easier on my symbol layer.
// put I in it's dvorak spot instead of thumbs, move W up to make room for I.
// I'd rather have w and i on different fingers. One domino...

// beakl-wi - mod iw-

#define CARTE_BEAKLWIa                          \
  carte_de_map(" ;youw ctrsv ",                 \
               " qheai gdnmz ",                 \
               " j,.k' bplfx ")

// Alt target is BKW
#define ___BEAKLWIa___                                                  \
  LANG_MAP(TL_COLN, _Y,      _O,     _U, _W,      _C, _T, _R, _S, _V,   \
           _Q,      _H,      _E,     _A, _I,      _G, _D, _N, _M, _Z,   \
           _J,      TL_COMM, TL_DOT, _K, _QUOT,   _B, _P, _L, _F, _X)
