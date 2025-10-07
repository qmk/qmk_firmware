// Copyright 2025 lucky(@lucky-zang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_rgblight.h"
#include "rgblight.h"
LED_TYPE led[RGBLED_NUM];
extern rgblight_config_t rgblight_config;


void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {

    memcpy(led, start_led, sizeof(LED_TYPE) * num_leds);
}

void rgblight_set(void) {
    LED_TYPE *start_led;
    uint8_t num_leds = rgblight_ranges.clipping_num_leds;
    const uint8_t led_map[] = RGBLIGHT_LED_MAP;

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

bool rgb_matrix_indicators_advanced_rgblight(uint8_t led_min, uint8_t led_max) {

    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        rgb_matrix_set_color(i + (RGB_MATRIX_LED_COUNT -RGBLED_NUM), led[i].r, led[i].g, led[i].b); 
    }

    return true;
}

uint8_t buff[] = {14,8,2,1,1,1,1,1,1,1,0}; 
void im_rgblight_increase(uint8_t kj_rl_mode) {
    HSV rgb;
    uint8_t moude = rgblight_get_mode();

    if (moude == 1) {
        rgb = rgblight_get_hsv();
        if (rgb.h == 0 && rgb.s != 0) {
            kj_rl_mode = 3;
        } else {
            kj_rl_mode = 9;
        }

        switch (rgb.h) {
            case 40:  kj_rl_mode = 4; break;
            case 80:  kj_rl_mode = 5; break;
            case 120: kj_rl_mode = 6; break;
            case 160: kj_rl_mode = 7; break;
            case 200: kj_rl_mode = 8; break;
            default:  break;
        }
    }

    kj_rl_mode++;

    if (kj_rl_mode == 11) {
        kj_rl_mode = 0;
    }

    if (kj_rl_mode == 10) {
        rgb = rgblight_get_hsv();
        rgblight_sethsv(0, 255, rgb.v);
        rgblight_disable();
    } else {
        rgblight_enable();
        rgblight_mode(buff[kj_rl_mode]);
    }

    rgb = rgblight_get_hsv();
    switch (kj_rl_mode) {
        case 3: rgblight_sethsv(0,   255, rgb.v); break;
        case 4: rgblight_sethsv(40,  255, rgb.v); break;
        case 5: rgblight_sethsv(80,  255, rgb.v); break;
        case 6: rgblight_sethsv(120, 255, rgb.v); break;
        case 7: rgblight_sethsv(160, 255, rgb.v); break;
        case 8: rgblight_sethsv(200, 255, rgb.v); break;
        case 9: rgblight_sethsv(0,   0,   rgb.v); break;
        case 0: rgblight_set_speed(255);          break;
        default: rgblight_set_speed(200);         break;
    }
}

#define STEPS_PER_LED 4
#define START_RL_LED_INDEX 76
#define END_RL_LED_INDEX 81

void kj_mode_rgblight_1(uint8_t mode) {
    switch(mode) {
        case 0: { 
            for (uint8_t i = START_RL_LED_INDEX; i <= END_RL_LED_INDEX; i++) {
                rgb_matrix_set_color(i, RGBLIGHT_LIMIT_VAL, RGBLIGHT_LIMIT_VAL, RGBLIGHT_LIMIT_VAL);
            }
        } break;

        case 1: { 
            static uint8_t breath_value = 0;
            static bool increasing = true;
            static uint16_t last_update = 0;
            uint16_t interval = 20;
            if (timer_elapsed(last_update) > interval) {
                last_update = timer_read();
                uint8_t step = 5;
                if (increasing) {
                    if (breath_value + step >= RGBLIGHT_LIMIT_VAL) {
                        breath_value = RGBLIGHT_LIMIT_VAL;
                        increasing = false;
                    } else {
                        breath_value += step;
                    }
                } else {
                    if (breath_value < step) {
                        breath_value = 0;
                        increasing = true;
                    } else {
                        breath_value -= step;
                    }
                }
            }
            for (uint8_t i = START_RL_LED_INDEX; i <= END_RL_LED_INDEX; i++) {
                rgb_matrix_set_color(i, breath_value, breath_value, breath_value);
            }
        } break;

        case 2: { 
            const uint16_t comet_length = 4 * STEPS_PER_LED;
            const uint16_t comet_head_max = END_RL_LED_INDEX * STEPS_PER_LED;
            const uint16_t comet_head_min = START_RL_LED_INDEX * STEPS_PER_LED;
            static uint16_t comet_head = comet_head_max;
            static uint16_t last_update = 0;
            uint16_t interval = 20; 

            if (timer_elapsed(last_update) > interval) {
                last_update = timer_read();
                
                comet_head--;
                if (comet_head < comet_head_min) {
                    comet_head = comet_head_max;
                }
            }
            
            for (uint8_t i = START_RL_LED_INDEX; i <= END_RL_LED_INDEX; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }

            for (uint8_t i = 76; i <= 81; i++) {
                uint16_t led_pos = i * STEPS_PER_LED;
                int16_t diff = led_pos - comet_head;
                if (diff >= 0 && diff < comet_length) {

                    uint8_t brightness = (RGBLIGHT_LIMIT_VAL * (comet_length - diff)) / comet_length;
                    rgb_matrix_set_color(i, brightness, brightness, brightness);
                }
            }
        } break;

        case 3: { 
            for (uint8_t i = START_RL_LED_INDEX; i <= END_RL_LED_INDEX; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        } break;
    }
}

