/*
  Copyright 2020 Joel Elkins <joel@elkins.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jdelkins.h"

#undef LAYOUT
#define LAYOUT LAYOUT_directional_nosplitspace

#define IDLE_TIMEOUT 360
uint16_t rgb_idle_seconds = 0;
uint16_t rgb_timer;
bool rgb_was_enabled;

// Tap Dance

int ctl_state = 0;

void ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    ctl_state = cur_dance(state);
    switch(ctl_state) {
        case SINGLE_TAP:    qk_leader_start(); break;
        case SINGLE_HOLD:   register_code(KC_LCTL); break;
        case DOUBLE_TAP:    tap_code(KC_RCTL); break;
        case DOUBLE_HOLD:   register_code(KC_RCTL); break;
        case TRIPLE_TAP:    tap_code(KC_RCTL); tap_code(KC_RCTL); break;
        case TRIPLE_HOLD:   tap_code(KC_RCTL); register_code(KC_RCTL); break;
    }
}

void ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch(ctl_state) {
        case SINGLE_HOLD:   unregister_code(KC_LCTL); break;
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:   unregister_code(KC_RCTL); break;
    }
    ctl_state = 0;
}

void g_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case SINGLE_TAP:
            tap_code16(C(KC_END));
            break;
        case DOUBLE_TAP:
            tap_code16(C(KC_HOME));
            break;
    }
}

enum {
    TD_LDCTL,
    TD_G,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LDCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_finished, ctl_reset),
    [TD_G]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, g_finished, NULL),
};

// Layers

const uint16_t PROGMEM keymaps[_LAYER_MAX][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            KC_GESC,      KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,        KC_MINS, KC_EQL,  KC_BSPC,
            KC_TAB,       KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,        KC_LBRC, KC_RBRC, KC_BSLS,
            MY_CAPS,      KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN,     KC_QUOT,          KC_ENT,
            KC_LSFT,      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,     KC_RSFT, KC_BSPC, MO(_ADJUST),
            TD(TD_LDCTL), MY_GUI, MY_ALT,                 MY_SPC,                KC_RALT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [_GAME] = LAYOUT(
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, KC_LALT,                       KC_SPC,                         _______, _______, _______, _______, _______
    ),
    [_FUNC] = LAYOUT(
            KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,
            _______, _______, FW_WRD,  KB_EOL,  _______, _______,  KB_COPY, KC_PGUP, _______, _______, KB_PASTE, KC_SLCK, _______, MY_CALC,
            _______, KB_BOL,  _______, KC_PGDN, _______, TD(TD_G), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,  _______,          _______,
            _______, _______, KC_DEL,  _______, _______, BK_WRD,   _______, _______, _______, _______, _______,  _______, KC_INS,  _______,
            _______, MY_RGUI, MY_RALT,                        _______,                        _______, KC_HOME,  KC_PGDN, KC_PGUP, KC_END
    ),
    [_KP] = LAYOUT(
            _______,    _______, _______, _______, _______, _______, _______, _______, KC_KP_ASTERISK, _______,   _______,     _______, _______, _______,
            KC_NUMLOCK, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, KC_KP_7, KC_KP_8,        KC_KP_9,   KC_KP_MINUS, _______, _______, _______,
            _______,    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, KC_KP_4, KC_KP_5,        KC_KP_6,   KC_KP_PLUS,  _______,          _______,
            _______,    _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2,        KC_KP_3,   KC_KP_SLASH, _______, _______, TG(_KP),
            _______,    _______, _______,                       KC_KP_0,                               KC_KP_DOT, _______,     _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
            KC_GRV,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
            _______, RGB_SPD,  RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, KC_PSCR, KC_SLCK, _______, KC_MUTE,
            _______, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, TG(_KP), _______, _______, _______,          KC_MPLY,
            _______, RGB_TOG,  KB_MAKE, KB_FLSH, KB_VRSN, KB_BOOT, _______, TG_SYS,  _______, _______, _______, _______, KC_DEL,  _______,
            _______, MY_RGUI,  MY_RALT,                      _______,                         _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
    ),
};

const rgblight_segment_t PROGMEM game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED},
    {7, 2, HSV_RED},
    {15, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_GREEN}
);

const rgblight_segment_t PROGMEM kp_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_BLUE}
);

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_WHITE}
);

const rgblight_segment_t PROGMEM numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_PURPLE},
    {14, 2, HSV_PURPLE}
);


enum rgb_layer_index {
    L_GAME,
    L_FUNC,
    L_KP,
    L_ADJUST,
    L_CAPSLOCK,
    L_NUMLOCK,
};

const rgblight_segment_t * const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        [L_GAME] = game_layer,
        [L_FUNC] = func_layer,
        [L_KP] = kp_layer,
        [L_ADJUST] = adjust_layer,
        [L_CAPSLOCK] = capslock_layer,
        [L_NUMLOCK] = numlock_layer
);

layer_state_t layer_state_set_keymap(layer_state_t state) {
    rgblight_set_layer_state(L_GAME, layer_state_cmp(state, _GAME));
    rgblight_set_layer_state(L_FUNC, layer_state_cmp(state, _FUNC));
    rgblight_set_layer_state(L_KP, layer_state_cmp(state, _KP));
    rgblight_set_layer_state(L_ADJUST, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(L_CAPSLOCK, CAPSLOCK_ON);
    rgblight_set_layer_state(L_NUMLOCK, NUMLOCK_ON && layer_state_cmp(state, _KP));
    if (layer_state_cmp(state, _GAME))
        autoshift_disable();
    else
        autoshift_enable();
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(L_CAPSLOCK, led_state.caps_lock);
    rgblight_set_layer_state(L_NUMLOCK, led_state.num_lock && layer_state_is(_KP));
    return true;
}

void keyboard_post_init_keymap(void) {
    rgblight_layers = my_rgb_layers;
    rgb_was_enabled = rgblight_is_enabled();
}

LEADER_EXTERNS();

void matrix_scan_keymap(void) {
    if (rgblight_is_enabled() && timer_elapsed(rgb_timer) > 1000) {
        rgb_idle_seconds++;
        rgb_timer = timer_read();
    }
    if (rgb_idle_seconds > IDLE_TIMEOUT) {
        rgb_was_enabled = rgblight_is_enabled();
        rgblight_disable_noeeprom();
        rgb_idle_seconds = 0;
    }
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_K) {
            layer_invert(_KP);
        }
        SEQ_ONE_KEY(KC_G) {
            layer_invert(_GAME);
        }
        SEQ_ONE_KEY(KC_KP_5) {
            layer_invert(_KP);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_1) {
            send_secret_string(0);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_2) {
            send_secret_string(1);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_3) {
            send_secret_string(2);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_4) {
            send_secret_string(3);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_5) {
            send_secret_string(4);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_6) {
            send_secret_string(5);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_M) {
            send_secret_string(0);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_COMM) {
            send_secret_string(1);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_DOT) {
            send_secret_string(2);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_J) {
            send_secret_string(3);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_K) {
            send_secret_string(4);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_L) {
            send_secret_string(5);
        }
        SEQ_ONE_KEY(KC_C) {
            tap_code16(C(KC_C));
        }
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    static uint16_t gesc_timer;

    rgb_idle_seconds = 0;
    if (!rgblight_is_enabled() && rgb_was_enabled)
        rgblight_enable_noeeprom();

    switch (keycode) {
        // custom handle KC_GESC to emulate auto shift on it
        case KC_GESC:
            if (get_autoshift_state()) {
                if (record->event.pressed)
                    gesc_timer = timer_read();
                else {
                    if (timer_elapsed(gesc_timer) > AUTO_SHIFT_TIMEOUT || MODS_SHIFT) {
                        tap_code16(S(KC_GRV));
                    } else if (MODS_GUI)
                        tap_code(KC_GRV);
                    else
                        tap_code(KC_ESC);
                }
                return false;
            }
            return false;
    }

    return true;
}
