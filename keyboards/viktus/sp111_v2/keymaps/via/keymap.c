// Copyright 2023 BlindAssassin111 (@blindassassin111)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    KC_MUTE,KC_MPRV,KC_MPLY,KC_MNXT,    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SCRL, KC_PAUS,
    KC_NUM, KC_PSLS,KC_PAST,KC_PMNS,    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_HOME, KC_INS,
    KC_P7,  KC_P8,  KC_P9,  KC_PMNS,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,  KC_DEL,
    KC_P4,  KC_P5,  KC_P6,  KC_PPLS,    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGUP, KC_PGDN,
    KC_P1,  KC_P2,  KC_P3,  KC_PPLS,    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),            KC_UP,
    KC_P0,  KC_P0,  KC_PDOT,  KC_PENT,  KC_LCTL, KC_LGUI, KC_LALT, KC_MUTE, KC_SPC,           KC_SPC,  KC_APP,  KC_RALT, KC_RGUI, KC_RCTL,                            KC_LEFT, KC_DOWN, KC_RIGHT),

    [1] = LAYOUT(
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, QK_BOOT,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,                            _______, _______, _______),

    [2] = LAYOUT(
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, QK_BOOT,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______,      _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,                            _______, _______, _______)
};

#ifdef RGB_MATRIX_ENABLE

// Single Indicator memory layout
typedef struct _indicator_config_t {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    bool    enabled;
} indicator_config;

// Board memory layout
typedef struct _fave_config_t {
    indicator_config caps;
    indicator_config scroll;
    indicator_config num;
} fave_config;

fave_config fave;

// Check if the size of the reserved persistent memory is the same as the size of struct apc_config
_Static_assert(sizeof(fave_config) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard EECONFIG stored data");

void eeconfig_init_user(void) {
    // Default values
    fave.caps.h       = 0;
    fave.caps.s       = 0;
    fave.caps.v       = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    fave.caps.enabled = true;
    fave.scroll.h       = 0;
    fave.scroll.s       = 0;
    fave.scroll.v       = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    fave.scroll.enabled = true;
    fave.num.h       = 0;
    fave.num.s       = 0;
    fave.num.v       = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    fave.num.enabled = true;

    // Write default value to EEPROM now
    //eeconfig_update_kb_datablock(&fave);
    eeconfig_update_kb_datablock(&fave);
}

enum via_fave {
    id_caps_indicator_enabled    = 1,
    id_caps_indicator_brightness = 2,
    id_caps_indicator_color      = 3,
    id_scroll_indicator_enabled    = 4,
    id_scroll_indicator_brightness = 5,
    id_scroll_indicator_color      = 6,
    id_num_indicator_enabled    = 7,
    id_num_indicator_brightness = 8,
    id_num_indicator_color      = 9
};

//On Keyboard startup
void keyboard_post_init_user(void) {
    //Read our custom menu variables from memory
    eeconfig_read_kb_datablock(&fave);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv_caps_indicator_color = {fave.caps.h, fave.caps.s, fave.caps.v};
    HSV hsv_scroll_indicator_color = {fave.scroll.h, fave.scroll.s, fave.scroll.v};
    HSV hsv_num_indicator_color = {fave.num.h, fave.num.s, fave.num.v};
    RGB rgb_caps_indicator_color = hsv_to_rgb(hsv_caps_indicator_color);
    RGB rgb_scroll_indicator_color = hsv_to_rgb(hsv_scroll_indicator_color);
    RGB rgb_num_indicator_color = hsv_to_rgb(hsv_num_indicator_color);
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(0, rgb_caps_indicator_color.r, rgb_caps_indicator_color.g, rgb_caps_indicator_color.b);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 0);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(1, rgb_scroll_indicator_color.r, rgb_scroll_indicator_color.g, rgb_scroll_indicator_color.b);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 0, 0, 0);
    }
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(2, rgb_num_indicator_color.r, rgb_num_indicator_color.g, rgb_num_indicator_color.b);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 0, 0);
    }
    return false;
}

void fave_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled: {
            fave.caps.enabled = value_data[0];
            break;
        }
        case id_caps_indicator_brightness: {
            fave.caps.v = value_data[0];
            break;
        }
        case id_caps_indicator_color: {
            fave.caps.h = value_data[0];
            fave.caps.s = value_data[1];
            break;
        }
        case id_scroll_indicator_enabled: {
            fave.scroll.enabled = value_data[0];
            break;
        }
        case id_scroll_indicator_brightness: {
            fave.scroll.v = value_data[0];
            break;
        }
        case id_scroll_indicator_color: {
            fave.scroll.h = value_data[0];
            fave.scroll.s = value_data[1];
            break;
        }
        case id_num_indicator_enabled: {
            fave.num.enabled = value_data[0];
            break;
        }
        case id_num_indicator_brightness: {
            fave.num.v = value_data[0];
            break;
        }
        case id_num_indicator_color: {
            fave.num.h = value_data[0];
            fave.num.s = value_data[1];
            break;
        }
    }
}

void fave_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled: {
            value_data[0] = fave.caps.enabled;
            break;
        }
        case id_caps_indicator_brightness: {
            value_data[0] = fave.caps.v;
            break;
        }
        case id_caps_indicator_color: {
            value_data[0] = fave.caps.h;
            value_data[1] = fave.caps.s;
            break;
        }
        case id_scroll_indicator_enabled: {
            value_data[0] = fave.scroll.enabled;
            break;
        }
        case id_scroll_indicator_brightness: {
            value_data[0] = fave.scroll.v;
            break;
        }
        case id_scroll_indicator_color: {
            value_data[0] = fave.scroll.h;
            value_data[1] = fave.scroll.s;
            break;
        }
        case id_num_indicator_enabled: {
            value_data[0] = fave.num.enabled;
            break;
        }
        case id_num_indicator_brightness: {
            value_data[0] = fave.num.v;
            break;
        }
        case id_num_indicator_color: {
            value_data[0] = fave.num.h;
            value_data[1] = fave.num.s;
            break;
        }
    }
}

void fave_config_save(void) {
    eeconfig_update_kb_datablock(&fave);
    // eeprom_update_block( &fave,
    //     ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR),
    //     sizeof(fave) );
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                fave_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                fave_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                fave_config_save();
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

#endif
