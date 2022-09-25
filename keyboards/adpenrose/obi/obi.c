// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "obi.h"

/* Encoder */
#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { 
        return false; 
    }
/* The switch case allows for different encoder mappings on different layers, "default" map gets applied for all unspecified layers */
    switch(get_highest_layer(layer_state)){
        case 1:
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
            break;
        default:
            if (clockwise){
                tap_code(KC_VOLU);
            } else{
                tap_code(KC_VOLD);
            }
            break;
        }
    return true;
}
#endif
