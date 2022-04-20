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
    _BASE,
    _FN,
    _OHK_R, // one-handed keyboard (right side)
    _OHK_L, // one-handed keyboard (left side)
    // add new ones above here
    _JUMP,
    _LAYER_COUNT
} layer_names;

typedef enum dancy_ {
    ESC_LAYER = 0,
    BS_LAYER,
    LAYERED,
    DANCE_COUNT,
} edancy;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMK_YGID = SAFE_RANGE,
    QMK_BYE_BOO,
    TMUX_N,
    TMUX_L,
    TMUX_R,
    TMUX_U,
    TMUX_D,
    TMUX_LSB,
    VIM_W,
    VIM_H,
    VIM_J,
    VIM_K,
    VIM_L,
    OHK_R,
    OHK_L,
    LOWER,
    RAISE,
    TO_BASE,
    TO_FN,
    TO_NUM,
};

layer_names base_layer = _BASE;

#define AUDIO LSG(KC_A)
#define VIDEO LSG(KC_V)
#define WCOPY LCTL(KC_C)
#define WPASTE LCTL(KC_V)
#define MCOPY LGUI(KC_C)
#define MPASTE LGUI(KC_V)
#define LSG_T_SPACE LSG_T(KC_SPACE)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_MS_BTN1,    KC_MS_BTN2,   KC_BSPC,   KC_KP_7,   KC_KP_8,    KC_KP_9,
        KC_WH_U,       KC_WH_D,      TMUX_LSB,  KC_KP_4,   KC_KP_5,    KC_KP_6,
        TMUX_R,        TMUX_N,       KC_SPACE,  KC_KP_1,   KC_KP_2,    KC_KP_3,
        MO(_JUMP),     RAISE,        KC_LSFT,   KC_KP_0,   KC_KP_DOT,  KC_ENTER
    ),
    [_FN] = LAYOUT(
        KC_TRNS,       KC_TRNS,      XXXXXXX,   KC_F7,     KC_F8,      KC_F9,
        TMUX_R,        TMUX_N,       XXXXXXX,   KC_F4,     KC_F5,      KC_F6,
        KC_TRNS,       KC_TRNS,      XXXXXXX,   KC_F1,     KC_F2,      KC_F3,
        LOWER,         RAISE,        KC_TRNS,   KC_F10,    KC_RGUI,    KC_RALT
    ),
    // one-handed keyboard
    [_OHK_R] = LAYOUT(
        KC_Y,          KC_U,         KC_I,      KC_O,       KC_P,       KC_BSPC,
        KC_H,          KC_J,         KC_K,      KC_L,       KC_COLON,   KC_ENTER,
        KC_N,          KC_M,         KC_COMM,   KC_DOT,     KC_SLSH,    KC_RSHIFT,
        KC_SPACE,      RAISE,        LOWER,     KC_RGUI,    KC_RALT,    KC_RCTL
    ),
    [_OHK_L] = LAYOUT(
        KC_T,          KC_R,         KC_E,      KC_W,       KC_Q,       KC_ESC,
        KC_G,          KC_F,         KC_D,      KC_S,       KC_A,       KC_TAB,
        KC_B,          KC_V,         KC_C,      KC_X,       KC_Z,       KC_LSFT,
        KC_SPACE,      RAISE,        LOWER,     KC_LGUI,    KC_LALT,    KC_LCTL
    ),
    // one-off for jumping
    [_JUMP] = LAYOUT(
        XXXXXXX,       XXXXXXX,      XXXXXXX,   G(KC_7),   G(KC_8),    G(KC_9),
        XXXXXXX,       XXXXXXX,      XXXXXXX,   G(KC_4),   G(KC_5),    G(KC_6),
        XXXXXXX,       XXXXXXX,      XXXXXXX,   G(KC_1),   G(KC_2),    G(KC_3),
        XXXXXXX,       XXXXXXX,      XXXXXXX,   G(KC_0),   XXXXXXX,    XXXXXXX
    ),

};
// clang-format on

#define CTRL_B              \
    register_code(KC_LCTL); \
    register_code(KC_B);    \
    unregister_code(KC_B);  \
    unregister_code(KC_LCTL);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMK_YGID:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(":you-got-it-dude:");
            } else {
                // when keycode is released
            }
            break;
        case QMK_BYE_BOO:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(":bye-boo:");
            } else {
                // when keycode is released
            }
            break;
        case TMUX_N:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("b") "n");
            } else {
                // when keycode is released
            }
            break;
        case TMUX_L:
            if (record->event.pressed) {
                // when keycode is pressed
                CTRL_B;
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            } else {
                // when keycode is released
            }
            break;
        case TMUX_R:
            if (record->event.pressed) {
                // when keycode is pressed
                CTRL_B;
                register_code(KC_L);
                unregister_code(KC_L);
                // unregister_code(KC_LEFT);
                // when keycode is released
            }
            break;
        case TMUX_U:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("b") "k");
            } else {
                // when keycode is released
            }
            break;
        case TMUX_D:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("b") "j");
            } else {
                // when keycode is released
            }
            break;
        case TMUX_LSB:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("b") "[");
            } else {
                // when keycode is released
            }
            break;
        case VIM_H:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("w") "h");
            } else {
                // when keycode is released
            }
            break;
        case VIM_J:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("w") "j");
            } else {
                // when keycode is released
            }
            break;
        case VIM_K:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("w") "k");
            } else {
                // when keycode is released
            }
            break;
        case VIM_L:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_LCTL("w") "l");
            } else {
                // when keycode is released
            }
            break;
        case TO_BASE:
            if (record->event.pressed) {
                // when keycode is pressed
                base_layer = _BASE;
                layer_clear();
                layer_on(base_layer);
            } else {
                // when keycode is released
            }
            break;
    }
    return true;
}

