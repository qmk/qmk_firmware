/* Copyright 2021 mo
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

// Defines names for use in layer keycodes and the keymap
typedef enum _layer_names {
    _LETTER,
    _NUMBER,
    _FUNCTION,
    _SYMBOL,
    _SPECIAL,
    // add new ones above here
    _JUMP,
    _LAYER_COUNT
} layer_names;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMK_YGID = SAFE_RANGE,
    KC_NUMBER,
    KC_SYMBOL,
    _SHIFT,
    LOWER,
    RAISE,
    KC_SHIFT_LOCK,
};

enum custom_taps {
    TD_RESET = 0,
    TD_SHIFT,

    // add more tap-dance things above here
    TD_MAX,
};

static td_state_t states[TD_MAX] = {
    // TD_RESET
    TD_NONE,

    // TD_SHIFT
    TD_NONE,
};

// We need to include this after the custom keycode definitions
#include "g/keymap_combo.h"

layer_names base_layer = _LETTER;

#define AUDIO LSG(KC_A)
#define VIDEO LSG(KC_V)
#define WCOPY LCTL(KC_C)
#define WPASTE LCTL(KC_V)
#define MCOPY LGUI(KC_C)
#define MPASTE LGUI(KC_V)
#define LSG_T_SPACE LSG_T(KC_SPACE)
#define ONUM OSL(_NUMBER)
#define OSYM OSL(_SYMBOL)
#define OSPEC OSL(_SPECIAL)
#define OSFT OSM(MOD_LSFT)
#define OCTL OSM(MOD_LCTL)
#define OALT OSM(MOD_LALT)
#define OGUI OSM(MOD_LGUI)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Letter */
    [_LETTER] = LAYOUT(
        KC_UP,         KC_F,         KC_A,      KC_R,      KC_W,       KC_P,
        KC_DOWN,       KC_O,         KC_E,      KC_H,      KC_T,       KC_D,
        KC_BSPC,       KC_U,         KC_I,      KC_N,      KC_S,       KC_Y,
        MO(_JUMP),     KC_SPACE,     KC_NUMBER, KC_SYMBOL, KC_ENTER,   TD(TD_SHIFT)
    ),
    [_NUMBER] = LAYOUT(
        KC_TRNS,       KC_ASTR,      KC_7,      KC_8,      KC_9,       KC_MINUS,
        KC_TRNS,       KC_SLASH,     KC_4,      KC_5,      KC_6,       KC_PLUS,
        KC_TRNS,       KC_0,         KC_1,      KC_2,      KC_3,       KC_EQUAL,
        KC_TRNS,       KC_TRNS,      KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    ),
    [_FUNCTION] = LAYOUT(
        KC_TRNS,       KC_ESC,       KC_HOME,   KC_END,    KC_PAUSE,   KC_PGUP,
        KC_TRNS,       KC_INS,       OCTL,      OALT,      KC_UP,      KC_PGDN,
        KC_TRNS,       KC_DEL,       KC_BSPC,   KC_LEFT,   KC_DOWN,    KC_RIGHT,
        KC_TRNS,       KC_TRNS,      KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    ),
    [_SYMBOL] = LAYOUT(
        KC_TRNS,       KC_QUES,      KC_AMPR,   KC_ASTR,   KC_COLON,   KC_SCLN,
        KC_TRNS,       KC_SLASH,     KC_EXLM,   KC_MINUS,  KC_AT,      KC_UNDS,
        KC_TRNS,       KC_DQUO,      KC_LT,     KC_LPRN,   KC_LBRC,    KC_LCBR,
        KC_TRNS,       KC_TRNS,      OSPEC,     KC_TRNS,   KC_TRNS,    KC_TRNS
    ),
    [_SPECIAL] = LAYOUT(
        KC_TRNS,       XXXXXXX,      KC_SCRL,   KC_PSCR,   XXXXXXX,    KC_NUM,
        KC_TRNS,       KC_LEFT,      XXXXXXX,   XXXXXXX,   OGUI,       KC_RIGHT,
        KC_TRNS,       XXXXXXX,      XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,
        KC_TRNS,       KC_TRNS,      KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    ),
    // one-off for jumping
    [_JUMP] = LAYOUT(
        KC_UP,         KC_HOME,      KC_PGUP,   G(KC_7),   G(KC_8),    G(KC_9),
        KC_DOWN,       KC_END,       KC_PGDN,   G(KC_4),   G(KC_5),    G(KC_6),
        XXXXXXX,       XXXXXXX,      OGUI,      G(KC_1),   G(KC_2),    G(KC_3),
        XXXXXXX,       KC_LOCK,      KC_LSFT,   G(KC_0),   KC_LALT,    KC_TAB
    ),
};
// clang-format on

uint8_t  mod_state;
uint16_t shift_count = 0;
bool     process_record_user(uint16_t keycode, keyrecord_t *record) {
    // we need to process the shift+number differently
    mod_state = get_mods();

    switch (keycode) {
            // if we a
        case KC_SYMBOL: {
            if (record->event.pressed) {
                layer_invert(_SYMBOL);
            } else {
            }
            return false;
            break;
        }

            // handle KC_NUMBER presses (toggle the _NUMBER layer with _LETTER if pressed)
            // if held, either go to _FUNCTION (from _LETTER/_NUMBER) or _SPECIAL (from _SYMBOL)
        case KC_NUMBER: {
            static uint16_t number_timer;

            if (record->event.pressed) {
                number_timer = timer_read();

                // go to _NUMBER/_FUNCTION/_SPECIAL
                if (IS_LAYER_ON(_SYMBOL)) {
                    layer_on(_SPECIAL);
                } else {
                    layer_on(_FUNCTION);
                }
            } else {
                // turn off the held layer bits
                if (IS_LAYER_ON(_SPECIAL)) {
                    layer_off(_SPECIAL);
                } else if (IS_LAYER_ON(_FUNCTION)) {
                    layer_off(_FUNCTION);
                }

                // this was a tap, so toggle the number layer
                if (timer_elapsed(number_timer) < TAPPING_TERM) {
                    // toggle num layer
                    layer_invert(_NUMBER);
                }
            }
            return false;
            break;
        }
    }

    return true;
}

void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        // reset the keyboard if you tap more than thrice
        reset_keyboard();
        reset_tap_dance(state);
    }
}

void shift_finished(qk_tap_dance_state_t *state, void *user_data) {
    // get the correct state
    td_state_t *tap_state = &(states[TD_SHIFT]);
    *tap_state            = cur_dance(state);
    switch (*tap_state) {
        case TD_SINGLE_TAP:
            // set one-shot modifier
            set_oneshot_mods(MOD_BIT(KC_LSFT));
            break;

        case TD_DOUBLE_TAP:
            // turn on caps-lock
            tap_code(KC_CAPS);
            break;
        default:
            break;
    }
}

void shift_reset(qk_tap_dance_state_t *state, void *user_data) {
    td_state_t *tap_state = &(states[TD_SHIFT]);
    switch (*tap_state) {
        case TD_SINGLE_TAP:
            // clear_oneshot_mods();
            break;
        case TD_DOUBLE_TAP:
            break;
        default:
            break;
    }
    *tap_state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_RESET] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, safe_reset, NULL, 600),
    [TD_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, shift_finished, shift_reset, 200),
};
/*
bool
led_update_user(led_t led_state)
{
    caps_lock_on = led_state.caps_lock;
    return true;
}
*/
