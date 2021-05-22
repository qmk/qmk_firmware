/* Copyright 2019 monksoffunk
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

#include "common/oled_helper.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    RGBRST = SAFE_RANGE,
    WRTROM,
};

enum layer_number {
    _AUDIO = 0,
    _HUE,
    _SAT,
    _VAL,
    _MODE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // LAYOUT(LeftEncoder, RightEncoder, LeftSwitch, CenterLeftSwitch, CenterRightSwitch, RightSwitch)
    [_AUDIO] = LAYOUT(KC_MUTE, KC_ENT, LT(_HUE, KC_MPRV), LT(_SAT, KC_MPLY), LT(_VAL, KC_MNXT), LT(_MODE, KC_SPC)),
    [_HUE]   = LAYOUT(RGB_TOG, RGBRST, _______, _______, RGB_HUD, RGB_HUI),
    [_SAT]   = LAYOUT(_______, _______, _______, _______, RGB_SAD, RGB_SAI),
    [_VAL]   = LAYOUT(_______, _______, RGB_VAD, RGB_VAI, _______, RGB_VAI),
    [_MODE]  = LAYOUT(_______, WRTROM, RGB_RMOD, RGB_MOD, RGB_MOD, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WRTROM:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_current();
            }
#endif
            return false;
            break;

        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
#endif
            return false;
            break;
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
#    include <stdio.h>
#    include <string.h>

// assign the right code to your layers for OLED display
#    define L_AUDIO 0
#    define L_HUE (1 << _HUE)
#    define L_SAT (1 << _SAT)
#    define L_VAL (1 << _VAL)
#    define L_MODE (1 << _MODE)

void render_status(void) {
    render_logo();
    // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
    switch (layer_state) {
        case L_AUDIO:
            oled_write_P(PSTR("audio control\n"), false);
            break;
        case L_HUE:
            oled_write_P(PSTR("rgb HUE control\n"), false);
            break;
        case L_SAT:
            oled_write_P(PSTR("rgb SAT control\n"), false);
            break;
        case L_VAL:
            oled_write_P(PSTR("rgb VAL control\n"), false);
            break;
        case L_MODE:
            oled_write_P(PSTR("rgb MODE control\n"), false);
            break;
        default:
            break;
    }
    UPDATE_LED_STATUS();
    RENDER_LED_STATUS();
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_logo();
    }
}
#endif

void led_set_user(uint8_t usb_led) {}

bool encoder_update_user(uint8_t index, bool clockwise) {
    oled_on();
    if (index == 0) { /* left encoder */
        switch (layer_state) {
            case L_AUDIO:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            case L_HUE:
#ifdef RGBLIGHT_ENABLE
                if (clockwise) {
                    rgblight_increase_hue_noeeprom();
                } else {
                    rgblight_decrease_hue_noeeprom();
                }
#endif
                break;

            case L_SAT:
#ifdef RGBLIGHT_ENABLE
                if (clockwise) {
                    rgblight_increase_sat_noeeprom();
                } else {
                    rgblight_decrease_sat_noeeprom();
                }
#endif
                break;

            case L_VAL:
#ifdef RGBLIGHT_ENABLE
                if (clockwise) {
                    rgblight_increase_val_noeeprom();
                } else {
                    rgblight_decrease_val_noeeprom();
                }
#endif
                break;

            case L_MODE:
#ifdef RGBLIGHT_ENABLE
                if (clockwise) {
                    rgblight_step_noeeprom();
                } else {
                    rgblight_step_reverse_noeeprom();
                }
#endif
                break;
        }
    } else if (index == 1) { /* right encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}
