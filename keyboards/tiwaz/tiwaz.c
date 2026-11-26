// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "tiwaz.h"
#include "analog.h"
#include "gpio.h"
#include "split_util.h"
#include "transactions.h"
#include <math.h>

// Configuration
kb_config_t kb_config = {
    .joystick_mode_left = JOY_MODE_DIGITAL,
    .joystick_mode_right = JOY_MODE_DIGITAL
};

// Joystick state tracking
static joystick_state_t local_joystick_state = {
    .up = false,
    .down = false,
    .left = false,
    .right = false,
    .btn = false
};

static joystick_state_t remote_joystick_state = {
    .up = false,
    .down = false,
    .left = false,
    .right = false,
    .btn = false
};

// Joystick ADC values
static joystick_adc_t local_joystick_axis = {
    .x = JOY_CENTER,
    .y = JOY_CENTER,
    .btn = false
};

static joystick_adc_t remote_joystick_axis = {
    .x = JOY_CENTER,
    .y = JOY_CENTER,
    .btn = false
};

// Joystick keymaps
__attribute__ ((weak)) const joystick_keymap_t left_joystick_keymap = {
    .up = KC_UP,
    .down = KC_DOWN,
    .left = KC_LEFT,
    .right = KC_RGHT,
    .btn = KC_ENT
};

__attribute__ ((weak)) const joystick_keymap_t right_joystick_keymap = {
    .up = KC_UP,
    .down = KC_DOWN,
    .left = KC_LEFT,
    .right = KC_RGHT,
    .btn = KC_ENT
};

// Button hold tracking
static button_hold_t local_button_hold = {0, false, false, 0};
static button_hold_t remote_button_hold = {0, false, false, 0};

// Initialization tracking
static uint32_t init_timeout = 0;
static bool init_completed = false;

static void release_joystick_keys(uint8_t mode, joystick_state_t *state, button_hold_t *btn_hold, const joystick_keymap_t *keymap, int js_btn) {
    if (mode == JOY_MODE_DIGITAL) {
        if (state->up) unregister_code16(keymap->up);
        if (state->down) unregister_code16(keymap->down);
        if (state->left) unregister_code16(keymap->left);
        if (state->right) unregister_code16(keymap->right);
        if (state->btn) unregister_code16(keymap->btn);
    } else if (mode == JOY_MODE_ANALOG) {
        if (state->btn) unregister_joystick_button(js_btn);
    } else if (mode == JOY_MODE_MOUSE) {
        if (btn_hold->button_registered) {
            if (btn_hold->motion_detected) {
                unregister_code(MS_BTN1);
            } else {
                unregister_code(MS_BTN2);
            }
        }
        report_mouse_t report = pointing_device_get_report();
        report.x = 0;
        report.y = 0;
        pointing_device_set_report(report);
    }

    state->up = false;
    state->down = false;
    state->left = false;
    state->right = false;
    state->btn = false;

    btn_hold->press_time = 0;
    btn_hold->button_registered = false;
    btn_hold->motion_detected = false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case MD_JOYL:
                if (is_keyboard_left()) {
                    release_joystick_keys(kb_config.joystick_mode_left, &local_joystick_state, &local_button_hold, &left_joystick_keymap, JS_0);
                } else {
                    release_joystick_keys(kb_config.joystick_mode_left, &remote_joystick_state, &remote_button_hold, &left_joystick_keymap, JS_0);
                }
                kb_config.joystick_mode_left = (kb_config.joystick_mode_left + 1) % 3;
                save_kb_config();
                return false;

            case MD_JOYR:
                if (is_keyboard_left()) {
                    release_joystick_keys(kb_config.joystick_mode_right, &remote_joystick_state, &remote_button_hold, &right_joystick_keymap, JS_1);
                } else {
                    release_joystick_keys(kb_config.joystick_mode_right, &local_joystick_state, &local_button_hold, &right_joystick_keymap, JS_1);
                }
                kb_config.joystick_mode_right = (kb_config.joystick_mode_right + 1) % 3;
                save_kb_config();
                return false;
        }
    }
    return process_record_user(keycode, record);
}

