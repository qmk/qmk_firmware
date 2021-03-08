/*
 * Copyright 2020 Jason Chestnut <jason.chestnut@gmail.com>
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

#include "wrappers.h"

enum userspace_layers {
    _BASE,
    _NAV,
    _MOUSE,
    _RSYMBOL,
    _LSYMBOL,
    _NUMBER,
    _FUNCTION,
    _ADJUST,
    _RGB_CONTROL
};

enum userspace_keycodes {
    BASE = SAFE_RANGE,
    NAV,
    MOUSE,
    RSYMBOL,
    LSYMBOL,
    NUMBER,
    FUNCTION,
    ADJUST,
    RGB_CONTROL
};

/*
 * Mod-taps.
 */
#define KC_SFTA   MT(MOD_LSFT, KC_A)
#define KC_GUIZ   MT(MOD_LGUI, KC_Z)
#define KC_CTLX   MT(MOD_LCTL, KC_X)
#define KC_ALTC   MT(MOD_LALT, KC_C)
#define KC_SFTCLN MT(MOD_LSFT, KC_SCLN)
#define KC_ALTCM  MT(MOD_LALT, KC_COMM)
#define KC_CTLDT  MT(MOD_LCTL, KC_DOT)
#define KC_GUISL  MT(MOD_LGUI, KC_SLSH)

/*
 * Layer-taps.
 */
#define LT_NAV  LT(_NAV,KC_D)
#define LT_MSE  LT(_MOUSE,KC_K)
#define LT_RSYM LT(_RSYMBOL,KC_F)
#define LT_LSYM LT(_LSYMBOL,KC_J)
#define LT_NUM  LT(_NUMBER,KC_S)
#define LT_FUNC LT(_FUNCTION,KC_L)
#define LT_ADJ  LT(_ADJUST,KC_SPC)
#define LT_RGB  LT(_RGB_CONTROL, KC_ENT)

/*
 * Key shortcuts.
 */
#define DT_NXT LCTL(KC_RGHT)
#define DT_PRV LCTL(KC_LEFT)

/*
 * Common key combos used in multiple keymaps.
 */

#ifdef COMBO_ENABLE 
enum combos {
    ESC_COMBO
};

const uint16_t PROGMEM esc_combo [] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC)
};
#endif

