/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
#ifdef EUCALYN_LAYER_ENABLE
  B_LAYER(LANG_N(_EUCALYN), ___10_NUMBERS___, ___EUCALYN___),
#endif
#ifdef MALTRON_LAYER_ENABLE
#undef THUMBS_ARE
#define THUMBS_ARE MALTRON_LTR_THUMBS_ARE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_E)
    B_LAYER(LANG_N(_MALTRON), ___10_NUMBERS___, ___MALTRON___),
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#undef THUMB_LETTER
#endif

#ifdef CARPLAX_LAYER_ENABLE
  B_LAYER(LANG_N(_CARPLAX), ___10_NUMBERS___, ___CARPLAX_QGMLWY___),
#endif

#ifdef MTGAP_LAYER_ENABLE
  B_LAYER(LANG_N(_MTGAP), ___10_NUMBERS___, ___MTGAP___),
#endif

#ifdef APT_LAYER_ENABLE
    B_LAYER(LANG_N(_APT), ___10_NUMBERS___, ___APT___),
#endif

#ifdef RSTHD_LAYER_ENABLE
#undef THUMBS_ARE
#define THUMBS_ARE RSTHD_LTR_THUMBS_ARE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_E)
    B_LAYER(LANG_N(_RSTHD), ___10_NUMBERS___, ___RSTHD___),
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#undef THUMB_LETTER
#endif
