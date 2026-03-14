// Copyright 2025 FabiClawZ (@FFS2309)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "layer_select_4.h"



void render_layer_status(void){
    led_t led_state = host_keyboard_led_state();
    char layer_output[sizeof(layer_base)];
    for(int i = 0; i < sizeof(layer_output); i++){
        layer_output[i] = layer_base[i];
        if(IS_LAYER_ON(0)) layer_output[i] ^= layer_en_1[i];
        if(IS_LAYER_ON(1)) layer_output[i] ^= layer_en_2[i];
        if(IS_LAYER_ON(2)) layer_output[i] ^= layer_en_3[i];
        if(IS_LAYER_ON(3)) layer_output[i] ^= layer_en_4[i];
        if(led_state.num_lock) layer_output[i] ^= indicator_en_num[i];
        if(led_state.caps_lock) layer_output[i] ^= indicator_en_caps[i];
    }
    oled_write_raw(layer_output, sizeof(layer_output));
}

