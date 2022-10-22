 /* Copyright 2020 Hekeke 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details.  
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        
    /* Base layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ ` │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ^ │     │Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent├───┤
     * │ FN   │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │PUp│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │Shft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │PDn│
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┼───┴┬──┴─┬─┴──┬───┼───┼───┤
     * │Ctrl│LAlt│LGUI│        Space        │RAlt│App │RCtl│ ← │ ↓ │ → │
     * └────┴────┴────┴─────────────────────┴────┴────┴────┴───┴───┴───┘
     */
    [0] = LAYOUT_65_iso(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Function layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬────┐
     * │§  │ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│Delete │PrtS│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼────┤
     * │Caps │Prv│Pau│Nxt│   │   │   │   │   │   │BL+│BL-│BL │QK_BOOT│Ins │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├────┤
     * │      │V- │V0 │V+ │   │   │   │   │   │   │   │   │   │    │Home│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼────┤
     * │    │TOG│MOD│HU+│HU-│SA+│SA-│   │   │   │   │   │LClick│MUp│End │
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┼───┴┬──┴─┬─┴──┬───┼───┼────┤
     * │    │    │    │                     │    │    │    │MLt│MDw│MRgt│
     * └────┴────┴────┴─────────────────────┴────┴────┴────┴───┴───┴────┘
     */

    [1] = LAYOUT_65_iso(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_PSCR,
        KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, BL_INC,  BL_DEC,  BL_TOGG,          KC_INS,
        _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, KC_HOME,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_END,
        _______, _______, _______,                   _______,                            _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
    ),
};


