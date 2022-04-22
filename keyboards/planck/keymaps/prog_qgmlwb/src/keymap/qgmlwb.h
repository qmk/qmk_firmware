// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "layouts.h"

/* QGMLWB
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   G  |   M  |   L  |   W  |   B  |   Y  |   U  |   V  |   '" | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   D  |   S  |   T  |   N  |   R  |   I  |   A  |   E  |   O  |  H   |Return|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shft |   Z  |   X  |   C  |   F  |   J  |   K  |   P  |  ,;  |  .:  |  -_  |   \| |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | NmPd | GUI  | Lower| Space|Space |Raise | Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
*/
// Norwegian Layout
#define qgmlwb_no_map LAYOUT_ortho_4x12(\
    KC_TAB,  KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_B,    KC_Y,    KC_U,    KC_V,    NO_QUOT, KC_BSPC,\
    KC_ESC,  KC_D,    KC_S,    KC_T,    KC_N,    KC_R,    KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_ENT,\
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_F,    KC_J,    KC_K,    KC_P,    KC_COMM, KC_DOT,  NO_MINS, NO_BSLS,\
    KC_LCTL, KC_LALT, numpad,  KC_LGUI, QNLower, KC_SPC,  KC_SPC,  QNRaise, KC_LEFT, KC_DOWN, KC_UP,   SPACE_TRI\
)
// English Layout
#define qgmlwb_us_map LAYOUT_ortho_4x12(\
    KC_TAB,  KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_B,    KC_Y,    KC_U,    KC_V,    KC_QUOT, KC_BSPC,\
    KC_ESC,  KC_D,    KC_S,    KC_T,    KC_N,    KC_R,    KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_ENT,\
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_F,    KC_J,    KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_MINS, KC_BSLS,\
    KC_LCTL, KC_LALT, numpad,  KC_LGUI, QELower, KC_SPC,  KC_SPC,  QERaise, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT\
)

/* Lower - QGMLWB
* ,-----------------------------------------------------------------------------------.
* |   !  |   %  |   [  |   {  |   (  |   <  |   >  |   )  |   }  |   ]  |   &  |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |  Del | Mute | XXXX | Refr | XXXX | XXXX | XXXX |   =  |   +  |   *  |   /  |  ~   |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |Sleep |ScrLck| Caps |NumLck|PrtScr|  Ins |  End | Home |   æ  |   ø  |  å   |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |      |      |Adjust| Bri- | Vol- | Vol+ | Bri+ |
* `-----------------------------------------------------------------------------------'
*/
// Norwegian
#define qgmlwb_no_lower_map LAYOUT_ortho_4x12(\
    KC_EXLM, KC_PERC, NO_LBRC, NO_LCBR, NO_LPRN, NO_LESS, NO_GRTR, NO_RPRN, NO_RCBR, NO_RBRC, NO_AMPR, _______,\
    KC_DEL,  KC_MUTE, XXXXXXX, KC_WREF, TEST_0,  TEST_1,  TEST_2,  NO_EQL,  NO_PLUS, NO_ASTR, NO_SLSH, NO_TILD,\
    _______, KC_SLEP, KC_SLCK, KC_CAPS, KC_NLCK, KC_PSCR, KC_INS,  KC_END,  KC_HOME, NO_AE,   NO_OE,   NO_AA,\
    _______, _______, _______, _______, _______, _______, _______, adjust,  KC_BRID, KC_VOLD, KC_VOLU, KC_BRIU\
)
// English Same as Nok - without æøå
#define qgmlwb_us_lower_map LAYOUT_ortho_4x12(\
    KC_EXLM, KC_PERC, KC_LBRC, KC_LCBR, KC_LPRN, KC_LT,   KC_GT,   KC_RPRN, KC_RCBR, KC_RBRC, KC_AMPR, _______,\
    KC_DEL,  KC_MUTE, XXXXXXX, KC_WREF, TEST_0,  TEST_1,  TEST_2,  KC_EQL,  KC_PLUS, KC_ASTR, KC_SLSH, KC_TILD,\
    _______, KC_SLEP, KC_SLCK, KC_CAPS, KC_NLCK, KC_PSCR, KC_INS,  KC_END,  KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX,\
    _______, _______, _______, _______, _______, _______, _______, adjust,  KC_BRID, KC_VOLD, KC_VOLU, KC_BRIU\
)

/* Raise - QGMLWB
* ,-----------------------------------------------------------------------------------.
* |   ?  |   9  |   7  |   5  |   3  |   1  |   0  |  2   |   4  |   6  |   8  |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Del+ |  F1  |  F2  |  F3  |   F4 |   F5 |  F6  |   #  |   @  |   ^  |   $  |   `  |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |RShift|  F7  |  F8  | F9   |  F10 |  F11 |  F12 | PgDn | PgUp | XXXX | XXXX | XXXX |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |RCtrl | RAlt |      |      |      |      |      |Adjust| Prev | Stop | Play | Next |
* `-----------------------------------------------------------------------------------'
*/
// Norwegian
#define qgmlwb_no_raise_map LAYOUT_ortho_4x12(\
    NO_QUES,      KC_9,    KC_7,    KC_5,    KC_3,    KC_1,    KC_0,    KC_2,    KC_4,    KC_6,    KC_8,    _______,\
    LCTL(KC_DEL), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_HASH, NO_AT,   NO_CIRC, NO_DLR,  NO_GRV,\
    KC_RSFT,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,\
    KC_RCTL,      KC_RALT, _______, _______, adjust,  _______, _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT\
)
// English
#define qgmlwb_us_raise_map LAYOUT_ortho_4x12(\
    KC_QUES,      KC_9,    KC_7,    KC_5,    KC_3,    KC_1,    KC_0,    KC_2,    KC_4,    KC_6,    KC_8,    _______,\
    LCTL(KC_DEL), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_HASH, KC_AT,   KC_CIRC, KC_DLR,  KC_GRV,\
    KC_RSFT,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,\
    KC_RCTL,      KC_RALT, _______, _______, adjust,  _______, _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT\
)
