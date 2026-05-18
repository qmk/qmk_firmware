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
#include "../../lib/rdr_lib/rdr_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tkl_ansi(
        KC_ESC,  KC_F1,   KC_F2,     KC_F3,        KC_F4,      KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_INS,    KC_MUTE,
        KC_GRV,  KC_1,    KC_2,      KC_3,         KC_4,       KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,   KC_DEL,
        KC_TAB,  KC_Q,    KC_W,      KC_E,         KC_R,       KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,   KC_HOME,
        KC_CAPS, KC_A,    KC_S,      KC_D,         KC_F,       KC_G,     KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                KC_PGUP,
        KC_LSFT,          KC_Z,      KC_X,         KC_C,       KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,    KC_UP,     KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC,                     KC_RALT, MO(2),                        KC_LEFT,    KC_DOWN,   KC_RGHT
    ),
    [1] = LAYOUT_tkl_ansi(
        KC_ESC,  KC_BRID, KC_BRIU,   KC_MCTL,      KC_LPAD,    RGB_VAD,  RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_INS,    KC_MUTE,
        KC_GRV,  KC_1,    KC_2,      KC_3,         KC_4,       KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,   KC_DEL,
        KC_TAB,  KC_Q,    KC_W,      KC_E,         KC_R,       KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,   KC_HOME,
        KC_CAPS, KC_A,    KC_S,      KC_D,         KC_F,       KC_G,     KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                KC_PGUP,
        KC_LSFT,          KC_Z,      KC_X,         KC_C,       KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,    KC_UP,     KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                     KC_RGUI, MO(3),                        KC_LEFT,    KC_DOWN,   KC_RGHT
    ),
    [2] = LAYOUT_tkl_ansi(
        KC_ESC,  KC_BRID, KC_BRIU,   QK_TASK,      QK_FILE,    KC_MAIL,  KC_WHOM, KC_MPRV, KC_MPLY, KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_INS,    KC_MUTE,
        KC_GRV,  KC_1,    KC_2,      KC_3,         KC_4,       KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,     QK_BAT,    KC_INS,
        KC_TAB,  MD_BLE1, MD_BLE2,   MD_BLE3,      MD_24G,     KC_T,     TIME_ST, KC_U,    KC_PAUS, KC_SCRL,  KC_PSCR,  RGB_HUD,  RGB_HUI,    RGB_RTOG,  KC_END,
        KC_CAPS, KC_A,    KC_S,      KC_D,         KC_F,       KC_G,     QK_DEB,  KC_J,    KC_K,    KC_L,     RGB_SAD,  RGB_SAI,  KC_ENT,                KC_PGUP,
        KC_LSFT,          WIN_CH,    MAC_CH,       KC_C,       KC_V,     KC_B,    KC_N,    RGB_MOD, LOGO_TOG, LOGO_MOD, LOGO_HUD, KC_RSFT,    RGB_VAI,   KC_PGDN,
        KC_LCTL, QK_WLO,  KC_LALT,                             U_EE_CLR,                   KC_RALT, KC_NO,                        RGB_SPD,    RGB_VAD,   RGB_SPI
    ),
    [3] = LAYOUT_tkl_ansi(
        KC_ESC,  KC_F1,   KC_F2,     KC_F3,        KC_F4,      KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_INS,    KC_MUTE,
        KC_GRV,  KC_1,    KC_2,      KC_3,         KC_4,       KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,     QK_BAT,    KC_INS,
        KC_TAB,  MD_BLE1, MD_BLE2,   MD_BLE3,      MD_24G,     KC_T,     TIME_ST, KC_U,    KC_PAUS, KC_SCRL,  KC_PSCR,  RGB_HUD,  RGB_HUI,    RGB_RTOG,  KC_END,
        KC_CAPS, KC_A,    KC_S,      KC_D,         KC_F,       KC_G,     QK_DEB,  KC_J,    KC_K,    KC_L,     RGB_SAD,  RGB_SAI,  KC_ENT,                KC_PGUP,
        KC_LSFT,          WIN_CH,    MAC_CH,       KC_C,       KC_V,     KC_B,    KC_N,    RGB_MOD, LOGO_TOG, LOGO_MOD, LOGO_HUD, KC_RSFT,    RGB_VAI,   KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                             U_EE_CLR,                   KC_RGUI, KC_NO,                        RGB_SPD,    RGB_VAD,   RGB_SPI
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [1] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [2] = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_SPD, RGB_SPI) }
};

#endif
