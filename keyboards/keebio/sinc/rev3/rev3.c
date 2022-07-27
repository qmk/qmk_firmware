/* Copyright 2022 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "sinc.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // Left Half
    { 53, 52, 16, 15, 14, 13, 12, 11, 10 },
    { 50, 51, 17, 18, 19, 20, 21, 22, NO_LED },
    { 49, 48, 28, 27, 26, 25, 24, 23, NO_LED },
    { 46, 47, 29, NO_LED, 30, 31, 32, 33, 34},
    { 45, 43, 42, 40, 39, 37, NO_LED, 36, NO_LED },
    { 54, NO_LED, 0, 2, 3, 5, 6, 7, 9 },
    // Right Half
    { 68, 69, 70, 71, 72, 73, 74, 75, 76 },
    { 85, 84, 83, 82, 81, 80, 79, 78, 77 },
    { 86, 87, 88, 89, 90, 91, NO_LED, 92, 93 },
    { 101, 100, 99, 98, 97, NO_LED, 96, 95, 94},
    { NO_LED, 103, 105, 106, 107, 109, 110, 112 },
    { NO_LED, 67, 65, 64, 62, 61, 59, 58, 57 }
}, {
    // LED Index to Physical Position
    // Left Half
    { 30,0  }, { 42,6  }, { 45,0  }, { 58,0  }, { 67,6  }, { 70,0  }, { 82,0  }, { 97,0  }, {103,6  },
    {109,0  }, {103,15 }, { 91,15 }, { 79,15 }, { 67,15 }, { 54,15 }, { 42,15 }, { 30,15 }, { 33,27 },
    { 48,27 }, { 61,27 }, { 73,27 }, { 85,27 }, { 97,27 }, {100,40 }, { 88,40 }, { 76,40 }, { 64,40 },
    { 51,40 }, { 35,40 }, { 38,52 }, { 58,52 }, { 70,52 }, { 82,52 }, { 94,52 }, {106,52 }, {106,64 },
    { 98,64 }, { 77,64 }, { 67,64 }, { 62,64 }, { 47,64 }, { 39,64 }, { 32,64 }, { 12,64 }, {  6,64 },
    {  0,64 }, {  0,52 }, { 12,52 }, { 12,40 }, {  0,40 }, {  0,27 }, { 12,27 }, { 12,15 }, {  0,15 },
    {  0,0  }, {  9,0  },
    // Right Half
    {224,6  }, {224,0  }, {212,0  }, {197,0  }, {191,6  }, {185,0  }, {173,0  },
    {166,6  }, {160,0  }, {145,0  }, {139,6  }, {133,0  }, {127,15 }, {139,15 }, {151,15 }, {163,15 },
    {176,15 }, {188,15 }, {200,15 }, {212,15 }, {224,15 }, {224,27 }, {209,27 }, {194,27 }, {182,27 },
    {170,27 }, {157,27 }, {145,27 }, {133,27 }, {121,27 }, {124,40 }, {136,40 }, {148,40 }, {160,40 },
    {173,40 }, {185,40 }, {204,40 }, {224,40 }, {224,52 }, {212,52 }, {195,52 }, {179,52 }, {166,52 },
    {154,52 }, {142,52 }, {130,52 }, {133,64 }, {141,64 }, {160,64 }, {163,64 }, {176,64 }, {188,64 },
    {194,64 }, {200,64 }, {212,64 }, {218,64 }, {224,64 }
}, {
    // LED Index to Flag
    // Left Half
    4, 2, 4, 4, 2, 4, 4, 4, 2, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    2, 4, 4, 2, 4, 4, 2, 4,
    4, 2, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
    // Right Half
    2, 4, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    2, 4, 2, 4, 4, 4, 2, 4, 4, 2, 4
} };

#    if defined(VIA_ENABLE) && defined(VIA_CUSTOM_LIGHTING_ENABLE)

// VIA supports only 4 discrete values for effect speed; map these to some
// useful speed values for RGB Matrix.
enum speed_values {
    RGBLIGHT_SPEED_0 = UINT8_MAX / 16, // not 0 to avoid really slow effects
    RGBLIGHT_SPEED_1 = UINT8_MAX / 4,
    RGBLIGHT_SPEED_2 = UINT8_MAX / 2,     // matches the default value
    RGBLIGHT_SPEED_3 = UINT8_MAX / 4 * 3, // UINT8_MAX is really fast
};

static uint8_t speed_from_rgblight(uint8_t rgblight_speed) {
    switch (rgblight_speed) {
        case 0:
            return RGBLIGHT_SPEED_0;
        case 1:
            return RGBLIGHT_SPEED_1;
        case 2:
        default:
            return RGBLIGHT_SPEED_2;
        case 3:
            return RGBLIGHT_SPEED_3;
    }
}

static uint8_t speed_to_rgblight(uint8_t rgb_matrix_speed) {
    if (rgb_matrix_speed < ((RGBLIGHT_SPEED_0 + RGBLIGHT_SPEED_1) / 2)) {
        return 0;
    } else if (rgb_matrix_speed < ((RGBLIGHT_SPEED_1 + RGBLIGHT_SPEED_2) / 2)) {
        return 1;
    } else if (rgb_matrix_speed < ((RGBLIGHT_SPEED_2 + RGBLIGHT_SPEED_3) / 2)) {
        return 2;
    } else {
        return 3;
    }
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    switch (data[0]) {
        case id_lighting_get_value:
            if (data[1] == id_qmk_rgblight_effect_speed) {
                data[2] = speed_to_rgblight(rgb_matrix_get_speed());
            }
            break;
        case id_lighting_set_value:
            if (data[1] == id_qmk_rgblight_effect_speed) {
                rgb_matrix_set_speed_noeeprom(speed_from_rgblight(data[2]));
            }
            break;
    }
}

#    endif // defined(VIA_ENABLE) && defined(VIA_CUSTOM_LIGHTING_ENABLE)

#endif

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
