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
    _WIN,
    _WINFN
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

void keyboard_post_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap (layer_state_t state);

// typedef union {
//     uint32_t raw;
//     struct {
//         uint8_t  os_mode          :4;
//     };
// } userspace_config_t;

// extern userspace_config_t userspace_config;
