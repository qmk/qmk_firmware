/*
Copyright 2023 <contact@vwolf.be>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = |Bsp|Bsp|Hom│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │PgU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │PgD│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │End│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│GUI │Alt │                        │Alt│ Fn│Ctl│ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_65_ansi_split_bs(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_65_ansi_split_bs(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,  _______,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,  _______,
        _______,          _______, _______, _______, _______, QK_BOOT, _______, KC_MUTE, _______, _______, _______, _______, KC_VOLU, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    )

};


// Single Indicator memory layout
typedef struct _indicator_config_t {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    bool    enabled;
} indicator_config;

// Led State Config
typedef enum {  
    LED_STATE_ALL, 
    LED_STATE_BACKLIGHT,
    LED_STATE_UNDERGLOW,
    LED_STATE_INDICATORS
} led_states;

// Board memory layout
typedef struct _customKB_config_t {
    led_states leds;
    indicator_config caps;

} customKB_config;

customKB_config customKB;

void eeconfig_init_user(void) {

    customKB.leds         = LED_STATE_ALL;

    // Default values
    customKB.caps.h       = 128;
    customKB.caps.s       = 128;
    customKB.caps.v       = RGB_MATRIX_MAXIMUM_BRIGHTNESS / 2;
    customKB.caps.enabled = true;

    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&customKB);
}

enum via_customKB {
    id_leds_state                = 1,
    id_caps_indicator_enabled    = 2,
    id_caps_indicator_brightness = 3,
    id_caps_indicator_color      = 4
};

//On Keyboard startup
void keyboard_post_init_user(void) {
    //Read our custom menu variables from memory
    eeconfig_read_kb_datablock(&customKB);
}

void set_caps_lock_led(void) {
    if (customKB.caps.enabled) {
        // The rgb_matrix_set_color function needs an RGB code to work, so first the indicator color is cast to an HSV value and then translated to RGB
        HSV hsv_caps_indicator_color = {customKB.caps.h, customKB.caps.s, customKB.caps.v};
        RGB rgb_caps_indicator_color = hsv_to_rgb(hsv_caps_indicator_color);
        if (host_keyboard_led_state().caps_lock)
            rgb_matrix_set_color(CAPS_INDICATOR_INDEX, rgb_caps_indicator_color.r, rgb_caps_indicator_color.g, rgb_caps_indicator_color.b);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    switch(customKB.leds){
            case LED_STATE_ALL:
                set_caps_lock_led();
                return true;
            case LED_STATE_BACKLIGHT:
                for (uint8_t i = led_min; i < led_max; i++) {
                    if (!HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
                        rgb_matrix_set_color(i, 0, 0, 0);
                    }
                }
                set_caps_lock_led();
                return true;
            case LED_STATE_UNDERGLOW: 
                for (uint8_t i = led_min; i < led_max; i++) {
                    if (!HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                        rgb_matrix_set_color(i, 0, 0, 0);
                    }
                }
                set_caps_lock_led();
                return true;
            case LED_STATE_INDICATORS:
                for (uint8_t i = led_min; i < led_max; i++) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
                set_caps_lock_led();
                return true;
        }

    return true;
}

void customKB_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled: {
            customKB.caps.enabled = value_data[0];
            break;
        }
        case id_caps_indicator_brightness: {
            customKB.caps.v = value_data[0];
            break;
        }
        case id_caps_indicator_color: {
            customKB.caps.h = value_data[0];
            customKB.caps.s = value_data[1];
            break;
        }
        case id_leds_state: {
            customKB.leds = value_data[0];
            break;
        }
    }
}

void customKB_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled: {
            value_data[0] = customKB.caps.enabled;
            break;
        }
        case id_caps_indicator_brightness: {
            value_data[0] = customKB.caps.v;
            break;
        }
        case id_caps_indicator_color: {
            value_data[0] = customKB.caps.h;
            value_data[1] = customKB.caps.s;
            break;
        }
        case id_leds_state: {
            value_data[0] = customKB.leds;
            break;
        }
    }
}

void customKB_config_save(void) {
    eeconfig_update_kb_datablock(&customKB);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                customKB_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                customKB_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                customKB_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    *command_id = id_unhandled;
}