// tap-dance code here
typedef enum elayer_direction {
    _DIRECTION_UP,
    _DIRECTION_DOWN,
    _DIRECTION_COUNT,
} layer_direction;

layer_names get_next_layer(layer_direction direction) {
    layer_names result = base_layer;

    // don't allow wrapping
    if (direction == _DIRECTION_DOWN) {
        if (result > _BASE) {
            result -= 1;
        }
    } else {
        if (result < _FN) {
            result += 1;
        }
    }
    return result;
}

static td_tap_t dancy_tap_state[DANCE_COUNT] = {
    {// ESC_LAYER
     .is_pressed_action = true,
     .state             = TD_NONE},
    {// BS_LAYER
     .is_pressed_action = true,
     .state             = TD_NONE},
    {// LAYERED
     .is_pressed_action = true,
     .state             = TD_NONE},
};

void escl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_tap_t *tap_state = &(dancy_tap_state[0]);

    tap_state->state = cur_dance(state);

    switch (tap_state->state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ESC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_FN);
            break;
        case TD_DOUBLE_TAP:
            // check to see if the layer is already set
            if (layer_state_is(_FN)) {
                // if already set, then switch it off
                layer_off(_FN);
            } else {
                // if not already set, switch the layer on
                layer_on(_FN);
            }
            break;
        default:
            break;
    }
}

void escl_reset(qk_tap_dance_state_t *state, void *user_data) {
    // get the correct button
    td_tap_t *tap_state = &(dancy_tap_state[0]);

    if (tap_state->state == TD_SINGLE_HOLD) {
        layer_off(_FN);
    }

    tap_state->state = TD_NONE;
}

void bsl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_tap_t *tap_state = &(dancy_tap_state[1]);

    tap_state->state = cur_dance(state);

    switch (tap_state->state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BSPACE);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_FN);
            break;
        case TD_DOUBLE_TAP:
            // check to see if the layer is already set
            if (layer_state_is(_FN)) {
                // if already set, then switch it off
                layer_off(_FN);
            } else {
                // if not already set, switch the layer on
                layer_on(_FN);
            }
            break;
        default:
            break;
    }
}

void bsl_reset(qk_tap_dance_state_t *state, void *user_data) {
    // get the correct button
    td_tap_t *tap_state = &(dancy_tap_state[1]);

    if (tap_state->state == TD_SINGLE_HOLD) {
        layer_off(_FN);
    }

    tap_state->state = TD_NONE;
}

bool bHeld = false;
void layers_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_tap_t *tap_state = &(dancy_tap_state[0]);

    tap_state->state = cur_dance(state);
    layer_names next = get_next_layer(_DIRECTION_UP);
    ;

    switch (tap_state->state) {
        case TD_SINGLE_TAP:
            if (next != base_layer) {
                set_oneshot_layer(next, ONESHOT_START);
            }
            break;

        case TD_SINGLE_HOLD:
            // only do something if we're still going up
            if (next != base_layer) {
                bHeld = true;
                layer_on(next);
                base_layer = next;
            }
            break;
        case TD_DOUBLE_TAP:
            // if we hit the top, stop
            if (next != base_layer) {
                layer_on(next);
                base_layer = next;
            }
            break;
        case TD_TRIPLE_TAP:
            next = get_next_layer(_DIRECTION_DOWN);

            // if we hit the bottom, stop
            if (next != base_layer) {
                layer_on(next);
                layer_off(base_layer);
                base_layer = next;
            }
            break;
        case TD_QUAD_TAP:
            // just reset the things
            base_layer = _BASE;
            layer_clear();
            layer_on(base_layer);
            break;
        default:
            break;
    }
}

void layers_reset(qk_tap_dance_state_t *state, void *user_data) {
    // get the correct button
    td_tap_t *  tap_state = &(dancy_tap_state[0]);
    layer_names next      = get_next_layer(_DIRECTION_DOWN);

    if (tap_state->state == TD_SINGLE_TAP) {
        if (base_layer != get_next_layer(_DIRECTION_UP)) {
            clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
    } else if (tap_state->state == TD_SINGLE_HOLD) {
        if (bHeld) {
            layer_off(base_layer);
            base_layer = next;
        }
        bHeld = false;
    }

    tap_state->state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [ESC_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, escl_finished, escl_reset, 275),
    [BS_LAYER]  = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, bsl_finished, bsl_reset, 275),
};
