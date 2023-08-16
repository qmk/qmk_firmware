// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_tri_layer.h"
#include "tri_layer.h"
#include "action_layer.h"

bool process_tri_layer(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TRI_LAYER_LOWER:
            if (record->event.pressed) {
                layer_on(get_tri_layer_lower_layer());
                update_tri_layer(get_tri_layer_lower_layer(), get_tri_layer_upper_layer(), get_tri_layer_adjust_layer());
            } else {
                layer_off(get_tri_layer_lower_layer());
                update_tri_layer(get_tri_layer_lower_layer(), get_tri_layer_upper_layer(), get_tri_layer_adjust_layer());
            }
            return false;
        case QK_TRI_LAYER_UPPER:
            if (record->event.pressed) {
                layer_on(get_tri_layer_upper_layer());
                update_tri_layer(get_tri_layer_lower_layer(), get_tri_layer_upper_layer(), get_tri_layer_adjust_layer());
            } else {
                layer_off(get_tri_layer_upper_layer());
                update_tri_layer(get_tri_layer_lower_layer(), get_tri_layer_upper_layer(), get_tri_layer_adjust_layer());
            }
            return false;
    }
    return true;
}
