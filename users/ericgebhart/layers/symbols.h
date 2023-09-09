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
/******************************************************************/
/*                                                                */
/* Symbol layers:                                                 */
/*                                                                */
/* The BEAKL15 Symbol layer with or without additions.            */
/*                                                                */
/* There is the offical beakl symbol layer, an extended symbol    */
/* layer which is expanded with: !?@`'/-;.                        */
/*                                                                */
/* Placing these 8 keys in the pinky and index corners            */
/* at the edges of the, 3x3, BEAKL home Region.                   */
/*                                                                */
/* Beakl has these keys in it's base layer which isn't the case   */
/* for other layouts like dvorak, colemak, etc.                   */
/*                                                                */
/* The third layer moves /:? to more accessible places.           */
/* to make vi keybindings more accessible.                        */
/*                                                                */
/* Note that there are 2 widths. 12 and 10. The wider layer adds  */
/* - and ; to the middle row edges.                               */
/*                                                                */
/* Official:                                                      */
/*         <$>   [_]                                              */
/*      - \(")# %{=}| ;                                           */
/*         :*+   &^~                                              */
/*                                                                */
/*   not yet implemented                                          */
/* BEAKL27 (punctuation layer):                                   */
/*   ↹@$#↹  ~^`                                                  */
/*   ↹<=>   [_]                                                   */
/*   \(-)+ %{;}!                                                  */
/*    *:/⏎  |~&                                                   */
/*                                                                */
/*                                                                */
/* BEAKL Extended symbol layer                                    */
/* Expanded with: !?@`'/-;                                        */
/*                                                                */
/* A:                                                             */
/*        `<$>' ?[_]-                                             */
/*      - \(")# %{=}| ;                                           */
/*        @:*+; !&^~/                                             */
/*                                                                */
/* Optimized for Vi.                                              */
/* B:                                                             */
/*                                                                */
/*        `<$>' ?[_]-                                             */
/*      - \(")# !{:}/ ;                                           */
/*        @=*+; %&^~|                                             */
/*                                                                */
/* C:                                                             */
/*                                                                */
/*        `<$>' ?[_-]                                             */
/*      - \("#) !{:/} ;                                           */
/*        @=*+; %&^~|                                             */
/*                                                                */
/*                                                                */
/* Both ; and ' could have found their dvorak positions. Analysis showed */
/* that only caused pinky overuse. Rotating the symbols around Put better */
/* keys on the index finger which showed a huge improvement in efficiency. */
/* The same is true of the exclamation point.                     */
/*                                                                */

/* Beakl Wi */

/* This Symbol layer does not improve on the above extended symbol */
/* layers in my opinon, for my usage. */

/* The original symbol was the Left side with defined/but/transparent */
/* right. The regex layer was the opposite. I combined them into one, I am */
/* not sure of the functionality that might be lost due to that, but they */
/* are defined as original sans extra tap dance functions. It would be easy to */
/* make two layers with transparent right and left. There is duplication */
/* of | and *. */

/* Symbols on the left */
/* .*&+ */
/* ?!/| */
/* <>%@ */

// regex on the right
/* *[^] */
/* ?($) */
/* |{#} */

// Altogether
/* .*&+  *[^] */
/* ?!/|  ?($) */
/* <>%@  |{#} */
/******************************************************************/

// Left
#define ___SB_L1___          _OCLTGT, _DLR,    _GT
#define ___SB_L2___  _BSLS,  _OCPRN,  _OCDQUO, _RPRN, _HASH
#define ___SB_L2c___ _BSLS,  _OCPRN,  _OCDQUO, _HASH, _RPRN
#define ___SB_L3___          _COLN,   _ASTR,   _PLUS

// Right
#define ___SB_R1___          _OCBRC,   _UNDS,     _RBRC
#define ___SB_R1c___         _OCBRC,   _UNDS,     _MINS
#define ___SB_R2___  _PERC,  _OCCBR,   _EQL,      _RCBR,  _PIPE
#define ___SB_R3___          _AMPR,    _CIRC_ND,  _TILD_ND

// a and b... left and right.
#define ___SB_L3b___          _EQL,    _ASTR,   _PLUS

#define ___SB_R2a___ _PERC,  _OCCBR,   _EXLM,  _RCBR,  _PIPE
#define ___SB_R2b___ _EXLM,  _OCCBR,   _COLN,  _RCBR,  _SLSH
#define ___SB_R2c___ _EXLM,  _OCCBR,   _COLN,  _SLSH,  _RCBR

// ---------------------------
// ---------------------------
#define CARTE_SYMB_BEAKL                        \
  carte_de_map("  <$>   [_]   ",                \
               "-\\(\")# %{=}|;",               \
               "  :*+   &^~   ")

#define ___SYMB_BEAKL_3x10___                                           \
  CHUNK_LANG_MAP(_TRNS,   ___SB_L1___, _TRNS,    _TRNS,  ___SB_R1___, _TRNS, \
                 ___SB_L2___,                    ___SB_R2___,           \
                 _TRNS,   ___SB_L3___, _TRNS,    _TRNS, ___SB_R3___, _TRNS)

// ---------------------------
// A: Extended.
#define CARTE_SYMB_BEAKLA                       \
  carte_de_map("   `<$>'  ?[_]-",               \
               "  -\\(\")#  %{:}|;",            \
               "   @=*+;  !&^~/")

