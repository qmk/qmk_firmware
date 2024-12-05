/* Copyright 2020 Takeshi Nishio
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
#include "keymap_japanese.h"

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _MAC = 0,
    _WIN,
    _NUM,
    _LOWER,
    _RAISE,
    _NUM_RAISE,
    _ADJUST
};

// Tap Dance
enum tap_dances{
    TD_LSFT_CAPS = 0,
    TD_ESC_NUM,
};

// Tap Dance state
enum {
    SINGLE_TAP = 1,
    DOUBLE_TAP,
    TRIPLE_TAP,
    TAP_HOLD,
};

// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
uint8_t cur_dance(tap_dance_state_t *state);
// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_ESC_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ESC_NUM):
            return 275;
        default:
            return TAPPING_TERM;
    }
}

// Key Macro
#define ESC_NUM TD(TD_ESC_NUM)
#define S_CAP   TD(TD_LSFT_CAPS)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_NRAI LT(_NUM_RAISE, KC_SPC)
#define SP_SFT  MT(MOD_LSFT, KC_SPC)
#define S_BSLS  RSFT_T(JP_BSLS)
#define C_SLSH  RCTL_T(JP_SLSH)
#define CT_E    LCTL(KC_E)
#define CT_A    LCTL(KC_A)
#define ALT_GRV LALT(KC_GRV)
#define LOWER   MO(_LOWER)
#define NUM     TG(_NUM)
#define MAC     PDF(_MAC)
#define WIN     PDF(_WIN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT_jp(
        ESC_NUM,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   JP_MINS,KC_BSPC,JP_CIRC,JP_YEN,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,               JP_AT,  JP_LBRC,
        KC_LCTL,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   JP_SCLN, KC_ENT,    JP_COLN,JP_RBRC,
        S_CAP,          KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   JP_COMM,JP_DOT, C_SLSH, S_BSLS, KC_UP,  LOWER,
        KC_MUTE,KC_LALT,KC_LGUI,KC_LNG2,       SP_SFT,         SP_RAI,        KC_LNG1,KC_RGUI,KC_RALT,KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [_WIN] = LAYOUT_jp(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,            _______,_______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,_______,
        _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,KC_LGUI,KC_LALT,JP_MHEN,        _______,        _______,        JP_HENK,JP_KANA,KC_APP, _______,_______,_______
    ),
    [_NUM] = LAYOUT_jp(
        _______,_______,_______,_______,_______,_______,_______,XXXXXXX,KC_PSLS,KC_PSLS,KC_PAST,_______,_______,_______,_______,
        _______,    _______,_______,_______,_______,_______,_______,KC_P7,  KC_P8,  KC_P9,  KC_PPLS,            _______,_______,
        _______,    _______,_______,_______,_______,_______,_______,KC_P4,  KC_P5,  KC_P6,  XXXXXXX,_______,    _______,_______,
        _______,        _______,_______,_______,_______,_______,_______,KC_P1,  KC_P2,  KC_P3,  KC_PENT,_______,_______,_______,
        _______,_______,_______,_______,        _______,        SP_NRAI,        KC_P0,  KC_PDOT,_______,_______,_______,_______
    ),
    [_LOWER] = LAYOUT_jp(
        KC_PAUS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_PSCR,    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,            KC_END, KC_VOLU,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,KC_PGUP,KC_LEFT,KC_RGHT,    _______,KC_VOLD,
        _______,        _______,_______,_______,_______,_______,_______,_______,_______,KC_PGDN,KC_DOWN,_______,KC_PGUP,_______,
        _______,_______,_______,_______,        _______,        _______,         _______,_______,_______,KC_HOME,KC_PGDN,KC_END
    ),
    [_RAISE] = LAYOUT_jp(
        KC_PAUS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_PSCR,    _______,_______,CT_E,   _______,_______,_______,_______,_______,_______,KC_PGUP,            _______,_______,
        _______,    CT_A,   _______,KC_DEL, KC_RGHT,KC_ESC, KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,_______,_______,    _______,_______,
        _______,        _______,_______,_______,_______,KC_LEFT,KC_PGDN,KC_ENT, _______,KC_MRWD,KC_MFFD,_______,KC_PGUP,_______,
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,KC_HOME,KC_PGDN,KC_END
    ),
    [_NUM_RAISE] = LAYOUT_jp(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   JP_MINS,KC_BSPC,JP_CIRC,JP_YEN,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,               JP_AT,  JP_LBRC,
        KC_LCTL,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   JP_SCLN, KC_ENT,    JP_COLN,JP_RBRC,
        S_CAP,          KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   JP_COMM,JP_DOT, C_SLSH, S_BSLS, KC_UP,  _______,
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,_______,_______,_______
    ),
    [_ADJUST] = LAYOUT_jp(
        _______,UG_HUEU,UG_SATU,UG_VALU,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    _______,WIN,    _______,QK_BOOT,_______,UG_HUEU,UG_SATU,UG_VALU,_______,UG_PREV,            _______,_______,
        _______,    _______,_______,_______,_______,_______,UG_HUED,UG_SATD,UG_VALD,UG_TOGG,UG_NEXT,_______,    _______,_______,
        _______,        _______,_______,_______,_______,_______,NUM,     MAC,   _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,_______,_______,_______
    )
};

#if defined(AUDIO_ENABLE) && defined(MUSIC_MAP)
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_jp(
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
    38,   39, 40, 41, 42, 43, 44, 45, 46, 47, 48,       49, 50,
    25,   26, 27, 28, 29, 30, 31, 32, 33, 34, 35,  36,  37, 38,
    11,     12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    0,   1,  2,  3,      4,      5,      6,  7,  8,  9, 10, 11
);
#endif

//------------------------------------------------------------------------------
// RGB Light settings
#ifdef RGBLIGHT_LAYERS

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_win_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_YELLOW}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_num_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_RED}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_mac_layer,
    my_win_layer,
    my_num_layer,
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_num_raise_layer,
    my_adjust_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
     state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

   rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _NUM_RAISE));
    rgblight_set_layer_state(7, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _MAC));
    rgblight_set_layer_state(1, layer_state_cmp(state, _WIN));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    return true;
}
#endif


//------------------------------------------------------------------------------
// Rotary Encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder, Right side */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    if (index == 1) { /* Second encoder, Left side */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return true;
}


