/* Copyright 2015-2021 Jack Humbert
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
#include "muse.h"
#include "jugemu.h"

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GAME_GENSHIN,
};

#define L_RAISE MO(_RAISE)
#define L_LOWER MO(_LOWER)
#define L_ADJUST MO(_ADJUST)
#define TG_GENSHIN TG(_GAME_GENSHIN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  ~   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  | MODE |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
// [_QWERTY] = LAYOUT(
KC_ESC,        KC_1,   KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,        KC_GRV,
KC_TAB,        KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,        KC_MINS,
KC_LCTL,       KC_A,   KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,     KC_QUOT,
KC_LSFT,       KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,     KC_RSFT,
_______,    KC_LCTL,   KC_LALT, KC_LGUI, L_LOWER, KC_SPC,   KC_ENT,  L_RAISE, KC_BSPC, KC_RGUI, TG_GENSHIN,  CK_TD_MODE
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
    _______,          KC_VOLD, KC_VOLU,TD_AUDIO, _______, _______,    _______, _______, _______,_______, _______, _______,
    KC_F1,              KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    TD(TD_LCTL_GRV),  KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    _______,          _______, _______, _______, _______, _______,    XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______,          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      | vold | volu | audio| PPSCR| FPSCR| del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | volu |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  | vold |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | Pg Up| Pg Dn|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
    _______,         _______,  _______, _______, _______, _______,    KC_VOLD,  KC_VOLU,TD_AUDIO,CK_PPSCR,  CK_FPSCR,  KC_DEL,
    KC_GRV,             KC_1,     KC_2,    KC_3,    KC_4,    KC_5,       KC_6,     KC_7,    KC_8,    KC_9,      KC_0, KC_VOLU,
    TD(TD_RCTL_F1),    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_LEFT,  KC_DOWN,   KC_UP,   KC_RGHT, _______, KC_VOLD,
    TD(TD_LSFT_F7),    KC_F8,    KC_F9,  KC_F10,  KC_F11,  KC_F12,    KC_PLUS,  KC_MINS,  KC_EQL, KC_LBRC,   KC_RBRC, KC_BSLS,
    _______,         _______,  _______, _______, _______,   _______,  _______,  _______, _______, _______,   _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |TermOf|TermOn|      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  KC_INS, KC_HOME, KC_PGUP, XXXXXXX, XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  KC_DEL,  KC_END, KC_PGDN, XXXXXXX,  KC_DOT,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_0,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/* Game Genshin Impact
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  ~   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  | MODE |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME_GENSHIN] = LAYOUT_preonic_grid(
KC_ESC,    KC_1,   KC_2,    KC_3,    KC_4,    KC_M,  KC_6,    KC_7,    KC_8,    KC_9,   CK_FPSCR,   TD_AUDIO,
KC_TAB,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,    KC_VOLU,
KC_LALT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_J,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_VOLD,
KC_LSFT,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,
_______, _______,  KC_LALT, KC_LCTL, KC_SPC, KC_SPC, KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI,  _______, _______
),

};

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){
    return true;
}
