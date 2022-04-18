/*
Copyright 2022 Hector Galindo <hi@hsuchil.com>

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

#pragma once

enum custom_user_layers {
    _BSE,
    _LOW,
    _HGH,
    _FNC,
    NEW_SAFE_LAYER_RANGE,
};

enum custom_user_keycodes {
    OLD_SAFE_RANGE = SAFE_RANGE,
    TOG_MAC,                     // Swaps LGUI<->LALT and LGUI<->RCTL
    NEW_SAFE_RANGE               // Set a new safe range for keymap-specific custom keycodes
};

#define L_LOW MO(_LOW)
#define L_HGH MO(_HGH)
#define L_FNC MO(_FNC)

#define L_BLOW LT(_LOW, KC_B) // B if tapped, LOW if held.
#define L_BHGH LT(_HGH, KC_B) // B if tapped, HGH if held.
#define L_BFNC LT(_FNC, KC_B) // B if tapped, FNC if held.

#define L_LWESC LT(_LOW, KC_ESC) // ESC if tapped, LOW if held.

#define LCT_ESC LCTL_T(KC_ESC) // ESC if tapped, LCTL if held.
#define RCT_ESC RCTL_T(KC_ESC) // ESC if tapped, RCTL if held.
