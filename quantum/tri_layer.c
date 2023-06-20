// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tri_layer.h"
#include <stdint.h>

static uint8_t tri_layer_lower_layer  = TRI_LAYER_LOWER_LAYER;
static uint8_t tri_layer_upper_layer  = TRI_LAYER_UPPER_LAYER;
static uint8_t tri_layer_adjust_layer = TRI_LAYER_ADJUST_LAYER;

void set_tri_layer_lower_layer(uint8_t layer) {
    tri_layer_lower_layer = layer;
}

void set_tri_layer_upper_layer(uint8_t layer) {
    tri_layer_upper_layer = layer;
}

void set_tri_layer_adjust_layer(uint8_t layer) {
    tri_layer_adjust_layer = layer;
}

void set_tri_layer_layers(uint8_t lower, uint8_t raise, uint8_t adjust) {
    tri_layer_lower_layer  = lower;
    tri_layer_upper_layer  = raise;
    tri_layer_adjust_layer = adjust;
}

uint8_t get_tri_layer_lower_layer(void) {
    return tri_layer_lower_layer;
}

uint8_t get_tri_layer_upper_layer(void) {
    return tri_layer_upper_layer;
}

uint8_t get_tri_layer_adjust_layer(void) {
    return tri_layer_adjust_layer;
}
