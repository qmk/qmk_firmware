/*
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

#pragma once

#include "util.h"

/*
 * The WS2812 datasheets define T1H 900ns, T0H 350ns, T1L 350ns, T0L 900ns. Hence, by default, these
 * are chosen to be conservative and avoid problems rather than for maximum throughput; in the code,
 * this is done by default using a WS2812_TIMING parameter that accounts for the whole window (1250ns)
 * and defining T1H and T0H; T1L and T0L are obtained by subtracting their low counterparts from the window.
 *
 * However, there are certain "WS2812"-like LEDs, like the SK6812s, which work in a similar
 * communication topology but use different timings for the window and the T1L, T1H, T0L and T0H.
 * This means that, albeit the same driver being applicable, the timings must be adapted.
 */

#ifndef WS2812_TIMING
#    define WS2812_TIMING 1250
#endif

#ifndef WS2812_T1H
#    define WS2812_T1H 900 // Width of a 1 bit in ns
#endif

#ifndef WS2812_T1L
#    define WS2812_T1L (WS2812_TIMING - WS2812_T1H) // Width of a 1 bit in ns
#endif

#ifndef WS2812_T0H
#    define WS2812_T0H 350 // Width of a 0 bit in ns
#endif

#ifndef WS2812_T0L
#    define WS2812_T0L (WS2812_TIMING - WS2812_T0H) // Width of a 0 bit in ns
#endif

/*
 * Older WS2812s can handle a reset time (TRST) of 50us, but recent
 * component revisions require a minimum of 280us.
 */
#if !defined(WS2812_TRST_US)
#    define WS2812_TRST_US 280
#endif

#if defined(RGBLIGHT_WS2812)
#    define WS2812_LED_COUNT RGBLIGHT_LED_COUNT
#elif defined(RGB_MATRIX_WS2812)
#    define WS2812_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#define WS2812_BYTE_ORDER_RGB 0
#define WS2812_BYTE_ORDER_GRB 1
#define WS2812_BYTE_ORDER_BGR 2

#ifndef WS2812_BYTE_ORDER
#    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB
#endif

typedef struct PACKED ws2812_led_t {
#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
    uint8_t g;
    uint8_t r;
    uint8_t b;
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
    uint8_t r;
    uint8_t g;
    uint8_t b;
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
    uint8_t b;
    uint8_t g;
    uint8_t r;
#endif
#ifdef WS2812_RGBW
    uint8_t w;
#endif
} ws2812_led_t;

void ws2812_init(void);
void ws2812_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void ws2812_flush(void);

void ws2812_rgb_to_rgbw(ws2812_led_t *led);
