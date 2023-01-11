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
/********************************************************************************/
/* MEDIA  - Mute, Vol, play, pause, stop, next, prev, etc.   */
/********************************************************************************/
#define ___PRV_PLAY_NXT_STOP___ KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___VDN_MUTE_VUP___ KC_VOLD, KC_MUTE, KC_VOLU

#define ___PRV_VDN_VUP_NXT___ KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
#define ___STOP_PLAY_MUTE___ KC_MSTP, KC_MPLY, KC_MUTE

#define ___MUTE_PRV_PLAY_NXT_STOP___  KC_MUTE,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___MUTE_PLAY_STOP___  KC_MUTE,  KC_MPLY,  KC_MSTP

#define CARTE_MEDIA                      \
  carte_de_map(" ",                      \
               "  < vdn vup >",          \
               "  stp play mute")

// miryoku, to be used with stop play mute on thumbs. - MEDIA thumbs.
#define ___MEDIA_3x10___                        \
  ___5___, ___5___,                             \
    ___5___, ___, ___PRV_VDN_VUP_NXT___,        \
    ___5___, ___5___


/********************************************************************************/
/* RGB  - Control those lights.                                                 */

/* ___, HUE SAT_INT MOD (UP),            | */
/* ___, HUE SAT INT MOD (DOWN), RGB_TOG  | P_B_R_SW_SN___, ___ */
/* ___6___,                              | ___, ___RGB_KXGT___, ___ */
/********************************************************************************/
// RGB FUNCTION Keysets
// RGB row for the _FN layer from the redo of the default keymap.c
#define ___RGB_HUE_SAT_INT_UP___ RGB_HUI, RGB_SAI, RGB_VAI, RGB_RMOD
#define ___RGB_HUE_SAT_INT_DN___ RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD
#define ___RGB_MODE_PRV_NXT___   RGB_RMOD, RGB_MOD
#define ___RGB_TOGGLE___         RGB_TOG
#define ___RGB_P_B_R_SW_SN___    RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN
#define ___RGB_KXGT___           RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T

/// An RGB Layer
#define ___10_RGB_1___ ___RGB_HUE_SAT_INT_UP___, ___,     ___5___
#define ___10_RGB_2___ ___RGB_HUE_SAT_INT_DN___, RGB_TOG, ___RGB_P_B_R_SW_SN___
#define ___10_RGB_3___ ___5___,                                ___, ___RGB_KXGT___

/********************************************************************************/
/* The RGB LAYER Chunk                                                          */
/********************************************************************************/
#define ___RGB_3x10___ ___10_RGB_1___, ___10_RGB_2___, ___10_RGB_3___


/********************************************************************************/
/* ADJUST - Miscellaneous Melange.                                              */
/********************************************************************************/
// For an Adjust layer. Like RBB with audio, flash, etc.
#define ___ADJUST_L1___ ___RGB_HUE_SAT_INT_UP___,       RGB_TOG
#define ___ADJUST_L2___ MU_TOG, CK_TOGG, AU_ON, AU_OFF, CG_NORM
#define ___ADJUST_L3___ ___RGB_HUE_SAT_INT_DN___,       KC_RGB_T

#define ___ADJUST_R1___  ___, KC_MAKE, VRSN, MG_NKRO, KC_RESET
#define ___ADJUST_R2___  EE_CLR, ___PRV_PLAY_NXT_STOP___,
#define ___ADJUST_R3___  MG_NKRO, ___VDN_MUTE_VUP___, RGB_IDL
/********************************************************************************/
/* The Adjust LAYER Chunks                                                      */
/********************************************************************************/
#define ___ADJUST_3x10___  ___ADJUST_L1___, ___ADJUST_R1___,    \
    ___ADJUST_L2___, ___ADJUST_R2___,                           \
    ___ADJUST_L3___, ___ADJUST_R3___


/********************************************************************************/
/* LAYERS - Define a base layer, switch to any layer. Get around. Experiment.   */
/*                                                                              */
/* Base Layers on the left hand,                                                */
/* transient layers on the right. Centered on the home region.                  */
/* A good place to attach an experimental layer.                                */
/*                                                                              */
/********************************************************************************/
//  Base Layers
// this was kc_dvorak et al. But since its configurable as to who would be here
// that no longer makes sense. So next keys for locale and base layer. and a set to
// make it permanent. Cycling of layers is based on current locale.
#define ___BASE_LAYERS___ ___, KC_SET_BASE, KC_NEXT_BASE_LAYER, KC_NEXT_LOCALE, ___

// transient layers.
#define ___5_LAYERS_T___     ___, MO(_NAV),  MO_SYMB,  MO_KEYPAD,  MO_TOPROWS
#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE
#define ___5_LAYERS_T_BP___  ___, MO(_NAV),  MO_SYMB,  MO_KEYPAD,  MO_TOPROWS
#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#else
#define ___5_LAYERS_T_BP___  ___, MO(_NAV),  ___3___
#endif

#define ___5_LAYERS_T_CTL___ ___, MO_RGB, ___, ___, MO_ADJUST


#define CARTE_LAYERS                            \
  carte_de_map("          |Nv S K TR",          \
               "  EE Bs Ln|Nv S K TR",          \
               " ")

/// A Layers Layer
#define ___LAYERS_3x10___                       \
  ___5___,            ___5_LAYERS_T_BP___,      \
    ___BASE_LAYERS___,  ___5_LAYERS_T___,       \
    ___5___,            ___5_LAYERS_T_CTL___
