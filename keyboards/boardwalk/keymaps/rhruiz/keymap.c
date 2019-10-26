/*
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
#include "rhruiz.h"

const hue_sat_pair hue_sat_pairs[] = {[_FN1] = {2, 255}, [_FN2] = {200, 255}, [_CFG] = {80, 255}};

// clang-format off
#ifndef LAYOUT_kc
#define LAYOUT_kc( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16, R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26, R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43, L44, L45, L46, R40, R41, R42, R43, R44, R45, R46 \
    ) \
    LAYOUT_ortho_5x14( \
        KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, KC_##L06, KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, KC_##R06, \
        KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, KC_##L16, KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, KC_##R16, \
        KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##L26, KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25, KC_##R26, \
        KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##L36, KC_##R30, KC_##R31, KC_##R32, KC_##R33, KC_##R34, KC_##R35, KC_##R36, \
        KC_##L40, KC_##L41, KC_##L42, KC_##L43, KC_##L44, KC_##L45, KC_##L46, KC_##R40, KC_##R41, KC_##R42, KC_##R43, KC_##R44, KC_##R45, KC_##R46 \
    )
#endif
// clang-format on

#define KC__FN1 MO(_FN1)
#define KC__FN2 MO(_FN2)
#define KC_RFN1 LT(_FN1, KC_RGHT)
#define KC_DFN2 LT(_FN2, KC_DEL)
#define KC_BFN2 BKSFN2
#define KC_CESC CTRLESC
#define KC_MISS MISCTRL
#define KC_____ KC_TRNS
#define KC__VUP KC__VOLUP
#define KC__VDN KC__VOLDOWN
#define KC_RST RESET
#define KC_ENTS SFT_T(KC_ENT)
#ifdef RGBLIGHT_ENABLE
#    define KC_RVAD RGB_VAD
#    define KC_RVAI RGB_VAI
#else
#    define KC_RVAD KC_TRNS
#    define KC_RVAI KC_TRNS
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_kc(
    GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,  ESC ,
    TAB,  Q,    W,    E,    R,    T,    LBRC, RBRC, Y,    U,    I,    O,    P,    BSLS,
    CESC, A,    S,    D,    F,    G,    PGUP, ENT , H,    J,    K,    L,    SCLN, QUOT,
    LSFT, Z,    X,    C,    V,    B,    PGDN, BSLS, N,    M,    COMM, DOT,  SLSH, ENTS,
    _FN2, LCTL, LALT, LGUI, _FN1, SPC,  SPC,  BFN2, BFN2, RGUI, LEFT, DOWN, UP,   RFN1
  ),

  [_VIM_EMACS] = LAYOUT_kc(
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, LEFT, DOWN, UP  , RGHT, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____
  ),

  [_MOUSE] = LAYOUT_kc(
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____
  ),

  [_KEY_OVERRIDE] = LAYOUT_kc(
    TILD, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, UNDS, PLUS,
    ____, ____, ____, ____, ____, ____, LCBR,   RCBR, ____, LPRN, RPRN, ____, ____, PIPE,
    ____, ____, ____, ____, ____, ____, ____,   PENT, ____, ____, ____, ____, COLN, DQUO,
    ____, ____, ____, ____, ____, ____, ____,   PIPE, ____, ____, LT  , GT  , QUES, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, MRWD, MPLY, MFFD, ____
  ),

  [_FN1] = LAYOUT_kc(
    ____, EXLM, AT  , HASH, DLR , PERC, CIRC,   AMPR, ASTR, LPRN, RPRN, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, LBRC, RBRC, ____,
    ____, ____, ____, ____, MINS, EQL , ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   DFN2, DFN2, ____, ____, ____, ____, ____
  ),

  [_FN2] = LAYOUT_kc(
    ____, F1  , F2  , F3  , F4  , F5  , ____,   F6  , F7  , F8  , F9  , F10 , F11 , F12 ,
    ____, BTN1, MS_U, BTN2, ____, ____, ____,   ____, ____, ____, ____, LCBR, RCBR, ____,
    ____, MS_L, MS_D, MS_R, UNDS, PLUS, WH_D,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, WH_U,   ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,   ____, ____, ____, ____, ____, ____, ____
  ),

  [_CFG] = LAYOUT_ortho_5x14(
    KC_ESC , KC_SLCK, KC_PAUS, KC_MISS, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, RESET  ,
    _______, KC__VUP, KC__VDN, KC_MUTE, KC_EJCT, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

// clang-format on

void matrix_scan_user(void) { rhruiz_update_layer_colors(); }

bool rhruiz_is_layer_indicator_led(uint8_t index) { return index == RGBLED_NUM - 1 || index == RGBLED_NUM / 2; }

void rhruiz_update_layer_colors() {
    if (biton32(layer_state) < 1UL) {
        return;
    }

    const hue_sat_pair hs = hue_sat_pairs[biton32(layer_state)];

    rhruiz_change_leds_to(hs.hue, hs.sat);
}
