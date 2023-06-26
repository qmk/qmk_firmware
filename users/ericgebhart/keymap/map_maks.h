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
#ifdef COLEMAK_LAYER_ENABLE
B_LAYER(LANG_N(_COLEMAK), ___10_NUMBERS___, ___COLEMAK___),
#endif
#ifdef COLEMAK_DH_LAYER_ENABLE
  B_LAYER(LANG_N(_COLEMAK_DH), ___10_NUMBERS___, ___COLEMAK_DH___),
#endif
#ifdef HALMAK_LAYER_ENABLE
  B_LAYER(LANG_N(_HALMAK), ___10_NUMBERS___, ___HALMAK___),
#endif
#ifdef MINIMAK_LAYER_ENABLE
  B_LAYER(LANG_N(_MINIMAK), ___10_NUMBERS___, ___MINIMAK___),
#endif
#ifdef MINIMAK_8_LAYER_ENABLE
  B_LAYER(LANG_N(_MINIMAK_8), ___10_NUMBERS___, ___MINIMAK___),
#endif
#ifdef MINIMAK_12_LAYER_ENABLE
  B_LAYER(LANG_N(_MINIMAK_12), ___10_NUMBERS___, ___MINIMAK___),
#endif
#ifdef SEMIMAK_JQ_LAYER_ENABLE
  B_LAYER(LANG_N(_SEMIMAK_JQ), ___10_NUMBERS___, ___SEMIMAK_JQ___),
#endif
#ifdef SEMIMAK_LAYER_ENABLE
  B_LAYER(LANG_N(_SEMIMAK), ___10_NUMBERS___, ___SEMIMAK___),
#endif

#ifdef APTMAK_LAYER_ENABLE
#undef THUMBS_ARE
#define THUMBS_ARE APTMAK_LTR_THUMBS_ARE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_E)
  B_LAYER(LANG_N(_APTMAK), ___10_NUMBERS___, ___APTMAK___),
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#undef THUMB_LETTER
#endif
#ifdef APTMAK_30_LAYER_ENABLE
#undef THUMBS_ARE
#define THUMBS_ARE APTMAK_LTR_THUMBS_ARE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_E)
  B_LAYER(LANG_N(_APTMAK_30), ___10_NUMBERS___, ___APTMAK_30___),
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#undef THUMB_LETTER
#endif
#ifdef APTMAK_ALT_LAYER_ENABLE
#undef THUMBS_ARE
#define THUMBS_ARE APTMAK_LTR_THUMBS_ARE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_E)
  B_LAYER(LANG_N(_APTMAK_ALT), ___10_NUMBERS___, ___APTMAK_ALT___),
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#undef THUMB_LETTER
#endif
