// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void matrix_init_user(void) {
    setPinOutput(B2);
//    writePinLow(B2);
    writePinHigh(B2);
}

//layer_state_t layer_state_set_user(layer_state_t state) {
//    switch (get_highest_layer(state)) {
//        case 1:
//		    writePinHigh(B2);
//		    break;	
//        case 2:
//		    writePinHigh(B2);
//		    break;
//        case 3:
//		    writePinHigh(B2);
//		    break;	
//        default:
//		    writePinLow(B2);
//        break;
//    }
//    return state;
//}
