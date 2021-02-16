/* Copyright 2021 Takeshi Nishio
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
enum layer_number {
    _MAC = 0,
    _WIN,
    _LOWER,
    _RAISE,
    _ADJUST,
    _CAPS,          // This is not a "REAL" layer. Define here to use for RGB light layer.
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MAC = SAFE_RANGE,
    WIN,
    LOWER,
    RAISE,
    M_PSCR,
    M_VOLD,
    M_VOLU,
    ALT_EN,
    ALT_JA,
    GUI_EN,
    GUI_JA,
};

// Key Macro
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define S_DOT   RSFT_T(KC_DOT)
#define C_SLS   RCTL_T(KC_SLSH)
#define C_ESC   LCTL_T(KC_ESC)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define ALT_EN  LALT_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define GUI_JA  LGUI_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT_all(
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_BSLS,KC_PSLS,KC_PAST,KC_PMNS,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  KC_MINS,KC_EQL,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_P7,  KC_P8,  KC_P9,  KC_PPLS,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,       KC_BSPC,
        C_ESC,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,    KC_ENT,
        KC_LSFT,XXXXXXX,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_P1,  KC_P2,  KC_P3,  KC_PENT,KC_N,   KC_M,   KC_COMM,S_DOT,  C_SLS,  KC_UP,
        XXXXXXX,XXXXXXX,ALT_JA, XXXXXXX,GUI_EN, SP_LOW, XXXXXXX,KC_P0,  XXXXXXX,KC_PDOT,SP_RAI, XXXXXXX,KC_RGUI,KC_ROPT,KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [_WIN] = LAYOUT_all(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_APP,
        _______,_______,GUI_JA, _______,ALT_EN, _______,_______,_______,_______,_______,_______,_______,KC_RALT,_______,_______,_______,_______
    ),
    [_LOWER] = LAYOUT_all(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        KC_GRV,     KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_PSLS,KC_PSLS,KC_PAST,_______,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,    KC_DEL,
        _______,    M_PSCR, KC_SLCK,KC_PAUS,_______,_______,_______,_______,_______,_______,KC_GRV, KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,    KC_BSLS,
        _______,_______,KC_MUTE,M_VOLD, M_VOLU,_______,_______,_______,_______,_______,_______,KC_TILD,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END
    ),
    [_RAISE] = LAYOUT_all(
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,_______,_______,_______,_______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,   KC_F11, KC_F12,
        KC_ESC,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   _______,_______,_______,_______,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,       KC_DEL,
        _______,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SCLN,    KC_QUOT,
        _______,_______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,_______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_COLN,KC_DQUO,
        _______,_______,KC_F11, _______,KC_F12,_______,_______,_______,_______,_______,_______,_______,_______,KC_ESC,  _______,_______,_______
    ),
    [_ADJUST] = LAYOUT_all(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    MAC,    WIN,    _______,RESET,  _______,_______,_______,_______,_______,RGB_HUI,RGB_SAI,RGB_VAI,_______,RGB_RMOD,   _______,
        _______,    AU_TOG, CK_TOGG,MU_TOG, MU_MOD, _______,_______,_______,_______,_______,RGB_HUD,RGB_SAD,RGB_VAD,RGB_TOG,RGB_MOD,    _______,
        KC_CAPS,_______,CK_RST, CK_DOWN,CK_UP,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC:
            if (record->event.pressed) {
                // Change default layer --> Write to EEPROM
                set_single_persistent_default_layer(_MAC);
            }
            return false;
            break;
        case WIN:
            if (record->event.pressed) {
                // Change default layer --> Write to EEPROM
                set_single_persistent_default_layer(_WIN);
            }
            return false;
            break;
        case M_PSCR: // provide Mac's advanced screen capture
            if (record->event.pressed) {
                switch(biton32(default_layer_state)) {
                case _WIN:
                    tap_code(KC_PSCR);
                    break;
                default:
                    tap_code16(LSFT(LGUI(KC_5)));
                    break;
                }
            }
            return false;
            break;
        case M_VOLD:
            if (record->event.pressed) {
                switch(biton32(default_layer_state)) {
                case _WIN:
                    tap_code(KC_VOLD);
                    break;
                default:
                    tap_code16(LSFT(LOPT(KC_VOLD)));
                    break;
                }
            }
            return false;
            break;
        case M_VOLU:
            if (record->event.pressed) {
                switch(biton32(default_layer_state)) {
                case _WIN:
                    tap_code(KC_VOLU);
                    break;
                default:
                    tap_code16(LSFT(LOPT(KC_VOLU)));
                    break;
                }
            }
            return false;
            break;
        default:
            break;
    }
    return true;
}


/* ------------------------------------------------------------------------------
   RGB Light settings
------------------------------------------------------------------------------ */
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define INDICATOR_INDEX 0        // where to start indicator
#define INDICATOR_COUNT 2         // how many leds for indicator
#define INDICATOR_CHANGE_COUNT 1  // how meny leds to change color for temporally layer
#define DIMMER_LEVEL 230          // brightness dimmer

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_WHITE - DIMMER_LEVEL}
);
const rgblight_segment_t PROGMEM my_win_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_BLUE - DIMMER_LEVEL}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_GREEN - DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_CYAN - DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_RED - DIMMER_LEVEL}
);

// for Lock indicator
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX + 1 , INDICATOR_CHANGE_COUNT, HSV_MAGENTA - DIMMER_LEVEL}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_mac_layer,
    my_win_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer,
    my_caps_layer
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    rgblight_set_layer_state(_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(_ADJUST, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_MAC, layer_state_cmp(state, _MAC));
    rgblight_set_layer_state(_WIN, layer_state_cmp(state, _WIN));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(_CAPS, led_state.caps_lock);
    return true;
}
#endif


/* ------------------------------------------------------------------------------
   Rotary Encoder
------------------------------------------------------------------------------ */
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* 1st encoder, Left side */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* 2nd encoder, Right side */
        switch(biton32(default_layer_state)) {
            default:
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
                break;
        }
    } else if (index == 2) { /* 3rd encoder, Right side */
        switch(biton32(default_layer_state)) {
            default:
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
        }
    } else if (index == 3) { /* 4th encoder, Right side */
            default:
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                break;
        }
    } else if (index == 4) { /* 5th encoder, Right side */
            default:
                if (clockwise) {
                    rgblight_step();
                    // tap_code(KC_MS_WH_UP);
                } else {
                    rgblight_step_reverse();
                    // tap_code(KC_MS_WH_DOWN);
                }
                break;
        }
    }
}
#endif

void keyboard_post_init_user(void) {
    // Debugging
    // debug_enable=true;

    #ifdef RGBLIGHT_LAYERS
    // RGB Lighting Layers: Enable LED layers
    rgblight_layers = my_rgb_layers;
    #endif
}
