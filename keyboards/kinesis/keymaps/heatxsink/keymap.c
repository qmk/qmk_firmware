/* Copyright 2022 Nicholas Granado <ngranado@gmail.com>
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

enum layer_names {
    _DEFAULT,
    _QWERTY,
    _COLEMAK_MOD_DH,
    _WORKMAN,
    _KEYPAD,
    _LAYERS,
};

#define DEFAULT DF(_DEFAULT)
#define QWERTY  TO(_QWERTY)
#define CMMDH   TO(_COLEMAK_MOD_DH)
#define WM      TO(_WORKMAN)
#define KEYPAD  TO(_KEYPAD)
#define LAYERS  OSL(_LAYERS)
#define HCTLESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEFAULT] = LAYOUT(
        KC_ESC ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,        KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PSCR,KC_SCRL,KC_PAUS,KEYPAD ,QK_BOOT,
        KC_EQL ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,        KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,
        KC_TAB ,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,KC_BSLS,
        HCTLESC,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,KC_QUOT,
        SC_LSPO,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,SC_RSPC,
                KC_GRV ,LAYERS ,KC_LEFT,KC_RGHT,                KC_UP  ,KC_DOWN,KC_LBRC,KC_RBRC,
                KC_LALT,KC_LCTL,        KC_RCTL,KC_LGUI,
                        KC_HOME,        KC_PGUP,
        KC_BSPC,KC_DEL ,KC_END ,        KC_PGDN,KC_ENT ,KC_SPC
    ),

    [_QWERTY] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,
        _______,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,        KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,_______,
        _______,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,        KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,_______,
        _______,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,        KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,_______,
                _______,_______,_______,_______,                _______,_______,_______,_______,
                _______,_______,        _______,_______,
                        _______,        _______,
        _______,_______,_______,        _______,_______,_______
    ),

    [_COLEMAK_MOD_DH] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,
        _______,KC_Q   ,KC_W   ,KC_F   ,KC_P   ,KC_B,        KC_J   ,KC_L   ,KC_U   ,KC_Y   ,KC_SCLN,_______,
        _______,KC_A   ,KC_R   ,KC_S   ,KC_T   ,KC_G,        KC_M   ,KC_N   ,KC_E   ,KC_I   ,KC_O   ,_______,
        _______,KC_Z   ,KC_X   ,KC_C   ,KC_D   ,KC_V,        KC_K   ,KC_H   ,KC_COMM,KC_DOT ,KC_SLSH,_______,
                _______,_______,_______,_______,                _______,_______,_______,_______,
                _______,_______,        _______,_______,
                        _______,        _______,
        _______,_______,_______,        _______,_______,_______
    ),

    [_WORKMAN] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,
        _______,KC_Q   ,KC_D   ,KC_R   ,KC_W   ,KC_B,        KC_J   ,KC_F   ,KC_U   ,KC_P   ,KC_SCLN,_______,
        _______,KC_A   ,KC_S   ,KC_H   ,KC_T   ,KC_G,        KC_Y   ,KC_N   ,KC_E   ,KC_O   ,KC_I   ,_______,
        _______,KC_Z   ,KC_X   ,KC_M   ,KC_C   ,KC_V,        KC_K   ,KC_L   ,KC_COMM,KC_DOT ,KC_SLSH,_______,
                _______,_______,_______,_______,                _______,_______,_______,_______,
                _______,_______,        _______,_______,
                        _______,        _______,
        _______,_______,_______,        _______,_______,_______
    ),

    [_KEYPAD] = LAYOUT (
        _______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,        _______,KC_NUM, KC_PEQL,KC_PSLS,KC_PAST,_______,
        _______,_______,KC_MUTE,KC_VOLD,KC_VOLU,_______,        _______,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,_______,
        _______,KC_MSTP,KC_MPRV,KC_MPLY,KC_MNXT,KC_MSEL,        _______,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,_______,
        _______,_______,_______,_______,_______,_______,        _______,KC_P1,  KC_P2,  KC_P3,  KC_PENT,_______,
                _______,_______,_______,_______,                KC_LPRN,KC_RPRN,KC_PDOT,KC_PENT,
                _______,_______,        _______,_______,
                        _______,        _______,
        _______,_______,_______,        _______,KC_PENT,KC_P0
    ),

    [_LAYERS] = LAYOUT (
        _______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,QWERTY ,CMMDH  ,WM     ,KEYPAD ,_______,        _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,                _______,_______,_______,_______,
                _______,_______,        _______,_______,
                        _______,        _______,
        _______,_______,_______,        _______,_______,_______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    writePinHigh(LED_NUM_LOCK_PIN);
    writePinHigh(LED_SCROLL_LOCK_PIN);
    writePinHigh(LED_COMPOSE_PIN);
    writePinHigh(LED_CAPS_LOCK_PIN);
    switch (get_highest_layer(state)) {
        case _QWERTY:
            // Caps Lock Lit
            writePinLow(LED_CAPS_LOCK_PIN);
            break;
        case _COLEMAK_MOD_DH:
            // Num Lock Lit
            writePinLow(LED_NUM_LOCK_PIN);
            break;
        case _WORKMAN:
            // Scroll Lock Lit
            writePinLow(LED_SCROLL_LOCK_PIN);
            break;
        case _KEYPAD:
            // Compose Lit
            writePinLow(LED_COMPOSE_PIN);
            break;
        case _LAYERS:
            // All LEDs Lit
            writePinLow(LED_SCROLL_LOCK_PIN);
            writePinLow(LED_NUM_LOCK_PIN);
            writePinLow(LED_CAPS_LOCK_PIN);
            writePinLow(LED_COMPOSE_PIN);
            break;
    }
  return state;
}

bool led_update_user(led_t led_state) {
    // disable led_update_kb() so that we do not override layer indicators
    return false;
}

