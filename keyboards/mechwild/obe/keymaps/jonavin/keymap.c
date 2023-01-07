/* Copyright 2021 Kyle McCreery
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
    #define HSV_OBE_BOW 180, 100, 100 // colour for matching keycaps
#endif // RGBLIGHT_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_TSTOG,QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_PGDN, TT(_RAISE), KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFTCAPSWIN,KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, LT(_LOWER,KC_B), KC_N, KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_SFTUP,KC_RSFT,
             KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,  MO(_FN1),         KC_RAISESPC,      KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN1] = LAYOUT(
    KC_MUTE, KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_INS,
    KC_HOME, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PSCR, KC_SCRL, KC_PAUS, KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
    KC_END,  KC_CAPS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_TRNS,
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NUM,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PGUP, KC_TRNS,
             KC_TRNS,KC_WINLCK,KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,          KC_NO,   KC_NO,   KC_HOME, KC_PGDN, KC_END
    ),
    [_LOWER] = LAYOUT(
    EE_CLR,  KC_TILD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_VAD, RGB_VAI, KC_TRNS, KC_DEL,
    RGB_HUI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, EMO_TEARS, EMO_SAD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_TOG,
    RGB_HUD, KC_NO,   KC_NO,   EMO_SHRUG,KC_NO,  KC_NO,   KC_NO,   KC_NO,   EMO_JOY, KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_TRNS,
             KC_NO,   KC_NO,   KC_NO,   EMO_CONFUSE,KC_NO,KC_NO,KC_TRNS,EMO_NERVOUS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_MOD, KC_TRNS,
             KC_TRNS, KC_APP,  KC_TRNS,          KC_BSPC, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, RGB_SPD, RGB_RMOD,RGB_SPI
    ),
    [_RAISE] = LAYOUT(
    KC_NO,   KC_GRV,  KC_NO,  KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, KC_PSLS, KC_DEL,
    KC_VOLU, KC_NO,   KC_HOME,KC_UP,   KC_END,   KC_PGUP, KC_NO,   KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_NO,   KC_NO,   KC_NO,   KC_PEQL,
    KC_VOLD,TT(_RAISE),KC_LEFT,KC_DOWN,KC_RGHT,  KC_PGDN, KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST,          KC_PENT,
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_P0,   KC_00,   KC_NO,   KC_PDOT, KC_PSLS, CT_PGUP, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS,          KC_BSPC, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, CT_HOME, CT_PGDN, CT_END
    )
};

#ifdef RGBLIGHT_ENABLE

    enum custom_rgblight_layers
    {
        _rgbWINLOCK,   _rgbFN,
        _rgbLOWER,
        _rgbRAISE
    };

    // Optional RGB Light Mapping Zones {LED Posiiton, Number of LEDs, Colour}
    const rgblight_segment_t PROGMEM _rgb_winlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {1, 3, HSV_RED},
        {15, 3, HSV_RED}
    );
    const rgblight_segment_t PROGMEM _rgb_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {6, 6, HSV_PURPLE}
    );
    // Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
    const rgblight_segment_t PROGMEM _rgb_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {4, 10, HSV_YELLOW}
    );

    const rgblight_segment_t PROGMEM _rgb_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {3, 5, HSV_GREEN},
        {10, 5, HSV_GREEN}
    );

    const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        _rgb_winlock_layer,
        _rgb_fn_layer,
        _rgb_lower_layer,
        _rgb_raise_layer
    );

    bool led_update_user(led_t led_state) {
        rgblight_set_layer_state(_rgbWINLOCK, keymap_config.no_gui);
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
        #ifdef INVERT_NUMLOCK_INDICATOR
            writePin(LED_NUM_LOCK_PIN, !led_state.num_lock);   // inverse numlock indicator override
        #else
            writePin(LED_NUM_LOCK_PIN, led_state.num_lock);   // normal, light LED when numlock on
        #endif // INVERT_NUMLOCK_INDICATOR
        return false;
    }

    layer_state_t layer_state_set_user(layer_state_t state) {
        rgblight_set_layer_state(_rgbFN, layer_state_cmp(state, _FN1));
        rgblight_set_layer_state(_rgbLOWER, layer_state_cmp(state, _LOWER));
        rgblight_set_layer_state(_rgbRAISE, layer_state_cmp(state, _RAISE));
        return state;
    }
#endif // RGBLIGHT_ENABLE

void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
    #ifdef RGBLIGHT_ENABLE
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv_noeeprom(HSV_OBE_BOW); // Default startup colour
        rgblight_layers = _rgb_layers;
    #endif
}

