/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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
#include "version.h"
#include "keymap_steno.h"
#include "itg.h"

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
};

//      KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,              KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
//      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,              KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
//      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,              KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
//      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LSFT_T(KC_ENT),
//      KC_LALT, KC_PGUP, KC_PGDN, LALT_T(KC_DEL), MO(1),     KC_ESC,            KC_LGUI,          KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_NO,
//                                          KC_SPC,  MO(1),   MO(2),             MO(3),   MO(2),   KC_ENT
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWE] = LAYOUT_moonlander(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,           KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,           KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HYPR,           KC_MEH,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LSFT_T(KC_ENT),
        KC_LALT, KC_PGUP, KC_PGDN, LALT_T(KC_DEL), MO(1),     KC_ESC,            KC_LGUI,          KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_NO,
                                            KC_SPC, MO(SYM),  KC_LGUI,           MO(MED), KC_DEL,  KC_ENT
    ),

    [SYM] = LAYOUT_moonlander(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        XXXXXXX, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, TG(SYM),           TG(STN), KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        XXXXXXX, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______,           _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PLUS, _______,
        XXXXXXX, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, XXXXXXX,
        XXXXXXX, _______, _______, _______, _______,          RGB_VAI,           RGB_TOG,          _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,_______, _______
    ),

    [MED] = LAYOUT_moonlander(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, RESET,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,          _______,           _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    /* Keymap 3: Modified QWERTY for Stenography
    *
    * ,--------------------------------------------------.  ,--------------------------------------------------.
    * |   [x]  |   1  |   2  |   3  |   4  |   5  |      |  |  [x] |   6  |   7  |   8  |   9  |   0  |  [x]   |
    * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
    * |   [x]  |   S  |   T  |   P  |   H  |   *  |      |  |      |   Y  |   U  |   I  |   O  |   P  |   [    |
    * |--------+------+------+------+------+------|------|  |------|------+------+------+------+------+--------|
    * |   [x]  |   S  |   K  |   W  |   R  |   *  |      |  |      |   H  |   J  |   K  |   L  |   ;  |   '    |
    * |--------+------+------+------+------+------|------'  `------|------+------+------+------+------+--------|
    * |   [x]  |  [x] |  [x] |  [x] |  [x] |      |                |  [x] |  [x] |  [x] |  [x] |  [x] |  [x]   |
    * `--------+------+------+------+------+------'                `------+------+------+------+------+--------'
    *   | [x]  |  [x] |  [x] |  [x] |  [x] |                              |  [x] |  [x] |  [x] |  [x] |  [x] |
    *   `----------------------------------'                              `----------------------------------'
    *                               ,-------------.                ,-------------.
    *                               |     [x]     |                |     [x]     |
    *                               |--------------------.  ,--------------------|
    *                               |   A  |  O   |  [x] |  |  [x] |   E  |  U   |
    *                               ` -------------------'  `--------------------'
    *
    *
    */
    [STN] = LAYOUT_moonlander(
        XXXXXXX, STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  _______,           XXXXXXX, STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,
        XXXXXXX, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, XXXXXXX,           TG(STN), STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
        XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, XXXXXXX,           XXXXXXX, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            STN_A,   STN_O,   XXXXXXX,           XXXXXXX, STN_E,   STN_U
  ),
};

// #ifdef AUDIO_ENABLE
//   float plover_song[][2]     = SONG(PLOVER_SOUND);
//   float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
// #endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}

void matrix_init_user() {
  steno_set_mode(STENO_MODE_BOLT); // or STENO_MODE_BOLT
}
