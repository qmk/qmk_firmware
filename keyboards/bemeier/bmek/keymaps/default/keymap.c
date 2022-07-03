/* Copyright 2020 bemeier
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
   [0] = LAYOUT_hhkb(
/* Default layer
┌─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ F13 │ │ ESC │  1  │  2  │  3  │  4  │  5  │  6  │    │  7  │  8  │  9  │  0  │  -  │  =  │  \  │  `  │
├─────┤ ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┘  ┌─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴─────┤
│ F14 │ │  TAB  │  Q  │  W  │  E  │  R  │  T  │      │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  BSPC │
├─────┤ ├───────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐     └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴───────┤
│ F15 │ │  CTRL  │  A  │  S  │  D  │  F  │  G  │       │  H  │  J  │  K  │  L  │  ;  │  '  │   ENTER   │
├─────┤ ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐     ┌┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴──────┬────┤
│ F16 │ │ SHFT    │  Z  │  X  │  C  │  V  │  B  │     │  B  │  N  │  M  │  ,  │  .  │  /  │  SHFT │ Fn │
└─────┘ └─────────┼─────┼─────┴┬────┴─────┴─────┤     ├─────┴─────┴────┬┴─────┼─────┼─────┴───────┴────┘
                  │ GUI │ ALT  │     SPACE      │     │   SPACE/Fn_1   │  ALT │ CTL │
                  └─────┴──────┴────────────────┘     └────────────────┴──────┴─────┘
*/
  KC_F13,  KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  KC_F14,  KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,  KC_BSPC,
  KC_F15, KC_LCTL,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,         KC_ENT,
  KC_F16, KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_B,   KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   KC_RSFT,  MO(1),
                     KC_LGUI, KC_LALT,                KC_SPC,           LT(1, KC_SPC),          KC_RALT, KC_RCTL
), [1] = LAYOUT_hhkb(
/* Function Layer 1: Nav
┌─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ RST │ │ PWR │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │    │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │ INS │ DEL │
├─────┤ ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┘  ┌─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴─────┤
│     │ │ CAPS  │     │     │     │     │     │      │     │     │PSCR │SLCK │PAUS │  ^  │     │       │
├─────┤ ├───────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐     └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴───────┤
│     │ │        │ o)  │ o)} │  Ø  │EJCT │     │       │  *  │  /  │HOME │PGUP │ <-  │  -> │           │
├─────┤ ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐     ┌┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴──────┬────┤
│     │ │         │     │     │ CFG │     │     │     │  +  │  -  │     │ END │PGDN │  v  │       │    │
└─────┘ └─────────┼─────┼─────┴┬────┴─────┴─────┤     ├─────┴─────┴────┬┴─────┼─────┼─────┴───────┴────┘
                  │     │      │                │     │                │      │     │
                  └─────┴──────┴────────────────┘     └────────────────┴──────┴─────┘
*/
 QK_BOOT,   KC_PWR,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
 _______, KC_CAPS,   _______, _______, _______, _______, _______,        _______, _______, KC_PSCR, KC_SLCK, KC_PAUS,   KC_UP, _______,  _______,
 _______, _______,    KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______,          KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,        KC_PENT,
 _______, _______, _______, _______, TG(2), _______, _______, _______,    KC_PPLS, KC_PMNS,  KC_END, KC_PGDN, KC_DOWN,       _______,    _______,
                     _______, _______,               _______,                 _______,          _______, _______
), [2] = LAYOUT_hhkb(
/* Function Layer 4: Firmware Config (TODO)
┌─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ RST │ │     │     │     │     │     │     │     │    │     │     │     │     │     │     │     │     │
├─────┤ ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┘  ┌─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴───┬─┴─────┤
│     │ │       │ RGB │RGB+ │RGB- │HUE+ │HUE- │      │     │     │     │     │     │     │     │       │
├─────┤ ├───────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐     └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴───────┤
│     │ │        │     │SPD+ │SPD- │SAT+ │SAT- │       │     │     │     │     │     │     │           │
├─────┤ ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┐     ┌┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴──────┬────┤
│     │ │         │     │     │ ___ │VAL+ │VAL- │     │     │     │     │     │     │     │       │    │
└─────┘ └─────────┼─────┼─────┴┬────┴─────┴─────┤     ├─────┴─────┴────┬┴─────┼─────┼─────┴───────┴────┘
                  │     │      │                │     │                │      │     │
                  └─────┴──────┴────────────────┘     └────────────────┴──────┴─────┘
*/
 QK_BOOT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 XXXXXXX, XXXXXXX,  RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
 XXXXXXX, XXXXXXX,    XXXXXXX, RGB_SPI, RGB_SPD, RGB_SAI, RGB_SAD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,
 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TG(2), RGB_VAI, RGB_VAD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______,
                     XXXXXXX, XXXXXXX,               XXXXXXX,                 _______,          XXXXXXX, XXXXXXX
) };
