#pragma once

#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
#   include "tap_dances.h"
#endif // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include "rgb_bs.h"
#endif

// Define layer names
enum bs_layers {
#if !defined(IS_MACROPAD) // Keyboard Layers
    _BASE = 0,
    _FN = 1,
    _LOWER = 1,
    _RAISE,
#else // Macropad Layers
    _REEDER = 0,
    _MEDIA,
    _NAVI,
    _MACRO,
#endif
    KEYMAP_LAYERS, // Add more layers in keymaps
    _AUDIO = 13, // Layer for Audio controls
    _LIGHT = 14, // Layer for BLight/RGB controls
    _ADJUST = 15 // Change keyboard settings
};

// EEPROM User Config
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
    uint8_t  rgb_theme :2;
  };
} user_config_t;
extern user_config_t user_config;

void matrix_init_keymap(void);
void keyboard_post_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
layer_state_t layer_state_set_keymap(layer_state_t state);
