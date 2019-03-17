//#ifndef LEDS_H
//#define LEDS_H
//
//#include "hsv2rgb.h"
//
//void set_leds_color_hsv(hsv_color color);
//void set_leds_color_rgb(rgb_color color);
//void set_led_color_hsv(hsv_color color, int pos);
//void set_led_color_rgb(rgb_color color, int pos);
//
//void leds_init(void);
//
//#endif


#pragma once

#include "hal.h"
#include "rgblight_types.h"


void set_leds_color_rgb(LED_TYPE color);
void set_led_color_rgb(LED_TYPE color, int pos);
void leds_init(void);


 // This is what users will use to interface with this
void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds);
void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t number_of_leds);


void WS2812_init(void);
void WS2812_set_color( uint8_t index, uint8_t red, uint8_t green, uint8_t blue );
void WS2812_set_color_all( uint8_t red, uint8_t green, uint8_t blue );
void WS2812_send_colors(void);
