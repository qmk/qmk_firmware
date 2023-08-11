/* Copyright 2017 WunderaaaaaAa
 * Modified by RAOEUS
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
#include "keymap_steno.h"

void matrix_init_user(void) {
    steno_set_mode(STENO_MODE_GEMINI);
}

enum layer_names { _QWERTY, _LOWER, _RAISE, _BOTH, _STENO };

enum keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, STENO, EXT_STN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | Bksp   | NUM    | /      | *      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | Del    | 7      | 8      | 9      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | Esc    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | "      | 4      | 5      | 6      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LShift | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | Enter  | 1      | 2      | 3      |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
     * | LCtl   | LAlt   | LGUI   | Steno  | Lower  | Space  | Space  | Raise  | Left   | Down   | Up     | Right  | 0      | .      | Enter  |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_ortho_5x15(
	KC_GRV,   KC_1,    KC_2,    KC_3,  KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC, KC_NUM, KC_PSLS, KC_PAST, 
	KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_DEL,  KC_P7,  KC_P8,   KC_P9, 
	KC_ESC,   KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_P4,  KC_P5,   KC_P6, 
	KC_LSFT,  KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_P1,  KC_P2,   KC_P3, 
	KC_LCTL,  KC_LALT, KC_LGUI, STENO, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_P0,  KC_PDOT, KC_PENT),

    /* STENO
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | #      | #      | #      | #      | #      | #      | #      | #      | #      | #      | #      | #      |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | FN     | S      | T      | P      | H      | *      | *      | F      | P      | L      | T      | D      |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        | S      | K      | W      | R      | *      | *      | R      | B      | G      | S      | Z      |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
     * | EXIT   |        |        | #      | A      | O      | E      | U      | #      | PWR    | RES1   | RES2   |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_STENO] = LAYOUT_ortho_5x15(
	STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,  XXXXXXX, XXXXXXX, XXXXXXX, 
	STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,  XXXXXXX, XXXXXXX, XXXXXXX, 
	XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,  XXXXXXX, XXXXXXX, XXXXXXX, 
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	EXT_STN, XXXXXXX, XXXXXXX, STN_N1,  STN_A,   STN_O,   STN_E,   STN_U,   STN_N2,  STN_PWR, STN_RE1, STN_RE2, XXXXXXX, XXXXXXX, XXXXXXX),

    /* LOWER
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | ~      | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | Bksp   |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | ~      | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | Del    |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | CAPS   | F1     | F2     | F3     | F4     | F5     | F6     | _      | +      | {      | }      | |      |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        | F7     | F8     | F9     | F10    | F11    | F12    | ISO ~  | ISO |  | Home   | End    |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        | Next   | Vol-   | Vol+   | Play   |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_ortho_5x15(
	KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC, _______, _______, _______, 
	KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,  _______, _______, _______, 
	KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, _______, 
	_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______, _______, _______, _______, 
	_______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, _______),

    /* RAISE
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | Bksp   |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | Del    |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | CAPS   | F1     | F2     | F3     | F4     | F5     | F6     | -      | =      | [      | ]      | \      |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        | F7     | F8     | F9     | F10    | F11    | F12    | ISO #  | ISO /  | Pg Up  | Pg Dn  |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        | Next   | Vol-   | Vol+   | Play   |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_ortho_5x15(
	KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, _______, _______, _______, 
	KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  _______, _______, _______, 
	KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______, _______, _______, 
	_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, _______, _______, _______, 
	_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, _______),

    /* BOTH (LOWER + RAISE)
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        | Reset  | Debug  |        |        |        |        |        |        |        |        | Del    |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        | AGNorm | AGSwap | QWERTY | STENO  |        |        | PLAIN  |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | RGB+   |        |        |        |        |        |        | RGBTOG | HUE+   | SAT+   | BRITE+ | SPEED+ |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | RGB-   |        |        |        |        |        |        |        | HUE-   | SAT-   | BRITE- | SPEED- |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_BOTH] = LAYOUT_ortho_5x15(
	KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, 
	_______,  QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, 
	_______,  _______, _______, _______, _______, AG_NORM, AG_SWAP, QWERTY,  STENO,   _______, _______, RGB_M_P, _______, _______, _______, 
	RGB_MOD,  _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, 
	RGB_RMOD, _______, _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                layer_move(_QWERTY);
            };
            return false;
            break;
        case STENO:
            if (record->event.pressed) {
                layer_move(_STENO);
            }
            return false;
            break;
        case EXT_STN:
            if (record->event.pressed) {
                layer_off(_STENO);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _BOTH);
            }
            return false;
            break;
    }
    return true;
}
