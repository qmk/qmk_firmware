/*
Copyright 2020 Moritz Plattner
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

#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PAL_MODE 6
#define BACKLIGHT_PWM_OUTPUT_FREQUENCY 1000 // Increases backlight PWM freq if compiled with an unmerged PR. Does no harm without it.

/* Underglow */
#define WS2812_EXTERNAL_PULLUP // This board uses a pull-up + 5 V tolerant GPIO in open drain config ro generate a 5 V signal
/* section for PWM WS2812 driver */
#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#define WS2812_DMA_CHANNEL 7
