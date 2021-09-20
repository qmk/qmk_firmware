/* Copyright 2020 ademey "MsMustard"
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "terrazzo.h"

#ifdef LED_MATRIX_ENABLE
    #include <math.h>
    #include "print.h"
    #include "quantum.h"

const is31_led __flash g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 * https://cdn-learn.adafruit.com/downloads/pdf/adafruit-15x7-7x15-charlieplex-led-matrix-charliewing-featherwing.pdf
 */
    {0, C1_2}, {0, C1_3}, {0, C1_4}, {0, C1_5}, {0, C1_6}, {0, C1_7}, {0, C1_8},
    {0, C2_2}, {0, C2_3}, {0, C2_4}, {0, C2_5}, {0, C2_6}, {0, C2_7}, {0, C2_8},
    {0, C3_2}, {0, C3_3}, {0, C3_4}, {0, C3_5}, {0, C3_6}, {0, C3_7}, {0, C3_8},
    {0, C4_2}, {0, C4_3}, {0, C4_4}, {0, C4_5}, {0, C4_6}, {0, C4_7}, {0, C4_8},
    {0, C5_2}, {0, C5_3}, {0, C5_4}, {0, C5_5}, {0, C5_6}, {0, C5_7}, {0, C5_8},
    {0, C6_2}, {0, C6_3}, {0, C6_4}, {0, C6_5}, {0, C6_6}, {0, C6_7}, {0, C6_8},
    {0, C7_2}, {0, C7_3}, {0, C7_4}, {0, C7_5}, {0, C7_6}, {0, C7_7}, {0, C7_8},
    {0, C8_2}, {0, C8_3}, {0, C8_4}, {0, C8_5}, {0, C8_6}, {0, C8_7}, {0, C8_8},
    //
    {0, C8_15},{0, C8_14},{0, C8_13},{0, C8_12},{0, C8_11},{0, C8_10},{0, C8_9},
    {0, C7_15},{0, C7_14},{0, C7_13},{0, C7_12},{0, C7_11},{0, C7_10},{0, C7_9},
    {0, C6_15},{0, C6_14},{0, C6_13},{0, C6_12},{0, C6_11},{0, C6_10},{0, C6_9},
    {0, C5_15},{0, C5_14},{0, C5_13},{0, C5_12},{0, C5_11},{0, C5_10},{0, C5_9},
    {0, C4_15},{0, C4_14},{0, C4_13},{0, C4_12},{0, C4_11},{0, C4_10},{0, C4_9},
    {0, C3_15},{0, C3_14},{0, C3_13},{0, C3_12},{0, C3_11},{0, C3_10},{0, C3_9},
    {0, C2_15},{0, C2_14},{0, C2_13},{0, C2_12},{0, C2_11},{0, C2_10},{0, C2_9}
};

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    }, {
        // LED Index to Physical Position
        {   0,  0 }, {  16,  0 }, {  32,  0 }, {  48,  0 }, {  64,  0 }, {  80,  0 }, {  96,  0 }, { 112,  0 }, { 128,  0 }, { 144,  0 }, { 160,  0 }, { 176,  0 }, { 192,  0 }, { 208,  0 }, { 224,  0 },
        {   0, 11 }, {  16, 11 }, {  32, 11 }, {  48, 11 }, {  64, 11 }, {  80, 11 }, {  96, 11 }, { 112, 11 }, { 128, 11 }, { 144, 11 }, { 160, 11 }, { 176, 11 }, { 192, 11 }, { 208, 11 }, { 224, 11 },
        {   0, 21 }, {  16, 21 }, {  32, 21 }, {  48, 21 }, {  64, 21 }, {  80, 21 }, {  96, 21 }, { 112, 21 }, { 128, 21 }, { 144, 21 }, { 160, 21 }, { 176, 21 }, { 192, 21 }, { 208, 21 }, { 224, 21 },
        {   0, 32 }, {  16, 32 }, {  32, 32 }, {  48, 32 }, {  64, 32 }, {  80, 32 }, {  96, 32 }, { 112, 32 }, { 128, 32 }, { 144, 32 }, { 160, 32 }, { 176, 32 }, { 192, 32 }, { 208, 32 }, { 224, 32 },
        {   0, 43 }, {  16, 43 }, {  32, 43 }, {  48, 43 }, {  64, 43 }, {  80, 43 }, {  96, 43 }, { 112, 43 }, { 128, 43 }, { 144, 43 }, { 160, 43 }, { 176, 43 }, { 192, 43 }, { 208, 43 }, { 224, 43 },
        {   0, 53 }, {  16, 53 }, {  32, 53 }, {  48, 53 }, {  64, 53 }, {  80, 53 }, {  96, 53 }, { 112, 53 }, { 128, 53 }, { 144, 53 }, { 160, 53 }, { 176, 53 }, { 192, 53 }, { 208, 53 }, { 224, 53 },
        {   0, 64 }, {  16, 64 }, {  32, 64 }, {  48, 64 }, {  64, 64 }, {  80, 64 }, {  96, 64 }, { 112, 64 }, { 128, 64 }, { 144, 64 }, { 160, 64 }, { 176, 64 }, { 192, 64 }, { 208, 64 }, { 224, 64 }
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

#define TERRAZZO_EFFECT(name)
#define TERRAZZO_EFFECT_IMPLS

#include "terrazzo_effects/terrazzo_effects.inc"

#undef TERRAZZO_EFFECT_IMPLS
#undef TERRAZZO_EFFECT

uint8_t terrazzo_led_index = 0;
uint8_t terrazzo_dir = 1;
uint8_t terrazzo_effect = 1;

void terrazzo_set_pixel(uint8_t x, uint8_t y, uint8_t value) {
    uint8_t target = y * LED_MATRIX_COLS + x;
    if (target < DRIVER_LED_TOTAL && target >= 0) {
      led_matrix_set_value(y * LED_MATRIX_COLS + x, value);
    }
}

void terrazzo_draw_at(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t image[]) {
    uint8_t index = 0;
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            uint8_t pixel_value = image[index];
            if (pixel_value != 0) {
               terrazzo_set_pixel(x + h, y + v, image[index]);
            }
            index++;
        }
    }
}

