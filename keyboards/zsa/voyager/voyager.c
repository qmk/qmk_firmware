// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "voyager.h"

keyboard_config_t keyboard_config;

bool mcp23018_leds[2] = {0, 0};
bool is_launching     = false;

#if defined(DEFERRED_EXEC_ENABLE)
#    if defined(DYNAMIC_MACRO_ENABLE)
deferred_token dynamic_macro_token = INVALID_DEFERRED_TOKEN;
static uint32_t dynamic_macro_led(uint32_t trigger_time, void *cb_arg) {
    static bool led_state = true;
    if (!is_launching) {
        led_state = !led_state;
        STATUS_LED_3(led_state);
    }
    return 100;
}

bool dynamic_macro_record_start_kb(int8_t direction) {
    if (!dynamic_macro_record_start_user(direction)) {
        return false;
    }
    if (dynamic_macro_token == INVALID_DEFERRED_TOKEN) {
        STATUS_LED_3(true);
        dynamic_macro_token = defer_exec(100, dynamic_macro_led, NULL);
    }
    return true;
}

bool dynamic_macro_record_end_kb(int8_t direction) {
    if (!dynamic_macro_record_end_user(direction)) {
        return false;
    }
    if (cancel_deferred_exec(dynamic_macro_token)) {
        dynamic_macro_token = INVALID_DEFERRED_TOKEN;
        STATUS_LED_3(false);
    }
    return true;
}
#    endif

static uint32_t startup_exec(uint32_t trigger_time, void *cb_arg) {
    static uint8_t startup_loop = 0;

    switch (startup_loop++) {
        case 0:
            STATUS_LED_1(true);
            STATUS_LED_2(false);
            STATUS_LED_3(false);
            STATUS_LED_4(false);
            break;
        case 1:
            STATUS_LED_2(true);
            break;
        case 2:
            STATUS_LED_3(true);
            break;
        case 3:
            STATUS_LED_4(true);
            break;
        case 4:
            STATUS_LED_1(false);
            break;
        case 5:
            STATUS_LED_2(false);
            break;
        case 6:
            STATUS_LED_3(false);
            break;
        case 7:
            STATUS_LED_4(false);
            break;
        case 8:
            is_launching = false;
            layer_state_set_kb(layer_state);
            return 0;
    }
    return 250;
}
#endif

void keyboard_pre_init_kb(void) {
    // Initialize Reset pins
    gpio_set_pin_input(A8);
    gpio_set_pin_output(A9);
    gpio_write_pin_low(A9);

    gpio_set_pin_output(B5);
    gpio_set_pin_output(B4);
    gpio_set_pin_output(B3);

    gpio_write_pin_low(B5);
    gpio_write_pin_low(B4);
    gpio_write_pin_low(B3);

    keyboard_pre_init_user();
}

#if !defined(VOYAGER_USER_LEDS)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    if (is_launching || !keyboard_config.led_level) return state;

    uint8_t layer = get_highest_layer(state);

    STATUS_LED_1(layer & (1 << 0));
    STATUS_LED_2(layer & (1 << 1));
    STATUS_LED_3(layer & (1 << 2));

#    if !defined(CAPS_LOCK_STATUS)
    STATUS_LED_4(layer & (1 << 3));
#    endif
    return state;
}
#endif

#ifdef RGB_MATRIX_ENABLE
// clang-format off
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_2,  C1_2,  C4_3},
    {0, C2_3,  C1_3,  C3_3},
    {0, C2_4,  C1_4,  C3_4},
    {0, C2_5,  C1_5,  C3_5},
    {0, C2_6,  C1_6,  C3_6},
    {0, C2_7,  C1_7,  C3_7},
    {0, C2_8,  C1_8,  C3_8},
    {0, C8_1,  C7_1,  C9_1},
    {0, C8_2,  C7_2,  C9_2},
    {0, C8_3,  C7_3,  C9_3},
    {0, C8_4,  C7_4,  C9_4},
    {0, C8_5,  C7_5,  C9_5},
    {0, C8_6,  C7_6,  C9_6},
    {0, C2_10,  C1_10,  C4_11},
    {0, C2_11,  C1_11,  C3_11},
    {0, C2_12,  C1_12,  C3_12},
    {0, C2_13,  C1_13,  C3_13},
    {0, C2_14,  C1_14,  C3_14},
    {0, C2_15,  C1_15,  C3_15},
    {0, C2_16,  C1_16,  C3_16},
    {0, C8_9,  C7_9,  C9_9},
    {0, C8_10,  C7_10,  C9_10},
    {0, C8_11,  C7_11,  C9_11},
    {0, C8_12,  C7_12,  C9_12},
    {0, C8_13,  C7_13,  C9_13},
    {0, C8_14,  C7_14,  C9_14},

    {1, C2_7,  C1_7,  C3_7},
    {1, C2_6,  C1_6,  C3_6},
    {1, C2_5,  C1_5,  C3_5},
    {1, C2_4,  C1_4,  C3_4},
    {1, C2_3,  C1_3,  C3_3},
    {1, C2_2,  C1_2,  C4_3},

    {1, C8_5,  C7_5,  C9_5},
    {1, C8_4,  C7_4,  C9_4},
    {1, C8_3,  C7_3,  C9_3},
    {1, C8_2,  C7_2,  C9_2},
    {1, C8_1,  C7_1,  C9_1},
    {1, C2_8,  C1_8,  C3_8},

    {1, C2_14,  C1_14,  C3_14},
    {1, C2_13,  C1_13,  C3_13},
    {1, C2_12,  C1_12,  C3_12},
    {1, C2_11,  C1_11,  C3_11},
    {1, C2_10,  C1_10,  C4_11},
    {1, C8_6,  C7_6,  C9_6},

    {1, C8_12,  C7_12,  C9_12},
    {1, C8_11,  C7_11,  C9_11},
    {1, C8_10,  C7_10,  C9_10},
    {1, C8_9,  C7_9,  C9_9},
    {1, C2_16,  C1_16,  C3_16},
    {1, C2_15,  C1_15,  C3_15},

    {1, C8_14,  C7_14,  C9_14},
    {1, C8_13,  C7_13,  C9_13},
};
// clang-format on
#endif

