/* Copyright 2020 Guillaume Gérard
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
#include "keymap_helpers.h"
#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif
#ifdef RGBLIGHT_ENABLE
#    include "underglow.h"
#endif
#ifdef LAYER_FN
#    include "fn.h"
#endif
#ifdef LAYER_GAME
#    include "game.h"
#endif
#ifdef LAYER_GIT
#    include "git.h"
#endif
#ifdef LAYERS_ORTHO
#    include "ortho.h"
#endif
#ifdef LAYERS_PROGRAMMER
#    include "programmer.h"
#endif

typedef union {
    uint32_t raw;
    struct {
#ifdef RGBLIGHT_ENABLE
        bool rgb_layer_change : 1;
#endif
    };
} user_config_t;

enum layers {
    _QWERTY,
    _WORKMAN,
    _COLEMAK,
    _DVORAK,
#ifdef LAYER_GAME
    _GAME,
#endif
#ifdef LAYERS_PROGRAMMER
    _QWERTY_PROGRAMMER,
    _WORKMAN_PROGRAMMER,
    _COLEMAK_PROGRAMMER,
    _DVORAK_PROGRAMMER,
    _PROGRAMMER_SHIFTED,
#endif
#ifdef LAYERS_ORTHO
    _LOWER,
    _RAISE,
    _ADJUST,
#endif
#ifdef LAYER_FN
    _FN,
#endif
#ifdef LAYER_GIT
    _GIT,
#endif
};

enum keycodes {
    // Persistent layers switcher keys
    QWERTY = SAFE_RANGE,
    WORKMAN,
    COLEMAK,
    DVORAK,
#ifdef LAYER_GAME
    GAME,
#endif
#ifdef LAYERS_PROGRAMMER
    // Workman Programmer
    QWERTY_PROGRAMMER,
    WORKMAN_PROGRAMMER,
    COLEMAK_PROGRAMMER,
    DVORAK_PROGRAMMER,
    PROGRAMMER_SHIFTED,
    PG_GRV,
    PG_1,
    PG_2,
    PG_3,
    PG_4,
    PG_5,
    PG_6,
    PG_7,
    PG_8,
    PG_9,
    PG_0,
#endif
    // RGB Underglow lights based on the layer key
    RGB_LAYER,
#ifdef LAYER_GIT
    // GIT commands
    GIT_ADD,
    GIT_BRANCH,
    GIT_CHECKOUT,
    GIT_CHERRYPICK,
    GIT_COMMIT,
    GIT_DIFF,
    GIT_FETCH,
    GIT_GREP,
    GIT_LOG,
    GIT_INIT,
    GIT_MV,
    GIT_MERGE,
    GIT_PUSH,
    GIT_PULL,
    GIT_REBASE,
    GIT_REMOTE,
    GIT_RESET,
    GIT_SHOW,
    GIT_STASH,
    GIT_STATUS,
    GIT_TAG
#endif
};

#define RGB_LYR RGB_LAYER