#define ___SYMB_BEAKLA_3x10___                                          \
  CHUNK_LANG_MAP(_OCGRV, ___SB_L1___, _OCQUOT,   _QUES,  ___SB_R1___, _MINS, \
                 ___SB_L2___,                    ___SB_R2a___,          \
                 _AT,    ___SB_L3___, _SCLN,     _EXLM, ___SB_R3___, _SLSH)

// ---------------------------
// B: Extended & Vi
#define CARTE_SYMB_BEAKLB                       \
  carte_de_map("   `<$>'  ?[_]-",               \
               "  -\\(\")#  !{:}/;",            \
               "   @=*+;  %&^~|")

#define ___SYMB_BEAKLB_3x10___                                          \
  CHUNK_LANG_MAP(_OCGRV, ___SB_L1___,  _OCQUOT,   _QUES,  ___SB_R1___, _MINS, \
                 ___SB_L2___,                     ___SB_R2b___,         \
                 _AT,    ___SB_L3b___, _SCLN,     _PERC, ___SB_R3___, _PIPE)

// ---------------------------
// C: Extended & Vi, move closing braces to pinky, seldom used.
// because of tap hold - open_openclose feature.
// Also emacs which mostly closes them.
#define CARTE_SYMB_BEAKLC                       \
  carte_de_map("   `<$>'  ?[_-]",               \
               "  -\\(\"#)  !{:/};",            \
               "   @=*+;  %&^~|")

#define ___SYMB_BEAKLC_3x10___                                          \
  CHUNK_LANG_MAP(_OCGRV, ___SB_L1___,  _OCQUOT,   _QUES,  ___SB_R1c___, _RBRC, \
                 ___SB_L2c___,                     ___SB_R2c___,        \
                 _AT,    ___SB_L3b___, _SCLN,     _PERC, ___SB_R3___, _PIPE)

// wants ( and ) on the left thumb.
#define CARTE_SYMB_MIRYOKU                                  \
  carte_de_map("  {&.(} ",                                  \
               "  :$%^+ ",                                  \
               "  ~!@#| ")

#define ___SYMB_MIRYOKU_3x10___                         \
  CHUNK_LANG_MAP(_OCCBR,   _AMPR, _DOT,  _OCPRN,   _RCBR, ____5_,     \
                 _COLN,    _DLR,  _PERC, _CIRC_ND, _PLUS, ____5_,     \
                 _TILD_ND, _EXLM, _AT,   _HASH,    _PIPE, ____5_)

// ---------------------------
// WI: the Beakl Wi definition.
#define ___SYMB_BKL_WI_L1___ ___,   _DOT,  _ASTR, _AMPR, _PLUS
#define ___SYMB_BKL_WI_L2___ ___,   _QUES, _EXLM, _SLSH, _PIPE
#define ___SYMB_BKL_WI_L3___ ___,   _LT,   _GT,   _PERC, _AT

#define ___SYMB_BKL_WI_R1___ _ASTR, _OCBRC, _CIRC_ND, _RBRC, ___
#define ___SYMB_BKL_WI_R2___ _QUES, _OCPRN, _DLR ,    _RPRN, ___
#define ___SYMB_BKL_WI_R3___ _PIPE, _OCCBR, _HASH,    _RCBR, ___

#define CARTE_SYMB_BEAKLWI                      \
  carte_de_map(" .*&+  *[^] ",                  \
               " ?!/|  ?($) ",                  \
               " <>%@  |{#} ")

#define ___SYMB_BEAKL_WI_3x10___                                \
  CHUNK_LANG_MAP(___SYMB_BKL_WI_L1___, ___SYMB_BKL_WI_R1___,    \
                 ___SYMB_BKL_WI_L2___, ___SYMB_BKL_WI_R2___,    \
                 ___SYMB_BKL_WI_L3___, ___SYMB_BKL_WI_R3___)

// ---------------------------
// Neo symbol layer
#define ___SYMB_NEO_L1___ ___,  _OCDQUOT, _UNDS,  _OCLBRC, _RBRC, _CIRC_ND
#define ___SYMB_NEO_L2___ ___,  _SLSH,  _MINS,  _OCLCBR, _RCBR, _ASTR
#define ___SYMB_NEO_L3___ ___,  _HASH,  _DLR,   _PIPE, _TILD_ND, _OCGRV

#define ___SYMB_NEO_R1___ _EXLM, _LT,    _GT,    _EQL,  _AMPR
#define ___SYMB_NEO_R2___ _QUES, _OCPRN, _RPRN , _QUOT, _COLN
#define ___SYMB_NEO_R3___ _PLUS, _PERC,  _BSLS,  _AT,   ___

#define CARTE_SYMB_NEO                          \
  carte_de_map("\"_[]^  !<>=&",                 \
               "/-{}*  ?()':",                  \
               "#$|~`  +%\@")

#define ___SYMB_NEO_3x10___                                     \
  CHUNK_LANG_MAP(___SYMB_NEO_L1___, ___SYMB_NEO_R1___,          \
                 ___SYMB_NEO_L2___, ___SYMB_NEO_R2___,          \
                 ___SYMB_NEO_L3___, ___SYMB_NEO_R3___)
