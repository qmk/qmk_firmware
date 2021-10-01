/* Copyright 2021 Christian C. Berclaz
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

// Standard layers

enum CHRISGVE_layers {
    _QWERTY_MAC,
    _DIR,
    _FULL_DIR,
    _QWERTY_LINUX,
    _QWERTY_WIN,
    _ADJUST,
    _CONFIG,
    _FN,
    _TMUX,
    _VIM,
};

#define CHAR_MOVE   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
#define LINE_MOVE   KC_HOME, KC_PGDN, KC_PGUP, KC_END


#define CPS_CTL     CTL_T(KC_CAPS)
#define ADJUST      MO(_ADJUST)
#define CONFIG      MO(_CONFIG)
#define FN          MO(_FN)
#define D_DIR       LT(_DIR, KC_D)
#define F_DIR       MO(_FULL_DIR)
#define F_WORD      A(KC_RIGHT)
#define B_WORD      A(KC_LEFT)

/*
 * Move via D + any of CHAR_MOVE or D + F + any of LINE_MOVE
 * Hidden keys, e.g. function keys, via Fn + Adjust layer
 * Configuation keys via Fn +
 */
