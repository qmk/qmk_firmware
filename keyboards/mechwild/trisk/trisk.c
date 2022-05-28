// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "trisk.h"

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
		case 1:
            if (clockwise) {
                tap_code(KC_BRIU);
            } else {
                tap_code(KC_BRID);
            }
        break;
    }
    return true;
}
#endif

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4 },
    {  5,  6,  7,  8,  9 },
    {  10, 11, 12, NO_LED, NO_LED}
}, {
	{ 0,  32 }, { 18,  32 }, { 37,  32 }, { 55,  32 }, {  74,  32 }, {  93,  32 }, { 112,  32 }, { 131,  32 }, { 150,  32 }, { 168,  32 }, {  187,  32 }, {  205,  32 }, {  224,  32 }
}, {
    1, 4, 4, 4, 4, 4, 4,4, 4, 4, 4, 4, 1, 2, 2, 2, 2
} };
#endif