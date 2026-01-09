/* Copyright 2021 @ Keychron (https://www.keychron.com)
 * Copyright 2025 @ Raw HID Menu Mod
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "raw_hid.h"

// clang-format off

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// ========================================
// RAW HID PROTOCOL DEFINITIONS
// ========================================

// Device -> Host Event Types
#define HID_EVT_MARKER      0x01
#define EVT_ENCODER_CW      0x01
#define EVT_ENCODER_CCW     0x02
#define EVT_ENCODER_PRESS   0x03
#define EVT_ENCODER_RELEASE 0x04
#define EVT_ENCODER_LONG    0x05
#define EVT_ENCODER_DOUBLE  0x06

// Host -> Device Command Types
#define HID_CMD_MARKER      0x02
#define CMD_SET_MODE        0x10
#define CMD_SET_COLOR       0x11

// ========================================
// ENCODER GESTURE STATE MACHINE
// ========================================

static uint16_t encoder_timer = 0;
static bool encoder_is_held = false;
static uint16_t last_press_time = 0;
static uint8_t press_count = 0;

#define LONG_PRESS_MS 500
#define DOUBLE_TAP_MS 300

// ========================================
// LED STATE MANAGEMENT
// ========================================

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

enum led_modes {
    MODE_DEFAULT = 0,
    MODE_VOLUME,
    MODE_MEDIA,
    MODE_VOICEMEETER,
    MODE_WINDOW_MGMT,
    MODE_APP_LAUNCH
};

static uint8_t current_led_mode = MODE_DEFAULT;
static rgb_color_t current_color = {255, 255, 255};

// ========================================
// KEYMAP LAYOUT (Same as default)
// ========================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_NO,    KC_NO,    RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LCMD,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),
};

// ========================================
// RAW HID HELPER FUNCTIONS
// ========================================

void send_encoder_event(uint8_t event_type, uint8_t value) {
    uint8_t packet[32] = {0};
    packet[0] = HID_EVT_MARKER;
    packet[1] = event_type;
    packet[2] = 0; // Encoder ID (always 0 for main knob)
    packet[3] = value;
    packet[4] = (uint8_t)(timer_read() & 0xFF);       // Timestamp LSB
    packet[5] = (uint8_t)((timer_read() >> 8) & 0xFF); // Timestamp MSB
    raw_hid_send(packet, 32);
}

// ========================================
// ENCODER ROTATION HANDLING
// ========================================

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Send rotation event to host
        send_encoder_event(clockwise ? EVT_ENCODER_CW : EVT_ENCODER_CCW, 1);
        
        // Optional: Still allow FN layer to control RGB brightness
        if (get_highest_layer(layer_state) == MAC_FN || get_highest_layer(layer_state) == WIN_FN) {
            if (clockwise) {
                rgb_matrix_increase_val();
            } else {
                rgb_matrix_decrease_val();
            }
        }
    }
    return false;
}

// ========================================
// ENCODER BUTTON GESTURE DETECTION
// ========================================

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Encoder button is mapped to KC_MUTE in the layout
    if (keycode == KC_MUTE) {
        if (record->event.pressed) {
            // Button pressed
            encoder_timer = timer_read();
            encoder_is_held = true;
            
            // Check for double-tap
            if (timer_elapsed(last_press_time) < DOUBLE_TAP_MS && press_count == 1) {
                send_encoder_event(EVT_ENCODER_DOUBLE, 0);
                press_count = 0; // Reset to prevent triple-tap false positive
            } else {
                press_count = 1;
                send_encoder_event(EVT_ENCODER_PRESS, 0);
            }
            last_press_time = timer_read();
            
        } else {
            // Button released
            uint16_t hold_time = timer_elapsed(encoder_timer);
            
            if (encoder_is_held && hold_time > LONG_PRESS_MS) {
                send_encoder_event(EVT_ENCODER_LONG, 0);
            } else {
                send_encoder_event(EVT_ENCODER_RELEASE, 0);
            }
            encoder_is_held = false;
        }
        return false; // Prevent default KC_MUTE behavior
    }
    return true;
}

// ========================================
// RAW HID RECEIVE (Host -> Device Commands)
// ========================================

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Check if this is our custom protocol (not VIA)
    if (data[0] == HID_CMD_MARKER) {
        uint8_t sub_command = data[1];
        
        switch (sub_command) {
            case CMD_SET_MODE:
                current_led_mode = data[2];
                break;
                
            case CMD_SET_COLOR:
                current_color.r = data[2];
                current_color.g = data[3];
                current_color.b = data[4];
                break;
        }
    }
    // If not our protocol, let VIA handle it (if VIA is processing Raw HID)
}

// ========================================
// RGB MATRIX CUSTOM INDICATORS
// ========================================

bool rgb_matrix_indicators_user(void) {
    // Apply custom LED patterns based on mode
    switch (current_led_mode) {
        case MODE_VOLUME:
            // Light up encoder knob area (LED index 67, adjust as needed)
            rgb_matrix_set_color(67, current_color.r, current_color.g, current_color.b);
            break;
            
        case MODE_MEDIA:
            // Example: Light up media keys
            rgb_matrix_set_color(67, current_color.r, current_color.g, current_color.b);
            rgb_matrix_set_color(7, current_color.r, current_color.g, current_color.b);  // MPRV
            rgb_matrix_set_color(8, current_color.r, current_color.g, current_color.b);  // MPLY
            rgb_matrix_set_color(9, current_color.r, current_color.g, current_color.b);  // MNXT
            break;
            
        case MODE_VOICEMEETER:
            // Custom color for Voicemeeter mode
            rgb_matrix_set_color(67, current_color.r, current_color.g, current_color.b);
            break;
            
        case MODE_WINDOW_MGMT:
            // Custom color for window management
            rgb_matrix_set_color(67, current_color.r, current_color.g, current_color.b);
            break;
            
        case MODE_APP_LAUNCH:
            // Custom color for app launcher
            rgb_matrix_set_color(67, current_color.r, current_color.g, current_color.b);
            break;
            
        case MODE_DEFAULT:
        default:
            // Normal RGB matrix behavior
            break;
    }
    
    return false;
}
