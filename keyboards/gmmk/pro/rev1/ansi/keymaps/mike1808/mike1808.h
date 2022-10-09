/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
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
#include "rgb_matrix_ledmaps.h"

enum layout_names {
    LINUX = 0,  // Base Layout: The main keyboard layout that has all the characters
    WINDOWS,    // Base ayout for Windows
    MACOS,      // Base Layout for MacOS
    FUNCTIONS,  // Function Layout: The function key activated layout with default functions and
                // some added ones
    GIT,        // GIT Layout: GIT shortcuts and macros
    SECRETS,    // Layer with secrets
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE,  // Hold to copy, tap to paste
    KC_LINUX,
    KC_MAC,
    KC_WIN,

    KC_SECRET_1,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,
    KC_SECRET_5,

    KC_RGB_ENC_HUE,
    KC_RGB_ENC_SAT,
    KC_RGB_ENC_VAL,
    KC_RGB_ENC_EFFECT_SPEED,
    KC_RGB_ENC_EFFECT,

    KC_WPM_RGB,
};

enum git_macros {
    // The start of this enum should always be equal to end of ctrl_keycodes + 1
    G_INIT = KC_WPM_RGB + 1,  // git init
    G_CLONE,                  // git clone
    G_CONF,                   // git config --global
    G_ADD,                    // git add
    G_DIFF,                   // git diff
    G_QK_BOOT,                // git reset
    G_REBAS,                  // git rebase
    G_BRANH,                  // git branch
    G_CHECK,                  // git checkout
    G_MERGE,                  // git merge
    G_REMTE,                  // git remote add
    G_FETCH,                  // git fetch
    G_PULL,                   // git pull
    G_PUSH,                   // git push
    G_COMM,                   // git commit
    G_STAT,                   // git status
    G_LOG,                    // git log
    NEW_SAFE_RANGE,
};

enum combos {
    JK_ESC,  // jk to ESC for Vim
};

#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3
#define KC_SEC4 KC_SECRET_4
#define KC_SEC5 KC_SECRET_5

#define KC_RGBH KC_RGB_ENC_HUE
#define KC_RGBS KC_RGB_ENC_SAT
#define KC_RGBV KC_RGB_ENC_VAL
#define KC_RGBE KC_RGB_ENC_EFFECT
#define KC_RGBP KC_RGB_ENC_EFFECT_SPEED

#define KC_WRGB KC_WPM_RGB

#define KC_LINX KC_LINUX

#define KC_RESET RESET
#define KC_RST KC_RESET

#define OS_GIT OSL(GIT)
#define TT_FN TT(FUNCTIONS)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_MEH OSM(MOD_MEH)
#define OS_HYPR OSM(MOD_HYPR)

#define CAPS_LOCK_COLOR HSV_RED