//------------------------------------------------------------------------------
// Tap Dance function


typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Determine the current tap dance state
uint8_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return SINGLE_TAP;
        } else {
            return TAP_HOLD;
        }
    } else if (state->count == 2) {
        if (!state->pressed) {
            return DOUBLE_TAP;
        } else {
            return TAP_HOLD;
        }
    } else if (state->count == 3) {
        if (!state->pressed) {
            return TRIPLE_TAP;
        } else {
            return TAP_HOLD;
        }
    } else {
        return 8; // Magic number. At some point this method will expand to work for more presses
    }
}

// Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
    .is_press_action = true,
    .state = 0
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch(TAP_DANCE_KEYCODE(state)) {
        case TD(TD_ESC_NUM): // ESC key action
            switch (ql_tap_state.state) {
                case SINGLE_TAP:
                case DOUBLE_TAP:
                    // ESC
                    tap_code(KC_ESC);
                    break;
                case TAP_HOLD:
                    // temporal layer change
                    layer_on(_NUM);
                    break;
                case TRIPLE_TAP:
                    // toggle layer
                    // Check to see if the layer is already set
                    if (layer_state_is(_NUM)) {
                        // If already set, then switch it off
                        layer_off(_NUM);
                    } else {
                        // If not already set, then switch the layer on
                        layer_on(_NUM);
                    }
                    break;
            }
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    switch(TAP_DANCE_KEYCODE(state)) {
        case TD(TD_ESC_NUM):
            // If the key was held down and now is released then switch off the layer
            if (ql_tap_state.state == TAP_HOLD) {
                layer_off(_NUM);
            }
            ql_tap_state.state = 0;
            break;
    }
}
