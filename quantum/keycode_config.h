#include "eeconfig.h"
#include "keycode.h"

#ifndef KEYCODE_CONFIG_H
#define KEYCODE_CONFIG_H

uint16_t keycode_config(uint16_t keycode);

/* NOTE: Not portable. Bit field order depends on implementation */
typedef union {
    uint16_t raw;
    struct {
        bool swap_control_capslock:1;
        bool capslock_to_control:1;
        bool swap_lalt_lgui:1;
        bool swap_ralt_rgui:1;
        bool no_gui:1;
        bool swap_grave_esc:1;
        bool swap_backslash_backspace:1;
        bool nkro:1;
    };
} keymap_config_t;

extern keymap_config_t keymap_config;

#endif /* KEYCODE_CONFIG_H */
