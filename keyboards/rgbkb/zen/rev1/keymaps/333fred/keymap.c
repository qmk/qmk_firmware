/*
  Copyright (c) 2020 Fred Silberberg

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include QMK_KEYBOARD_H
#include "333fred.h"

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.             .-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |SHIFT |
 * |------+------+------+------+------+------+------..-----+------+------+------+------+------+------|
 * | Ctrl |  F4  |  F5  |  GUI | Alt  | Bksp |Lwr/VM||Enter|Space |  NAV |   -  |   =  |  Alt | Del  |
 * `------------------------------------------------''-----------------------------------------------'
 */
[BASE] = LAYOUT( \
  KC_GRV,        KC_1,         KC_2,  KC_3,    KC_4,    KC_5,                            KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_MINUS, \
  KC_TAB,        KC_Q,         KC_W,  KC_E,    KC_R,    KC_T,                            KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_ESC,        KC_A,         KC_S,  KC_D,    KC_F,    KC_G,                            KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  OSM(MOD_LSFT), LCTL_T(KC_Z), KC_X,  KC_C,    KC_V,    KC_B,                            KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT) , \
  KC_LCTL,       KC_F4,        KC_F5, KC_LGUI, KC_LALT, KC_BSPC, TD(TD_SYM_VIM), KC_ENT, KC_SPACE, OSL(VIM), KC_MINS, KC_EQL,  KC_RALT, KC_DEL \
),

/* Symbols
 * ,-----------------------------------------.              .-----------------------------------------.
 * | Caps |  F1  |  F2  |  F3  |  F4  |  F5  |              |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |   !  |   @  |   (  |   )  |   |  |              |   7  |   8  |   9  |   *  |   )  |  F12 |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |   #  |   $  |   {  |   }  |   `  |              |   4  |   5  |   6  |   +  |   }  |  |   |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * | APscr|   %  |   ^  |   [  |   ]  |   ~  |              |   1  |   2  |   3  |   \  | Vol- | Vol+ |
 * |------+------+------+------+------+------+------..------+------+------+------+------+------+------|
 * | Pscr |      | RESET|      |      | GAME |      ||      |   0  |   .  |   =  | Prev | Next | Play |
 * `------------------------------------------------- -------------------------------------------------'
 */
[SYMB] = LAYOUT( \
    KC_CAPS,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6, KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11, \
    _______,     KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PIPE,                    KC_7,  KC_8,   KC_9,   KC_ASTR, KC_RPRN, KC_F12, \
    _______,     KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                     KC_4,  KC_5,   KC_6,   KC_PLUS, KC_RCBR, KC_PIPE, \
    PSCREEN_APP, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                    KC_1,  KC_2,   KC_3,   KC_BSLS, KC_VOLD, KC_VOLU, \
    KC_PSCR,     _______, RESET,   _______, _______, TO(GAME), _______, _______, KC_0,  KC_DOT, KC_EQL, KC_MPRV, KC_MNXT, KC_MPLY \
),

/* Vim Movement
 * ,-----------------------------------------.              .-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      | RESET|      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |RGBSAI|RGBVAI|RGBSAD| LSFT |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      | DLeft|DRight| LCTRL| LGUI |      |              | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |RGBHUD|RGBVAD|RGBHUI|      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------..------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      ||      |      |      |      |      |      |      |
 * `------------------------------------------------..------------------------------------------------'
 */
[VIM] =  LAYOUT( \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, RESET,   _______, \
    _______, RGB_SAI, RGB_VAI, RGB_SAD, KC_LSFT, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, DLEFT,   DRIGHT,  KC_LCTL, KC_LGUI, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, RGB_HUD, RGB_VAD, RGB_HUI, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Gaming mode (Raise)
 * All one-shot mods are disabled on this layer
 * ,-----------------------------------------.              .-----------------------------------------.
 * | ESC  |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * | CTRL |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * | Shift|   Z  |      |      |      |      |              |      |      |      |      |      |  GUI |
 * |------+------+------+------+------+------+------..------+------+------+------+------+------+------|
 * | Enter|      | Lock | Bksp |  Alt |  Spc | RESET||      | Lower| Left |  Up  | Down | Right|QWERTY|
 * `------------------------------------------------..-----------------------------------------------'
 */
[GAME] =  LAYOUT( \
    KC_ESC,  _______,        _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______, \
    _______, _______,        _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______, \
    KC_LCTL, _______,        _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______, \
    KC_LSFT, KC_Z,           _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_LGUI, \
    KC_ENT,  TG(GAME_ARROW), KC_LOCK, KC_BSPC, KC_F5,   KC_LALT, KC_SPC, OSL(SYMB), KC_F6,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, TO(BASE) \
),
/* Gaming Arrow mode (Raise)
 * Turns wasd into arrows
 * ,-----------------------------------------.              .-----------------------------------------.
 * | ESC  |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * | CTRL | Left | Down | Right|      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * | Shift|   Z  |      |      |      |      |              |      |      |      |      |      |  GUI |
 * |------+------+------+------+------+------+------..------+------+------+------+------+------+------|
 * | Enter|      | Lock | Bksp |  Alt |  Spc | RESET||      | Lower| Left |  Up  | Down | Right|QWERTY|
 * `------------------------------------------------..-----------------------------------------------'
 */
[GAME_ARROW] =  LAYOUT( \
    KC_ESC,  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______, \
    _______, _______, KC_UP,   _______, _______, _______,                    _______, _______, _______, _______, _______, _______, \
    KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                    _______, _______, _______, _______, _______, _______, \
    KC_LSFT, KC_Z,    _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_LGUI, \
    KC_ENT,  _______, KC_LOCK, KC_BSPC, KC_F5,   KC_LALT, KC_SPC, OSL(SYMB), KC_F6,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, TO(BASE) \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_process_keycode(keycode);
    return true;
}
