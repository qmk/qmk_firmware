// Copyright 2021 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define XXX KC_NO


#define LAYOUT_miryoku( \
                  K00,     K01,     K02,     K03,     K04,                       K05,     K06,     K07,     K08,     K09,     \
                  K10,     K11,     K12,     K13,     K14,                       K15,     K16,     K17,     K18,     K19,     \
                  K20,     K21,     K22,     K23,     K24,                       K25,     K26,     K27,     K28,     K29,     \
                  N30,     N31,     K32,     K33,     K34,                       K35,     K36,     K37,     N38,     N39      \
) \
LAYOUT_alice( \
KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,             KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, \
KC_PGUP, KC_TAB,  K00,     K01,     K02,     K03,     K04,                       K05,     K06,     K07,     K08,     K09,     KC_LBRC, KC_RBRC, KC_BSLS, \
KC_PGDN, KC_CAPS, K10,     K11,     K12,     K13,     K14,                       K15,     K16,     K17,     K18,     K19,     KC_SCLN,          KC_ENT, \
         KC_LSFT, K20,     K21,     K22,     K23,     K24,                       K25,     K26,     K27,     K28,     K29,     KC_SLSH, KC_RSFT, KC_RSFT, \
         KC_LCTL,          K32,              K33,     K34,                       K36,              K37,                                KC_RCTL \
)
