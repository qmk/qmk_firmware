/*
 * Copyright 2016 Thomas Fitzsimmons <fitzsim@fitzsim.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "yoruian.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_ergodox_YORUIAN\
(9,  7,    5,    3,    1,    GRV,  MINS, EQL,  LBRC, 0,    2,    4,    6,    8,
 ES, RBRC, Y,    O,    R,    BSLS, P3,   P3,   J,    V,    D,    F,    W,    Q,
 LC, U,    I,    A,    N,    SCLN,             M,    H,    T,    S,    C,    RC,
 FF, QUOT, COMM, DOT,  SLSH, P0,   LGUI, LGUI, K,    L,    P,    G,    B,    X,
 IN, P1,   NO,   NO,   LALT,                         LALT, NO,   NO,   Z,    PS,
                             BSPC, RALT, P2,   TAB,
                                   NO,   NO,
                       E,    LSFT, NO,   NO,   ENT,  SPC),
[1] = LAYOUT_ergodox_YORUIAN\
(TR, TR,   TR,   TR,   TR,   TR,   TR,   TR,   TR,   F5,   F6,   F7,   F8,   F9,
 TR, TR,   TR,   TR,   TR,   TR,   TR,   TR,   TR,   F1,   F2,   F3,   F4,   FT,
 TR, TR,   TR,   TR,   TR,   TR,               PAUS, LEFT, DOWN, UP,   RGHT, FE,
 TR, TR,   TR,   TR,   TR,   TR,   TR,   TR,   TR,   HOME, PGDN, PGUP, END,  FW,
 TR, TR,   TR,   TR,   TR,                           TR,   TR,   TR,   TR,   TR,
                             TR,   TR,   TR,   TR,
                                   TR,   TR,
                       TR,   TR,   TR,   TR,   TR,   TR),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    return MACRO_NONE;
};

void matrix_init_user(void) {
};

void matrix_scan_user(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
};

/*
 * Local Variables:
 * electric-indent-mode: nil
 * End:
 */
