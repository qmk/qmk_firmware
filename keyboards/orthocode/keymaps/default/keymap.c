/* Copyright 2020 Jrodna
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
     /* Rotary                                                                                                                                  */
        KC_MUTE,
     /*           esc      1        2        3        4        5        6        7        8        9        0        -        =        home     */
        UG_TOGG,    QK_GESC, KC_1,    KC_2,    KC_3,  KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_HOME,
     /*           tab      Q        W        E        R        T        Y        U        I        O        P        \        delete   end      */
        UG_NEXT,    KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS, KC_DEL,  KC_END,
     /*           caps     A        S        D        F        G        H        J        K        L        ;        '        enter             */
        UG_PREV,    KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
     /*           shift    Z        X        C        V        B        N        M        ,        .        /                 up                */
                  KC_LSFT,   KC_Z,    KC_X,    KC_C,  KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,          KC_UP,
     /*           ctrl     win      alt      fn       th1      th2      th3      th4      fn       alt      ctrl     left     down     right    */
                  KC_LCTL, KC_LGUI, KC_LALT, MO(1),  KC_RSFT, KC_ENT,  KC_BSPC, KC_SPC, MO(1),   KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [1] = LAYOUT(
     /* Rotary                                                                                                                                                  */
        TG(2),
     /*          esc      1        2        3        4       5       6        7            8          9           0        -         =     home  */
      KC_TRNS, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,   KC_F7,       KC_F8,      KC_F9,      KC_F10,  KC_F11,   KC_F12,  KC_TRNS,
     /*          tab      Q       W        E        R        T       Y        U             I           O          P         \      delete     end */
      UG_HUEU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,KC_TRNS,KC_TRNS, KC_TRNS, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_TRNS, KC_TRNS,  KC_PAUS, KC_TRNS,
     /*          caps      A       S        D        F        G      H         J            K          L         ;        '        enter    */
      UG_HUED, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,     KC_LBRC,    KC_RBRC, KC_TRNS, KC_TRNS,  KC_TRNS,
     /*         shift      Z         X        C       V       B       N       M             ,           .          /                       up      */
              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, LSFT(KC_EQL), LSFT(KC_9), LSFT(KC_0), KC_TRNS,             KC_VOLU,
     /*         ctrl     win      alt        fn     th1      th2     th3      th4          fn         alt       ctrl      left     down     right*/
              KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS, KC_VOLD,  KC_TRNS
    ),
    [2] = LAYOUT(
     /* Rotary                                                                                                                                 */
        KC_TRNS,
     /*          esc      1        2        3        4        5        6        7        8        9        0        -        =        home     */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     /*          tab      Q        W        E        R        T        Y        U        I        O        P        \        delete   end      */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS, KC_TRNS,
     /*          caps     A        S        D        F        G        H        J        K        L        ;        '        enter             */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS,
     /*          shift    Z        X        C        V        B        N        M        ,        .        /                 up                */
                 KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
     /*          ctrl     win      alt      fn       th1      th2      th3      th4      fn       alt      ctrl     left     down     right    */
                 KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_SPC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

    )
};