void save_kb_config(void) {
    eeconfig_update_kb(kb_config.raw);
    transaction_rpc_send(RPC_KB_CONFIG, sizeof(kb_config.raw), &kb_config.raw);
}

bool pointing_device_driver_init(void) {
    return true;
}

static void joystick_axes_to_mouse_delta(int8_t sx, int8_t sy, mouse_xy_report_t *out_x, mouse_xy_report_t *out_y) {
    float magnitude = sqrtf((float)sx * sx + (float)sy * sy);
    if (magnitude <= JOY_MOUSE_DEADZONE) {
        *out_x = 0;
        *out_y = 0;
        return;
    }

    float travel = magnitude - JOY_MOUSE_DEADZONE;
    float range  = (float)INT8_MAX - JOY_MOUSE_DEADZONE;
    float speed  = (travel * travel) / (range * range) * JOY_MOUSE_MAX_SPEED;
    if (speed > JOY_MOUSE_MAX_SPEED) {
        speed = JOY_MOUSE_MAX_SPEED;
    }

    *out_x = (mouse_xy_report_t)(speed * sx / magnitude);
    *out_y = (mouse_xy_report_t)(speed * sy / magnitude);
}

static void handle_joystick(uint8_t mode, joystick_adc_t* adc, joystick_state_t* state, button_hold_t* btn_hold,
                            int js_btn, const joystick_keymap_t* keymap) {

    if (mode == JOY_MODE_DIGITAL) { // DIGITAL mode
        int8_t sx = (int8_t)adc->x;
        int8_t sy = (int8_t)adc->y;

        // UP
        if (sy < -JOY_DIGITAL_ON && !state->up) {
            register_code16(keymap->up);
            state->up = true;
        } else if (sy > -JOY_DIGITAL_OFF && state->up) {
            unregister_code16(keymap->up);
            state->up = false;
        }

        // DOWN
        if (sy > JOY_DIGITAL_ON && !state->down) {
            register_code16(keymap->down);
            state->down = true;
        } else if (sy < JOY_DIGITAL_OFF && state->down) {
            unregister_code16(keymap->down);
            state->down = false;
        }

        // LEFT
        if (sx < -JOY_DIGITAL_ON && !state->left) {
            register_code16(keymap->left);
            state->left = true;
        } else if (sx > -JOY_DIGITAL_OFF && state->left) {
            unregister_code16(keymap->left);
            state->left = false;
        }

        // RIGHT
        if (sx > JOY_DIGITAL_ON && !state->right) {
            register_code16(keymap->right);
            state->right = true;
        } else if (sx < JOY_DIGITAL_OFF && state->right) {
            unregister_code16(keymap->right);
            state->right = false;
        }

        // BUTTON
        if (adc->btn && !state->btn) {
            register_code16(keymap->btn);
            state->btn = true;
        } else if (!adc->btn && state->btn) {
            unregister_code16(keymap->btn);
            state->btn = false;
        }

    } else if (mode == JOY_MODE_ANALOG) { // ANALOG mode
        if (adc->btn && !state->btn) {
            register_joystick_button(js_btn);
            state->btn = true;
        } else if (!adc->btn && state->btn) {
            unregister_joystick_button(js_btn);
            state->btn = false;
        }

    } else if (mode == JOY_MODE_MOUSE) { // MOUSE mode
        int8_t sx = (int8_t)adc->x;
        int8_t sy = (int8_t)adc->y;

        if (timer_elapsed32(btn_hold->last_move_time) >= JOY_POLLING_INTERVAL) {
            btn_hold->last_move_time = timer_read32();
            report_mouse_t report = pointing_device_get_report();
            joystick_axes_to_mouse_delta(sx, sy, &report.x, &report.y);
            pointing_device_set_report(report);
        }

        // Button handling with hold detection and motion lockout
        if (adc->btn && !state->btn) {
            // Button pressed - don't register yet, wait to see if there's motion or timeout
            btn_hold->press_time = timer_read32();
            btn_hold->button_registered = false;
            btn_hold->motion_detected = false;
            state->btn = true;
        } else if (!adc->btn && state->btn) {
            // Button released
            if (btn_hold->button_registered) {
                // A button was registered, unregister it
                if (btn_hold->motion_detected) {
                    unregister_code(MS_BTN1);  // Was left-click
                } else {
                    unregister_code(MS_BTN2);  // Was right-click
                }
            } else {
                // Button was released before any button was registered (quick click)
                // Treat as left-click
                register_code(MS_BTN1);
                unregister_code(MS_BTN1);
            }
            state->btn = false;
            btn_hold->button_registered = false;
            btn_hold->motion_detected = false;
        } else if (adc->btn && state->btn) {
            // Button held - decide which button to register based on motion or timeout
            if (!btn_hold->button_registered) {
                // Check for motion
                if (sx < -JOY_MOUSE_DEADZONE || sx > JOY_MOUSE_DEADZONE ||
                    sy < -JOY_MOUSE_DEADZONE || sy > JOY_MOUSE_DEADZONE) {
                    // Motion detected - register left-click
                    btn_hold->motion_detected = true;
                    register_code(MS_BTN1);
                    btn_hold->button_registered = true;
                } else if (timer_elapsed32(btn_hold->press_time) >= MOUSE_BUTTON_HOLD_MS) {
                    // 500ms timeout without motion - register right-click
                    register_code(MS_BTN2);
                    btn_hold->button_registered = true;
                }
            }
        }
    }
}

