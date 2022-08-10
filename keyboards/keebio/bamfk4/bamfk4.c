// Copyright 2022 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bamfk4.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { NO_LED, NO_LED, NO_LED, NO_LED },
}, {
    // LED Index to Physical Position
    //through switch
    { 26.6, 10 }, { 4.3, 10 }, { 3.8, 49.3 }, { 23.3, 49.3 },
    { 69.4, 49.3 }, { 68.9, 10 }, { 90.6, 10 }, { 89.5, 49.3 },
    { 134, 49.3 }, { 132.9, 10 }, { 155.7, 10 }, { 155.1, 49.3 },
    { 199.6, 49.3 }, { 199.6, 10 }, { 219.1, 10 }, { 219.1, 49.3 },

    //underglow
    { 218, 62.2 }, { 188.7, 62.2 }, { 159.5, 62.2 }, { 123.7, 62.2 }, //bottom right
    { 100.3, 62.2 }, { 59.1, 62.2 }, { 35.3, 62.2 }, { 5.4, 62.2 }, //bottom left
    { 6, 6.4 }, { 35.3, 6.4 }, { 59.1, 6.4 }, { 100.3, 6.4 }, //top left
    { 123.7, 6.4 }, { 159.5, 6.4 }, { 188.7, 6.4 }, { 218, 6.4 } //top right
}, {
    // LED Index to Flag
    4, 4, 4, 4, 
    4, 4, 4, 4, 
    4, 4, 4, 4,
    4, 4, 4, 4, 
    2, 2, 2, 2,
    2, 2, 2, 2,
    2, 2, 2, 2,
    2, 2, 2, 2 
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