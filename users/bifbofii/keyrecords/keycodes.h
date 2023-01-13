/* Copyright 2022 Christoph Jabs (BifbofII)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "bifbofii.h"

enum userspace_custom_keycodes {
    KC_QWERTY                   = QK_USER,   // Sets default layer to QWERTY
    FIRST_DEFAULT_LAYER_KEYCODE = KC_QWERTY, // Sets default layer to QWERTY
    KC_COLEMAK,                              // Sets default layer to COLEMAK
    KC_DVORAK,                               // Sets default layer to DVORAK
    LAST_DEFAULT_LAYER_KEYCODE = KC_DVORAK,  // Sets default layer to WORKMAN
    NEW_SAFE_RANGE                           // use "NEWPLACEHOLDER for keymap specific codes
};

// Weakly defined keymap variants of callbacks implemented
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

// Layer switching
#define ADJUST MO(_ADJUST)
#define FUNC_SPACE LT(_FUNC, KC_SPACE)
#define UNICODE_ESC LT(_UNICODE, KC_ESC)
#ifdef RAISE_LOWER
#    define LOWER MO(_LOWER)
#    define RAISE MO(_RAISE)
#    define FUNC2 XXXXXXX
#else
#    define LOWER XXXXXXX
#    define RAISE XXXXXXX
#    define FUNC2 MO(_FUNC2)
#endif
#ifdef GAMING_ENABLE
#    define GAMING TG(_GAMING)
#else
#    define GAMING XXXXXXX
#endif
#define SFT_ENT RSFT_T(KC_ENT)
#define SFT_ESC LSFT_T(KC_ESC)
#define GUI_BSPC RGUI_T(KC_BSPC)
#define CTL_DEL RCTL_T(KC_DEL)

#define QWERTY KC_QWERTY
#define COLEMAK KC_COLEMAK
#define DVORAK KC_DVORAK

// Unicode
#define KC_AE XP(SAE, CAE)
#define KC_UE XP(SUE, CUE)
#define KC_OE XP(SOE, COE)
#define KC_SS X(SS)
#define KC_EUR X(EUR)
#define KC_CPR X(CPR)
