// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


enum wl_micro_layers {
    _L0,
    _L1,
    _L2,
    _L3,
    _L4,
    _L5,
    _L6,
    _ADJUST
};

// enum custom_keycodes {
//     LED_LEVEL = SAFE_RANGE,
// };

#define CK_UNDO G(KC_Z)       // UNDO = CMD + Z
#define CK_REDO LSG(KC_Z)     // REDO = CMD + SHIFT + Z

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT(
        KC_MPLY, KC_9,    KC_0,    KC_NO,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_1,    KC_2,    KC_3,    KC_4,
        TO(1),   KC_DOT,  KC_COMM, _______
    ),
    [_L1] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_A,    KC_B,
        TO(2),   KC_C,    KC_D,    KC_E
    ),
    [_L2] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        TO(3),   _______, _______, _______
    ),
    [_L3] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        TO(4),   _______, _______, _______
    ),
    [_L4] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        TO(5),   _______, _______, _______
    ),
    [_L5] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        TO(6),   _______, _______, _______
    ),
    [_L6] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        TO(7),   _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
        QK_BOOT, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        TO(0),   _______, _______, _______
    ),
};

// typedef union {
//     uint32_t raw;
//     struct {
//         uint8_t led_level : 3;
//     };
// } work_louder_config_t;

// work_louder_config_t work_louder_config;

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case LED_LEVEL:
//             if (record->event.pressed) {
//                 work_louder_config.led_level++;
//                 if (work_louder_config.led_level > 4) {
//                     work_louder_config.led_level = 0;
//                 }
//                 work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * 255 / 4));
//                 eeconfig_update_user(work_louder_config.raw);
//                 layer_state_set_kb(layer_state);
//             }
//             break;
//     }
//     return true;
// }

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(CK_UNDO, CK_REDO)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
};
#endif


layer_state_t layer_state_set_user(layer_state_t state) {
    // Get highest layer as number
    int layer = get_highest_layer(state);
    // Toggle leds based on binary layer number [2 1 3]
    layer & 0x02 ? work_louder_micro_led_1_on(): work_louder_micro_led_1_off();
    layer & 0x04 ? work_louder_micro_led_2_on(): work_louder_micro_led_2_off();
    layer & 0x01 ? work_louder_micro_led_3_on(): work_louder_micro_led_3_off();

    return state;
}

// void eeconfig_init_user(void) {
//     work_louder_config.raw = 0;
//     work_louder_config.led_level = 1;
//     eeconfig_update_user(work_louder_config.raw);
// }

// void matrix_init_user(void) {
//     work_louder_config.raw = eeconfig_read_user();
//     work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * 255 / 4));
// }
