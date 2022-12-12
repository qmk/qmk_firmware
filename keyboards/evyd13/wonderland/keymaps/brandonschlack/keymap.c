/* Copyright 2019 Brandon Schlack
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
#include "brandonschlack.h"

// LEDs
#define TOP_LED    B1
#define MIDDLE_LED B2
#define BOTTOM_LED B3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( \
    KC_HOME, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  \
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, \
    KC_PGDN, HY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  \
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, PLY_FN1, \
             KC_LOPT,          KC_LCMD,     SPC_RAI,       KC_LCTL,          SPC_RAI,           KC_RCMD,                   KC_ROPT \
),
[_FN1] = LAYOUT( \
    KC_MUTE, QM_MAKE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  MC_LHPD, MC_SLPD, \
    KC_VOLU, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_DEL,  \
    KC_VOLD, RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, KC_MPRV, KC_MNXT, KC_PGDN, KC_UP,            KC_MPLY, \
             _______, RGB_LYR, RGB_THM, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, RGT_SFT, _______, \
             _______,          _______,     _______,      _______,          _______,          _______,                   _______ \

),
[_FN2] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
             _______,          _______,     _______,      _______,          _______,          _______,                   _______ \

),
[_ADJUST] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
             _______,          _______,     _______,      _______,          _______,          _______,                   _______ \

)
/*
[_BLANK] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
             _______,          _______,     _______,      _______,          _______,          _______,                   _______ \

)
*/
};

#ifdef STOPLIGHT_LED
bool is_led_stoplight_active = false;
uint8_t led_stoplight_index = 0;
uint16_t led_stoplight_timer = 0;
void matrix_scan_led_stoplight(void);

void led_stoplight_start(void) {
    writePinHigh(TOP_LED);
    writePinHigh(MIDDLE_LED);
    writePinHigh(BOTTOM_LED);

    is_led_stoplight_active = true;
    led_stoplight_timer = timer_read();
};

void led_stoplight_set(pin_t pin) {
    writePinLow(pin);
};

void led_stoplight_end(void) {
    // Reset timer and status variables
    led_stoplight_index = 0;
    is_led_stoplight_active = false;
    led_stoplight_timer = 0;
    led_update_kb(host_keyboard_led_state());
};

void matrix_scan_led_stoplight(void) {
    if (is_led_stoplight_active) {
        if (timer_elapsed(led_stoplight_timer) > (1000 * (led_stoplight_index + 1))) {
            switch (led_stoplight_index){
                case 0:
                    led_stoplight_set(TOP_LED);
                    led_stoplight_index++;
                    break;
                case 1:
                    led_stoplight_set(MIDDLE_LED);
                    led_stoplight_index++;
                    break;
                case 2:
                    led_stoplight_set(BOTTOM_LED);
                    led_stoplight_index++;
                    break;
                default:
                    led_stoplight_index = 0;
                    is_led_stoplight_active = false;
                    led_stoplight_timer = 0;
                    led_update_kb(host_keyboard_led_state());
                    break;
            }
        }
    }
};
#endif

void keyboard_post_init_keymap(void) {
#ifdef STOPLIGHT_LED
    led_stoplight_start();
#endif
};

void matrix_scan_keymap(void) {
#ifdef STOPLIGHT_LED
    matrix_scan_led_stoplight();
#endif
};

#ifdef USE_LEDS_FOR_LAYERS
// example of how to use LEDs as layer indicators
static uint8_t top = 0;
static uint8_t middle = 0;

layer_state_t layer_state_set_keymap(layer_state_t state) {
    top = middle = 0;
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    switch (get_highest_layer(state)) {
    case _FN1:
        top = 1;
        break;
    case _FN2:
        middle = 1;
        break;
    case _ADJUST:
        top = 1;
        middle = 1;
        break;
    default: //  for any other layers, or the default layer
        break;
    }
  return state;
}

// override kb level function
bool led_update_user(led_t usb_led) {
    if (!is_led_stoplight_active) {
        writePin(TOP_LED, !top);
        writePin(MIDDLE_LED, !middle);
        writePin(BOTTOM_LED, !usb_led.caps_lock); // still use bottom for Caps Lock
    };
    return false; // we are using LEDs for something else override kb
}
#endif
