/* Copyright 2023 Will Hedges (@will-hedges)
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

enum layers {
    _WORK,
    _QWER,
    _FN1
};

enum custom_keycodes {
    BASE_QWER = SAFE_RANGE,
    BASE_WORK
};

// Tap Dance enum
enum {
    N8_F8,
    N9_F9,
    N0_F10,
    MINS_F11,
    EQL_F12,
    DEL_BSLS,
    G_END,
    H_HOME,
    LALT_PGUP,
    RALT_PGDN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WORK] = LAYOUT_60_ansi(
        QK_GESC,           KC_1,    KC_2,            KC_3,   KC_4,    KC_5,      KC_6,       KC_7,    TD(N8_F8), TD(N9_F9), TD(N0_F10),      TD(MINS_F11), TD(EQL_F12), KC_BSPC,
        KC_TAB,            KC_Q,    KC_W,            KC_E,   KC_R,    KC_T,      KC_Y,       KC_U,    KC_I,      KC_O,      KC_P,            KC_LBRC,      KC_RBRC,     TD(DEL_BSLS),
        LT(_FN1, KC_CAPS), KC_A,    KC_S,            KC_D,   KC_F,    TD(G_END), TD(H_HOME), KC_J,    KC_K,      KC_L,      KC_SCLN,         KC_QUOT,                   KC_ENT,
        KC_LSFT,                    KC_Z,            KC_X,   KC_C,    KC_V,      KC_B,       KC_N,    KC_M,      KC_COMM,   KC_DOT,          KC_SLSH,                   KC_RSFT,
        KC_LCTL,           KC_LGUI, LALT_T(KC_PGUP),                  KC_SPC,                                               RALT_T(KC_PGDN), KC_APP,       MO(_FN1),    KC_RCTL
    ),

    [_QWER] = LAYOUT_60_ansi(
        QK_GESC,           KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
        KC_TAB,            KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  TD(DEL_BSLS),
        LT(_FN1, KC_CAPS), KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT,                    KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT,
        KC_LCTL,           KC_LGUI, KC_LALT,                  KC_SPC,                                      KC_RALT, KC_APP,  MO(_FN1), KC_RCTL
    ),

    [_FN1] = LAYOUT_60_ansi(
        _______, KC_F1,        KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_DEL,
        _______, _______,      KC_PGUP, _______, QK_RBT,  _______, _______, _______, KC_UP,   _______, _______, _______,   _______, _______,
        _______, KC_HOME,      KC_PGDN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,            _______,
        _______,               _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, _______,            _______,
        _______, C(A(KC_DEL)), _______,                   _______,                                     _______, BASE_WORK, _______, BASE_QWER
    )

};


// Tap Dance tap vs. hold docs @ https://docs.qmk.fm/#/feature_tap_dance?id=example-3
//  Macros are also used with process_record_user @ https://docs.qmk.fm/#/feature_macros?id=using-macros-in-c-keymaps
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        // MACROS
        case BASE_QWER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWER);
            }
            break;

        case BASE_WORK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORK);
            }
            break;

        // TAP DANCES
        case TD(N8_F8):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(N9_F9):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(N0_F10):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(MINS_F11):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(EQL_F12):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(DEL_BSLS):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(G_END):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(H_HOME):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [N8_F8] = ACTION_TAP_DANCE_TAP_HOLD(KC_8, KC_F8),
    [N9_F9] = ACTION_TAP_DANCE_TAP_HOLD(KC_9, KC_F9),
    [N0_F10] = ACTION_TAP_DANCE_TAP_HOLD(KC_0, KC_F10),
    [MINS_F11] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, KC_F11),
    [EQL_F12] = ACTION_TAP_DANCE_TAP_HOLD(KC_EQL, KC_F12),
    [DEL_BSLS] = ACTION_TAP_DANCE_TAP_HOLD(KC_DEL, KC_BSLS),
    [G_END] = ACTION_TAP_DANCE_TAP_HOLD(KC_G, KC_END),
    [H_HOME] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, KC_HOME)
};
