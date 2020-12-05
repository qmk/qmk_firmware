#pragma once

#include QMK_KEYBOARD_H
#include "version.h"
#include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"

#if defined(TAP_DANCE_ENABLE)
#    include "tap_dances.h"
#endif  // TAP_DANCE_ENABLE

#if defined(RGB_MATRIX_ENABLE)
#   include "rgb_matrix_user.h"
#endif

#if defined(RGBLIGHT_ENABLE)
#   include "rgb_lighting_user.h"
#endif

#if defined(KEYBOARD_lily58_rev1) & defined(PROTOCOL_LUFA)
#    include "lufa.h"
#    include "split_util.h"
#endif

/* Define layer names */
enum userspace_layers {
    _QWERTY  = 0,
    _COLEMAK,
    _DVORAK,
    _WORKMAN,
    _MODS,
    _LOWER,
    _RAISE,
    _ADJUST,
};

void          matrix_init_keymap(void);
void          shutdown_keymap(void);
void          suspend_power_down_keymap(void);
void          suspend_wakeup_init_keymap(void);
void          matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
void          led_set_keymap(uint8_t usb_led);
void          eeconfig_init_keymap(void);

// clang-format off
typedef union {
    uint32_t raw;
    struct {
        bool    rgb_layer_change     :1;
        bool    nuke_switch          :1;
        bool    rgb_matrix_idle_anim :1;
    };
} userspace_config_t;
// clang-format on

extern userspace_config_t userspace_config;
