/* Copyright 2021 Drashna Jael're
 *
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

#include "rgblight.h"
#include "rgb_matrix.h"

#ifdef RGBLIGHT_ENABLE
#undef WS2812_DI_PIN
#define WS2812_DI_PIN RGBLIGHT_DI_PIN

#define ws2812_init ws2812_rgb_init
#define ws2812_setleds ws2812_rgb_setleds

#include "ws2812_bitbang.c"

const rgblight_driver_t rgblight_driver = {
    .init    = ws2812_init,
    .setleds = ws2812_setleds,
};
#endif
