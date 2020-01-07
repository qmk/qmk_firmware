#pragma once

#include "quantum.h"

typedef union {
    uint8_t raw;
    struct {
        bool    enable :1;
        bool    breathing : 1;
        uint8_t level  :6;
    };
} backlight_config_t;

// Backlighting
extern backlight_config_t kb_backlight_config;
extern bool kb_backlight_breathing;
void backlight_init_ports(void);
void backlight_set(uint8_t level);
bool is_breathing(void);
void breathing_enable(void);
void breathing_disable(void);
void backlight_config_load(void);
void backlight_config_save(void);
