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

#define JOY_PIN_B GP29
#define JOY_PIN_X GP28
#define JOY_PIN_Y GP27

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

// Joystick keymap
typedef struct {
    uint16_t up;
    uint16_t down;
    uint16_t left;
    uint16_t right;
    uint16_t btn;
} joystick_keymap_t;

// Global configuration (accessible to keymaps if needed)
extern kb_config_t kb_config;

// Functions
void save_kb_config(void);
