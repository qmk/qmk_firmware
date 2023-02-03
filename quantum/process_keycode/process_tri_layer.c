// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_tri_layer.h"
#include "action_layer.h"

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3);

#ifndef TRI_LAYER_LOWER_LAYER
#    define TRI_LAYER_LOWER_LAYER 1
#endif
#ifndef TRI_LAYER_RAISE_LAYER
#    define TRI_LAYER_RAISE_LAYER 2
#endif
#ifndef TRI_LAYER_ADJUST_LAYER
#    define TRI_LAYER_ADJUST_LAYER 3
#endif

bool process_tri_layer(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TRI_LAYER_LOWER:
            if (record->event.pressed) {
                layer_on(TRI_LAYER_LOWER_LAYER);
                update_tri_layer(TRI_LAYER_LOWER_LAYER, TRI_LAYER_RAISE_LAYER, TRI_LAYER_ADJUST_LAYER);
            } else {
                layer_off(TRI_LAYER_LOWER_LAYER);
                update_tri_layer(TRI_LAYER_LOWER_LAYER, TRI_LAYER_RAISE_LAYER, TRI_LAYER_ADJUST_LAYER);
            }
            return false;
            break;
        case QK_TRI_LAYER_RAISE:
            if (record->event.pressed) {
                layer_on(TRI_LAYER_RAISE_LAYER);
                update_tri_layer(TRI_LAYER_LOWER_LAYER, TRI_LAYER_RAISE_LAYER, TRI_LAYER_ADJUST_LAYER);
            } else {
                layer_off(TRI_LAYER_RAISE_LAYER);
                update_tri_layer(TRI_LAYER_LOWER_LAYER, TRI_LAYER_RAISE_LAYER, TRI_LAYER_ADJUST_LAYER);
            }
            return false;
            break;
    }
    return true;
}
