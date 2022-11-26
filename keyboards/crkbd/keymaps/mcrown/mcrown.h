/** @file mcrown.h
 *  @brief mcrown header thant incluedes key layout and some definintions.
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
 * @author Mario Corona (mariocc@comunidad.unam.mx) 2021
 *
 */

#pragma once

#include QMK_KEYBOARD_H
#include "oled.h"

#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define LAYOUT_wrapper(...)   LAYOUT(__VA_ARGS__)

/* For values greater than 0x200, substract that value and add 0x20 so the characters can be mapped  */
#define RM_LSFT(kc)           ((uint8_t)(0x20)+(kc-0x200))

/* ######################################################################### LAYOUT BLOCKS ##################################################### */
/* -----------------------------------------BUTTON1---BUTTON2- BUTTON3------- */
#define _____________MOD_LEFT_____________ KC_GUIEI, KC_LOWER, KC_SPC
#define _____________MOD_RIGHT____________ KC_ENT,   KC_RAISE, KC_ALTKN


/* ------------------------------------------------------------COL1------COL2-----COL3-----COL4-----COL5-----COL6--------- */
#define   _____________________RAISE_L1_______________________ KC_ESC,   KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC
#define   _____________________RAISE_L2_______________________ KC_LSFT,  KC_MPLY, KC_VOLU, KC_MNXT,  XXXXXXX,  XXXXXXX
#define   _____________________RAISE_L3_______________________ KC_CTLTB, KC_CALC, KC_VOLD, KC_MPRV,  KC_BRIU,  KC_BRID

#define   _____________________RAISE_R1_______________________ KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN,  KC_DEL
#define   _____________________RAISE_R2_______________________ KC_MINS,  KC_EQL,  KC_LCBR, KC_RCBR,  KC_PIPE,  KC_GRV
#define   _____________________RAISE_R3_______________________ KC_UNDS,  KC_PLUS, KC_LBRC, KC_RBRC,  KC_BSLS,  KC_TILD

/* ------------------------------------------------------------COL1------COL2-----COL3-----COL4-----COL5-----COL6--------- */
#define   _____________________QWERTY_L1______________________ KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define   _____________________QWERTY_L2______________________ KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define   _____________________QWERTY_L3______________________ KC_CTLTB, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define   _____________________QWERTY_R1______________________ KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC
#define   _____________________QWERTY_R2______________________ KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define   _____________________QWERTY_R3______________________ KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT

/* ------------------------------------------------------------COL1------COL2-----COL3-----COL4-----COL5-----COL6--------- */
#define   _____________________LOWER_L1_______________________ KC_CAPS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define   _____________________LOWER_L2_______________________ KC_LSFT,  XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN
#define   _____________________LOWER_L3_______________________ KC_CTLTB, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5

#define   _____________________LOWER_R1_______________________ KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_BSPC
#define   _____________________LOWER_R2_______________________ KC_LEFT,  KC_UP,   KC_DOWN, KC_RIGHT, KC_HOME,  KC_END
#define   _____________________LOWER_R3_______________________ KC_F6,    KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11

/* ------------------------------------------------------------COL1------COL2-----COL3-----COL4-----COL5-----COL6--------- */
#define   _____________________ADJUST_L1______________________ XXXXXXX,  EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
  #define _____________________ADJUST_L2______________________ XXXXXXX,  XXXXXXX, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI
  #define _____________________ADJUST_L3______________________ XXXXXXX,  XXXXXXX, RGB_SPD, RGB_SAD, RGB_HUD, RGB_VAD
#else/* ---------------------------------------------------------------|---------|--------|--------|--------|------------- */
  #define _____________________ADJUST_L2______________________ M_VRSN,   M_MALL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  #define _____________________ADJUST_L3______________________ M_FLSH,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#endif/* --------------------------------------------------------------|---------|--------|--------|--------|------------- */
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
  #define _____________________ADJUST_R1______________________ RGB_TOG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  #define _____________________ADJUST_R3______________________ RGB_MOD,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#else/* ---------------------------------------------------------------|---------|--------|--------|--------|------------- */
  #define _____________________ADJUST_R1______________________ XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  #define _____________________ADJUST_R3______________________ XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#endif/* --------------------------------------------------------------|---------|--------|--------|--------|------------- */
#define   _____________________ADJUST_R2______________________ RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

/* Each layer gets a name for readability */
typedef enum custom_layers {
    _QWERTY,
    _DVORAK,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
    _MAX_LAYERS
}CUSTOM_LAYERS_T;

/* To be used to identify the current working layer */
typedef enum custom_keycodes{
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    BACKLIT,
    RGBRST
}CUSTOM_KEYCODES_T;
