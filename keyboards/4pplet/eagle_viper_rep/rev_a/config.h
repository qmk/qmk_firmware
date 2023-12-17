/*
Copyright 2021 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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

#define BACKLIGHT_PWM_DRIVER    PWMD2
#define BACKLIGHT_PWM_CHANNEL   4

/* Underglow */
#define WS2812_SPI_DRIVER SPID1
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PIN A5
#define WS2812_SPI_SCK_PAL_MODE 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Indicator leds */
#define LOCK_LIGHTS     TRUE
#define DISPLAY_LAYERS  TRUE
#define CAPS_PIN        B2
#define NUM_PIN         B12
#define SCROLL_PIN      B13
#define LAYER_1         B14
#define LAYER_2         B15
#define LAYER_3         A8
#define LAYER_4         A9
#define LAYER_5         B9
