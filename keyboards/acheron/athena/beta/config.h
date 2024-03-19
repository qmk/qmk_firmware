/*
Copyright 2020 Gondolindrim

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

#pragma once

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define BACKLIGHT_PWM_DRIVER    PWMD3

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+5

#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_PWM_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_PWM_DMA_CHANNEL 6

// If this is defined, the caps lock LED will turn on and off according to the state of caps lock. If not, the LED will shine like all other LEDs despite the caps lock state.
#define CAPSLOCK_INDICATOR
