/*
Copyright 2023 Gondolindrim

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

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+5

#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

#define BACKLIGHT_PWM_DRIVER  PWMD3
#define BACKLIGHT_PWM_CHANNEL 4
#define BAKCLIGHT_PAL_MODE    2
#define BREATHING_PERIOD      10
#define BACKLIGHT_DEFAULT_LEVEL	10

#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define WEAR_LEVELING_BACKING_SIZE 4096

#define CAPS_INDICATOR_PIN C8
#define INDICATOR_1_PIN D2 // RIGHT INDICATOR
#define INDICATOR_2_PIN B3 // TOP INDICATOR
#define INDICATOR_3_PIN B4 // LEFT INDICATOR
