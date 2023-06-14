/* Copyright 2021 Fernando "ManoShu" Rodrigues
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

#include "keymap_brazilian_abnt2.h"
#include "sendstring_brazilian_abnt2.h"

enum { 
    LAYER_BASE, 
    LAYER_FUNCTIONS 
};

#define L_FUNCT MO(LAYER_FUNCTIONS)
#define W_CHOLD LGUI_T(KC_CAPS)

//Combination keycodes
#define KC_PSBR C(KC_PAUSE)    // Ctrl+Pause/Break
#define KC_SNIP SGUI(BR_S)     // Screen Snip (GUI + Shift + S)
#define KC_WRUN G(BR_R)        // Run (GUI + R)
#define KC_WLCK G(BR_L)        // Lock (GUI + L)
#define KC_WDSK G(BR_D)        // Desktop (GUI + D)
#define KC_WEXP G(BR_E)        // Explorer (GUI + E)
#define KC_WPSE G(KC_PAUSE)    // System Properties (GUI + Pause)
#define KC_WMGP G(BR_EQL)      // Magnify (+)
#define KC_WMGM G(BR_MINS)     // Magnify (-)

enum custom_keycodes {
    KC_WPRN = SAFE_RANGE,  // Project (P)
    KC_WSPC                // Input Select (Space)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == LAYER_BASE) {
        unregister_mods(MOD_MASK_GUI);
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(keycode == KC_WPRN || keycode == KC_WSPC) {
        if (record->event.pressed) {

            register_code(KC_LGUI);

            if(keycode == KC_WPRN) {
                tap_code(KC_P);
            } else if (keycode == KC_WSPC) {
                tap_code(KC_SPACE);
            }
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT(
        /* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
              KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,              KC_F9,    KC_F10,  KC_F11,   KC_F12,
        /* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┤ */
             BR_QUOT,   BR_1,     BR_2,     BR_3,      BR_4,    BR_5,     BR_6,      BR_7,    BR_8,     BR_9,     BR_0,    BR_MINS,  BR_EQL,        KC_BSPC,
        /* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┤ */
                KC_TAB,      BR_Q,     BR_W,     BR_E,     BR_R,     BR_T,     BR_Y,     BR_U,     BR_I,     BR_O,     BR_P,    BR_ACUT,  BR_LBRC,      KC_ENT,
        /* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬           ┤ */
                  W_CHOLD,      BR_A,     BR_S,      BR_D,    BR_F,     BR_G,     BR_H,     BR_J,     BR_K,     BR_L,    BR_CCED,  BR_TILD,  BR_RBRC,
        /* ├───────────┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴─────────┴─┬─────────┤ */
              KC_LSFT,   BR_BSLS,   BR_Z,     BR_X,     BR_C,     BR_V,     BR_B,     BR_N,     BR_M,    BR_COMM,  BR_DOT,   BR_SCLN,      BR_SLSH,       KC_UP,
        /* ├───────────┼─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┤ */
              KC_LCTL,   L_FUNCT,    KC_LALT,                                 KC_SPC,                            KC_APP,    KC_DEL,  KC_LEFT,  KC_DOWN,  KC_RGHT
        /* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
    ),
    [LAYER_FUNCTIONS] = LAYOUT(
        /* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
              QK_BOOT,           _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_PSBR,  KC_SNIP, 
        /* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┤ */
             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_WMGM,  KC_WMGP,       _______,
        /* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┤ */
               _______,     KC_MPLY,  KC_MUTE,  KC_WEXP,  KC_WRUN,  _______,  _______,  _______,  _______,  _______,  KC_WPRN,  _______,  _______,      _______,
        /* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬           ┤ */
                 _______,      KC_MPRV,  KC_MNXT,  KC_WDSK,  _______,  _______,  _______,  _______,  _______,  KC_WLCK,  _______,  _______,  _______,    
        /* ├───────────┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴─────────┴─┬─────────┤ */
              _______,   _______,  KC_VOLU,  KC_VOLD,  KC_CALC,  _______,  _______,  _______,  _______,  _______,  _______,  _______,      _______,      KC_PGUP, 
        /* ├───────────┼─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┤ */
              _______,    _______,    _______,                                KC_WSPC,                           _______,   KC_INS,  KC_HOME,  KC_PGDN,  KC_END
        /* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
    )
};