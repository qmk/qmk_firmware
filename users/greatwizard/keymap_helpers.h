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

#define _______________QWERTY_LEFT1________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _______________QWERTY_LEFT2________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _______________QWERTY_LEFT3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _______________QWERTY_RIGHT1_______________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _______________QWERTY_RIGHT2_______________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _______________QWERTY_RIGHT3_______________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _______________WORKMAN_LEFT1_______________ KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _______________WORKMAN_LEFT2_______________ KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _______________WORKMAN_LEFT3_______________ KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _______________WORKMAN_RIGHT1______________ KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _______________WORKMAN_RIGHT2______________ KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _______________WORKMAN_RIGHT3______________ KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH

#define _______________COLEMAK_LEFT1_______________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _______________COLEMAK_LEFT2_______________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _______________COLEMAK_LEFT3_______________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _______________COLEMAK_RIGHT1______________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _______________COLEMAK_RIGHT2______________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _______________COLEMAK_RIGHT3______________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _______________DVORAK_LEFT1________________ KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _______________DVORAK_LEFT2________________ KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _______________DVORAK_LEFT3________________ KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _______________DVORAK_RIGHT1_______________ KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _______________DVORAK_RIGHT2_______________ KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _______________DVORAK_RIGHT3_______________ KC_B,    KC_M,    KC_W,    KC_V,    KC_Z

#define _______________NUMBER_LEFT_________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _______________NUMBER_RIGHT________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________GIT_LEFT1_________________ GIT_CPK, GIT_SHW, GIT_RBS, GIT_RST, GIT_TAG
#define _________________GIT_LEFT2_________________ GIT_ADD, GIT_STT, GIT_DIF, GIT_FTC, GIT_GRP
#define _________________GIT_LEFT3_________________ _______, _______, GIT_CMT, GIT_MV,  GIT_BRC

#define _________________GIT_RIGHT1________________ _______, GIT_PUL, GIT_INI, GIT_RMT, GIT_PUS
#define _________________GIT_RIGHT2________________ GIT_STS, _______, GIT_CKT, GIT_LOG, _______
#define _________________GIT_RIGHT3________________ _______, GIT_MRG, _______, _______, _______
