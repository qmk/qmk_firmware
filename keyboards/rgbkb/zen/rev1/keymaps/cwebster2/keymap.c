/* Copyright 2020 Casey Webster <casey@e1337.dev>
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
#include "rev1.h"
#include "cwebster2.h"

#define LAYOUT_zen_base( \
    L01, L02, L03, L04, L05, R05, R04, R03, R02, R01, \
    L11, L12, L13, L14, L15, R15, R14, R13, R12, R11, \
    L21, L22, L23, L24, L25, R25, R24, R23, R22, R21,  \
              L33, L34, L35, R35, R34, R33 \
    ) \
    LAYOUT_zen_wrapper ( \
    KC_ESC,   KC_1, KC_2, KC_3, KC_4, KC_5,                                    KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, \
    KC_GRV,   L01,  L02,  L03,  L04,  L05,                                     R05,  R04,  R03,  R02,  R01,  KC_BSLS, \
    KC_CTLBS, L11,  L12,  L13,  L14,  L15,                                     R15,  R14,  R13,  R12,  R11,  KC_QUOT, \
    KC_EQL,   L21,  L22,  L23,  L24,  L25,                                     R25,  R24,  R23,  R22,  R21,  KC_MINS, \
    KC_LCCL, KC_LGUI,  SCMD_T(KC_LBRC), C_S_T(KC_MINS), L33, L34, L35, R35, R34, R33, TO(_GAME), KC_PSCR, KC_ALTCL, KC_LSFT \
        )
#define LAYOUT_zen_base_wrapper(...)       LAYOUT_zen_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT_zen_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______QWERTY_L1______,                 _______QWERTY_R1______,
      _______QWERTY_L2______,                 _______QWERTY_R2______,
      _______QWERTY_L3______,                 _______QWERTY_R3______,
              _______THUMBS_L_______,  _______THUMBS_R_______
 /*           `---------------------'  `---------------------' */
    ),
    [_COLEMAK] = LAYOUT_zen_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
     KC_ESC,   KC_1, KC_2, KC_3, KC_4, KC_5,                                    KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
     KC_GRV,   _______COLEMAK_L1_____,                                                        _______COLEMAK_R1_____, KC_BSLS,
     KC_CTLBS, _______COLEMAK_L2_____,                                                        _______COLEMAK_R2_____, KC_SCLN,
     KC_EQL,   _______COLEMAK_L3_____,                                                        _______COLEMAK_R3_____, KC_MINS,
     KC_LCCL, KC_LGUI, SCMD_T(KC_LBRC), C_S_T(KC_MINS), _______THUMBS_L_______,   _______THUMBS_R_______, TO(_QWERTY), KC_PSCR, KC_ALTCL, KC_LSFT
 /*           `---------------------'  `---------------------' */
    ),
 // GAME layout -- qwerty without homerow mods
    [_GAME] = LAYOUT_zen_wrapper(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
    KC_ESC,   KC_1, KC_2, KC_3, KC_4, KC_5,                                    KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
    KC_GRV,   _______QWERTY_L1______,                                     _______QWERTY_R1______, KC_BSLS,
    KC_CTLBS, KC_A, KC_S, KC_D, KC_F, KC_G,                               KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_EQL,   _______QWERTY_L3______,                                     _______QWERTY_R3______, KC_MINS,
    KC_LCCL, KC_LGUI,  SCMD_T(KC_LBRC), C_S_T(KC_MINS), _______THUMBS_L_______,   _______THUMBS_R_______, TO(_COLEMAK), KC_PSCR, KC_ALTCL, KC_LSFT
 /*                        `----------------------------------'  `----------------------------------' */
    ),
    [_FN] = LAYOUT_zen_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______FN_______L1____,                 _______INACTIVE_R1____,
      _______FN_______L2____,                 _______INACTIVE_R2____,
      _______FN_______L3____,                 _______NAV______R2____,
              _______FN________T____,  _______INACTIVE__T____
 /*           `---------------------'  `---------------------' */
      ),
    [_SYMBOLS] = LAYOUT_zen_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______SYM______L1____,                 _______INACTIVE_R1____,
      _______SYM______L2____,                 _______INACTIVE_R2____,
      _______SYM______L3____,                 _______INACTIVE_R3____,
              _______SYM_______T____,  _______INACTIVE__T____
 /*           `---------------------'  `---------------------' */
    ),
    [_NUM] = LAYOUT_zen_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______NUM______L1____,                 _______INACTIVE_R1____,
      _______NUM______L2____,                 _______INACTIVE_R2____,
      _______NUM______L3____,                 _______INACTIVE_R3____,
              _______NUM_______T____,  _______INACTIVE__T____
 /*           `---------------------'  `---------------------' */
      ),
    [_NAV] = LAYOUT_zen_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______INACTIVE_L1____,                 _______NAV______R1____,
      _______INACTIVE_L2____,                 _______NAV______R2____,
      _______INACTIVE_L3____,                 _______NAV______R3____,
              _______INACTIVE__T____,  _______NAV_______T____
 /*           `---------------------'  `---------------------' */
      ),
    [_MOUSE] = LAYOUT_zen_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______INACTIVE_L1____,                 _______MOUSE____R1____,
      _______INACTIVE_L2____,                 _______MOUSE____R2____,
      _______INACTIVE_L3____,                 _______MOUSE____R3____,
              _______INACTIVE__T____,  _______MOUSE_____T____
 /*           `---------------------'  `---------------------' */
      ),
    [_MEDIA] = LAYOUT_zen_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______INACTIVE_L1____,                 _______MEDIA____R1____,
      _______INACTIVE_L2____,                 _______MEDIA____R2____,
      _______INACTIVE_L3____,                 _______MEDIA____R3____,
              _______INACTIVE__T____,  _______MEDIA_____T____
 /*           `---------------------'  `---------------------' */
     ),
};

