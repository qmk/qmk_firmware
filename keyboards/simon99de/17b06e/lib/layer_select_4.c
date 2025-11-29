// Copyright 2025 FabiClawZ (@FFS2309)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "oled_driver.h"
#include "action_layer.h"
#include QMK_KEYBOARD_H
#include "progmem.h"
#include "layer_select_4.h"
#include "print.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

void xor_layers(char * layer1, const char * layer2){
    if(sizeof(layer1) != sizeof(layer2)) return;
    for(int i = 0; i < sizeof(layer1); i++){
        layer1[i] = layer1[i] ^ layer2[i];
    }
};


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

