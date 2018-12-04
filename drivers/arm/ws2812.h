/*
    Copyright (C) 2013 Omri Iluz
                  2018 Jack Humbert

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include "hal.h"
#include "rgblight_types.h"

#define sign(x) (( x > 0 ) - ( x < 0 ))

typedef struct Color Color;
struct Color {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

void ledDriverInit(int leds, stm32_gpio_t *port, uint32_t mask, uint8_t **o_fb);
void setColorRGB(Color c, uint8_t *buf, uint32_t mask);
void testPatternFB(uint8_t *fb);
void ledDriverWaitCycle(void);

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds);
void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t number_of_leds);


void WS2812_init(void);
void WS2812_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void WS2812_set_color_all( uint8_t red, uint8_t green, uint8_t blue );
void WS2812_send_colors(void);
