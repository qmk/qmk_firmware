/* Copyright 2024 keymagichorse
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
#pragma once


#ifndef SERIAL_NUMBER
#   define SERIAL_NUMBER "mjl_hl6095"
#endif

#define WS2812_POWER_PIN        B8
#define WS2812_POWER_ON_LEVEL   0      // 0-低电平打开电源  1-高电平关闭电源，根据原理图设置

#define WS2812_BYTE_ORDER   WS2812_BYTE_ORDER_GRB
#define RGBLIGHT_LIMIT_VAL 180
#define RGBLIGHT_LAYER_BLINK
