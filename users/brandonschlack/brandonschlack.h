#pragma once

#include "quantum.h"
#include "eeprom.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
#   include "tap_dances.h"
#endif // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include "rgb_bs.h"
#endif

// Define layer names
#ifndef IS_MACROPAD
enum bs_layers {
    _MAC = 0,
    _MACFN,
};
#else
enum macropad_layers {
    _NAVI = 0,
    _REEDER,
    _MEDIA,
    _KEYPAD,
    KEYMAP_LAYERS
};
#endif
#define _MAGIC 15

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
layer_state_t layer_state_set_keymap (layer_state_t state);
