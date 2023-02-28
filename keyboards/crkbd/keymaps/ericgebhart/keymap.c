/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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
#include "ericgebhart.h"

#define Crkbd_base(...)        Base_3x6_3(__VA_ARGS__)
#define Crkbd_bepo(...)        Base_bepo_3x6_3(__VA_ARGS__)
#define Crkbd_bepo6(...)       Base_bepo6_3x6_3(__VA_ARGS__)
#define Crkbd_transient(...)   Transient6_3x6_3(__VA_ARGS__)

/*
 * The `Crkbd_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Qwerty based Base layers
    [_DVORAK]  = Crkbd_base(___DVORAK___),
    [_BEAKL]   = Crkbd_base(___BEAKL15___),
    [_COLEMAK] = Crkbd_base(___COLEMAK_DH___),
    [_QWERTY]  = Crkbd_base(___QWERTY___),

    // Bepo base layers
    [_BEAKL_BP]  = Crkbd_bepo(___BEAKL15_FR___),
    [_DVORAK_BP] = Crkbd_bepo(___DVORAK_FR___),
    [_BEPO]      = Crkbd_bepo6(___BEPO6___),

    // Transient layers.
    [_SYMB]    = Crkbd_transient(___SYMB_BEAKLB_3x12___),
    [_SYMB_BP] = Crkbd_transient(___SYMB_BEAKLB_BP_3x12___),

    [_KEYPAD]    = Crkbd_transient(___KP_C_3x12___),
    [_KEYPAD_BP] = Crkbd_transient(___KP_C_BP_3x12___),

    [_TOPROWS]    = Crkbd_transient(___TOPROWS_3x12___),
    [_TOPROWS_BP] = Crkbd_transient(___TOPROWS_BP_3x12___),

    [_NAV] = Crkbd_transient(___NAV_3x12___),

    [_LAYERS] = Crkbd_transient(___LAYERS_3x12___),
    //[_RGB] = Crkbd_transient(___RGB_3x12___),
    [_ADJUST] = Crkbd_transient(___ADJUST_3x12___),
    ///HPT_TOG, KC_NUKE, ___,        ___, TG_MODS, HPT_FBK
};
