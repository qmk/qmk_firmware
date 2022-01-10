/* Copyright 2021 Tybera
 * Copyright 2021 thewerther
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_GRV,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,      KC_DEL,
        KC_RALT,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,              KC_PGUP,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,          KC_PGDN,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       LT(1, KC_SPC),                       MO(2),     KC_RCTL,   KC_LEFT,   KC_DOWN,    KC_RGHT
    ),
    [1] = LAYOUT_65_ansi_blocker(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          _______,
        _______,     _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,
        _______,        _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,  _______, _______, _______,            _______,
        _______,           _______,  _______,  _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,    _______,
        _______,   _______,   _______,                      _______,                              _______,   _______,   _______,   _______,    _______
    ),
    [2] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,     RGB_TOG, _______,  RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_MPLY, KC_MPRV, KC_MNXT, _______,     _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_HOME,
        _______,           RESET,  RGB_SPI,  RGB_SPD, _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,  _______,  _______,  _______,      KC_END,
        _______,   _______,   _______,                      _______,                              _______,   _______,   _______,   _______,    _______
    ),
};

void set_layer_rgb_color(uint8_t led_min, uint8_t led_max, uint8_t layer);
static bool shift_space_pressed = false;

void keyboard_post_init_user(void) {
#   if defined(COMMAND_ENABLE) || defined(CONSOLE_ENABLE)
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
#   endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status
    // of each key pressed.
#   if defined(CONSOLE_ENABLE)
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n",
            keycode,
            record->event.key.col,
            record->event.key.row,
            record->event.pressed);
#   endif
    switch (keycode) {
        case LT(1, KC_SPC):
            if (record->event.pressed) { // key pressed
                // disable the hold action of LT(1, KC_SPC) when pressing LSFT
                // TODO: There is probably a better way of doing this
                if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    /* On LSHIFT down we set this to false again to avoid
                     * getting space "stuck" and keep sending down events.
                     */
                    shift_space_pressed = true;
                    register_code(KC_SPC);
                    return false;
                } else {
                    return true;
                }
            } else { // key released
                if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    if (shift_space_pressed) {
                        unregister_code(KC_SPC);
                        return true;
                    }
                } else {
                    return true;
                }
            }
            return true;

        case KC_LSHIFT:
            if (!record->event.pressed) {
                if (shift_space_pressed) {
                    unregister_code(KC_SPC);
                    shift_space_pressed = false;
                }
            }
            return true;
        default:
            return true;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_SPC):
            // When pressing shift and space set tapping term to 0 in order to
            // be able to press space faster consecutively
            if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                return 0;
            } else {
                return TAPPING_TERM;
            }
        default:
            return TAPPING_TERM;
    }
}

void matrix_scan_user(void) {
#   if defined(RGB_MATRIX_ENABLE)
    /* Set the bottom leds of the PCB to the current color for all reactive
     * RGB Matrix effects.
     */
    int current_effect = rgb_matrix_get_mode();
    if (current_effect >= RGB_MATRIX_SOLID_REACTIVE_SIMPLE &&
        current_effect <= RGB_MATRIX_SOLID_MULTISPLASH) {
        // set all underglow leds to current color
        RGB current_color = hsv_to_rgb(rgb_matrix_get_hsv());
        for (int i = DRIVER_LED_TOTAL - DRIVER_LED_UNDERGLOW;
            i < DRIVER_LED_TOTAL; i++) {
            rgb_matrix_set_color(i,
                    current_color.r,
                    current_color.g,
                    current_color.b);
        }
    }
#   endif
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#   if defined(RGB_MATRIX_ENABLE)
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);
        set_layer_rgb_color(led_min, led_max, layer);
    }
#   endif
}

void set_layer_rgb_color(uint8_t led_min, uint8_t led_max, uint8_t layer) {
    // Set only the assigned keys of the current layer to a specific color.
#   if defined(RGB_MATRIX_ENABLE)
    RGB color = hsv_to_rgb((HSV){0, 0, rgb_matrix_config.hsv.v});
    if (layer == 2) {
        color = hsv_to_rgb(rgb_matrix_get_hsv());
    }
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min &&
                index <= led_max &&
                index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, color.r, color.g, color.b);
            }
        }
    }
#   endif
}