void terrazzo_scroll_pixel(bool clockwise) {
    terrazzo_dir = clockwise;

    if (clockwise) {
        terrazzo_led_index = terrazzo_led_index + 1;
    } else {
        terrazzo_led_index = terrazzo_led_index - 1;
    } 
    
    if (terrazzo_led_index >= DRIVER_LED_TOTAL) {
        terrazzo_led_index = 0;
    } else if (terrazzo_led_index <= 0 ) {
        terrazzo_led_index = DRIVER_LED_TOTAL - 1;
    }
}

void terrazzo_step_mode(void) {
    terrazzo_effect++;
    if (terrazzo_effect >= TERRAZZO_EFFECT_MAX) {
        terrazzo_effect = 1;
    }
}

void terrazzo_step_mode_reverse(void) {
    terrazzo_effect--;
    if (terrazzo_effect < 1) {
        terrazzo_effect = TERRAZZO_EFFECT_MAX - 1;
    }
}

void terrazzo_mode_off(void) {
    terrazzo_effect = TERRAZZO_NONE;
}

void terrazzo_render(void) {
    switch(terrazzo_effect) {
        case TERRAZZO_NONE:
            led_matrix_set_value_all(0);
            break;
        #define TERRAZZO_EFFECT(name, ...)              \
            case TERRAZZO_EFFECT_##name:                \
                name(terrazzo_led_index, terrazzo_dir); \
                break;
        #include "terrazzo_effects/terrazzo_effects.inc"
        #undef TERRAZZO_EFFECT
    }
}

void led_matrix_indicators_kb(void) {
    terrazzo_render();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case TZ_NXT:
                terrazzo_step_mode();
                return true;
            case TZ_PRV:
                terrazzo_step_mode_reverse();
                return true;
            case TZ_OFF:
                terrazzo_mode_off();
                return true;
            // Reverse animation on backspace
            case KC_BSPC:
                terrazzo_scroll_pixel(0);
                return true;
            // Any keycode increments counter
            default:
                terrazzo_scroll_pixel(1);
                break;
        }
    }
    return process_record_user(keycode, record);
}

void suspend_power_down_kb(void) {
    led_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void) {
    led_matrix_set_suspend_state(false);
}


#endif