// RPC handlers
static void receive_joystick(uint8_t in_len, const void *in_buf, uint8_t out_len, void *out_buf) {
    if (out_len == sizeof(joystick_adc_t)) {
        memcpy(out_buf, &remote_joystick_axis, out_len);
    }
}

static void receive_kb_config(uint8_t in_len, const void *in_buf, uint8_t out_len, void *out_buf) {
    if (in_len == sizeof(kb_config_t)) {
        memcpy(&kb_config, in_buf, in_len);
    }
}

// Keyboard initialization
void keyboard_post_init_kb(void) {
    gpio_set_pin_input_high(JOY_PIN_B);

    if (is_keyboard_master()) {
        init_timeout = timer_read32();
        kb_config.raw = eeconfig_read_kb();
    }
    transaction_register_rpc(RPC_JOYSTICK_AXES, receive_joystick);
    transaction_register_rpc(RPC_KB_CONFIG, receive_kb_config);
    keyboard_post_init_user();
}

// RGB Matrix indicator for Caps Lock
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        if (get_highest_layer(layer_state) == 0) {
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                    uint8_t index = g_led_config.matrix_co[row][col];
                    uint8_t layer = get_highest_layer(layer_state);

                    if (index >= led_min && index < led_max && index != NO_LED &&
                    keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_CAPS) {
                        hsv_t hsv = rgb_matrix_get_hsv();
                        hsv.h = (hsv.h + 128) % 256;
                        rgb_t rgb = hsv_to_rgb(hsv);
                        rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                    }
                }
            }
        }
    }
    return true;
}

