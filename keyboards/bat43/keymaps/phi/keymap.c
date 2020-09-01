/* Copyright 2020 yfuku
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

enum layer_numbers {
    BASE = 0,
    RAISE,
    FUNCTION,
    MOUSE,
    WHEEL,
    CURSOR,
};

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_D_MOU LT(MOUSE, KC_D)
#define KC_F_CUR LT(CURSOR, KC_F)
#define KC_A_ESC LALT_T(KC_ESC)

#define KC_RAISE MO(RAISE)
#define KC_WEEL  MO(WHEEL)
#define KC_MOUSE MO(MOUSE)
#define KC_FUNC  MO(FUNCTION)
#define KC_BASE  TO(BASE)
#define KC_DSCO  LCTL(LSFT(LALT(KC_N))) /* mute discord */

#define KC_MUP  KC_MS_U
#define KC_MDN  KC_MS_D
#define KC_MLFT KC_MS_L
#define KC_MRGT KC_MS_R
#define KC_WUP  KC_WH_U
#define KC_WDN  KC_WH_D
#define KC_WLFT KC_WH_L
#define KC_WRGT KC_WH_R
#define KC_ACCL KC_MS_ACCEL2

#define LAYOUT_kc(                                                      \
    k00, k01, k02, k03, k04, k05,      k40, k41, k42, k43, k44, k45,    \
    k10, k11, k12, k13, k14, k15, k30, k50, k51, k52, k53, k54, k55,    \
    k20, k21, k22, k23, k24, k25,      k60, k61, k62, k63, k64, k65,    \
                   k33, k34, k35,      k70, k71, k72,                   \
                        k75, k74,      k73, k31, k32                    \
) LAYOUT(                                                               \
    KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05,           KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_##k44, KC_##k45, \
    KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k30, KC_##k50, KC_##k51, KC_##k52, KC_##k53, KC_##k54, KC_##k55, \
    KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25,           KC_##k60, KC_##k61, KC_##k62, KC_##k63, KC_##k64, KC_##k65, \
                                  KC_##k33, KC_##k34, KC_##k35,           KC_##k70, KC_##k71, KC_##k72,                               \
                                            KC_##k75, KC_##k74,           KC_##k73, KC_##k31, KC_##k32                                \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_kc(
    TAB,  Q,    W,    E,    R,    T,          Y,    U,    I,    O,    P,    MINS,
    LCTL, A,    S,    D_MOU,F_CUR,G,    BSPC, H,    J,    K,    L,    SCLN, QUOT,
    LSFT, Z,    X,    C,    V,    B,          B,    N,    M,    COMM, DOT,  SLSH,
    /*             */ A_ESC,LANG2,SPC,        ENT,  LANG1,RAISE,
    /*                   */ ____, ____,       DSCO, ____, ____
),

[RAISE] = LAYOUT_kc(
    JYEN, 1,    2,    3,    4,    5,          6,    7,    8,    9,    0,    EQL,
    ____, TILD, ____, LCBR, LPRN, LBRC, BSPC, RBRC, RPRN, RCBR, ____, PIPE, PLUS,
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, BSLS,
    /*             */ FUNC, ____, ____,       ____, ____, ____,
    /*                   */ ____, ____,       ____, ____, ____
),

[FUNCTION] = LAYOUT_kc(
    ____, F1,   F2,   F3,   F4,   F5,         F6,   F7,   F8,   F9,   PSCR, ____,
    ____, ____, ____, ____, ____, ____, ____, HOME, PGDN, PGUP, END,  ____, ____,
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, ____,
    /*             */ ____, ____, ____,       ____, ____, ____,
    /*                   */ ____, ____,       ____, ____, ____
),

[MOUSE] = LAYOUT_kc(
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, ____,
    ____, ____, WEEL, ____, ACCL, ____, ____, MLFT, MDN,  MUP,  MRGT, ____, ____,
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, ____,
    /*             */ ____, BTN2, BTN1,       ____, ____, ____,
    /*                   */ ____, ____,       ____, ____, ____
),

[WHEEL] = LAYOUT_kc(
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ACCL, ____, ____, WRGT, WUP,  WDN,  WLFT, ____, ____,
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, ____,
    /*             */ ____, ____, ____,       ____, ____, ____,
    /*                   */ ____, ____,       ____, ____, ____
),

[CURSOR] = LAYOUT_kc(
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, ____,
    ____, ____, ____,MOUSE, ____, ____, ____, LEFT, DOWN, UP,   RGHT, ____, ____,
    ____, ____, ____, ____, ____, ____,       ____, ____, ____, ____, ____, ____,
    /*             */ ____, ____, ____,       ____, ____, ____,
    /*                   */ ____, ____,       ____, ____, ____
),

};
