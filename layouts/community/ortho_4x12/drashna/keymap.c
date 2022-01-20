/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"

#ifdef BACKLIGHT_ENABLE
enum planck_keycodes {
    BACKLIT = NEW_SAFE_RANGE,
    TH_LVL,
};

#else
#    define BACKLIT OSM(MOD_LSFT)
enum planck_keycodes {
    TH_LVL = NEW_SAFE_RANGE,
};
#endif

#ifdef KEYBOARD_planck_ez
#    define PLNK_1 BK_LWER
#    define PLNK_2 SP_LWER
#    define PLNK_3 KC_NO
#    define PLNK_4 ET_RAIS
#else
#    define PLNK_1 SP_LWER
#    define PLNK_2 BK_LWER
#    define PLNK_3 DL_RAIS
#    define PLNK_4 ET_RAIS
#endif

/*
 * The `LAYOUT_ortho_4x12_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */
// clang-format off
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_4x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ortho_4x12_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,     K06,     K07,     K08,     K09,     K0A,     KC_DEL, \
    LALT_T(KC_TAB), K11, K12, K13,      K14,     K15,     K16,     K17,     K18,     K19,     K1A, RALT_T(K1B), \
    KC_MLSF, CTL_T(K21), K22, K23,      K24,     K25,     K26,     K27,     K28,     K29, RCTL_T(K2A), KC_ENT,  \
    BACKLIT, OS_LCTL, OS_LALT, OS_LGUI, PLNK_1,  PLNK_2,  PLNK_3,  PLNK_4,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_ortho_4x12_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_DEFAULT_LAYER_2] = LAYOUT_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),
    [_DEFAULT_LAYER_3] = LAYOUT_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DEFAULT_LAYER_4] = LAYOUT_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

  [_LOWER] = LAYOUT_ortho_4x12_wrapper(
    KC_TILD, _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_BSPC,
    KC_DEL,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PIPE,
    _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_ortho_4x12_wrapper(
    KC_GRV,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_BSPC,
    KC_DEL,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _________________RAISE_R3__________________
  ),

  [_ADJUST] = LAYOUT_ortho_4x12_wrapper(
    KC_MAKE, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, KC_RST,
    VRSN,    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, EEP_RST,
    TH_LVL,  _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, RGB_IDL,
    KEYLOCK, _______, _______, _______, _______, KC_NUKE, _______, _______, _______, _______, _______, TG_MODS
  )

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DEFAULT_LAYER_1] = { { KC_DOWN, KC_UP   } },
    [_DEFAULT_LAYER_2] = { { _______, _______ } },
    [_DEFAULT_LAYER_3] = { { _______, _______ } },
    [_DEFAULT_LAYER_4] = { { _______, _______ } },
    [_GAMEPAD]         = { { _______, _______ } },
    [_DIABLO]          = { { _______, _______ } },
    [_MOUSE]           = { { KC_WH_D, KC_WH_U } },
    [_MEDIA]           = { { _______, _______ } },
    [_RAISE]           = { { KC_VOLD, KC_VOLU } },
    [_LOWER]           = { { RGB_MOD, RGB_RMOD} },
    [_ADJUST]          = { { CK_DOWN, CK_UP   } },
};
#endif
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef BACKLIGHT_ENABLE
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#    ifdef BACKLIGHT_ENABLE
                backlight_step();
#    endif
            } else {
                unregister_code(KC_RSFT);
            }
            break;
#endif
#ifdef KEYBOARD_planck_ez
        case TH_LVL:
            if (record->event.pressed) {
                keyboard_config.led_level++;
                if (keyboard_config.led_level > 4) {
                    keyboard_config.led_level = 0;
                }
                planck_ez_right_led_level((uint8_t)keyboard_config.led_level * 255 / 4);
                planck_ez_left_led_level((uint8_t)keyboard_config.led_level * 255 / 4);
                eeconfig_update_kb(keyboard_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
#endif
    }
    return true;
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
        case BK_LWER:
        case SP_LWER:
        case DL_RAIS:
        case ET_RAIS:
            return false;
        default:
            return true;
    }
}

#ifdef RGB_MATRIX_ENABLE

