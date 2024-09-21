// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, XXXXXXX, XXXXXXX, TO(1)
    ),
    [1] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, TO(2)
    ),
    [2] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, TO(3)
    ),
    [3] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_KB_0, QK_KB_1, QK_KB_3, QK_KB_5,
        XXXXXXX, QK_KB_2, QK_KB_4, QK_KB_6,
        XXXXXXX, XXXXXXX, XXXXXXX, TO(0)
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(C(KC_Z), C(KC_Y))  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  }
};
#endif


typedef union {
    uint32_t raw;
    struct {
        uint8_t led_level : 3;
    };
} work_louder_config_t;

work_louder_config_t work_louder_config;

#define WL_LED_MAX_BRIGHT 75

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_KB_9:
            if (record->event.pressed) {
                work_louder_config.led_level++;
                if (work_louder_config.led_level > 4) {
                    work_louder_config.led_level = 1;
                }
                work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
                eeconfig_update_user(work_louder_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
    }
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_cmp(state, 1) ? work_louder_micro_led_1_on(): work_louder_micro_led_1_off();
    layer_state_cmp(state, 2) ? work_louder_micro_led_2_on(): work_louder_micro_led_2_off();
    layer_state_cmp(state, 3) ? work_louder_micro_led_3_on(): work_louder_micro_led_3_off();

    return state;
}

void eeconfig_init_user(void) {
    work_louder_config.raw = 0;
    work_louder_config.led_level = 1;
    work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
    eeconfig_update_user(work_louder_config.raw);
}

void keyboard_post_init_user(void) {
    work_louder_config.raw = eeconfig_read_user();
    work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
}

void suspend_wakeup_init_user(void) {
    layer_state_set_user(layer_state);
}


enum via_indicator_value {
    id_wl_brightness = 1,
    id_wl_layer, // placeholder
};

void wl_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            work_louder_config.led_level = (uint8_t)*value_data;
            work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
            layer_state_set_kb(layer_state);
            break;
        // case id_wl_layer:
        //     layer_move(*value_data);
        //     break;
    }
}

void wl_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            *value_data = work_louder_config.led_level;
            break;
        // case id_wl_layer:
        //     *value_data = get_highest_layer(layer_state);
        //     break;
    }
}

void wl_config_save(void) {
    eeconfig_update_user(work_louder_config.raw);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                wl_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                wl_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                wl_config_save();
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
