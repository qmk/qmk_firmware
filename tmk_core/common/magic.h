#ifndef MAGIC_H
#define MAGIC_H

/* NOTE: The order of the bit field is implementation-defined */
typedef union {
    uint8_t raw;
    struct {
        union {
            uint8_t swap_control_capslock_or_capslock_to_control:2;
            struct {
                bool swap_control_capslock:1;
                bool capslock_to_control:1;
            };
        };
        bool swap_lalt_lgui:1;
        bool swap_ralt_rgui:1;
        bool no_gui:1;
        bool swap_grave_esc:1;
        bool swap_backslash_backspace:1;
        bool nkro:1;
    };
} keymap_config_t;

extern keymap_config_t keymap_config;

void magic(void);

#endif
