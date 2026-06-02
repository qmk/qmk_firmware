// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "quantum.h"

// Joystick configuration
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

// Joystick mode change keycodes
enum joy_keycodes {
    MD_JOYL = SAFE_RANGE,
    MD_JOYR
};

// Joystick modes
typedef enum {
    JOY_MODE_DIGITAL = 0,
    JOY_MODE_ANALOG = 1,
    JOY_MODE_MOUSE = 2
} joystick_mode_t;

// Configuration structure
typedef union {
    uint8_t raw;
    struct {
        uint8_t joystick_mode_left :2;  // 0=digital, 1=analog, 2=mouse
        uint8_t joystick_mode_right :2; // 0=digital, 1=analog, 2=mouse
    };
} kb_config_t;

// Joystick state tracking
typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool btn;
} joystick_state_t;

// Joystick ADC values
typedef struct {
    uint8_t x;
    uint8_t y;
    bool btn;
} joystick_adc_t;

// Button hold tracking for mouse mode
typedef struct {
    uint32_t press_time;
    bool button_registered;
    bool motion_detected;
} button_hold_t;

// Global configuration (accessible to keymaps if needed)
extern kb_config_t kb_config;

// Functions
void save_kb_config(void);
