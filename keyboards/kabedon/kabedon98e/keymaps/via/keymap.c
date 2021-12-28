/* Copyright 2021 KDon<370490639@qq.com>
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
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _FN1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
┌──┐  ┌──┐┌──┐┌──┐┌──┐   ┌──┐┌──┐┌──┐┌──┐   ┌──┐┌──┐┌──┐┌──┐  ┌──┐  ┌──┐  ┌──┐
│1A│  │0B││1B││0C││1C│   │0D││1D││0E││1E│   │0F││1F││1G││1H│  │5H│  │4I│  │4A│
└──┘  └──┘└──┘└──┘└──┘   └──┘└──┘└──┘└──┘   └──┘└──┘└──┘└──┘  └──┘  └──┘  └──┘
┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──────┐  ┌──┐┌──┐┌──┐┌──┐  ┌──┐
│3A││2B││3B││2C││3C││2D││3D││2E││3E││2F││3F││2G││3G││3H    │  │3J││4J││4K││5K│  │0A│
└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──────┘  └──┘└──┘└──┘└──┘  └──┘
┌────┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌────┐  ┌──┐┌──┐┌──┐┌──┐  ┌──┐
│5A  ││4B││5B││4C││5C││4D││5D││4E││5E││4F││5F││4G││5G││4H  │  │5J││6J││6K││2A│  │7A│
└────┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└────┘  └──┘└──┘└──┘│  │  └──┘
┌─────┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌───────┐  ┌──┐┌──┐┌──┐│  │
│6B   ││7B││6C││7C││6D││7D││6E││7E││6F││7F││6G││7H││7J     │  │8J││8K││7K││  │
└─────┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└───────┘  └──┘└──┘└──┘└──┘
┌───────┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌─────┐      ┌──┐┌──┐┌──┐┌──┐  ┌──┐
│9A     ││9B││8C││9C││8D││9D││8E││9E││8F││9F││8G││9H   │ ┌──┐ │9J││AJ││9K││6A│  │BA│
└───────┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└─────┘ │8I│ └──┘└──┘└──┘│  │  └──┘
┌───┐┌──┐┌──┐┌──┐┌───────────────────────┐┌───┐┌───┐     └──┘     ┌──┐┌──┐│  │  ┌──┐
│AB ││BB││BD││BC││BF                     ││AH ││BH │ ┌──┐┌──┐┌──┐ │AK││BK││  │  │8A│
└───┘└──┘└──┘└──┘└───────────────────────┘└───┘└───┘ │AI││BI││BJ│ └──┘└──┘└──┘  └──┘
                                                     └──┘└──┘└──┘
 */
[_BASE] = LAYOUT(
    KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,  KC_HOME, KC_INS,  KC_END,  KC_PGUP, KC_MUTE, KC_PGDN,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,     KC_UP,        KC_P1,   KC_P2,   KC_P3,
    KC_LCTL, KC_LGUI, KC_LALT, MO(1),                     KC_SPC,                             KC_RALT, KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,      KC_P0,   KC_PDOT, KC_PENT),

[_FN] = LAYOUT(
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,     RGB_VAI,      KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            RGB_TOG, RGB_MOD,     RGB_HUI, RGB_VAD, RGB_HUD,      KC_TRNS, KC_TRNS, KC_TRNS),

[_FN1] = LAYOUT(
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,     KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS)

};
