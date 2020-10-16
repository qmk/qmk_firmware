#include "print.h"

RGB_MATRIX_EFFECT(TEST_LEDS_MATRIX_SCAN)
RGB_MATRIX_EFFECT(TEST_LEDS_MATRIX_SOLID)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

int active_led = 0;
int led_color = 0;
int led_matrix[] = {
    0, 5, 10, 15, 20, 26, 31, 37, 43, 48, 53, 58,
    1, 6, 11, 16, 21, 27, 32, 38, 44, 49, 54, 59,
    2, 7, 12, 17, 22, 28, 33, 39, 45, 50, 55, 60,
    3, 8, 13, 18, 23, 29, 34, 40, 46, 51, 56, 61,
    4, 9, 14, 19, 24, 25, 30, 36, 35, 42, 41, 47, 52, 57, 62,
};

static void set_led_color(uint8_t i) {
    switch (led_color) {
        case 0:
        rgb_matrix_set_color(i, RGB_RED);
        break;
        case 1:
        rgb_matrix_set_color(i, RGB_GREEN);
        break;
        case 2:
        rgb_matrix_set_color(i, RGB_BLUE);
        break;
    }
}

static void advance_matrix(effect_params_t* params) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (i == led_matrix[active_led]) {
            set_led_color(led_matrix[active_led]);
        }else {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

    active_led ++;
    if (active_led >= DRIVER_LED_TOTAL) {
        led_color ++;
        active_led = 0;
    }

    if (led_color >= 3) {
        led_color = 0;
    }
}

static bool TEST_LEDS_MATRIX_SCAN(effect_params_t* params) {
    if (!params->init) {
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 8 == 0) {
            advance_matrix(params);
        }
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    return led_max < DRIVER_LED_TOTAL;
}

static bool TEST_LEDS_MATRIX_SOLID(effect_params_t* params) {
    if (!params->init) {
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 20 == 0) {
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                set_led_color(i);
            }
            led_color ++;
            if (led_color >= 3) {
                led_color = 0;
            }
        }
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        led_color = 0;
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
