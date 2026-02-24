/* Copyright 2023 Yiancar-Designs
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
        KC_ESC,  KC_F1,   KC_F2,     KC_F3,        KC_F4,      KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_PSCR,   KC_INS,    KC_DEL,
        KC_GRV,  KC_1,    KC_2,      KC_3,         KC_4,       KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,   KC_HOME,
        KC_TAB,  KC_Q,    KC_W,      KC_E,         KC_R,       KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,   KC_END,
        KC_CAPS, KC_A,    KC_S,      KC_D,         KC_F,       KC_G,     KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                KC_PGUP,
        KC_LSFT,          KC_Z,      KC_X,         KC_C,       KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,    KC_UP,     KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC,                     KC_RALT, MO(2),    KC_RCTL,            KC_LEFT,    KC_DOWN,   KC_RGHT
    ),
    [1] = LAYOUT_tkl_ansi(
        KC_ESC,  KC_BRID, KC_BRIU,   KC_MCTL,      G(KC_SPC),  RM_VALD,  RM_VALU, KC_MPRV, KC_MPLY, KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_PSCR,   KC_INS,    KC_DEL,
        KC_GRV,  KC_1,    KC_2,      KC_3,         KC_4,       KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,   KC_HOME,
        KC_TAB,  KC_Q,    KC_W,      KC_E,         KC_R,       KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,   KC_END,
        KC_CAPS, KC_A,    KC_S,      KC_D,         KC_F,       KC_G,     KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                KC_PGUP,
        KC_LSFT,          KC_Z,      KC_X,         KC_C,       KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,    KC_UP,     KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                     KC_RGUI, MO(3),    KC_RCTL,            KC_LEFT,    KC_DOWN,   KC_RGHT
    ),
    [2] = LAYOUT_tkl_ansi(
        KC_ESC,  KC_BRID, KC_BRIU,   G(KC_TAB),    KC_WSCH,    RM_VALD,  RM_VALU, KC_MPRV, KC_MPLY, KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_CALC,   G(KC_L),   RM_VALU,
        KC_GRV,  MD_BLE1, MD_BLE2,   MD_BLE3,      MD_24G,     KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     RM_SPDD,  RM_SPDU,    KC_BSPC,   LOGO_MOD,
        _______, KC_Q,    KC_W,      KC_E,         KC_R,       _______,  KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     RM_SATD,  RM_SATU,    KC_BSLS,   RM_TOGG,
        KC_CAPS, TO(0),   TO(1),     KC_D,         KC_F,       KC_G,     _______, KC_J,    KC_K,    KC_L,     LOGO_HUD, LOGO_HUI, KC_ENT,                LOGO_VAI,
        KC_LSFT,          KC_Z,      KC_X,         KC_C,       KC_V,     KC_B,    KC_N,    KC_M,    LOGO_SPD, LOGO_SPI, KC_SLSH,  KC_RSFT,    KC_UP,     LOGO_VAD,
        KC_LCTL, QK_WLO,  KC_LALT,                             QK_BAT,                     KC_RALT, KC_NO,    KC_RCTL,            RM_HUED,    KC_DOWN,   RM_HUEU
    ),
    [3] = LAYOUT_tkl_ansi(
        KC_ESC,  KC_F1,   KC_F2,     KC_F3,        KC_F4,      KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_PSCR,   G(KC_L),   RM_VALU,
        KC_GRV,  MD_BLE1, MD_BLE2,   MD_BLE3,      MD_24G,     KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     RM_SPDD,  RM_SPDU,    KC_BSPC,   LOGO_MOD,
        _______, KC_Q,    KC_W,      KC_E,         KC_R,       _______,  KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     RM_SATD,  RM_SATU,    KC_BSLS,   RM_TOGG,
        KC_CAPS, TO(0),   TO(1),     KC_D,         KC_F,       KC_G,     _______, KC_J,    KC_K,    KC_L,     LOGO_HUD, LOGO_HUI, KC_ENT,                LOGO_VAI,
        KC_LSFT,          KC_Z,      KC_X,         KC_C,       KC_V,     KC_B,    KC_N,    KC_M,    LOGO_SPD, LOGO_SPI, KC_SLSH,  KC_RSFT,    KC_UP,     LOGO_VAD,
        KC_LCTL, KC_LALT, KC_LGUI,                             QK_BAT,                     KC_RGUI, KC_NO,    KC_RCTL,            RM_HUED,    KC_DOWN,   RM_HUEU
    )
};

