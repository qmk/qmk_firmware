/*
Copyright 2020 Dan White <opensource@bluetufa.com>

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

#include QMK_KEYBOARD_H

enum layers {
  _QWERTY_MAC,
  _MOVE_MAC,
  _QWERTY_LINUX,
  _MOVE_LINUX,
  _ADJUST,
  _CONFIG
};

enum CustomKeys {
  CS_RIGHT = SAFE_RANGE,
  CS_DOWN
};

#define OS_POP     LCTL(KC_F10)
#define MAC_POP    LCTL(KC_UP)
#define MAC_FRC    LGUI(LALT(KC_ESC))
#define OS_COPY    LSFT(LCTL(KC_C))
#define OS_PAST    LSFT(LCTL(KC_V))
#define MAC_PST    LGUI(KC_V)
#define MAC_CPY    LGUI(KC_C)
#define KC_BACK    LCTL(LSFT(KC_LBRC))
#define KC_NEXT    LCTL(LSFT(KC_RBRC))

#define MOVE       LT(_MOVE_LINUX, KC_ESC)
#define MOVE_MAC   LT(_MOVE_MAC, KC_ESC)
#define ADJUST     MO(_ADJUST)
#define CFG_MAC    LT(_CONFIG, MAC_POP)
#define CFG_LNX    LT(_CONFIG, OS_POP)

#define WD_BACK    LALT(KC_LEFT)
#define WD_FRWD    LALT(KC_RIGHT)

#define VD_1       LCTL(KC_F1)
#define VD_2       LCTL(KC_F2)
#define VD_3       LCTL(KC_F3)

#define WM_UH      LGUI(KC_UP)
#define WM_BH      LGUI(KC_DOWN)
#define WM_LH      LGUI(KC_LEFT)
#define WM_RH      LGUI(KC_RIGHT)
#define WM_MAX     LGUI(KC_PGUP)

#define CM_RIGHT   LGUI(KC_D)
#define CM_DOWN    LGUI(LSFT(KC_D))

/* THESE are not defaults in KDE and must be set manually */
#define WM_VD1     HYPR(KC_1)
#define WM_VD2     HYPR(KC_2)
#define WM_VD3     HYPR(KC_3)

/* IntelliJ / JetBrains shortcuts with Mac keymap */
#define IJ_BACK    LGUI(LALT(KC_LEFT))
#define IJ_FWD     LGUI(LALT(KC_RIGHT))
#define IJ_UP      LGUI(LALT(KC_UP))
#define IJ_DOWN    LGUI(LALT(KC_DOWN))
#define IJ_IMPL    LGUI(LALT(KC_B))
#define IJ_DECL    LGUI(KC_B)
#define IJ_REN     LSFT(KC_F6)
#define IJ_USAG    LALT(KC_F7)
#define IJ_RUN     KC_F9
#define IJ_STEP    KC_F8
#define IJ_INTO    LSFT(KC_F7)
#define IJ_OUT     LSFT(KC_F8) 
#define IJ_STOP    LGUI(KC_F2) 
#define IJ_IMPS    LCTL(LALT(LSFT(KC_EQUAL)))
#define IJ_IMPH    LCTL(LALT(LSFT(KC_MINUS)))
#define IJ_TOP     LGUI(KC_HOME)
#define IJ_BOTT    LGUI(KC_END)
#define IJ_FIND    LGUI(LSFT(KC_F))

/* MacOS virtual desktop shortcuts */
#define M_VD1      LCTL(KC_1)
#define M_VD2      LCTL(KC_2)
#define M_VD3      LCTL(KC_3)

/* rectangle shortcuts */
#define MM_ULCN    LCTL(LGUI(KC_LEFT))
#define MM_URCN    LCTL(LGUI(KC_RIGHT))
#define MM_LLCN    LCTL(LSFT(LGUI(KC_LEFT)))
#define MM_LRCN    LCTL(LSFT(LGUI(KC_RIGHT)))
#define MM_MAX     LALT(LGUI(KC_F))
#define MM_LH      HYPR(KC_LBRC)
#define MM_RH      HYPR(KC_RBRC)
#define MM_UH      LALT(LGUI(KC_UP))
#define MM_BH      LALT(LGUI(KC_DOWN))
#define MM_LEFT    LCTL(LALT(LGUI(KC_LEFT)))
#define MM_RGHT    LCTL(LALT(LGUI(KC_RIGHT)))

#define DF_1       DF(_QWERTY_MAC)
#define DF_2       DF(_QWERTY_LINUX)