// Housekeeping task
void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        if (!init_completed) {
            if (timer_elapsed32(init_timeout) > 2000) {
                transaction_rpc_send(RPC_KB_CONFIG, sizeof(kb_config.raw), &kb_config.raw);
                init_completed = true;
            } else {
                return;
            }
        }

        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > JOY_POLLING_INTERVAL) {
            transaction_rpc_recv(RPC_JOYSTICK_AXES, sizeof(remote_joystick_axis), &remote_joystick_axis);
            last_sync = timer_read32();
        }

        local_joystick_axis = (joystick_adc_t){
            .x = JOY_CENTER - (analogReadPin(JOY_PIN_X) >> JOY_ADC_SHIFT),
            .y = (analogReadPin(JOY_PIN_Y) >> JOY_ADC_SHIFT) - JOY_CENTER,
            .btn = !gpio_read_pin(JOY_PIN_B)
        };

        if (is_keyboard_left()) {
            handle_joystick(kb_config.joystick_mode_left, &local_joystick_axis, &local_joystick_state, &local_button_hold,
                JS_0, &left_joystick_keymap);
            handle_joystick(kb_config.joystick_mode_right, &remote_joystick_axis, &remote_joystick_state, &remote_button_hold,
                JS_1, &right_joystick_keymap);
            
            // Set joystick axes only for analog mode
            joystick_set_axis(0, kb_config.joystick_mode_left == JOY_MODE_ANALOG ? local_joystick_axis.x : 0);
            joystick_set_axis(1, kb_config.joystick_mode_left == JOY_MODE_ANALOG ? local_joystick_axis.y : 0);
            joystick_set_axis(2, kb_config.joystick_mode_right == JOY_MODE_ANALOG ? remote_joystick_axis.x : 0);
            joystick_set_axis(3, kb_config.joystick_mode_right == JOY_MODE_ANALOG ? remote_joystick_axis.y : 0);
        } else {
            handle_joystick(kb_config.joystick_mode_left, &remote_joystick_axis, &remote_joystick_state, &remote_button_hold,
                JS_0, &left_joystick_keymap);
            handle_joystick(kb_config.joystick_mode_right, &local_joystick_axis, &local_joystick_state, &local_button_hold,
                JS_1, &right_joystick_keymap);
            
            // Set joystick axes only for analog mode
            joystick_set_axis(0, kb_config.joystick_mode_left == JOY_MODE_ANALOG ? remote_joystick_axis.x : 0);
            joystick_set_axis(1, kb_config.joystick_mode_left == JOY_MODE_ANALOG ? remote_joystick_axis.y : 0);
            joystick_set_axis(2, kb_config.joystick_mode_right == JOY_MODE_ANALOG ? local_joystick_axis.x : 0);
            joystick_set_axis(3, kb_config.joystick_mode_right == JOY_MODE_ANALOG ? local_joystick_axis.y : 0);
        }
    } else {
        remote_joystick_axis = (joystick_adc_t){
            .x = JOY_CENTER - (analogReadPin(JOY_PIN_X) >> JOY_ADC_SHIFT),
            .y = (analogReadPin(JOY_PIN_Y) >> JOY_ADC_SHIFT) - JOY_CENTER,
            .btn = !gpio_read_pin(JOY_PIN_B) // Active low
        };
    }
}

// RGB Matrix indicators
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (get_highest_layer(layer_state) == 1) {
        uint8_t mode_left = is_keyboard_left() ? kb_config.joystick_mode_left : kb_config.joystick_mode_right;
        uint8_t mode_right = is_keyboard_left() ? kb_config.joystick_mode_right : kb_config.joystick_mode_left;
        
        hsv_t hsv_left, hsv_right;
        
        // Set LED colors based on mode: 0=digital(blue), 1=analog(yellow), 2=mouse(red)
        switch(mode_left) {
            case JOY_MODE_MOUSE: hsv_left = (hsv_t){HSV_RED}; break;
            case JOY_MODE_ANALOG: hsv_left = (hsv_t){HSV_YELLOW}; break;
            default: hsv_left = (hsv_t){HSV_BLUE}; break;
        }
        
        switch(mode_right) {
            case JOY_MODE_MOUSE: hsv_right = (hsv_t){HSV_RED}; break;
            case JOY_MODE_ANALOG: hsv_right = (hsv_t){HSV_YELLOW}; break;
            default: hsv_right = (hsv_t){HSV_BLUE}; break;
        }
        
        int brightness = rgb_matrix_get_val();
        if (hsv_left.v > brightness) hsv_left.v = brightness;
        if (hsv_right.v > brightness) hsv_right.v = brightness;
        
        rgb_t rgb_left = hsv_to_rgb(hsv_left);
        rgb_t rgb_right = hsv_to_rgb(hsv_right);
        
        // Blink effect: alternate on/off every 500ms
        bool blink_state = (timer_read() / 500) % 2;
        if (blink_state) {
            rgb_matrix_set_color(LED_INDEX_JOY_MODE_LEFT, rgb_left.r, rgb_left.g, rgb_left.b);
            rgb_matrix_set_color(LED_INDEX_JOY_MODE_RIGHT, rgb_right.r, rgb_right.g, rgb_right.b);
        } else {
            rgb_matrix_set_color(LED_INDEX_JOY_MODE_LEFT, 0, 0, 0);
            rgb_matrix_set_color(LED_INDEX_JOY_MODE_RIGHT, 0, 0, 0);
        }
    }
    return true;
}
