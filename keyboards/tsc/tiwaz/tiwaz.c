// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "tiwaz.h"
#include "analog.h"
#include "gpio.h"
#include "split_util.h"
#include "transactions.h"

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

// Button hold tracking
static button_hold_t local_button_hold = {0, false, false};
static button_hold_t remote_button_hold = {0, false, false};

// Initialization tracking
static uint32_t init_timeout = 0;
static bool init_completed = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case MD_JOYL:
                kb_config.joystick_mode_left = (kb_config.joystick_mode_left + 1) % 3;
                save_kb_config();
                return false;

            case MD_JOYR:
                kb_config.joystick_mode_right = (kb_config.joystick_mode_right + 1) % 3;
                save_kb_config();
                return false;
        }
    }
    return true;
}

void save_kb_config(void) {
    eeconfig_update_kb(kb_config.raw);
    transaction_rpc_send(RPC_KB_CONFIG, sizeof(kb_config.raw), &kb_config.raw);
}

static void handle_joystick(uint8_t mode, joystick_adc_t* adc, joystick_state_t* state, button_hold_t* btn_hold,
                            int js_btn, keypos_t up, keypos_t down, keypos_t left, keypos_t right, keypos_t btn) {
    layer_state_t layer = get_highest_layer(layer_state | default_layer_state);

    if (mode == JOY_MODE_DIGITAL) { // DIGITAL mode
        int8_t sx = (int8_t)adc->x;
        int8_t sy = (int8_t)adc->y;

        // UP
        if (sy < -JOY_DIGITAL_ON && !state->up) {
            register_code16(keymap_key_to_keycode(layer, up));
            state->up = true;
        } else if (sy > -JOY_DIGITAL_OFF && state->up) {
            unregister_code16(keymap_key_to_keycode(layer, up));
            state->up = false;
        }

        // DOWN
        if (sy > JOY_DIGITAL_ON && !state->down) {
            register_code16(keymap_key_to_keycode(layer, down));
            state->down = true;
        } else if (sy < JOY_DIGITAL_OFF && state->down) {
            unregister_code16(keymap_key_to_keycode(layer, down));
            state->down = false;
        }

        // LEFT
        if (sx < -JOY_DIGITAL_ON && !state->left) {
            register_code16(keymap_key_to_keycode(layer, left));
            state->left = true;
        } else if (sx > -JOY_DIGITAL_OFF && state->left) {
            unregister_code16(keymap_key_to_keycode(layer, left));
            state->left = false;
        }

        // RIGHT
        if (sx > JOY_DIGITAL_ON && !state->right) {
            register_code16(keymap_key_to_keycode(layer, right));
            state->right = true;
        } else if (sx < JOY_DIGITAL_OFF && state->right) {
            unregister_code16(keymap_key_to_keycode(layer, right));
            state->right = false;
        }

        // BUTTON
        if (adc->btn && !state->btn) {
            register_code16(keymap_key_to_keycode(layer, btn));
            state->btn = true;
        } else if (!adc->btn && state->btn) {
            unregister_code16(keymap_key_to_keycode(layer, btn));
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
        // Map analog values to mouse movement keycodes
        int8_t sx = (int8_t)adc->x;
        int8_t sy = (int8_t)adc->y;
        
        // Detect motion while button is held
        if (state->btn && !btn_hold->motion_detected) {
            if (sx < -JOY_DIGITAL_ON || sx > JOY_DIGITAL_ON || 
                sy < -JOY_DIGITAL_ON || sy > JOY_DIGITAL_ON) {
                btn_hold->motion_detected = true;
            }
        }
        
        // Handle X-axis (LEFT/RIGHT)
        if (sx < -JOY_DIGITAL_ON && !state->left) {
            register_code(MS_LEFT);
            state->left = true;
        } else if (sx > -JOY_DIGITAL_OFF && state->left) {
            unregister_code(MS_LEFT);
            state->left = false;
        }
        
        if (sx > JOY_DIGITAL_ON && !state->right) {
            register_code(MS_RGHT);
            state->right = true;
        } else if (sx < JOY_DIGITAL_OFF && state->right) {
            unregister_code(MS_RGHT);
            state->right = false;
        }
        
        // Handle Y-axis (UP/DOWN)
        if (sy < -JOY_DIGITAL_ON && !state->up) {
            register_code(MS_UP);
            state->up = true;
        } else if (sy > -JOY_DIGITAL_OFF && state->up) {
            unregister_code(MS_UP);
            state->up = false;
        }
        
        if (sy > JOY_DIGITAL_ON && !state->down) {
            register_code(MS_DOWN);
            state->down = true;
        } else if (sy < JOY_DIGITAL_OFF && state->down) {
            unregister_code(MS_DOWN);
            state->down = false;
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
                if (sx < -JOY_DIGITAL_ON || sx > JOY_DIGITAL_ON || 
                    sy < -JOY_DIGITAL_ON || sy > JOY_DIGITAL_ON) {
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
}

// Housekeeping task
void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        if (!init_completed && timer_elapsed32(init_timeout) > 2000) {
            transaction_rpc_send(RPC_KB_CONFIG, sizeof(kb_config.raw), &kb_config.raw);
            init_completed = true;
        }

        static uint32_t last_sync = 0;
        if (is_transport_connected() && timer_elapsed32(last_sync) > JOY_POLLING_INTERVAL) {
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
                JS_0, LJOY_UP_POS, LJOY_DOWN_POS, LJOY_LEFT_POS, LJOY_RIGHT_POS, LJOY_BTN_POS);
            handle_joystick(kb_config.joystick_mode_right, &remote_joystick_axis, &remote_joystick_state, &remote_button_hold,
                JS_1, RJOY_UP_POS, RJOY_DOWN_POS, RJOY_LEFT_POS, RJOY_RIGHT_POS, RJOY_BTN_POS);
            
            // Set joystick axes only for analog mode
            joystick_set_axis(0, kb_config.joystick_mode_left == JOY_MODE_ANALOG ? local_joystick_axis.x : 0);
            joystick_set_axis(1, kb_config.joystick_mode_left == JOY_MODE_ANALOG ? local_joystick_axis.y : 0);
            joystick_set_axis(2, kb_config.joystick_mode_right == JOY_MODE_ANALOG ? remote_joystick_axis.x : 0);
            joystick_set_axis(3, kb_config.joystick_mode_right == JOY_MODE_ANALOG ? remote_joystick_axis.y : 0);
        } else {
            handle_joystick(kb_config.joystick_mode_left, &remote_joystick_axis, &remote_joystick_state, &remote_button_hold,
                JS_0, LJOY_UP_POS, LJOY_DOWN_POS, LJOY_LEFT_POS, LJOY_RIGHT_POS, LJOY_BTN_POS);
            handle_joystick(kb_config.joystick_mode_right, &local_joystick_axis, &local_joystick_state, &local_button_hold,
                JS_1, RJOY_UP_POS, RJOY_DOWN_POS, RJOY_LEFT_POS, RJOY_RIGHT_POS, RJOY_BTN_POS);
            
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
        uint8_t mode_right = is_keyboard_left() ? kb_config.joystick_mode_left : kb_config.joystick_mode_right;
        
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
        
        rgb_matrix_set_color(LED_INDEX_JOY_MODE_LEFT, rgb_left.r, rgb_left.g, rgb_left.b);
        rgb_matrix_set_color(LED_INDEX_JOY_MODE_RIGHT, rgb_right.r, rgb_right.g, rgb_right.b);
    }
    return true;
}
