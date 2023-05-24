/* Copyright 2020 Jonathan Rascher
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

#include "bcat.h"

#if defined(OLED_ENABLE)
#    include "bcat_oled.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /* Default layer: http://www.keyboard-layout-editor.com/#/gists/08d9827d916662a9414f48805aa895a5 */
    [LAYER_DEFAULT] = LAYOUT_split_3x6_3(
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                                KC_LCTL,  LY_LWR,   KC_SPC,   KC_ENT,   LY_RSE,   KC_RALT
    ),
    /* Lower layer: http://www.keyboard-layout-editor.com/#/gists/c3fba5eaa2cd70fdfbdbc0f9e34d3bc0 */
    [LAYER_LOWER] = LAYOUT_split_3x6_3(
        MC_ALTT,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                      KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
        KY_CSPC,  KY_ZMRST, KY_ZMOUT, KY_ZMIN,  KC_WBAK,  KC_WFWD,                      KC_PIPE,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_TILD,
        _______,  KC_APP,   KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_LGUI,                      KC_BSLS,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_GRV,
                                                _______,  _______,  _______,  _______,  _______,  _______
    ),
    /* Raise layer: http://www.keyboard-layout-editor.com/#/gists/08b44355d4ca85d294bad9e2821f91d7 */
    [LAYER_RAISE] = LAYOUT_split_3x6_3(
        KC_CAPS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_F11,   KC_DEL,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,                       KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_F12,   KC_INS,
                                                _______,  _______,  _______,  _______,  _______,  _______
    ),
    /* Adjust layer: http://www.keyboard-layout-editor.com/#/gists/77e7572e077b36a23eb2086017e16fee */
    [LAYER_ADJUST] = LAYOUT_split_3x6_3(
        _______,  _______,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,                      EEP_RST,  RESET,    _______,  _______,  _______,  _______,
        _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,                      RGB_RMOD, RGB_VAD,  RGB_VAI,  RGB_MOD,  RGB_SPI,  _______,
        _______,  _______,  _______,  KC_MUTE,  _______,  _______,                      RGB_HUI,  RGB_SAD,  RGB_SAI,  RGB_HUD,  RGB_SPD,  _______,
                                                _______,  _______,  _______,  RGB_TOG,  _______,  _______
    ),
    // clang-format on
};

#if defined(OLED_ENABLE)
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return is_keyboard_master() ? OLED_ROTATION_270 : OLED_ROTATION_180; }

void oled_task_keymap(const oled_keyboard_state_t *keyboard_state) {
    render_oled_layers();
    oled_advance_page(/*clearPageRemainder=*/false);
    render_oled_indicators(keyboard_state->leds);
    oled_advance_page(/*clearPageRemainder=*/false);
    oled_advance_page(/*clearPageRemainder=*/false);
    render_oled_wpm(keyboard_state->wpm);
    render_oled_pet(/*col=*/0, /*line=*/12, keyboard_state);
}
#endif
