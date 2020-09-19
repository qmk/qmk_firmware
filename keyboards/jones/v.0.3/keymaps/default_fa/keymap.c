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
    _LOWER,
    _RAISE,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MAC = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  A_IME_M,
  A_IME_W,
};

#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_SFT  MT(MOD_LSFT, KC_SPC)
#define S_SLS   RSFT_T(KC_SLSH)
#define C_SLSH  RCTL_T(KC_SLSH)
#define CT_E     LCTL(KC_E)
#define CT_A     LCTL(KC_A)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT_FA(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,  \
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,    KC_LBRC,KC_RBRC, \
        KC_LCTL,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_ENT,     KC_QUOT,KC_QUOT, \
        KC_LSFT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, C_SLSH, KC_RSFT,KC_UP,  LOWER,   \
        KC_MUTE,XXXXXXX,KC_LALT,KC_LGUI,        SP_SFT,         SP_RAI,         KC_RGUI,A_IME_M,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT, \
        KC_NLCK, KC_PSLS, KC_PAST, KC_PEQL,        KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU, \
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS, \
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
        KC_P1,   KC_P2,   KC_P3,            \
        KC_P0,            KC_PDOT, KC_PENT  \
    ),
    [_LOWER] = LAYOUT_FA(
        KC_PAUS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,  \
        KC_PSCR,    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_UP,      KC_END, KC_VOLU, \
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,KC_PGUP,KC_LEFT,KC_RGHT,    _______,KC_VOLD, \
        _______,        _______,_______,_______,_______,_______,_______,_______,_______,KC_PGDN,KC_DOWN,_______,KC_PGUP,_______, \
        ADJUST, _______,_______,_______,        _______,        ADJUST,         _______,_______,_______,KC_HOME,KC_PGDN,KC_END,  \
        _______,_______,_______,_______,           _______,_______,_______,_______, \
        _______,_______,_______,_______, \
        _______,_______,_______,_______, \
        _______,_______,_______,         \
        _______,        _______,_______  \
    ),
    [_RAISE] = LAYOUT_FA(
        KC_PAUS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,  \
        KC_PSCR,    _______,_______,CT_E,   _______,_______,_______,_______,_______,_______,KC_PGUP,KC_DEL,     _______,_______, \
        _______,    CT_A,   _______,KC_DEL, KC_RGHT,KC_ESC, KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_MINS,KC_INS,     _______,_______, \
        _______,        _______,_______,_______,_______,KC_LEFT,KC_PGDN,KC_ENT, _______,KC_MRWD,KC_MFFD,_______,KC_PGUP,ADJUST,  \
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,KC_HOME,KC_PGDN,KC_END,  \
        _______,_______,_______,_______,           _______,_______,_______,_______, \
        _______,_______,_______,_______, \
        _______,_______,_______,_______, \
        _______,_______,_______,         \
        _______,        _______,_______  \
    ),
    [_ADJUST] = LAYOUT_FA(
        _______,RGB_HUI,RGB_SAI,RGB_VAI,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
        _______,    _______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,    _______,_______, \
        _______,    _______,_______,_______,_______,_______,_______,_______,RGB_M_P,RGB_TOG,RGB_MOD,_______,    _______,_______, \
        _______,        _______,_______,_______,_______,_______,_______,MAC,   _______,_______,_______,_______,_______,_______, \
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,_______,_______,_______, \
        _______,_______,_______,_______,           _______,_______,_______,_______, \
        _______,_______,_______,_______, \
        _______,_______,_______,_______, \
        _______,_______,_______,         \
        _______,        _______,_______  \
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
    case MAC: // Write default layer to EEPROM
        if (record->event.pressed) {
            set_single_persistent_default_layer(_MAC);
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

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_RED}
);


// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_mac_layer,
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(7, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _MAC));

    if (layer_state_cmp(state, _MAC)) {
        current_default_layer = _MAC;
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
    if (index == 0) { /* First encoder, Right side or EXT1*/
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
    if (index == 2) { /* Third encoder, EXT2 */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    if (index == 3) { /* Fourth encoder, EXT3 */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
}


//------------------------------------------------------------------------------

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _MAC:
            oled_write_P(PSTR("Mac\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif

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
