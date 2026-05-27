// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "analog.h"
#include "color.h"
#include "eeprom.h"
#include "gpio.h"
#include "split_util.h"
#include "transactions.h"

// Joysticks
#define EEPROM_ADDR_JOY_LEFT       0
#define EEPROM_ADDR_JOY_RIGHT      1
#define LED_INDEX_JOY_MODE_LEFT    5
#define LED_INDEX_JOY_MODE_RIGHT  49
#define JOY_POLLING_INTERVAL      10
#define MOUSE_BUTTON_HOLD_MS     500

#define JOY_ADC_SHIFT              2
#define JOY_CENTER               127
#define JOY_DIGITAL_ON            50
#define JOY_DIGITAL_OFF           40

#define LJOY_UP_POS    (keypos_t){0, 5}
#define LJOY_DOWN_POS  (keypos_t){1, 5}
#define LJOY_LEFT_POS  (keypos_t){2, 5}
#define LJOY_RIGHT_POS (keypos_t){3, 5}
#define LJOY_BTN_POS   (keypos_t){4, 5}

#define RJOY_UP_POS    (keypos_t){5, 5}
#define RJOY_DOWN_POS  (keypos_t){6, 5}
#define RJOY_LEFT_POS  (keypos_t){7, 5}
#define RJOY_RIGHT_POS (keypos_t){8, 5}
#define RJOY_BTN_POS   (keypos_t){0, 11}

#define JOY_PIN_B GP29
#define JOY_PIN_X GP28
#define JOY_PIN_Y GP27

typedef union {
    uint8_t raw;
    struct {
        uint8_t joystick_mode_left :2;  // 0=digital, 1=analog, 2=mouse
        uint8_t joystick_mode_right :2; // 0=digital, 1=analog, 2=mouse
    };
} user_config_t;

// Joystick modes
enum joystick_mode {
    JOY_MODE_DIGITAL = 0,
    JOY_MODE_ANALOG = 1,
    JOY_MODE_MOUSE = 2
};

typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool btn;
} joystick_state_t;

typedef struct {
    uint8_t x;
    uint8_t y;
    bool btn;
} joystick_adc_t;

user_config_t user_config = {
    .joystick_mode_left = JOY_MODE_DIGITAL,
    .joystick_mode_right = JOY_MODE_DIGITAL
};

typedef struct {
    uint32_t press_time;
    bool button_registered;
    bool motion_detected;
} button_hold_t;

button_hold_t local_button_hold = {0, false, false};
button_hold_t remote_button_hold = {0, false, false};

joystick_state_t local_joystick_state = {
    .up = false,
    .down = false,
    .left = false,
    .right = false,
    .btn = false
};

joystick_state_t remote_joystick_state = {
    .up = false,
    .down = false,
    .left = false,
    .right = false,
    .btn = false
};

joystick_adc_t local_joystick_axis = {
    .x = JOY_CENTER,
    .y = JOY_CENTER,
    .btn = false
};

joystick_adc_t remote_joystick_axis = {
    .x = JOY_CENTER,
    .y = JOY_CENTER,
    .btn = false
};

static uint32_t init_timeout = 0;
static bool init_completed = false;

enum joy_keycodes {
    MD_JOYL = SAFE_RANGE,
    MD_JOYR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC ,KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_MPLY,KC_MPLY,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,KC_DEL ,
        KC_CUT ,KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_HOME,KC_MNXT,KC_MNXT,KC_PGUP,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_RBRC,
        KC_COPY,KC_CAPS,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_END ,KC_MPRV,KC_MPRV,KC_PGDN,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_ENT ,
        KC_PSTE,KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_MUTE,KC_VOLU,KC_VOLU,KC_MUTE,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_UP  ,KC_RSFT,
        KC_UNDO,KC_LCTL,MO(1)  ,KC_MENU,KC_LGUI,KC_LALT,KC_SPC         ,KC_VOLD,KC_VOLD        ,KC_BSPC,KC_PSCR,TG(1)  ,KC_BSLS,KC_LEFT,KC_DOWN,KC_RGHT,
        KC_F14 ,KC_F15 ,KC_F16 ,KC_F17 ,KC_F18 ,KC_F19 ,KC_F20 ,KC_F21 ,KC_F22 ,KC_F23
    ),
    [1] = LAYOUT(
        RM_TOGG,XXXXXXX,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,QK_BOOT,QK_BOOT,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PMNS,KC_PSLS,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_P7  ,KC_P8  ,KC_P9  ,KC_PPLS,KC_PSLS,
        RM_NEXT,RM_SPDU,RM_HUEU,RM_SATU,RM_VALU,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_P4  ,KC_P5  ,KC_P6  ,KC_PPLS,KC_PAST,
        RM_PREV,RM_SPDD,RM_HUED,RM_SATD,RM_VALD,XXXXXXX,XXXXXXX,MD_JOYL,XXXXXXX,XXXXXXX,MD_JOYR,XXXXXXX,XXXXXXX,KC_P1  ,KC_P2  ,KC_P3  ,KC_PENT,KC_PAST,
        KC_AGIN,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX        ,XXXXXXX,XXXXXXX        ,XXXXXXX,XXXXXXX,TG(1)  ,KC_P0  ,KC_PDOT,KC_PENT,KC_NUM ,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
    )
};