#ifdef SWAP_HANDS_ENABLE
// swap-hands action needs a matrix to define the swap
// clang-format off
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{6,6}, {5,6}, {4,6}, {3,6}, {2,6}, {1,6},{0,6}},
    {{6,7}, {5,7}, {4,7}, {3,7}, {2,7}, {1,7},{0,7}},
    {{6,8}, {5,8}, {4,8}, {3,8}, {2,8}, {1,8},{0,8}},
    {{6,9}, {5,9}, {4,9}, {3,9}, {2,9}, {1,9},{0,9}},
    {{6,10},{5,10},{4,10},{3,10},{2,10},{1,10},{0,10}},
    {{6,11},{5,11},{4,11},{3,11},{2,11},{1,11},{0,11}},
    /* Right hand, matrix positions */
    {{6,0}, {5,0}, {4,0}, {3,0}, {2,0}, {1,0},{0,0}},
    {{6,1}, {5,1}, {4,1}, {3,1}, {2,1}, {1,1},{0,1}},
    {{6,2}, {5,2}, {4,2}, {3,2}, {2,2}, {1,2},{0,2}},
    {{6,3}, {5,3}, {4,3}, {3,3}, {2,3}, {1,3},{0,3}},
    {{6,4}, {5,4}, {4,4}, {3,4}, {2,4}, {1,4},{0,4}},
    {{6,5}, {5,5}, {4,5}, {3,5}, {2,5}, {1,5},{0,5}},
};
// clang-format on
#endif

#ifdef CAPS_LOCK_STATUS
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        STATUS_LED_4(led_state.caps_lock);
    }
    return res;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#if !defined(VOYAGER_USER_LEDS)
        case LED_LEVEL:
            if (record->event.pressed) {
                keyboard_config.led_level ^= 1;
                eeconfig_update_kb(keyboard_config.raw);
                if (keyboard_config.led_level) {
                    layer_state_set_kb(layer_state);
                } else {
                    STATUS_LED_1(false);
                    STATUS_LED_2(false);
                    STATUS_LED_3(false);
                    STATUS_LED_4(false);
                }
            }
            break;
#endif
#ifdef RGB_MATRIX_ENABLE
        case TOGGLE_LAYER_COLOR:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led ^= 1;
                if (keyboard_config.disable_layer_led) rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case QK_RGB_MATRIX_TOGGLE:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            return false;
#endif
    }
    return true;
}

void keyboard_post_init_kb(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
#endif

    keyboard_config.raw = eeconfig_read_kb();

    if (!keyboard_config.led_level && !keyboard_config.led_level_res) {
        keyboard_config.led_level     = true;
        keyboard_config.led_level_res = 0b11;
        eeconfig_update_kb(keyboard_config.raw);
    }
#if defined(DEFERRED_EXEC_ENABLE)
    is_launching = true;
    defer_exec(500, startup_exec, NULL);
#endif
    keyboard_post_init_user();
}

void eeconfig_init_kb(void) { // EEPROM is getting reset!
    keyboard_config.raw           = 0;
    keyboard_config.led_level     = true;
    keyboard_config.led_level_res = 0b11;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

__attribute__((weak)) void bootloader_jump(void) {
    // The ignition bootloader is checking for a high signal on A8 for 100ms when powering on the board.
    // Setting both A8 and A9 high will charge the capacitor quickly.
    // Setting A9 low before reset will cause the capacitor to discharge
    // thus making the bootloder unlikely to trigger twice between power cycles.
    gpio_set_pin_output_push_pull(A9);
    gpio_set_pin_output_push_pull(A8);
    gpio_write_pin_high(A9);
    gpio_write_pin_high(A8);
    wait_ms(500);
    gpio_write_pin_low(A9);

    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    gpio_set_pin_output_push_pull(A9);
    gpio_set_pin_output_push_pull(A8);
    gpio_write_pin_low(A8);
    gpio_write_pin_low(A9);

    NVIC_SystemReset();
}
