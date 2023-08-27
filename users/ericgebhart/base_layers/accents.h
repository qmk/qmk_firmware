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

// probably best to have e and é on different fingers.

// doesnt work, oled displays garbage
/* #define CARTE_ACCENTED                          \ */
/*   carte_de_map(" æœêùì  ¿ïüöë ",                \ */
/*                " àôèéî  ûçñß^",                 \ */
/*                " âöíúí       ") */

// need to figure out a better way to display these on the oled.
#define CARTE_ACCENTED                          \
  carte_de_map(" aoeui  ?iuoe ",                \
               " aoeei  ucnS^",                 \
               " aoiúi       ")

#define ___ACCENTED___                                                  \
  LANG_MAP(_AE,   _OE,   _ECIR, _UGRV, _IGRV,   _IQUE, _IIAE, _UIAE, _OIAE, _EIAE, \
           _AGRV, _OCIR, _EGRV, _EACU, _ICIR,   _UCIR, _CCED, _NTIL, _SS,   _DCIR, \
           _AACU, _ODIA, _IACU, _UACU, _IACU,   _SPC,  _SPC,  _SPC , _SPC,  _SPC)


// A dead key layer, optimized for Most common,
// western european.
#define CARTE_MORTE                             \
  carte_de_map(" ˝˘̉   ̛ ˙° ",                    \
               "/`^´  ¸¨~¤",                    \
               " ,ˇ.  ˛µ¯")

#define ___MORTE___                                                     \
  LANG_MAP(_,     _DACU, _BREV, _HOKA, _,   _, _HORN, _DOTA, _RNGA, _,  \
           _DSLS, _DGRV, _DCIR, _ACUT, _,   _, _CEDL, _DIAE, _DTIL, _CURR, \
           _,     _DCMM, _CARN, _DOTB, _,   _, _OGON, _DGRK, _MACR, _)

// Just taking a guess and putting the things I know are most
// used in easy to use places., not sure about ntil and ss, put
// them in their dvorak spots on the home row.

/* #define CARTE_ACCENTS_MORTE                     \ */
/*   carte_de_map(" æœêùì  ¿`^´ë ",                \ */
/*                " àôèéî  ¸çñß~",                 \ */
/*                " âö,úí   ¨ˇ°   ") */

#define CARTE_ACCENTS_MORTE                     \
  carte_de_map(" aoeui  ?`^'e ",                \
               " aoeei  ,cnS~",                 \
               " ao,ui   \"^o")

#define ___ACCENTS_MORTE___                                             \
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
