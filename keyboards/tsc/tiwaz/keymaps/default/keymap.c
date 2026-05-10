// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "analog.h"
#include "color.h"
#include "eeprom.h"
#include "split_util.h"
#include "transactions.h"

// Default
#define TS_CUT C(KC_X)
#define TS_CPY C(KC_C)
#define TS_PST C(KC_V)
#define TS_LCK G(KC_L)
#define TS_MIC C(S(KC_M))

// Fruit
#define TSF_CUT G(KC_X)
#define TSF_CPY G(KC_C)
#define TSF_PST G(KC_V)
#define TSF_LCK G(C(KC_Q))
#define TSF_MIC G(S(KC_M))

// Joysticks
#define EEPROM_ADDR_JOY_LEFT    0
#define EEPROM_ADDR_JOY_RIGHT   1
#define LED_INDEX_JOY_MODE      6
#define JOY_POLLING_INTERVAL   10

#define JOY_ADC_SHIFT           2
#define JOY_CENTER            127
#define JOY_DIGITAL_ON         50
#define JOY_DIGITAL_OFF        40

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

#define JOY_PIN_X GP27
#define JOY_PIN_Y GP28
#define JOY_PIN_B GP29

typedef union {
    uint8_t raw;
    struct {
        bool joystick_digital_left :1;
        bool joystick_digital_right :1;
    };
} user_config_t;

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
    .joystick_digital_left = true,
    .joystick_digital_right = true
};

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
    TS_JOYL = SAFE_RANGE,
    TS_JOYR
};

enum layers {
    DF,
    MC,
    FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DF] = LAYOUT(
        KC_ESC ,KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_MPLY,KC_MPLY,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,KC_DEL ,
        TS_CUT ,KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_HOME,KC_MNXT,KC_MNXT,KC_PGUP,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_RBRC,
        TS_CPY ,KC_CAPS,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_END ,KC_MPRV,KC_MPRV,KC_PGDN,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_ENT ,
        TS_PST ,KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_SLEP,KC_MUTE,KC_MUTE,KC_SLEP,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_UP  ,KC_RSFT,
        TS_LCK ,KC_LCTL,MO(FN) ,PDF(MC),KC_LGUI,KC_LALT,KC_SPC         ,TS_MIC ,TS_MIC         ,KC_BSPC,KC_PSCR,TG(FN) ,KC_BSLS,KC_LEFT,KC_DOWN,KC_RGHT,
        KC_F14 ,KC_F15 ,KC_F16 ,KC_F17 ,KC_F18 ,KC_F19 ,KC_F20 ,KC_F21 ,KC_F22 ,KC_F23
    ),
    [MC] = LAYOUT(
        KC_ESC ,KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_MPLY,KC_MPLY,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,KC_DEL ,
        TSF_CUT,KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_HOME,KC_MNXT,KC_MNXT,KC_PGUP,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_RBRC,
        TSF_CPY,KC_CAPS,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_END ,KC_MPRV,KC_MPRV,KC_PGDN,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_ENT ,
        TSF_PST,KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_SLEP,KC_MUTE,KC_MUTE,KC_SLEP,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_UP  ,KC_RSFT,
        TSF_LCK,KC_LCTL,MO(FN) ,PDF(DF),KC_LGUI,KC_LALT,KC_SPC         ,TSF_MIC,TSF_MIC        ,KC_BSPC,KC_PSCR,TG(FN) ,KC_BSLS,KC_LEFT,KC_DOWN,KC_RGHT,
        KC_F14 ,KC_F15 ,KC_F16 ,KC_F17 ,KC_F18 ,KC_F19 ,KC_F20 ,KC_F21 ,KC_F22 ,KC_F23
    ),
    [FN] = LAYOUT(
        RM_TOGG,XXXXXXX,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,QK_BOOT,QK_BOOT,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PMNS,KC_PSLS,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_P7  ,KC_P8  ,KC_P9  ,KC_PPLS,KC_PSLS,
        RM_NEXT,RM_SPDU,RM_HUEU,RM_SATU,RM_VALU,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_P4  ,KC_P5  ,KC_P6  ,KC_PPLS,KC_PAST,
        RM_PREV,RM_SPDD,RM_HUED,RM_SATD,RM_VALD,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_P1  ,KC_P2  ,KC_P3  ,KC_PENT,KC_PAST,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX        ,TS_JOYR,TS_JOYL        ,XXXXXXX,XXXXXXX,XXXXXXX,KC_P0  ,KC_COMM,KC_PENT,KC_NUM ,
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
            case TS_JOYL:
                user_config.joystick_digital_left = !user_config.joystick_digital_left;
                save_user_eeprom();
                return false;

            case TS_JOYR:
                user_config.joystick_digital_right = !user_config.joystick_digital_right;
                save_user_eeprom();
                return false;
        }
    }
    return true;
}

