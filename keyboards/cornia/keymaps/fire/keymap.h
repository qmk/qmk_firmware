/* Copyright 2024 Vaarai
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

#include QMK_KEYBOARD_H

/* Trackpad srolling enablement flag */
extern bool set_scrolling;

/* Layers definitions */
enum layers {
  _ALPHA,
  _NAV,
  _NUM,
  _ADJUST,
  _G0,
  _G1
};

/* Custom Keycodes (CK_xxx) */
#define CK_LPAR LSFT(KC_9)
#define CK_RPAR LSFT(KC_0)
#define CK_LCBR LSFT(KC_LBRC)
#define CK_RCBR LSFT(KC_RBRC)
#define CK_QMRK LSFT(KC_SLSH)
#define CK_SSHT LSG(KC_S)
#define CK_UNSC LSFT(KC_MINS)

typedef enum {
    CK_RKJMP = SAFE_RANGE, /* Warframe rocket/bullet jump */
    CK_DPII,
    CK_DPID,
    CK_SCRL,
} cornia_custom_keycodes_t;
