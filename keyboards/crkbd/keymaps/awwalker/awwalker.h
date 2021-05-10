/** @file awwalker.h
 *  @brief awwalker header that incluedes key layout and some definintions.
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
 *
 * @author Aaron Walker (awwalker3@gmail.com) 2021
 *
 */

#pragma once

#include QMK_KEYBOARD_H
#include "oled.h"

/* Each layer gets a name for readability */
typedef enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
}CUSTOM_LAYERS_T;

/* To be used to identify the current working layer */
typedef enum custom_keycodes{
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    RGBRST
}CUSTOM_KEYCODES_T;

typedef enum custom_tapdances {
    TD_RALT_SUSPEND,
}CUSTOM_TAPDANCES;


#define LAYOUT_wrapper(...)   LAYOUT(__VA_ARGS__)


/* Left hand bottom thumb cluster */
#define _____________MOD_LEFT_____________ RAISE, KC_ENT, KC_LGUI
/* Right hand bottom thumb cluster */
#define _____________MOD_RIGHT____________ TD(TD_RALT_SUSPEND), KC_SPC, LOWER


/* QWERTY */
/* ------------------------------------------------------------COL1------COL2-----COL3-----COL4-----COL5-----COL6--------- */
#define   _____________________QWERTY_L1______________________ KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define   _____________________QWERTY_L2______________________ KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define   _____________________QWERTY_L3______________________ KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define   _____________________QWERTY_R1______________________ KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC
#define   _____________________QWERTY_R2______________________ KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define   _____________________QWERTY_R3______________________ KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT

/* RAISE */

/* ------------------------------------------------------------COL1--------COL2-----COL3-----COL4------COL5------COL6-------*/
#define   _____________________RAISE_L1_______________________ KC_GRV,     KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC
#define   _____________________RAISE_L2_______________________ KC_BSLS,    KC_NO,   KC_UNDS, KC_EQL,   KC_LPRN,  KC_RPRN
#define   _____________________RAISE_L3_______________________ KC_LSFT, RGB_TOG, KC_NO,   KC_ESC,   KC_LBRC,  KC_RBRC

#define   _____________________RAISE_R1_______________________ KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN,    KC_BSPC
#define   _____________________RAISE_R2_______________________ KC_LEFT,  KC_DOWN, KC_UP,   KC_RIGHT, KC__VOLUP,  KC_NO
#define   _____________________RAISE_R3_______________________ KC_MRWD,  KC_MPLY, KC_MFFD, KC__MUTE, KC__VOLDOWN, KC_RSFT

/* LOWER */

/* ------------------------------------------------------------COL1------COL2-----COL3-----COL4-----COL5-----COL6--------- */
#define   _____________________LOWER_L1_______________________ KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define   _____________________LOWER_L2_______________________ KC_LCTL,  KC_PIPE, KC_MINS, KC_UNDS, KC_LPRN, KC_RPRN
#define   _____________________LOWER_L3_______________________ KC_LSFT, KC_NO, KC_NO,   KC_ESC,  KC_LBRC, KC_RBRC

#define   _____________________LOWER_R1_______________________ KC_6,     KC_7,    KC_8,    KC_9,     KC_0,   KC_BSPC
#define   _____________________LOWER_R2_______________________ KC_PLUS,  KC_4,    KC_5,    KC_6,     KC_NO,  KC_NO
#define   _____________________LOWER_R3_______________________ KC_0,     KC_1,    KC_2,    KC_3,     KC_NO, KC_RSFT

/* ADJUST */

/* ------------------------------------------------------------COL1------COL2-----COL3-----COL4-----COL5-----COL6--------- */
#define   _____________________ADJUST_L1______________________ RESET,    RGBRST,  KC_NO,   KC_NO,   KC_NO,   KC_NO
#define   _____________________ADJUST_L2______________________ RGB_TOG,  RGB_HUI, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI
#define   _____________________ADJUST_L3______________________ RGB_MOD,  RGB_HUD, RGB_SAD, RGB_VAD, RGB_HUD, RGB_VAD

#define   _____________________ADJUST_R1______________________ KC_NO,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO
#define   _____________________ADJUST_R2______________________ KC_NO,    KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_NO
#define   _____________________ADJUST_R3______________________ KC_NO,    KC_F1,   KC_F2,   KC_F3,   KC_NO,   KC_NO
