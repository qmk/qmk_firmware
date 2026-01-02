/* Copyright 2024 EPOMAKER
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
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,   KC_END,   KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                               KC_RALT,  MO(2),              KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [1] = LAYOUT_tkl_ansi(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,   KC_END,   KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                               KC_RGUI,  MO(3),              KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [2] = LAYOUT_tkl_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,   RM_TOGG,  KC_INS,   KC_DEL,   KC_MUTE,
        KC_TAB,  MD_BLE1, MD_BLE2, MD_BLE3, MD_24G,  KC_T,     KC_Y,     KC_U,    RM_SATD, RM_SATU,  KC_P,     LG_HUD,   LG_HUI,   RM_HUEU,  KC_HOME,  KC_END,
        KC_CAPS, TO(0),   TO(1),   KC_D,    KC_F,    KC_G,     DB_TOGG,  KC_J,    KC_K,    KC_L,     LG_SAD,   LG_SAI,             RM_NEXT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,     QK_BAT,   LG_SPD,  LG_SPI,  LG_VAD,   LG_VAI,   LOGO_TOG,           LOGO_MOD, RM_VALU,
        MW_CH,   QK_WLO,  KC_LALT,                   EE_CLR,                               KC_RALT,  KC_NO,              KC_RCTL,  RM_SPDD,  RM_VALD,  RM_SPDU
    ),
    [3] = LAYOUT_tkl_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,   RM_TOGG,  KC_INS,   KC_DEL,   KC_MUTE,
        KC_TAB,  MD_BLE1, MD_BLE2, MD_BLE3, MD_24G,  KC_T,     KC_Y,     KC_U,    RM_SATD, RM_SATU,  KC_P,     LG_HUD,   LG_HUI,   RM_HUEU,  KC_HOME,  KC_END,
        KC_CAPS, TO(0),   TO(1),   KC_D,    KC_F,    KC_G,     DB_TOGG,  KC_J,    KC_K,    KC_L,     LG_SAD,   LG_SAI,             RM_NEXT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,     QK_BAT,   LG_SPD,  LG_SPI,  LG_VAD,   LG_VAI,   LOGO_TOG,           LOGO_MOD, RM_VALU,
        MW_CH,   QK_WLO,  KC_LGUI,                   EE_CLR,                               KC_RGUI,  KC_NO,              KC_RCTL,  RM_SPDD,  RM_VALD,  RM_SPDU
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [1] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [2] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [3] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
#endif


