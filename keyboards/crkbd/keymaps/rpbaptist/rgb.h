#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        bool     rgb_layer_indicator : 1;
        bool     rgb_matrix_idle_anim : 1;
        uint8_t  rgb_matrix_active_mode : 4;
        uint8_t  rgb_matrix_idle_mode : 4;
        uint8_t  rgb_matrix_active_speed : 8;
        uint8_t  rgb_matrix_idle_speed : 8;
        uint32_t rgb_matrix_idle_timeout : 32;
    };
} user_config_t;

user_config_t user_config;

const char *rgb_matrix_anim_oled_text(uint8_t mode);
void        rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_min, uint8_t led_max);
void        check_default_layer(uint8_t led_min, uint8_t led_max);
void        rgb_matrix_turn_off_underglow(void);
uint8_t     rgb_matrix_speed_for_mode(uint8_t mode);
bool        rgb_matrix_mode_active(uint8_t mode);
void        rgb_matrix_update_current_mode(uint8_t mode);
void        rgb_matrix_update_dynamic_mode(uint8_t mode);
void        rgb_matrix_update_mode(uint8_t mode);
uint8_t     get_rgb_matrix_active_mode(void);
void        rgb_matrix_toggle_active_mode(void);
uint8_t     get_rgb_matrix_idle_mode(void);
void        rgb_matrix_toggle_simple_passive_mode(void);
void        rgb_matrix_toggle_color_passive_mode(void);
void        rgb_matrix_toggle_underglow_layer_indicator(void);
void        rgb_matrix_toggle_idle_animation_change(void);
void        rgb_matrix_set_gaming_defaults(void);
void        rgb_matrix_set_typing_defaults(void);
void        rgb_matrix_set_defaults(void);
void        matrix_scan_rgb(void);
void        matrix_scan_user(void);
void        eeconfig_init_user(void);
void        keyboard_post_init_user(void);
bool        process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record);
