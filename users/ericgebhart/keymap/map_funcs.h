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
// navigation.  Mouse keys, arrows, home,end, etc.
#ifdef NAV_LAYER_ENABLE
#  ifdef MOUSEKEY_ENABLE
#      undef THUMBS_ARE
#      define THUMBS_ARE MOUSE_LAYER_THUMBS

#    ifdef NAV_FULL_LOCK_MODS
T_LAYER(_NAV, ___NAVA_3x10___),
#    endif

#    ifdef NAV_FULL
  T_LAYER(_NAV, ___NAV_3x10___),
#    endif

#    ifdef NAV_NO_MOUSE
  T_LAYER(_NAV, ___NAVnm_3x10___),
  T_LAYER(_NAVm, ___NAVm_3x10___),
#    endif

// give a default
#    if !defined(NAV_FULL) &&           \
        !defined(NAV_NO_MOUSE) &&       \
        !defined(NAV_FULL_LOCK_MODS)    \

  T_LAYER(_NAV, ___NAVA_3x10___),
#    endif

#    ifdef MOUSE_LAYER_ENABLE
  T_LAYER(_NAVm, ___NAVm_3x10___),
#    endif

#    undef THUMBS_ARE
#    define THUMBS_ARE DEFAULT_THUMBS

#  else // no mouse enable.
  T_LAYER(_NAV, ___NAVnm_3x10___),
#  endif // mousekey end.
#endif //nav end.

#ifdef MEDIA_LAYER_ENABLE
#undef THUMBS_ARE
#define THUMBS_ARE MEDIA_LAYER_THUMBS
  T_LAYER(_MEDIA, ___MEDIA_3x10___),
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#endif

#ifdef FUN_LAYER_ENABLE

#ifdef FUNCPAD_MIRYOKU_ENABLE
  T_LAYER(_FUN, ___FUN_3x10___),
#else
  T_LAYER(_FUN, ___FUN_MIRYOKU_3x10___),
#endif

#endif

// A layer for layers. to set the default, etc.
  T_LAYER(_LAYERS, ___LAYERS_3x10___),

// control the RGB if there are any.
#ifdef RGB_LAYER_ENABLE
  T_LAYER(_RGB, ___RGB_3x10___),
#endif

// control and adjust stuff.
#ifdef ADJUST_LAYER_ENABLE
  T_LAYER(_ADJUST, ___ADJUST_3x10___),
#endif


// put the combo reference layers at the end.
#ifdef COMBO_REF_LAYER_ENABLE
#undef LANG_IS
#define LANG_IS COMBO
#undef EDGE_KEY_SET_IS
#define EDGE_KEY_SET_IS REF1
#undef THUMBS_ARE
#define THUMBS_ARE COMBO
#undef MODS_ARE
#define MODS_ARE TRNS
  B_LAYER(_COMBO_REF, ___10_NUMBERS___, ___COMBO_REF___),
#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#undef EDGE_KEY_SET_IS
#define EDGE_KEY_SET_IS DEFAULT_EDGE_SET
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#undef MODS_ARE
#define MODS_ARE DEFAULT_MODS
#endif

#ifdef COMBO_REF_LAYER_TWO_ENABLE
#undef LANG_IS
#define LANG_IS COMBO2
#undef EDGE_KEY_SET_IS
#define EDGE_KEY_SET_IS REF2
#undef THUMBS_ARE
#define THUMBS_ARE COMBO2
#undef MODS_ARE
#define MODS_ARE TRNS
  B_LAYER(_COMBO_REF2, ___10_NUMBERS___, ___COMBO_REF___),
#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#undef EDGE_KEY_SET_IS
#define EDGE_KEY_SET_IS DEFAULT_EDGE_SET
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#undef MODS_ARE
#define MODS_ARE DEFAULT_MODS
#endif
