/* Copyright 2021 Alexis Jeandeau
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

// tap dance keys
enum tap_dance {
    _ASTR = 0,
    _BSPC,
    _COLM,
    _COLN,
    _COMM,
    _DEL,
    _DOT,
    _DQOT,
    _EMOJ,
    _ENT,
    _EQL,
    _GRV,
    _GT,
    _LT,
    _PASTE,
    _PERC,
    _QUOT,
    _SCLN,
    _SEND,
    _SPC,
    _TILD,
    _XPASTE,
};

#define TD_ASTR TD(_ASTR)
#define TD_BSPC TD(_BSPC)
#define TD_COMM TD(_COMM)
#define TD_COLM TD(_COLM)
#define TD_COLN TD(_COLN)
#define TD_DEL TD(_DEL)
#define TD_DOT TD(_DOT)
#define TD_DQOT TD(_DQOT)
#define TD_EMOJ TD(_EMOJ)
#define TD_ENT TD(_ENT)
#define TD_EQL TD(_EQL)
#define TD_GRV TD(_GRV)
#define TD_GT TD(_GT)
#define TD_LT TD(_LT)
#define TD_PASTE TD(_PASTE)
#define TD_PERC TD(_PERC)
#define TD_QUOT TD(_QUOT)
#define TD_SCLN TD(_SCLN)
#define TD_SEND TD(_SEND)  // config.h defined macro string
#define TD_SPC TD(_SPC)    // see process_record_user() for extended handling of Spc
#define TD_TILD TD(_TILD)
#define TD_XPASTE TD(_XPASTE)
