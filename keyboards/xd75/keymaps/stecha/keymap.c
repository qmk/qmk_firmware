/* Copyright 2017 Wunder
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

// Layer shorthand
#define _QWERTY 0
#define _NUM 1
#define _SYM 2

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { ALT_TAB = SAFE_RANGE, DSKP_LEFT, DSKP_RIGHT };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | '      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | CAP LK | A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
     * | LCTRL  | LGUI   | LALT   | FN     | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | SPACE  | FN     | RALT   | RGUI   | RCTRL  |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */

    [_QWERTY] = LAYOUT_ortho_5x15(/* QWERTY */
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_NO, KC_NO, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, C(G(KC_LEFT)), KC_NO, C(G(KC_RIGHT)), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_LBRC, KC_NO, KC_RBRC, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        LSFT_T(KC_BSLS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MINS, KC_UP, KC_EQL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, MO(_NUM), KC_SPC, KC_NO, KC_DOWN, KC_NO, KC_ENT, MO(_SYM), KC_RGUI, KC_RALT, KC_NO, KC_RCTRL),

    /* FUNCTION
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | F1     | F2     | F3     | F4     | F5     | F6     | NUM LK | P/     | P*     | F7     | F8     | F9     | F10    | F11    | F12    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | SELECT | CALC   | MYCOMP | MAIL   | RGB HD | RGB HI | P7     | P8     | P9     | -      |        |        | PR SCR | SCR LK | PAUSE  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | PREV   | PLAY   | NEXT   | STOP   | RGB SD | RGB SI | P4     | P5     | P6     | +      |        | RESET  |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | VOL-   | MUTE   | VOL+   | APP    | RGB VD | RGB VI | P1     | P2     | P3     | PENT   |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        | RGB TG | FN     | RGB RMD| RGB MD | P0     |        | P.     | PENT   | PENT   | FN     |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */

    [_NUM] = LAYOUT_ortho_5x15(/* NUM */
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_HOME, RESET, KC_PGUP, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        LCTL_T(KC_TAB), KC_LT, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_GT, KC_TAB,
        LSFT_T(KC_GRV), KC_UNDS, KC_LPRN, KC_DEL, KC_MINS, KC_LBRC, KC_END, KC_PSCREEN, KC_PGDN, KC_RBRC, KC_EQL, KC_INS, KC_RPRN, KC_PLUS, KC_RSFT,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, MO(_NUM), KC_SPC, KC_NO, KC_NO, KC_NO, KC_ENT, MO(_SYM), KC_RGUI, KC_RALT, KC_NO, KC_RCTRL),

    [_SYM] = LAYOUT_ortho_5x15(/* SYM */
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_HOME, RESET, KC_PGUP, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        LSFT_T(KC_GRV), RGB_MOD, RESET, RGB_HUD, RGB_SAD, RGB_VAD, KC_END, KC_PSCREEN, KC_PGDN, RGB_VAI, RGB_SAI, RGB_HUI, KC_NO, RGB_TOG, KC_RSFT,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, MO(_NUM), KC_SPC, KC_NO, KC_NO, KC_NO, KC_ENT, MO(_SYM), KC_RGUI, KC_RALT, KC_NO, KC_RCTRL)};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DSKP_LEFT:
            if (record->event.pressed) { r // key down
                key_timer = timer_read();
                register_mods(MOD_BIT(KC_LGUI));
            } else {                                   // key up
                if (timer_elapsed(key_timer) < 200) {  // up before 200ms considered a tap
                    tap_code16(C(KC_LEFT));
                }
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case DSKP_RIGHT:
            if (record->event.pressed) {  // key down
                key_timer = timer_read();
                register_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LALT));     // key up
                if (timer_elapsed(key_timer) < 200) {  // up before 200ms considered a tap
                    tap_code16(C(G(KC_RIGHT)));
                }
            }
            return false;
        case ALT_TAB:
            if (record->event.pressed) {  // key down
                key_timer = timer_read();
                register_mods(MOD_BIT(KC_LCTL));
            } else {  // key up
                unregister_mods(MOD_BIT(KC_LCTL));
                if (timer_elapsed(key_timer) < 200) {  // up before 200ms considered a tap
                    tap_code16(LALT(KC_TAB));
                }
            }
            return false;
    }
    return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
