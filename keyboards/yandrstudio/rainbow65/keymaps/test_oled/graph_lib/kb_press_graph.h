/* Copyright 2021 JasonRen(biu)
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
#include "progmem.h"
#include "../dev_oled/oled_driver.h"
#include "time.h"

void render_r65_kb(uint8_t col, uint8_t row, uint16_t keycode, bool on, uint16_t key_press_count);

static const char my_font_lib_etc_r65kb[] PROGMEM = {
    0x07, 0xFF, 0xFF, 0x49, 0x49, 0xFF, 0x49, 0x49,
    0xFF, 0x49, 0x49, 0xFF, 0x49, 0x49, 0xFF, 0x49,
    0x49, 0xFF, 0x49, 0x49, 0xFF, 0x49, 0x49, 0xFF,
    0x49, 0x49, 0xFF, 0x49, 0x49, 0xFF, 0xFF, 0x07,

    0xE0, 0xFF, 0xFF, 0x92, 0x92, 0xFF, 0x92, 0x92,
    0xFF, 0x92, 0x92, 0x9F, 0x92, 0x92, 0x9F, 0x92,
    0x92, 0xFF, 0x92, 0x92, 0xFF, 0x92, 0x92, 0xFF,
    0x92, 0x92, 0xFF, 0x92, 0x92, 0xFF, 0xFF, 0xE0,
};
