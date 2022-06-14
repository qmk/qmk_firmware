// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "christrotter.h"
#include "rgb_matrix.h"
#include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;

int led_min = 100; 
int led_max = 200;

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max) {
    // this is used for setting layer colours?
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    switch (mode) {
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
            }
            
            break;
        }
    }
}

// __attribute__((weak)) void rgb_matrix_indicator_keymap(void) {}

void matrix_scan_rgb_matrix(void) {
    // other kbs got it working using indicators...
    // void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // switch (get_highest_layer(layer_state)) { 
    /*
    if (userspace_config.rgb_layer_change)
    {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _SYMBOLS:
                rgb_matrix_layer_helper(HSV_ORANGE, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _MOUSE:
                rgb_matrix_layer_helper(HSV_GREEN, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _QWERTY:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
        }
    }
    */
    // info: using one line per key, 3% of flash is used to set one layer of 57 keys per-key rgb
    
    rgb_matrix_set_color(0, 0, 0, 255);
    rgb_matrix_set_color(1, 0, 255, 255);
    rgb_matrix_set_color(2, 0, 0, 255);
    rgb_matrix_set_color(3, 0, 255, 255);
    rgb_matrix_set_color(4, 0, 0, 255);
    rgb_matrix_set_color(5, 0, 255, 255);
    rgb_matrix_set_color(6, 0, 0, 255);
    rgb_matrix_set_color(7, 0, 255, 255);
    rgb_matrix_set_color(8, 0, 0, 255);
    rgb_matrix_set_color(9, 0, 255, 255);
    rgb_matrix_set_color(10, 0, 0, 255);
    rgb_matrix_set_color(11, 0, 255, 255);
    rgb_matrix_set_color(12, 0, 0, 255);
    rgb_matrix_set_color(13, 0, 255, 255);
    rgb_matrix_set_color(14, 0, 0, 255);
    rgb_matrix_set_color(15, 0, 255, 255);
    rgb_matrix_set_color(16, 0, 0, 255);
    rgb_matrix_set_color(17, 0, 255, 255);
    rgb_matrix_set_color(18, 0, 0, 255);
    rgb_matrix_set_color(19, 0, 255, 255);
    rgb_matrix_set_color(20, 0, 0, 255);
    rgb_matrix_set_color(21, 0, 255, 255);
    rgb_matrix_set_color(22, 0, 0, 255);
    rgb_matrix_set_color(23, 0, 255, 255);
    rgb_matrix_set_color(24, 0, 0, 255);
    rgb_matrix_set_color(25, 0, 255, 255);
    rgb_matrix_set_color(26, 0, 0, 255);
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_color(27, 100, 100, 100); // row1,col1 // y
    rgb_matrix_set_color(28, 100, 100, 100);
    rgb_matrix_set_color(29, 100, 100, 100);
    rgb_matrix_set_color(30, 100, 100, 100);
    rgb_matrix_set_color(31, 100, 100, 100);
    rgb_matrix_set_color(32, 0, 100, 100); // row1,col6 // -_
    rgb_matrix_set_color(33, 0, 100, 100); // row2,col6 // ;:
    rgb_matrix_set_color(34, 0, 100, 100); // "'
    rgb_matrix_set_color(35, 100, 100, 100);
    rgb_matrix_set_color(36, 100, 100, 100);
    rgb_matrix_set_color(37, 100, 100, 100);
    rgb_matrix_set_color(38, 100, 100, 100); // row2,col1  
    rgb_matrix_set_color(39, 100, 100, 100); // row3,col1  
    rgb_matrix_set_color(40, 100, 100, 100);
    rgb_matrix_set_color(41, 0, 100, 100); // <,
    rgb_matrix_set_color(42, 0, 100, 100); // >.
    rgb_matrix_set_color(43, 100, 100, 0); // /?
    rgb_matrix_set_color(44, 100, 100, 100); //row3, col6 // not sure what this key should be
    rgb_matrix_set_color(45, 0, 255, 0); // arrow key
    rgb_matrix_set_color(46, 0, 255, 0); // arrow key
    rgb_matrix_set_color(47, 0, 255, 0); // arrow key
    rgb_matrix_set_color(48, 0, 255, 0); // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_color(49, 0, 100, 100); // < // left-most key on kb
    rgb_matrix_set_color(50, 180, 0, 100); // > // key right next to trackball
    rgb_matrix_set_color(51, 100, 0, 255); // cmd // bottom of space/enter key row
    rgb_matrix_set_color(52, 150, 0, 0); // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_color(53, 0, 0, 255); // enter key
    rgb_matrix_set_color(54, 0, 255, 200); // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_color(55, 100, 75, 0); // key below layer button
    rgb_matrix_set_color(56, 0, 100, 255); // far right key, 'below' enter key
    
    // we are not using indicators
    // rgb_matrix_indicator_keymap();
}

void keyboard_post_init_rgb_matrix(void) {
    // what is this used for???
    
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    // pretty sure process_record_user is meant to be used 'when something is pressed, run this code'
    switch (keycode) {
//         case RGB_IDL:  // This allows me to use underglow as layer indication, or as normal
// #if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
//             if (record->event.pressed) {
//                 userspace_config.rgb_matrix_idle_anim ^= 1;
//                 dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
//                 eeconfig_update_user(userspace_config.raw);
//                 if (userspace_config.rgb_matrix_idle_anim) {
//                     rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
//                 }
//             }
// #endif
//             break;
    }
    return true;
}
// we are not using indicat
/*
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) { return true; }
void                       rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) { return; }

#if defined(RGBLIGHT_ENABLE)
    if (!userspace_config.rgb_layer_change)
#else
    if (userspace_config.rgb_layer_change)
#endif
    {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _DEFAULT_LAYER_1:
                rgb_matrix_layer_helper(DEFAULT_LAYER_1_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _DEFAULT_LAYER_2:
                rgb_matrix_layer_helper(DEFAULT_LAYER_2_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _DEFAULT_LAYER_3:
                rgb_matrix_layer_helper(DEFAULT_LAYER_3_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _DEFAULT_LAYER_4:
                rgb_matrix_layer_helper(DEFAULT_LAYER_4_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _SYMBOLS:
                rgb_matrix_layer_helper(HSV_ORANGE, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _MOUSE:
                rgb_matrix_layer_helper(HSV_GREEN, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _QWERTY:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
        }
    }
}

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
void                       rgb_matrix_indicators_user(void) { rgb_matrix_indicators_keymap(); }
*/