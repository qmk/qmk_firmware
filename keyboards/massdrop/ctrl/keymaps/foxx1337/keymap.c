/*
 * Copyright 2021 foxx1337 at yahoo dot com
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
#include "hid_protocol.h"

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

#define TIMEOUT_ACTIVITY 300000 // 300 seconds before lights go off

uint32_t time_last_activity;
bool is_led_timeout;
led_flags_t led_state;

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______,                              _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______
    ),
    */
};

void change_led_state(bool is_off) {
    is_led_timeout = is_off;

    if (is_led_timeout) {
        led_state = rgb_matrix_get_flags();
        if (led_state != LED_FLAG_NONE) {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
        }
    } else {
        if (led_state != LED_FLAG_NONE) {
            rgb_matrix_set_flags(led_state);
            rgb_matrix_enable_noeeprom();
        }
    }
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    time_last_activity = timer_read32();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    if (!is_led_timeout && timer_elapsed32(time_last_activity) > TIMEOUT_ACTIVITY) {
        change_led_state(true);
    }
};

#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    time_last_activity = timer_read32();
    if (is_led_timeout) {
        change_led_state(false);
    }

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    }
                    break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

void raw_hid_say_hello(void) {
    const char *ctrl = CTRL_HID_GREETING_VERSION;
    uint8_t i = 0;
    while (ctrl[i] != 0 && i + 2 < RAW_EPSIZE) {
        raw_hid_buffer[1 + i] = ctrl[i];
        i++;
    }
    raw_hid_buffer[i] = CTRL_HID_EOM;
}

void raw_hid_lights_toggle(void) {
    change_led_state(!is_led_timeout);

    raw_hid_buffer[1] = CTRL_HID_OK;
    raw_hid_buffer[2] = (uint8_t) is_led_timeout;
    raw_hid_buffer[3] = CTRL_HID_EOM;
}

void raw_hid_led(uint8_t *data) {
    //rgb_matrix_set_color(data[1], data[2], data[3], data[4]);
    const uint8_t led = data[1];

    if (led >= RGB_MATRIX_LED_COUNT) {
        raw_hid_buffer[1] = CTRL_HID_NOK;
        raw_hid_buffer[2] = RGB_MATRIX_LED_COUNT;
        raw_hid_buffer[3] = CTRL_HID_EOM;
        return;
    }

    rgb_matrix_led_state[led].r = data[2];
    rgb_matrix_led_state[led].g = data[3];
    rgb_matrix_led_state[led].b = data[4];

    raw_hid_buffer[1] = CTRL_HID_OK;
    raw_hid_buffer[2] = CTRL_HID_EOM;
}

void raw_hid_leds(uint8_t *data) {
    const uint8_t first_led = data[1];
    const uint8_t number_leds = data[2];

    uint8_t i = 0;
    while (i < number_leds && first_led + i < RGB_MATRIX_LED_COUNT && i * 3 + 5 < RAW_EPSIZE) {
        rgb_matrix_led_state[first_led + i].r = data[3 + i * 3 + 0];
        rgb_matrix_led_state[first_led + i].g = data[3 + i * 3 + 1];
        rgb_matrix_led_state[first_led + i].b = data[3 + i * 3 + 2];
        i++;
    }

    raw_hid_buffer[1] = CTRL_HID_OK;
    raw_hid_buffer[2] = i;
    raw_hid_buffer[3] = CTRL_HID_EOM;
}

void raw_hid_rgbmatrix_mode(uint8_t *data) {
    const uint8_t mode = data[1];
    if (mode >= RGB_MATRIX_EFFECT_MAX) {
        raw_hid_buffer[1] = CTRL_HID_NOK;
        raw_hid_buffer[2] = RGB_MATRIX_EFFECT_MAX - 1;
        raw_hid_buffer[3] = CTRL_HID_EOM;
        return;
    }
    rgb_matrix_mode_noeeprom(mode);

    raw_hid_buffer[1] = CTRL_HID_OK;
    raw_hid_buffer[2] = CTRL_HID_EOM;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    switch (*data) {
        case CTRL_HID_HELLO:
            raw_hid_say_hello();
            break;
        case CTRL_HID_LIGHTS_TOGGLE:
            raw_hid_lights_toggle();
            break;
        case CTRL_HID_LED:
            raw_hid_led(data);
            break;
        case CTRL_HID_LEDS:
            raw_hid_leds(data);
            break;
        case CTRL_HID_RGBMATRIX_MODE:
            raw_hid_rgbmatrix_mode(data);
            break;
    }

    raw_hid_perform_send();
}
