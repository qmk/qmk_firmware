/* Copyright 2021 Jonavin Eng @Jonavin
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
#include "jonavin.h"

#ifdef RGBLIGHT_ENABLE
    // Custom RGB Colours
    #define RGB_GODSPEED 0x00, 0xE4, 0xFF // colour for matching keycaps
#endif // RGBLIGHT_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65(
      QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_INS,
      KC_PSCR, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,
      TT(_LOWER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
      KC_LSFTCAPS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LALT, LT(_FN1, KC_SPC), KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    [_FN1] = LAYOUT_65(
      KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_CALC, KC_NO,
      RGB_TOG, RGB_MOD, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR, KC_SCRL, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
      KC_CAPS, KC_NO, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_HOME,
      KC_TRNS, KC_NO, RGB_HUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, RGB_MOD, KC_END,
      KC_TRNS, KC_WINLCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, RGB_SPD, RGB_RMOD, RGB_SPI),
    [_LOWER] = LAYOUT_65(
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_P0, KC_PMNS, KC_PPLS,   KC_PSLS, KC_PEQL, KC_TRNS,
      KC_TAB, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_NO, KC_NO, KC_NO,   KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO,   KC_TAB,  KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST, KC_PENT, KC_HOME,
      KC_TRNS, KC_NO,   KC_DEL,  KC_INS,  KC_NO,   KC_NO,   KC_NUM,  KC_P0,   KC_00,   KC_PDOT, KC_PSLS, KC_TRNS, RCTL(KC_PGUP), KC_END,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)),
    [_RAISE] = LAYOUT_65(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    // process_record_user() moved to userspace
    return true;
};

#ifdef ENCODER_ENABLE       // Encoder Functionality
    bool encoder_update_user(uint8_t index, bool clockwise) {
        uint8_t mods_state = get_mods();
        switch (index) {
        case 0:  // first encoder (Left Macro set)
            encoder_action_navpage(clockwise);
            break;

        default: // other encoder (Top right)
            if (mods_state & MOD_BIT(KC_LSFT) ) { // If you are holding Left shift, change layers
                encoder_action_layerchange(clockwise);
            } else if (mods_state & MOD_BIT(KC_RSFT) ) { // If you are holding Right shift, Page up
                unregister_mods(MOD_BIT(KC_RSFT));
                encoder_action_navpage(clockwise);
                register_mods(MOD_BIT(KC_RSFT));
            } else if (mods_state & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate next/prev word
                encoder_action_navword(clockwise);
            } else if (mods_state & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next/prev track
                encoder_action_mediatrack(clockwise);
            } else  {
                encoder_action_volume(clockwise);     // Otherwise it just changes volume
            }
            break;
        }
        return true;
    }
#endif

#ifdef RGBLIGHT_ENABLE

    enum custom_rgblight_layers
    {
        _rgbCAPS,
        _rgbNUMLOCK,
        _rgbWINLOCK,
        _rgbFN,
        _rgbNUMPAD,
    };

    // RGB map LEFT 1, 2, 3, 12, 13, 14, 15, 0  RIGHT 7, 6, 5, 4, 11, 10, 9, 8
    const rgblight_segment_t PROGMEM _rgb_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {14, 1, HSV_RED}       // Light 4 LEDs, starting with LED 6
    );
    const rgblight_segment_t PROGMEM _rgb_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {15, 1, HSV_BLUE}
    );    const rgblight_segment_t PROGMEM _rgb_winlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {13, 1, HSV_PURPLE}       // Light 4 LEDs, starting with LED 6
    );
    const rgblight_segment_t PROGMEM _rgb_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {9, 2, HSV_ORANGE},
        {12, 2, HSV_ORANGE}
    );
    // Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
    const rgblight_segment_t PROGMEM _rgb_numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {4, 3, HSV_PURPLE},
        {9, 3, HSV_PURPLE}
    );

    const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        _rgb_capslock_layer,
        _rgb_numlock_layer,
        _rgb_winlock_layer,
        _rgb_fn_layer,
        _rgb_numpad_layer
    );

    bool led_update_user(led_t led_state) {
        rgblight_set_layer_state(_rgbCAPS, led_state.caps_lock);

        #ifdef INVERT_NUMLOCK_INDICATOR
            rgblight_set_layer_state(_rgbNUMLOCK, !led_state.num_lock);   // inverse numlock indicator override
        #else
            rgblight_set_layer_state(_rgbNUMLOCK, led_state.num_lock);  // normal, light LED when numlock on
        #endif // INVERT_NUMLOCK_INDICATOR

        rgblight_set_layer_state(_rgbWINLOCK, keymap_config.no_gui);
        return true;
    }

    layer_state_t layer_state_set_user(layer_state_t state) {
        rgblight_set_layer_state(_rgbFN, layer_state_cmp(state, _FN1));
        rgblight_set_layer_state(_rgbNUMPAD, layer_state_cmp(state, _LOWER));
        return state;
    }
#endif // RGBLIGHT_ENABLE

void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
    #ifdef RGBLIGHT_ENABLE
        rgblight_mode(1); // single colour mode
        rgblight_setrgb(RGB_GODSPEED); // Default startup colour
        rgblight_layers = _rgb_layers;
    #endif
}
