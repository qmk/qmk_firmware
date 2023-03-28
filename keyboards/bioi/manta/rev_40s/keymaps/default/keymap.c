/* Copyright 2022 Basic I/O Instruments (Scott Wei)
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

#include "print.h"
#include "../../../../ble.h"
#include "quantum.h"

ble_led_stat ble_led;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    // 0: Base Layer
    [0] = LAYOUT(
        KC_ESC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_BSLS,  KC_BSPC,                                           \
        MT(MOD_LCTL, KC_TAB),  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,  KC_ENT,             KC_UP,                  \
        KC_LSFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,          KC_LEFT,  KC_NO,  KC_RIGHT,       \
        KC_LCTL,  KC_LGUI,  KC_LALT,        LT(1,KC_SPC),        LT(2,KC_SPC),        LT(3, KC_RALT),  KC_RCTL,             KC_DOWN                 ),

    // 1: Function Layer
    [1] = LAYOUT(
        KC_GRAVE,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  _______,  _______,                                             \
        KC_CAPS,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_MINS,  KC_EQL,  KC_LBRC,  KC_RBRC,  KC_QUOT,                   RGB_MOD,            \
        _______,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______,  _______,  _______,  _______,  _______,     _______,  RGB_TOG,  _______,  \
        _______,  _______,  _______,        _______,        _______,        _______,  _______,                                      RGB_RMOD            ),

    [2] = LAYOUT(
        KC_TILD,  KC_EXLM,  KC_AT,  KC_HASH,  KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,  KC_DEL,                                        \
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  _______,                          _______,            \
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,  \
        _______,  _______,  _______,            _______,            _______,            _______,  _______,                                              _______             ),

    [3] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                                    \
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                          _______,            \
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,  \
        _______,  _______,  _______,            _______,            _______,            _______,  _______,                                              _______             ),
    // clang-format on
};

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_WHITE});

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_MAGENTA});

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_capslock_layer, my_layer1_layer, my_layer2_layer, my_layer3_layer);

void led_set_user(uint8_t usb_led) {
    if (!ble_on) {
        rgblight_set_layer_state(0, IS_LED_ON(usb_led, USB_LED_CAPS_LOCK));
        if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
            ble_led.caplck = true;
        } else {
            ble_led.caplck = false;
        }
        if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
            rgblight_enable_noeeprom();
        }
        if (!IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) && layer_state_is(0)) {
            rgblight_reload_from_eeprom();
            if (!rgblight_is_enabled()) {
#ifdef RGB_UG_CONTROL_PIN
                writePinHigh(RGB_UG_CONTROL_PIN);
#endif
                rgblight_disable_noeeprom();
            } else {
#ifdef RGB_UG_CONTROL_PIN
                writePinLow(RGB_UG_CONTROL_PIN);
#endif
                rgblight_enable_noeeprom();
            }
        }
    }
}

void keyboard_pre_init_user(void) {}

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!layer_state_cmp(state, 0) && !rgblight_is_enabled()) {
        rgblight_enable_noeeprom();
#ifdef RGB_UG_CONTROL_PIN
        writePinLow(RGB_UG_CONTROL_PIN);
#endif
    }

    if (ble_on && layer_state_cmp(state, 0)) {
        rgblight_reload_from_eeprom();
        if (!rgblight_is_enabled()) {
#ifdef RGB_UG_CONTROL_PIN
            writePinHigh(RGB_UG_CONTROL_PIN);
#endif
            rgblight_disable_noeeprom();
        } else {
#ifdef RGB_UG_CONTROL_PIN
            writePinLow(RGB_UG_CONTROL_PIN);
#endif
            rgblight_enable_noeeprom();
        }
    }

    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_F21:
            if (record->event.pressed) {
                module_reset();
            }
            break;
        case KC_F19:
            if (record->event.pressed) {
                reset_ble_batt();
            }
            break;
        case KC_F20:
            if (record->event.pressed) {
                update_ble_batt();
                wait_ms(100);
            }
            break;
        case KC_CAPS:
            if (record->event.pressed) {
                if (ble_on) {
                    rgblight_reload_from_eeprom();
                    ble_led.caplck = !ble_led.caplck;
                    rgblight_set_layer_state(0, ble_led.caplck);
                    if (ble_led.caplck && !rgblight_is_enabled()) {
                        rgblight_enable_noeeprom();
                    }
                    if (!ble_led.caplck && !rgblight_is_enabled()) {
                        rgblight_disable_noeeprom();
                    }
                }
            }
            break;
        default:
            return true;
    }
    return true;
}

void matrix_scan_user(void) {
    if (ble_led.caplck) {
        writePinHigh(LED_CAPS_LOCK_PIN);
    } else {
        writePinLow(LED_CAPS_LOCK_PIN);
    }
}