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

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
extern rgblight_config_t rgblight_config;
#endif



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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MAC = SAFE_RANGE,
  WIN,
  NUM,
  LOWER,
  RAISE,
  NUM_RAISE,
  ADJUST,
  ALT_US,
  ALT_JP,
  MAC_IME,
  WIN_IME,
  A_IME_M,
  A_IME_W,
  DBG_LAY,
};

// Tap Dance
enum tap_dances{
    TD_GRV_ESC = 0 ,
    TD_Y_LBRC,
    TD_LSFT_CAPS,
    TD_LBRC_RBRC,
    TD_ESC_NUM,
    TD_MINS_MAC_IME,
    TD_MINS_WIN_IME,
    TD_SCLN_MINS,
};

// Tap Dance state
// for toggle layer by ESC
enum {
    SINGLE_TAP = 1,
    DOUBLE_TAP,
    TRIPLE_TAP,
    TAP_HOLD,
};

// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);
// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);
void ql_each(qk_tap_dance_state_t *state, void *user_data);

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_Y_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_LBRC),
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_LBRC_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_ESC_NUM] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275),
    [TD_MINS_MAC_IME] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275),
    [TD_MINS_WIN_IME] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, WIN_IME),
    [TD_SCLN_MINS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 500),
};

#define ESC_NUM TD(TD_ESC_NUM)
#define Y_LBRC  TD(TD_Y_LBRC)
#define S_CAP   TD(TD_LSFT_CAPS)
#define L_R_BRC TD(TD_LBRC_RBRC)
#define M_M_IME TD(TD_MINS_MAC_IME)
#define M_W_IME TD(TD_MINS_WIN_IME)
#define SCLN_M  TD(TD_SCLN_MINS)
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_NRAI LT(_NUM_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)
#define SP_GUI  MT(MOD_LGUI, KC_SPC)
#define SP_SFT  MT(MOD_LSFT, KC_SPC)
#define S_SLS   RSFT_T(KC_SLSH)
#define C_SCLN  RCTL_T(KC_SCLN)
#define C_QUOT  RCTL_T(KC_QUOT)
#define C_MINS  RCTL_T(KC_MINS)
#define C_SLSH  RCTL_T(KC_SLSH)
#define CT_E     LCTL(KC_E)
#define CT_A     LCTL(KC_A)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT(
        ESC_NUM,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, \
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,    KC_LBRC,KC_RBRC, \
        KC_LCTL,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   SCLN_M, KC_ENT,     XXXXXXX,KC_QUOT, \
        S_CAP,          KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, C_SLSH, KC_RSFT,KC_UP,  LOWER,   \
        KC_MUTE,XXXXXXX,KC_LALT,KC_LGUI,        SP_SFT,         SP_RAI,         KC_RGUI,A_IME_M,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT  \
    ),
    [_WIN] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,_______, \
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,_______, \
        _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
        _______,_______,KC_LGUI,KC_LALT,        _______,        _______,        A_IME_W,KC_APP, _______,_______,_______,_______  \
    ),
    [_NUM] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,XXXXXXX,KC_PSLS,KC_PSLS,KC_PAST,_______,_______,_______,_______, \
        _______,    _______,_______,_______,_______,_______,_______,KC_P7,  KC_P8,  KC_P9,  KC_PPLS,_______,    _______,_______, \
        _______,    _______,_______,_______,_______,_______,_______,KC_P4,  KC_P5,  KC_P6,  XXXXXXX,  _______,  _______,_______, \
        _______,        _______,_______,_______,_______,_______,_______,KC_P1,  KC_P2,  KC_P3,  KC_PENT,_______,_______,_______, \
        _______,_______,_______,_______,        _______,        SP_NRAI,        KC_P0,  KC_PDOT,_______,_______,_______,_______  \
    ),
    [_LOWER] = LAYOUT(
        KC_PAUS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, \
        KC_PSCR,    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_UP,      KC_END, KC_VOLU,  \
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,KC_PGUP,KC_LEFT,KC_RGHT,    _______,KC_VOLD,  \
        _______,        _______,_______,_______,_______,_______,_______,_______,_______,KC_PGDN,KC_DOWN,_______,KC_PGUP,_______, \
        ADJUST, _______,_______,_______,        _______,        ADJUST,         _______,_______,_______,KC_HOME,KC_PGDN,KC_END  \
    ),
    [_RAISE] = LAYOUT(
        KC_PAUS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, \
        KC_PSCR,    _______,_______,CT_E,   _______,_______,_______,_______,_______,_______,KC_PGUP,KC_DEL,     _______,_______,\
        _______,    CT_A,   _______,KC_DEL, KC_RGHT,KC_ESC, KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_MINS,KC_INS,     _______,_______, \
        _______,        _______,_______,_______,_______,KC_LEFT,KC_PGDN,KC_ENT, _______,KC_MRWD,KC_MFFD,_______,KC_PGUP,ADJUST,  \
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,KC_HOME,KC_PGDN,KC_END  \
    ),
    [_NUM_RAISE] = LAYOUT(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, \
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,    KC_LBRC,KC_RBRC, \
        KC_LCTL,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_ENT,    KC_SCLN,KC_QUOT, \
        S_CAP,          KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, S_SLS,  KC_RSFT,XXXXXXX,ADJUST,  \
        _______,_______,_______,_______,        _______,        ADJUST,         _______,_______,_______,_______,_______,_______  \
    ),
    [_ADJUST] = LAYOUT(
        _______,RGB_HUI,RGB_SAI,RGB_VAI,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
        _______,    _______,WIN,    _______,RESET,  _______,_______,_______,_______,_______,_______,_______,    _______,_______, \
        _______,    _______,_______,_______,_______,_______,_______,_______,RGB_M_P,RGB_TOG,RGB_MOD,_______,    _______,_______, \
        _______,        _______,_______,_______,_______,_______,TG(_NUM),MAC,   _______,_______,_______,_______,_______,_______, \
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,_______,_______,_______  \
    )
};

