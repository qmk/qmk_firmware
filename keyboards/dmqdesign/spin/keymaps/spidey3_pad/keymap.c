/* Copyright 2020 Joshua Moses Diamond
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

#include "version.h"
#include <stdlib.h>

#define RGB_LAYER_ACK_DURATION 500

enum layers { _MACRO, _NUMPAD, _RGB, _FN };

enum layer_base {
    LAYER_BASE     = _MACRO,
    LAYER_BASE_END = _FN + 1,
};

enum custom_keycodes {
    HELLO = SAFE_RANGE,
    CH_CPNL,  // AL Control Panel
    CH_ASST,  // AL Context-aware Desktop Assistant
    CH_SUSP,  // Suspend
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MACRO] = LAYOUT(
        A(S(KC_N)),    HELLO,         CH_SUSP,       TO(_MACRO), 
        KC_MPRV,       KC_MPLY,       KC_MNXT,       TO(_NUMPAD), 
        C(A(KC_COMM)), KC_F5,         C(A(KC_DOT)),  TO(_RGB),
        MO(_FN),       CH_ASST,       CH_CPNL),

    [_NUMPAD] = LAYOUT(
        KC_KP_7,   KC_KP_8,   KC_KP_9,   KC_TRNS,
        KC_KP_4,   KC_KP_5,   KC_KP_6,   KC_TRNS,
        KC_KP_1,   KC_KP_2,   KC_KP_3,   KC_TRNS,
        KC_KP_0,   KC_PDOT,   KC_PENT),

    [_RGB] = LAYOUT(
        RGB_HUI,   RGB_SAI,   RGB_VAI,   KC_TRNS,
        RGB_HUD,   RGB_SAD,   RGB_VAD,   KC_TRNS,
        RGB_SPD,   RGB_SPI,   KC_NO,     KC_TRNS,
        RGB_RMOD,  RGB_TOG,   RGB_MOD),

    [_FN] = LAYOUT(
        KC_TRNS,   DEBUG,     RESET,     KC_TRNS,
        KC_NO,     KC_NO,     EEP_RST,   KC_TRNS,
        KC_NO,     KC_NO,     KC_NO,     KC_TRNS,
        KC_NO,     KC_NO,     KC_NO),
};
// clang-format on 

typedef enum layer_ack {
    ACK_NO = 0,
    ACK_YES,
    ACK_MEH,
} layer_ack_t;

#define LAYER_OFFSET 0
const rgblight_segment_t PROGMEM _macro_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_TEAL});
const rgblight_segment_t PROGMEM _numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_TEAL});
const rgblight_segment_t PROGMEM _rgb_layer[]    = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_TEAL});
const rgblight_segment_t PROGMEM _fn_layer[]     = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_PURPLE});

#define ACK_OFFSET 4
const rgblight_segment_t PROGMEM _no_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_RED});
const rgblight_segment_t PROGMEM _yes_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_GREEN});
const rgblight_segment_t PROGMEM _meh_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_YELLOW});

// clang-format on 
const rgblight_segment_t *const PROGMEM _rgb_layers[] = {
    [LAYER_OFFSET + 0] = _macro_layer,
    [LAYER_OFFSET + 1] = _numpad_layer,
    [LAYER_OFFSET + 2] = _rgb_layer,
    [LAYER_OFFSET + 3] = _fn_layer,
   
    [ACK_OFFSET + ACK_NO] = _no_layer,
    [ACK_OFFSET + ACK_YES] = _yes_layer,
    [ACK_OFFSET + ACK_MEH] = _meh_layer,

    [ACK_OFFSET + ACK_MEH + 1] = NULL
};
// clang-format off 

const uint8_t PROGMEM _n_rgb_layers = sizeof(_rgb_layers) / sizeof(_rgb_layers[0]) - 1;

void clear_rgb_layers(void) {
    dprint("clear_rgb_layers()\n");
    for (uint8_t i = 0; i < _n_rgb_layers; i++) {
        rgblight_set_layer_state(i, false);
    }
}

void do_rgb_layers(layer_state_t state, uint8_t start, uint8_t end) {
    dprintf("start=%u, end=%u, LAYER_OFFSET=%u\n", start, end, LAYER_OFFSET);
    for (uint8_t i = start; i < end; i++) {
        bool    is_on = layer_state_cmp(state, i);
        uint8_t rl    = LAYER_OFFSET + i;
        dprintf("layer[%u]=%u, rl=%u\n", i, is_on, rl);
        rgblight_set_layer_state(rl, is_on);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    do_rgb_layers(state, LAYER_BASE, LAYER_BASE_END);
    return state;
}

void rgb_layer_ack(layer_ack_t n) {
    uint8_t layer = ACK_OFFSET + n;
    dprintf("rgb_layer_ack(%u) ==> %u\n", n, layer);
    rgblight_blink_layer(layer, RGB_LAYER_ACK_DURATION);
}

void rgb_layer_ack_yn(bool yn) { rgb_layer_ack(yn ? ACK_YES : ACK_NO); }

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
    do_rgb_layers(layer_state, LAYER_BASE, LAYER_BASE_END);
}

void shutdown_user() {
    clear_rgb_layers();
    rgblight_enable();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(HSV_RED);
}

void spidey_glow(void) {
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
    rgblight_sethsv(255, 230, 128);
}

void eeconfig_init_user(void) { spidey_glow(); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // Re-implement this here, but fix the persistence!
            case DEBUG:
                if (!debug_enable) {
                    debug_enable = 1;
                } else if (!debug_keyboard) {
                    debug_keyboard = 1;
                } else if (!debug_matrix) {
                    debug_matrix = 1;
                } else {
                    debug_enable   = 0;
                    debug_keyboard = 0;
                    debug_matrix   = 0;
                }
                uprintf("DEBUG: enable=%u, keyboard=%u, matrix=%u\n", debug_enable, debug_keyboard, debug_matrix);
                uprintln(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
                eeconfig_update_debug(debug_config.raw);
                return false;

                // clang-format off
            case CH_CPNL: host_consumer_send(AL_CONTROL_PANEL); return false;
            case CH_ASST: host_consumer_send(AL_ASSISTANT); return false;
            case CH_SUSP: tap_code16(LGUI(LSFT(KC_L))); return true;
            case HELLO:   SEND_STRING("Hello, world!"); return true;
                // clang-format on
        }
    } else {
        switch (keycode) {
            case CH_CPNL:
            case CH_ASST:
                host_consumer_send(0);
                return false;
        }
    }

    return true;
};


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Acks follow...
        case DEBUG:
            rgb_layer_ack_yn(debug_enable);
            break;
        case RGB_TOG:
            rgb_layer_ack_yn(rgblight_is_enabled());
            break;
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _RGB:
            if (index == 0) {
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
            } else if (index == 1) {
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
            } else if (index == 2) {
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
            }
            break;

        default:
            if (index == 0) {
                tap_code16(C(S(clockwise ? KC_EQL : KC_MINS)));
            } else if (index == 1) {
                tap_code16(C(clockwise ? KC_EQL : KC_MINS));
            } else if (index == 2) {
                tap_code(clockwise ? KC_VOLU : KC_VOLD);
            }
            break;
    }
}
