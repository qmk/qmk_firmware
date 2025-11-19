#include "rgb_rgblight.h"
#include "rgblight.h"

LED_TYPE led[RGBLED_NUM];
extern rgblight_config_t rgblight_config;
const uint8_t led_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

// Make these weak so they won't clash with the main rgblight implementation
// when the standard rgblight module is built. The strong definition in
// quantum/rgblight will be used instead.
__attribute__((weak)) void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {
    memcpy(led, start_led, sizeof(LED_TYPE) * num_leds);
}

__attribute__((weak)) void rgblight_set(void) {
    LED_TYPE *start_led;
    uint8_t num_leds = rgblight_ranges.clipping_num_leds;

    if (!rgblight_config.enable) {
        for (uint8_t i = rgblight_ranges.effect_start_pos; i < rgblight_ranges.effect_end_pos; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }
    LED_TYPE led0[RGBLED_NUM];
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        led0[i] = led[pgm_read_byte(&led_map[i])];
    }
    start_led = led0 + rgblight_ranges.clipping_start_pos;
    rgblight_call_driver(start_led, num_leds);
}

__attribute__((weak)) bool rgb_matrix_indicators_advanced_rgblight(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        rgb_matrix_set_color(i, led[i].r, led[i].g, led[i].b); // rgb light
    }

    return true;
}
