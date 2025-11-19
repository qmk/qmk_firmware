/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2021 QMK <https://github.com/qmk/qmk_firmware>
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

#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,
        KC_CAPS, KC_A,    KC_S,      KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,               KC_ENT,
        KC_LSFT, KC_SLSH, KC_Z,      KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                     KC_SPC,   MO(2),   KC_SPC,           KC_RALT,  KC_APP,   KC_RCTL
    ),
    [1] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,
        KC_CAPS, KC_A,    KC_S,      KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,               KC_ENT,
        KC_LSFT, KC_SLSH, KC_Z,      KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI,                     KC_SPC,   MO(3),   KC_SPC,           KC_RGUI,  KC_APP,   KC_RCTL
    ),
    [2] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_BSLS,
        KC_CAPS,  MD_BLE1, MD_BLE2,  MD_BLE3, MD_24G,  MD_USB,   RM_VALU, RM_SATD, KC_MINS, KC_EQL,             RM_TOGG,
        KC_LSFT,  KC_GRV,  RM_NEXT,  RM_SPDD, RM_SPDU, KC_V,     RM_HUED, RM_VALD, RM_HUEU, KC_COMM,  KC_UP,    MW_CH,
        EE_CLR,   QK_WLO,  KC_LALT,                    QK_BAT,   KC_NO,   KC_SPC,           KC_LEFT,  KC_DOWN,  DBG_SW
    ),
    [3] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_BSLS,
        KC_CAPS,  MD_BLE1, MD_BLE2,  MD_BLE3, MD_24G,  MD_USB,   RM_VALU, RM_SATD, KC_MINS, KC_EQL,             RM_TOGG,
        KC_LSFT,  KC_GRV,  RM_NEXT,  RM_SPDD, RM_SPDU, KC_V,     RM_HUED, RM_VALD, RM_HUEU, KC_COMM,  KC_UP,    MW_CH,
        EE_CLR,   KC_LALT, KC_LGUI,                    QK_BAT,   KC_NO,   KC_SPC,           KC_LEFT,  KC_DOWN,  DBG_SW
    )
};