void set_status_led(uint8_t i, bool digital) {
    hsv_t hsv = digital ? (hsv_t){HSV_BLUE} : (hsv_t){HSV_YELLOW};
    int brightness = rgb_matrix_get_val();
    if (hsv.v > brightness) hsv.v = brightness;
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_user(void) {
    set_status_led(LED_INDEX_JOY_MODE, is_keyboard_left() ? user_config.joystick_digital_left : user_config.joystick_digital_right);
    return false;
}

static void handle_joystick(bool digital_mode, joystick_adc_t* adc, joystick_state_t* state, int js_btn,
                            keypos_t up, keypos_t down, keypos_t left, keypos_t right, keypos_t btn) {
    layer_state_t layer = get_highest_layer(layer_state | default_layer_state);

    if (digital_mode) { // DIGITAL mode
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

    } else { // ANALOG mode
        if (adc->btn && !state->btn) {
            register_joystick_button(js_btn);
            state->btn = true;
        } else if (!adc->btn && state->btn) {
            unregister_joystick_button(js_btn);
            state->btn = false;
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
    setPinInputHigh(JOY_PIN_B);

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
            .y = JOY_CENTER - (analogReadPin(JOY_PIN_Y) >> JOY_ADC_SHIFT),
            .btn = !readPin(JOY_PIN_B)
        };

        if (is_keyboard_left()) {
            handle_joystick(user_config.joystick_digital_left, &local_joystick_axis, &local_joystick_state,
                JS_0, LJOY_UP_POS, LJOY_DOWN_POS, LJOY_LEFT_POS, LJOY_RIGHT_POS, LJOY_BTN_POS);
            handle_joystick(user_config.joystick_digital_right, &remote_joystick_axis, &remote_joystick_state,
                JS_1, RJOY_UP_POS, RJOY_DOWN_POS, RJOY_LEFT_POS, RJOY_RIGHT_POS, RJOY_BTN_POS);
            joystick_set_axis(0, user_config.joystick_digital_left  ? 0 : local_joystick_axis.x);
            joystick_set_axis(1, user_config.joystick_digital_left  ? 0 : local_joystick_axis.y);
            joystick_set_axis(2, user_config.joystick_digital_right ? 0 : remote_joystick_axis.x);
            joystick_set_axis(3, user_config.joystick_digital_right ? 0 : remote_joystick_axis.y);
        } else {
            handle_joystick(user_config.joystick_digital_left, &remote_joystick_axis, &remote_joystick_state,
                JS_0, LJOY_UP_POS, LJOY_DOWN_POS, LJOY_LEFT_POS, LJOY_RIGHT_POS, LJOY_BTN_POS);
            handle_joystick(user_config.joystick_digital_right, &local_joystick_axis, &local_joystick_state,
                JS_1, RJOY_UP_POS, RJOY_DOWN_POS, RJOY_LEFT_POS, RJOY_RIGHT_POS, RJOY_BTN_POS);
            joystick_set_axis(0, user_config.joystick_digital_left  ? 0 : remote_joystick_axis.x);
            joystick_set_axis(1, user_config.joystick_digital_left  ? 0 : remote_joystick_axis.y);
            joystick_set_axis(2, user_config.joystick_digital_right ? 0 : local_joystick_axis.x);
            joystick_set_axis(3, user_config.joystick_digital_right ? 0 : local_joystick_axis.y);
        }
    } else {
        remote_joystick_axis = (joystick_adc_t){
            .x = JOY_CENTER - (analogReadPin(JOY_PIN_X) >> JOY_ADC_SHIFT),
            .y = JOY_CENTER - (analogReadPin(JOY_PIN_Y) >> JOY_ADC_SHIFT),
            .btn = !readPin(JOY_PIN_B) // Active low
        };
    }
}