// レイヤーキーを変換・無変換キーと共用する際に動作を改善する。
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
static bool alt_ime_pressed = false;
static uint16_t alt_ime_pressed_time = 0;

// デフォルトレイヤー格納用
static uint16_t current_default_layer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

switch (keycode) {
    case DBG_LAY:
        if (current_default_layer == _MAC) {
            SEND_STRING("L-MAC");
        } else if (current_default_layer == _WIN) {
            SEND_STRING("L-WIN");
        } else {
            SEND_STRING("L-NO");
        }
        return false;
        break;
    case MAC: // Write default layer to EEPROM
        if (record->event.pressed) {
            set_single_persistent_default_layer(_MAC);
        }
        return false;
        break;
    case WIN: // Write default layer to EEPROM
        if (record->event.pressed) {
            set_single_persistent_default_layer(_WIN);
        }
        return false;
        break;
    case LOWER:
        if (record->event.pressed) {
            lower_pressed = true;
            lower_pressed_time = record->event.time;

            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);

            // /*
            // 長押し時に入力キャンセルする場合
            // if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
            //
            // 長押しキャンセルなしの場合
            // if (lower_pressed) {
            // */
            // if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
            //     register_code(KC_LANG1); // for macOS
            //     register_code(KC_HENK);
            //     unregister_code(KC_HENK);
            //     unregister_code(KC_LANG1);
            // }
            lower_pressed = false;
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            raise_pressed = true;
            raise_pressed_time = record->event.time;

            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);

            // /*
            // 長押し時に入力キャンセルする場合はこれ
            // if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
            // */
            // if (raise_pressed) {
            //     register_code(KC_LANG2); // for macOS
            //     register_code(KC_MHEN);
            //     unregister_code(KC_MHEN);
            //     unregister_code(KC_LANG2);
            // }
            raise_pressed = false;
          }
        return false;
        break;
    case ADJUST:
        if (record->event.pressed) {
            layer_on(_ADJUST);
        } else {
            layer_off(_ADJUST);
        }
        return false;
        break;
    case A_IME_M:
        if (record->event.pressed) {
            alt_ime_pressed = true;
            alt_ime_pressed_time = record->event.time;
            register_code(KC_RALT);
        } else {
            unregister_code(KC_RALT);
            /*
            長押し時に入力キャンセルする場合はこれ
            if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
            */
            // if (alt_ime_pressed) {
            if (alt_ime_pressed && (TIMER_DIFF_16(record->event.time, alt_ime_pressed_time) < TAPPING_TERM)) {
                register_code(KC_LCTL); // for macOS
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_LCTL);
            }
            alt_ime_pressed = false;
        }
        return false;
        break;
    case A_IME_W:
        if (record->event.pressed) {
            alt_ime_pressed = true;
            alt_ime_pressed_time = record->event.time;
            register_code(KC_RALT);
        } else {
            unregister_code(KC_RALT);
            /*
            長押し時に入力キャンセルする場合はこれ
            if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
            */
            // if (alt_ime_pressed) {
            if (alt_ime_pressed && (TIMER_DIFF_16(record->event.time, alt_ime_pressed_time) < TAPPING_TERM)) {
                // register_code(KC_LALT);
                // register_code(KC_GRV);
                // unregister_code(KC_GRV);
                // unregister_code(KC_LALT);
                SEND_STRING(SS_LALT("`"));
            }
            alt_ime_pressed = false;
        }
        return false;
        break;
    case MAC_IME:
        if (record->event.pressed) {
            // when pressed
            register_code(KC_LCTL);
            register_code(KC_SPC);
        } else {
            // when released
            unregister_code(KC_SPC);
            unregister_code(KC_LCTL);
        }
        break;
    case WIN_IME:
        if (record->event.pressed) {
            // when pressed
            register_code(KC_LALT);
            register_code(KC_GRV);
        } else {
            // when released
            unregister_code(KC_GRV);
            unregister_code(KC_LALT);
        }
        break;
    default:
        if (record->event.pressed) {
            // reset the flags
            lower_pressed = false;
            raise_pressed = false;
            alt_ime_pressed = false;
            alt_ime_pressed = false;
        }
        break;
    }
    return true;
}

