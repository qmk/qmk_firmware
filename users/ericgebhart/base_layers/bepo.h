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
// Maps based on BEPO  Mostly 3x12

// BEAKL 19bis - English with French optimisations.
// Least used letters in french xzykw QJÀ are fairly high.
// XZ are good choices for pushing out, from english and french,
// or using chords in both languages.

// Note: The percentages came from different sources so do not
// match between languages.
// French
/* Q	0.89 % */
/* J	0.71 % */
/* À	0.54 % */
/*-------------*/
/* X	0.42 % */
/* È	0.35 % */
/* Ê	0.24 % */
/* Z	0.21 % */
/* Y	0.19 % */
/* K	0.16 % */
/* Ô	0.07 % */
/* Û	0.05 % */
/* W	0.04 % */

/* Least used letters in english. */
/* X	0.2902%	1.48 */
/* Z	0.2722%	1.39 */
/* J	0.1965%	1.00 */
/* Q	0.1962%	(1) */


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

// swap z, e's, add à, ^, and ê, swap ; for -.
// it might be beneficial to swap w and à, as à is much more frequent than w
#define CARTE_BEAKL19bis                        \
  carte_de_map(" àqyoué  wdnck^ ",             \
               " ;hiea,  gtrsp- ",             \
               " zj'è.x  vmlfbê  ")

#define ___BEAKL19bis_3x12___                                           \
  LANG_MAP6(                                                            \
            _AGRV, _Q, _Y,    _O,    _U,   _EACU,   _W, _D, _N, _C, _K, _DCIR, \
            _SCLN, _H, _I,    _E,    _A,   _COMM,   _G, _T, _R, _S, _P, _MINS, \
            _Z,    _J, _QUOT, _EGRV, _DOT, _X,      _V, _M, _L, _F, _B, _ECIR)

// OPtimot by @Pyjam.
/*  àjoéb fdl’qxz */
/*  aieu, ptsrn^ç */
/* êkyè.w gcmhvz */

// -- rearranged z, and ç to get 3x12
#define CARTE_OPTIMOT                           \
  carte_de_map(" çàjoéb fdl’qx ",               \
               "  aieu, ptsrn^ ",               \
               " êkyè.w gcmhvz ")

#define ___OPTIMOT_3x12___                                              \
  LANG_MAP6(                                                            \
            _CCED, _AGRV, _J, _O,    _EACU, _B,     _F, _D, _L, _QUOT, _Q,  _X, \
            _TAB,  _A,    _I, _E,    _U,    _COMM,  _P, _T, _S, _R,    _N,  _DCIR, \
            _ECIR, _K,    _Y, _EGRV, _DOT,  _W,     _G, _C, _M, _H,    _V,  _Z)

// Maybe Use this for C
//BP_C_CCED = MT(BP_CCED, BP_C)

// BEPO

// No quot, à or ç
/* bépoè vdljz */
/* auie, ctsrn */
/* myx.k qghfw */
#define CARTE_BEPOc                             \
  carte_de_map("   bépoè  vdljz",               \
               "   auie,  ctsrn",               \
               "   myx.k  qghfw")

#define ___BEPOc_3x10___                                        \
  LANG_MAP(                                                     \
           _B, _EACU, _P, _O,   _EGRV,    _V, _D, _L, _J, _Z,   \
           _A, _U,    _I, _E,   _COMM,    _C, _T, _S, _R, _N,   \
           _M, _Y,    _X, _DOT, _K,       _Q, _G, _H, _F, _W)


#define CARTE_BEPO                              \
  carte_de_map(" çbépoè ^vdljz ",               \
               "  auie, ctsrnm ",               \
               " êàyx.k ’qghfw ")

#define ___BEPO_3x12___                                                 \
  LANG_MAP6(_CCED, _B,    _EACU, _P, _O,   _EGRV,    _DCIR, _V, _D, _L, _J, _Z, \
            _TAB,  _A,    _U,    _I, _E,   _COMM,    _C,    _T, _S, _R, _N, _M, \
            _ECIR, _AGRV, _Y,    _X, _DOT, _K,       _QUOT, _Q, _G, _H, _F, _W)


// probably best to have e and é on different fingers.
#define CARTE_ACCENTED                          \
  carte_de_map(" æœêùì  ¿ïüöë ",                \
               " àôèéî  ûçñß^",                 \
               " âöíúí       ")

#define ___ACCENTED_BP___                                               \
  LANG_MAP(_AE,   _OE,   _ECIR, _UGRV, _IGRV,   _IQUE, _IIAE, _UIAE, _OIAE, _EIAE, \
           _AGRV, _OCIR, _EGRV, _EACU, _ICIR,   _UCIR, _CCED, _NTIL, _SS,   _DCIR, \
           _AACU, _ODIA, _IACU, _UACU, _IACU,   _SPC,  _SPC,  _SPC , _SPC,  _SPC)


// A dead key layer, optimized for Most common,
// western european.
#define CARTE_MORTE                             \
  carte_de_map(" ˝˘̉   ̛ ˙° ",                    \
               "/`^´  ¸¨~¤",                    \
               " ,ˇ.  ˛µ¯")

#define ___MORTE_BP___                                                  \
  LANG_MAP(_,     _DACU, _BREV, _HOKA, _,   _, _HORN, _DOTA, _RNGA, _,  \
           _DSLS, _DGRV, _DCIR, _ACUT, _,   _, _CEDL, _DIAE, _DTIL, _CURR, \
           _,     _DCMM, _CARN, _DOTB, _,   _, _OGON, _DGRK, _MACR, _)

// Just taking a guess and putting the things I know are most
// used in easy to use places., not sure about ntil and ss, put
// them in their dvorak spots on the home row.
#define CARTE_ACCENTED_MORTE                    \
  carte_de_map(" æœêùì  ¿`^´ë ",                \
               " àôèéî  ¸çñß~",                 \
               " âö,úí   ¨ˇ°   ")

#define ___ACCENTED_MORTE_BP___                                         \
  LANG_MAP(_AE,   _OE,    _ECIR,  _UGRV,  _IGRV,    _IQUE, _DGRV, _DCIR, _ACUT, _EIAE, \
           _AGRV, _OCIR,  _EGRV,  _EACU,  _ICIR,    _CEDL, _CCED, _NTIL, _SS,   _DTIL, \
           _AACU, _OIAE,  _DCMM,  _UACU,  _IACU,    _OGON, _DIAE, _CARN, _RNGA, _HORN)

/* // DEAD layer. */
/* BP_DCIR // ^ (dead) */
/* BP_ACUT // ´ (dead) */
/* BP_DGRV // ` (dead) */
/* BP_CARN // ˇ (dead) */
/* BP_DSLS // / (dead) */
/* BP_BREV // ˘ (dead) */
/* BP_DIAE // ¨ (dead) */
/* BP_DTIL // ~ (dead) */
/* BP_MACR // ¯ (dead) */
/* BP_CEDL // ¸ (dead) */
/* BP_RNGA // ° (dead) */
/* BP_DGRK // µ (dead Greek key) */
/* BP_OGON // ˛ (dead) */
/* BP_DACU // ˝ (dead) */
/* BP_DOTA // ˙ (dead) */
/* BP_CURR // ¤ (dead) */
/* BP_HORN // ̛  (dead) */
/* BP_DCMM // , (dead) */
/* BP_HOKA // ̉  (dead) */
/* BP_DOTB // ̣  (dead) */
