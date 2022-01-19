/*   Copyright 2021 Jonavin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "jonavin.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65_ansi_blocker(
        KC_GESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,
      TT(_LOWER), KC_A,     KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDN,
  KC_LSFTCAPSWIN, KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,           KC_UP,     KC_END,
        KC_LCTL,  KC_LGUI,  KC_LALT,                             KC_SPC,                    MO(1),   KC_RCTL,            KC_LEFT, KC_DOWN,   KC_RIGHT
    ),
    [_FN1] = LAYOUT_65_ansi_blocker(
        KC_GESC,  KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_DEL,    KC_CALC,
        _______,  RGB_TOG,  RGB_MOD, RGB_HUI,  RGB_HUD, RGB_SAI, RGB_SAD, KC_PSCR, KC_SLCK, KC_PAUS, _______,  _______,  _______, RESET,     KC_HOME,
        KC_CAPS,  RGB_SPI,  RGB_SPD, RGB_VAD,  RGB_VAI, _______, _______, _______, _______, _______, _______,  _______,           EEP_RST,   KC_END,
        KC_LSFT,  RGB_NITE, _______, _______,  _______, _______, KC_NLCK, _______, RGB_TOD, RGB_TOI, KC_MPLY,  _______,           KC_VOLU,   KC_MUTE,
        _______,  KC_WINLCK, _______,                   _______,                            _______, _______,            KC_MPRV, KC_VOLD,   KC_MNXT
    ),
    [_LOWER] = LAYOUT_65_ansi_blocker(
        KC_TILD,  _______,  _______, _______,  _______,  _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS,  KC_PPLS, _______,   _______,
        _______,  KC_HOME,  KC_UP,   KC_END,   KC_PGUP,  _______, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______,  _______, _______,   KC_HOME,
        _______,  KC_LEFT,  KC_DOWN, KC_RGHT,  KC_PGDN,  _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST,           KC_PENT,   KC_END,
        _______,  KC_NO,    KC_DEL,  KC_INS,   KC_NO,    KC_NO,   KC_NO,   KC_P0,   KC_00,   KC_PDOT, KC_PSLS, _______,           _______,   _______,
        _______,  _______,  _______,                              KC_BSPC,                   _______, _______,           _______, _______,   _______
    ),
    [_RAISE] = LAYOUT_65_ansi_blocker(
        _______,  _______,  _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______,   _______,
        _______,  _______,  _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______,   _______,
        _______,  _______,  _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______,           _______,   _______,
        _______,  _______,  _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______,           _______,   _______,
        _______,  _______,  _______,                              KC_SPC,                    _______, _______,           _______, _______,   _______
    ),
};

#ifdef RGB_MATRIX_ENABLE
    // Capslock, Scroll lock and Numlock indicator
    void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_OFF);
        if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
            rgb_matrix_set_color(LED_I, RGB_GREEN);
        }

        #ifdef INVERT_NUMLOCK_INDICATOR
            if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {   // on if NUM lock is OFF
                rgb_matrix_set_color(LED_B, RGB_GREEN);
                rgb_matrix_set_color(LED_N, RGB_GREEN);
                rgb_matrix_set_color(LED_M, RGB_GREEN);
            }
        #else
            if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {   // Normal, on if NUM lock is ON
                rgb_matrix_set_color(LED_B, RGB_GREEN);
                rgb_matrix_set_color(LED_N, RGB_GREEN);
                rgb_matrix_set_color(LED_M, RGB_GREEN);
            }
        #endif // INVERT_NUMLOCK_INDICATOR

        if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            rgb_matrix_set_color(LED_CAPS, RGB_RED);
            rgb_matrix_set_color(LED_Q, RGB_RED);
            rgb_matrix_set_color(LED_A, RGB_RED);
        }
        if (keymap_config.no_gui) {
            rgb_matrix_set_color(LED_LCTL, RGB_RED);  //light up Win key when disabled
            rgb_matrix_set_color(LED_LWIN, RGB_RED);  //light up Win key when disabled
            rgb_matrix_set_color(LED_LALT, RGB_RED);  //light up Win key when disabled
        }
        switch(get_highest_layer(layer_state)){  // special handling per layer
        case _FN1:  // on Fn layer select what the encoder does when pressed
            rgb_matrix_set_color(LED_FN, RGB_GOLD);
            rgb_matrix_set_color(LED_RCTL, RGB_GOLD);

            #ifdef IDLE_TIMEOUT_ENABLE
                // Add RGB Timeout Indicator -- shows 0 to 139 using num row and qwerty row
                uint16_t timeout_threshold = get_timeout_threshold();
                if (timeout_threshold <= 10) rgb_matrix_set_color(LED_LIST_NUMROW[timeout_threshold], RGB_GOLD);
                else if (timeout_threshold < 140) {
                    rgb_matrix_set_color(LED_LIST_NUMROW[(timeout_threshold % 10)], RGB_GOLD);
                    rgb_matrix_set_color(LED_LIST_QWERTYROW[(timeout_threshold / 10)], RGB_GOLD);
                } else { // >= 140 minutes, just show these 3 lights
                    rgb_matrix_set_color(LED_LIST_NUMROW[10], RGB_GOLD);
                    rgb_matrix_set_color(LED_LIST_NUMROW[11], RGB_GOLD);
                    rgb_matrix_set_color(LED_LIST_NUMROW[12], RGB_GOLD);
                }
            #endif // IDLE_TIMEOUT_ENABLE

            break;
        case _LOWER:
            for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_NUMPAD); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_BLUE);
            }
            for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_WASD); i++) {
                rgb_matrix_set_color(LED_LIST_WASD[i], RGB_BLUE);
            }
            break;
        case _RAISE:
            rgb_matrix_set_color(LED_SPC, RGB_GREEN);
            break;
        default:
            break;
        }
    }

    void suspend_power_down_user(void) {
        rgb_matrix_set_suspend_state(true);
    }

    void suspend_wakeup_init_user(void) {
        rgb_matrix_set_suspend_state(false);
    }
#endif


void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        activate_rgb_nightmode(false);  // Set to true if you want to startup in nightmode, otherwise use Fn + Z to toggle
    #endif
}
