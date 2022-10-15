/* Copyright 2020 sotoba
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
enum layer_names {
    _BASE,
    _UNRULY,
    _FUNCTION
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    DOUBLE_ZERO = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                           KC_ESCAPE,   KC_LSFT,      KC_TAB,          KC_BSPC,
                           KC_NUM,      KC_KP_SLASH,  KC_KP_ASTERISK,  KC_EQUAL,
                           KC_KP_7,     KC_KP_8,      KC_KP_9,         KC_KP_MINUS,
      MO(_FUNCTION),       KC_KP_4,     KC_KP_5,      KC_KP_6,         KC_KP_PLUS,
      RGB_TOG,             KC_KP_1,     KC_KP_2,      KC_KP_3,         KC_KP_ENTER,
      TG(_UNRULY),         KC_KP_0,     DOUBLE_ZERO,  KC_KP_DOT
    ),
    /* Lightning */
    [_UNRULY] = LAYOUT(
                           KC_ESCAPE,   KC_LSFT,      KC_TAB,          KC_BSPC,
                           KC_NUM,      KC_KP_SLASH,  KC_KP_ASTERISK,  KC_EQUAL,
                           KC_KP_7,     KC_KP_8,      KC_KP_9,         KC_KP_MINUS,
      KC_TRNS,             KC_KP_4,     KC_KP_5,      KC_KP_6,         KC_KP_PLUS,
      KC_TRNS,             KC_KP_1,     KC_KP_2,      KC_KP_3,         KC_KP_ENTER,
      KC_TRNS,             KC_KP_0,     DOUBLE_ZERO,  KC_KP_DOT
    ),
    /* Function */
    [_FUNCTION] = LAYOUT(
                           QK_BOOT,       KC_NO,        KC_NO,           KC_NO,
                           KC_NO,       KC_NO,        KC_NO,           KC_NO,
                           KC_NO,       KC_NO,        KC_NO,           KC_NO,
      KC_TRNS,             RGB_RMOD,    RGB_MOD,      KC_NO,           KC_NO,
      KC_TRNS,             RGB_HUI,     RGB_SAI,      RGB_VAI,         KC_NO,
      KC_TRNS,             RGB_HUD,     RGB_SAD,      RGB_VAD
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DOUBLE_ZERO:
            if (record->event.pressed) {
                // when keycode DOUBLE_ZERO is pressed
                SEND_STRING("00");
            }
            break;
    }
    return true;
}

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {26, 7, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM unruly_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_OFF},
    {4, 2, HSV_WHITE},
    {6, 2, HSV_PURPLE},
    {8, 2, HSV_RED},
    {10, 2, HSV_BLUE},
    {12, 2, HSV_YELLOW},
    {14, 2, HSV_GREEN},
    {16, 3, HSV_ORANGE},
    {19, 1, HSV_OFF},
    {20, 3, HSV_PINK},
    {23, 10, HSV_GREEN}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    num_layer,
    unruly_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _UNRULY));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.num_lock);
    return true;
}

#endif
