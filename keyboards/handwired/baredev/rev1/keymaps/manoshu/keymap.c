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

#include "keymap_br_abnt2.h"
#include "sendstring_br_abnt2.h"

enum { 
    LAYER_BASE, 
    LAYER_FUNCTIONS 
};

#define L_FUNCT MO(LAYER_FUNCTIONS)
#define W_CHOLD LGUI_T(KC_CAPS)
#define SEND_WINDOWS(x) SEND_STRING(SS_LGUI(x))

enum custom_keycodes {
    KC_SNIP = SAFE_RANGE,  // Screen Snip (Shift + S)
    KC_WRUN,               // Run (R)
    KC_WLCK,               // Lock (L)
    KC_WDSK,               // Desktop (D)
    KC_WEXP,               // Explorer (E)
    KC_WPSE,               // System Properties (Pause)
    KC_WMGP,               // Magnify (+)
    KC_WMGM,               // Magnify (-)
    KC_WPRN,               // Project (P)
    KC_WSPC,               // Input Select (Space)
    KC_PSBR                // Ctrl-Pause/Break
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
    } else if (keycode == KC_PSBR) {
        if (record->event.pressed) {
            register_code(KC_LCTL);
            tap_code(KC_PAUSE);
            unregister_code(KC_LCTL);
        }
    } else if (record->event.pressed) {
        switch (keycode) {
            case KC_SNIP:               // Screen Snip (Win + Shift + S)
                SEND_WINDOWS(SS_LSFT("s"));
                break;
            case KC_WRUN:               // Run
                SEND_WINDOWS("r");
                break;
            case KC_WLCK:               // Lock
              SEND_WINDOWS("l");
              break;
            case KC_WDSK:               // Desktop
              SEND_WINDOWS("d");
              break;
            case KC_WEXP:               // Explorer
              SEND_WINDOWS("e");
              break;
            case KC_WPSE:               // System Properties (Pause)
              SEND_WINDOWS(SS_TAP(X_PAUSE));
              break;
            case KC_WMGP:               // Magnify +
              SEND_WINDOWS("=");
              break;
            case KC_WMGM:               // Magnify -
              SEND_WINDOWS("-");
              break;
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
              RESET,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_PSBR,  KC_SNIP, 
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