#    ifdef KEYBOARD_planck_rev6
// clang-format off
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { NO_LED,   6,    NO_LED, NO_LED,   5,    NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   0    },
        { NO_LED,   7,    NO_LED, NO_LED,   2,    NO_LED },
        { NO_LED,   4,    NO_LED, NO_LED,   3,    NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED,   1,    NO_LED, NO_LED,   8,    NO_LED }
    }, {
        // LED Index to Physical Position
        {112, 39}, {148, 60}, {206, 53}, {206, 3}, {150, 3}, {74, 3}, {18, 3}, {18, 54}, {77, 60}
    }, {
        // LED Index to Flag
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
    }
};
// clange-format on
#    endif


bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    uint8_t this_mod = get_mods();
    uint8_t this_led = host_keyboard_leds();
    uint8_t this_osm = get_oneshot_mods();
#    ifdef KEYBOARD_planck_ez
#        define THUMB_LED 41
#    else
#        define THUMB_LED 42
#    endif
#    define RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(...) RGB_MATRIX_INDICATOR_SET_COLOR(__VA_ARGS__)

    switch (get_highest_layer(default_layer_state)) {
        case _DEFAULT_LAYER_1:
            RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_1_RGB);
            break;
        case _DEFAULT_LAYER_2:
            RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_2_RGB);
            break;
        case _DEFAULT_LAYER_3:
            RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_3_RGB);
            break;
        case _DEFAULT_LAYER_4:
            RGB_MATRIX_INDICATOR_SET_COLOR_wrapper(THUMB_LED, DEFAULT_LAYER_4_RGB);
            break;
    }

    if ((this_mod | this_osm) & MOD_MASK_SHIFT || this_led & (1 << USB_LED_CAPS_LOCK)) {
        if (!layer_state_cmp(layer_state, _ADJUST)) {
            RGB_MATRIX_INDICATOR_SET_COLOR(24, 0x00, 0xFF, 0x00);
        }
        RGB_MATRIX_INDICATOR_SET_COLOR(36, 0x00, 0xFF, 0x00);
    }
    if ((this_mod | this_osm) & MOD_MASK_CTRL) {
        RGB_MATRIX_INDICATOR_SET_COLOR(25, 0xFF, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(34, 0xFF, 0x00, 0x00);
        RGB_MATRIX_INDICATOR_SET_COLOR(37, 0xFF, 0x00, 0x00);
    }
    if ((this_mod | this_osm) & MOD_MASK_GUI) {
        RGB_MATRIX_INDICATOR_SET_COLOR(39, 0xFF, 0xD9, 0x00);
    }
    if ((this_mod | this_osm) & MOD_MASK_ALT) {
        RGB_MATRIX_INDICATOR_SET_COLOR(38, 0x00, 0x00, 0xFF);
    }

    return true;
}

void matrix_init_keymap(void) {
#    ifdef KEYBOARD_planck_light
    writePinLow(D6);
#    endif
    // rgblight_mode(RGB_MATRIX_MULTISPLASH);
}
#else  // RGB_MATRIX_INIT

void matrix_init_keymap(void) {
#    if !defined(CONVERT_TO_PROTON_C) && !defined(KEYBOARD_planck)
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#    endif
}
#endif  // RGB_MATRIX_INIT

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            clockwise ? tap_code(KC_VOLD) : tap_code(KC_VOLU);
            break;
        case _LOWER:
#    ifdef RGB_MATRIX_ENABLE
            clockwise ? rgb_matrix_step() : rgb_matrix_step_reverse();
#    else
            clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
#    endif
            break;
        case _ADJUST:
#    ifdef AUDIO_CLICKY
            clockwise ? clicky_freq_up() : clicky_freq_down();
#    endif
            break;
        default:
            clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
    }
#    ifdef AUDIO_CLICKY
    clicky_play();
#    endif
    return true;
}
#endif  // ENCODER_ENABLE

#ifdef KEYBOARD_planck_rev6
bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                audio_on();
            } else {
                audio_off();
            }
            break;
        case 1:
            if (active) {
                clicky_on();
            } else {
                clicky_off();
            }
            break;
        case 2:
            keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = active;
            break;
        case 3:
            userspace_config.nuke_switch = active;
            break;
    }
    return true;
}
#endif  // KEYBOARD_planck_rev6

#ifdef KEYBOARD_planck_ez
layer_state_t layer_state_set_keymap(layer_state_t state) {
    planck_ez_left_led_off();
    planck_ez_right_led_off();
    switch (get_highest_layer(state)) {
        case _LOWER:
            planck_ez_left_led_on();
            break;
        case _RAISE:
            planck_ez_right_led_on();
            break;
        case _ADJUST:
            planck_ez_right_led_on();
            planck_ez_left_led_on();
            break;
        default:
            break;
    }
    return state;
}
#endif
