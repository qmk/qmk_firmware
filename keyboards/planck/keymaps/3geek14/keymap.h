/* Copyright 2023 Pi Fisher
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
#include "quantum.h"

enum planck_layers {
    _QWERTY,
    _COLEMAK_DH, // one day…I might learn this
    _RAISE,
    _LOWER,
    _MUSIC,
    _ADJUST,
    _UTILS,
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    END_MUS,
    SHRUG,
    SIGNATURE,
    EMAIL,
    THUMB_U,
    WAVE,
    EYES,
    INTERRO,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SCREEN_LEFT LCTL(LGUI(KC_LEFT))
#define SCREEN_RIGHT LCTL(LGUI(KC_RIGHT))
#define SCREENSHOT LGUI(LSFT(KC_S))