//------------------------------------------------------------------------------
// RGB Light settings
#ifdef RGBLIGHT_LAYERS

// 1st LED
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_win_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_YELLOW}
);

// 2nd LED
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

    if (layer_state_cmp(state, _MAC)) {
        current_default_layer = _MAC;
    } else if (layer_state_cmp(state, _WIN)) {
        current_default_layer = _WIN;
    }

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    return true;
}
#endif

//------------------------------------------------------------------------------
// TEST LEDs
// void keyboard_post_init_user(void) {
//     rgblight_enable_noeeprom();
//     rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
// }

//------------------------------------------------------------------------------
// Rotary Encoder
void encoder_update_user(uint8_t index, bool clockwise) {
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
}


//------------------------------------------------------------------------------
// Tap Dance function

// ESCキーの動作を、次のようにする設定
// シングルタップ：ESC
// シングルタップしてホールド：NUMレイヤー
// トリプルタップ：Numレイヤーをトグル
// NOTE:ESCを連打（＝タブルタップ）して、Numレイヤーになるのを防止するためトリプルに。

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return TAP_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed) return DOUBLE_TAP;
        else return TAP_HOLD;
    } else if (state->count == 3) return TRIPLE_TAP;
    else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
    .is_press_action = true,
    .state = 0
};

// Functions that control what our tap dance key does
void ql_each(qk_tap_dance_state_t *state, void *user_data) {
}

void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);

    switch(state->keycode) {
        case TD(TD_ESC_NUM):
            switch (ql_tap_state.state) {
                case SINGLE_TAP:
                case DOUBLE_TAP:
                    tap_code(KC_ESC);
                    break;
                case TAP_HOLD:
                    layer_on(_NUM);
                    break;
                case TRIPLE_TAP:
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

        case TD(TD_MINS_MAC_IME):
            switch (ql_tap_state.state) {
                case SINGLE_TAP:
                case TAP_HOLD:
                    register_code(KC_MINS);
                    break;
                case DOUBLE_TAP:
                    //TODO デフォルトレイヤーが何かを読み取り、MAC or WINで処理を変える
                    register_code(KC_LCTL);
                    register_code(KC_SPC);
                    break;
                }
            break;

        case TD(TD_SCLN_MINS):
            switch (ql_tap_state.state) {
                case SINGLE_TAP:
                case TAP_HOLD:
                    register_code(KC_SCLN);
                    break;
                case DOUBLE_TAP:
                    register_code(KC_MINS);
                    break;
            }
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->keycode) {
        case TD(TD_ESC_NUM):
            // If the key was held down and now is released then switch off the layer
            if (ql_tap_state.state == TAP_HOLD) {
                layer_off(_NUM);
            }
            ql_tap_state.state = 0;
            break;

        case TD(TD_MINS_MAC_IME):
            switch (ql_tap_state.state) {
                case SINGLE_TAP:
                case TAP_HOLD:
                    unregister_code(KC_MINS);
                    break;
                case DOUBLE_TAP:
                    //TODO デフォルトレイヤーが何かを読み取り、MAC or WINで処理を変える
                    unregister_code(KC_LCTL);
                    unregister_code(KC_SPC);
                    break;
            }
            break;

        case TD(TD_SCLN_MINS):
            switch (ql_tap_state.state) {
                case SINGLE_TAP:
                case TAP_HOLD:
                    unregister_code(KC_SCLN);
                    break;
                case DOUBLE_TAP:
                    unregister_code(KC_MINS);
                    break;
            }
            break;
    }
}

//------------------------------------------------------------------------------
/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
