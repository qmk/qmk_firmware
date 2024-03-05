// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "via.h"
#include "eeprom_driver.h"
#include "quantum.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tkl_f13_ansi_split_bs_rshift(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,              KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),                        KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RALT, KC_RGUI, KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT
    )
};

enum via_indicator_value {
    id_override_colors = 1,
    id_left_eye_color,
    id_right_eye_color,
};

typedef struct {
    uint8_t override;
    HSV left_eye_color;
    HSV right_eye_color;
} via_config;

via_config g_config = {
    .override = 1,
    .left_eye_color = {128, 0, 255},
    .right_eye_color = {128, 0, 255}
};

void color_config_set_value( uint8_t *data );
void color_config_get_value( uint8_t *data );

void color_config_load(void) {
    eeprom_read_block(&g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE);
}

void color_config_save(void) {
    eeprom_update_block(&g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE);
}

void via_init_kb(void) {
    if (via_eeprom_is_valid()) {
        color_config_load();
    } else {
        color_config_save();
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                color_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                color_config_get_value(value_id_and_data);
                break;
            case id_custom_save:
                color_config_save();
                break;
            default:
                // Unhandled message.
                *command_id = id_unhandled;
                break;
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void color_config_set_value(uint8_t* data) {
    // data = [ value_id, value_data ]
    uint8_t* value_id   = &(data[0]);
    uint8_t* value_data = &(data[1]);
    switch (*value_id) {
        case id_override_colors:
            g_config.override = *value_data;
            break;
        case id_left_eye_color:
            g_config.left_eye_color.h = value_data[0];
            g_config.left_eye_color.s = value_data[1];
            break;
        case id_right_eye_color:
            g_config.right_eye_color.h = value_data[0];
            g_config.right_eye_color.s = value_data[1];
            break;
    }
}

void color_config_get_value(uint8_t* data) {
    // data = [ value_id, value_data ]
    uint8_t* value_id   = &(data[0]);
    uint8_t* value_data = &(data[1]);
    switch (*value_id) {
        case id_override_colors:
            *value_data = g_config.override;
            break;
        case id_left_eye_color:
            value_data[0] = g_config.left_eye_color.h;
            value_data[1] = g_config.left_eye_color.s;
            break;
        case id_right_eye_color:
            value_data[0] = g_config.right_eye_color.h;
            value_data[1] = g_config.right_eye_color.s;
            break;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    led_t keyboard_state = host_keyboard_led_state();

    if (g_config.override == 0) {
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(3, 0, 0, 0);
    }
    if (g_config.override == 2) {
        HSV hsv_re = {
            .h = g_config.right_eye_color.h,
            .s = g_config.right_eye_color.s,
            .v = rgb_matrix_get_val()
        };
        RGB rgb_re = hsv_to_rgb(hsv_re);
        RGB_MATRIX_INDICATOR_SET_COLOR(2, rgb_re.r, rgb_re.g, rgb_re.b);
        HSV hsv_le = {
            .h = g_config.left_eye_color.h,
            .s = g_config.left_eye_color.s,
            .v = rgb_matrix_get_val()
        };
        RGB rgb_le = hsv_to_rgb(hsv_le);
        RGB_MATRIX_INDICATOR_SET_COLOR(3, rgb_le.r, rgb_le.g, rgb_le.b);
    }

    if (!keyboard_state.scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 0, 0, 0);
    }

    if (!keyboard_state.caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 0);
    }

    return true;
}
