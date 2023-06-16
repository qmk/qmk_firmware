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
  _QWERTY,
  _MOVE,
  _QWERTY_LINUX,
  _MOVE_LINUX,
  _FUNCTION,
  _MACRO,
  _CONFIG
};

enum CustomKeys {
  CS_RIGHT = SAFE_RANGE,
  CS_DOWN,
  SHEBANG,
  SHRUG,
  FN,
  CONST,
  SELECT,
  FOR_LOOP,
  SED,
  BASH_IF,
  P_PAREN,
  P_BRACE,
  P_BRACK,
  TS_IMPT,
};

#define OS_POP     LCTL(KC_F10)
#define MAC_POP    LT(_CONFIG, LCTL(KC_UP))
#define MAC_FRC    LGUI(LALT(KC_ESC))
#define OS_COPY    LSFT(LCTL(KC_C))
#define OS_PAST    LSFT(LCTL(KC_V))
#define MAC_UND    LGUI(KC_Z)
#define MAC_CUT    LGUI(KC_X)
#define MAC_PST    LGUI(KC_V)
#define MAC_SPS    LGUI(LSFT(LALT(KC_V)))
#define MAC_CPY    LGUI(KC_C)
#define MAC_DUP    LGUI(KC_D)
#define MAC_ALL    LGUI(KC_A)
#define MAC_SAV    LGUI(KC_S)
#define MAC_B      LGUI(KC_B)
#define MAC_FND    LGUI(KC_F)
#define MAC_WND    LGUI(KC_GRV)
#define KC_BACK    LGUI(KC_LBRC)
#define KC_NEXT    LGUI(KC_RBRC)

#define MOVE       LT(_MOVE_LINUX, KC_ESC)
#define MOVE_MAC   LT(_MOVE, KC_ESC)
#define LT_END     LT(_MACRO, KC_END)
#define LT_SPACE   LT(_MACRO, KC_SPC)
#define FN_SPACE   LT(_FUNCTION, KC_SPC)
#define LT_FUNC    LT(_FUNCTION, KC_LEFT)
#define CONFIG     MO(_CONFIG)
#define J_MACRO    MO(_MACRO)
#define J_FUNCT    MO(_FUNCTION)
#define CFG_LNX    MO(_CONFIG)

#define WD_BACK    LALT(KC_LEFT)
#define WD_FRWD    LALT(KC_RIGHT)
#define WD_DELE    LALT(KC_BSPC)

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
#define LT_SLSH    RSFT_T(KC_SLSH)
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
#define IJ_LINE    LGUI(KC_L)
#define IJ_RELD    LGUI(LSFT(KC_F9))
#define IJ_TERM    LALT(KC_F12)
#define IJ_DEBG    LGUI(KC_5)
#define IJ_RFMT    LALT(LSFT(LGUI(KC_L)))
#define IJ_FILE    LSFT(LGUI(KC_O))
#define IJ_PROJ    LSFT(LGUI(KC_O))

/* VS Code shortcuts */
#define VS_CMD     LGUI(LSFT(KC_A))
#define VS_EXP     LGUI(LSFT(KC_E))
#define VS_DBG     LGUI(LSFT(KC_F8))
#define VS_SCC     LCTL(LSFT(KC_G))
#define VS_RUN     KC_F5
#define VS_STEP    KC_F8
#define VS_INTO    KC_F7
#define VS_BPT     LGUI(KC_F8)
#define VS_OUT     LSFT(KC_F8)
#define VS_STOP    LSFT(KC_F5)
#define VS_TERM    LSFT(KC_ESC)
#define VS_FILE    LSFT(LGUI(KC_O))
#define VS_LINE    LGUI(KC_L)
#define VS_MVUP    LSFT(LALT(KC_UP))
#define VS_MVDN    LSFT(LALT(KC_DOWN))
#define VS_JSFT    RSFT_T(LGUI(LSFT((KC_P))))

/* MacOS virtual desktop shortcuts */
#define M_VD1      LCTL(KC_1)
#define M_VD2      LCTL(KC_2)
#define M_VD3      LCTL(KC_3)

/* rectangle shortcuts */
#define MM_ULCN    LCTL(LGUI(KC_LEFT))
#define MM_URCN    LCTL(LGUI(KC_RIGHT))
#define MM_LLCN    LCTL(LSFT(LGUI(KC_LEFT)))
#define MM_LRCN    LCTL(LSFT(LGUI(KC_RIGHT)))
#define MM_MAX     LCTL(LALT(KC_ENTER))
#define MM_LH      HYPR(KC_LBRC)
#define MM_RH      HYPR(KC_RBRC)
#define MM_UH      LALT(LGUI(KC_UP))
#define MM_BH      LALT(LGUI(KC_DOWN))
#define MM_LEFT    LCTL(LALT(LGUI(KC_LEFT)))
#define MM_RGHT    LCTL(LALT(LGUI(KC_RIGHT)))

#define DF_1       DF(_QWERTY)
#define DF_2       DF(_MOVE)
#define DF_3       DF(_FUNCTION)
#define DF_4       DF(_MACRO)