void save_user_eeprom(void) {
    eeconfig_update_user(user_config.raw);
    transaction_rpc_send(RPC_USER_CONFIG, sizeof(user_config.raw), &user_config.raw);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case MD_JOYL:
                user_config.joystick_mode_left = (user_config.joystick_mode_left + 1) % 3;
                save_user_eeprom();
                return false;

            case MD_JOYR:
                user_config.joystick_mode_right = (user_config.joystick_mode_right + 1) % 3;
                save_user_eeprom();
                return false;
        }
    }
    return true;
}

bool rgb_matrix_indicators_user(void) {
    if (get_highest_layer(layer_state) == 1) {
        uint8_t mode_left = is_keyboard_left() ? user_config.joystick_mode_left : user_config.joystick_mode_right;
        uint8_t mode_right = is_keyboard_left() ? user_config.joystick_mode_left : user_config.joystick_mode_right;
        
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
    return false;
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

void receive_joystick(uint8_t in_len, const void *in_buf, uint8_t out_len, void *out_buf) {
    if (out_len == sizeof(joystick_adc_t)) {
        memcpy(out_buf, &remote_joystick_axis, out_len);
    }
}

void receive_user_config(uint8_t in_len, const void *in_buf, uint8_t out_len, void *out_buf) {
    if (in_len == sizeof(user_config_t)) {
        memcpy(&user_config, in_buf, in_len);
    }
}

void keyboard_post_init_user(void) {
    gpio_set_pin_input_high(JOY_PIN_B);

    if (is_keyboard_master()) {
        init_timeout = timer_read32();
        user_config.raw = eeconfig_read_user();
    }
    transaction_register_rpc(RPC_JOYSTICK_AXES, receive_joystick);
    transaction_register_rpc(RPC_USER_CONFIG, receive_user_config);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        if (!init_completed && timer_elapsed32(init_timeout) > 2000) {
            transaction_rpc_send(RPC_USER_CONFIG, sizeof(user_config.raw), &user_config.raw);
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
            handle_joystick(user_config.joystick_mode_left, &local_joystick_axis, &local_joystick_state, &local_button_hold,
                JS_0, LJOY_UP_POS, LJOY_DOWN_POS, LJOY_LEFT_POS, LJOY_RIGHT_POS, LJOY_BTN_POS);
            handle_joystick(user_config.joystick_mode_right, &remote_joystick_axis, &remote_joystick_state, &remote_button_hold,
                JS_1, RJOY_UP_POS, RJOY_DOWN_POS, RJOY_LEFT_POS, RJOY_RIGHT_POS, RJOY_BTN_POS);
            
            // Set joystick axes only for analog mode
            joystick_set_axis(0, user_config.joystick_mode_left == JOY_MODE_ANALOG ? local_joystick_axis.x : 0);
            joystick_set_axis(1, user_config.joystick_mode_left == JOY_MODE_ANALOG ? local_joystick_axis.y : 0);
            joystick_set_axis(2, user_config.joystick_mode_right == JOY_MODE_ANALOG ? remote_joystick_axis.x : 0);
            joystick_set_axis(3, user_config.joystick_mode_right == JOY_MODE_ANALOG ? remote_joystick_axis.y : 0);
        } else {
            handle_joystick(user_config.joystick_mode_left, &remote_joystick_axis, &remote_joystick_state, &remote_button_hold,
                JS_0, LJOY_UP_POS, LJOY_DOWN_POS, LJOY_LEFT_POS, LJOY_RIGHT_POS, LJOY_BTN_POS);
            handle_joystick(user_config.joystick_mode_right, &local_joystick_axis, &local_joystick_state, &local_button_hold,
                JS_1, RJOY_UP_POS, RJOY_DOWN_POS, RJOY_LEFT_POS, RJOY_RIGHT_POS, RJOY_BTN_POS);
            
            // Set joystick axes only for analog mode
            joystick_set_axis(0, user_config.joystick_mode_left == JOY_MODE_ANALOG ? remote_joystick_axis.x : 0);
            joystick_set_axis(1, user_config.joystick_mode_left == JOY_MODE_ANALOG ? remote_joystick_axis.y : 0);
            joystick_set_axis(2, user_config.joystick_mode_right == JOY_MODE_ANALOG ? local_joystick_axis.x : 0);
            joystick_set_axis(3, user_config.joystick_mode_right == JOY_MODE_ANALOG ? local_joystick_axis.y : 0);
        }
    } else {
        remote_joystick_axis = (joystick_adc_t){
            .x = JOY_CENTER - (analogReadPin(JOY_PIN_X) >> JOY_ADC_SHIFT),
            .y = (analogReadPin(JOY_PIN_Y) >> JOY_ADC_SHIFT) - JOY_CENTER,
            .btn = !gpio_read_pin(JOY_PIN_B) // Active low
        };
    }
}
