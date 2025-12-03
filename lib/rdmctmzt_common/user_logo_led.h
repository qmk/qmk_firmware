/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
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

#include "quantum.h"

// Logo LED feature flag - define in keyboard's config.h to enable
#ifndef LOGO_LED_ENABLE
#    define LOGO_LED_ENABLE 0
#endif

#if LOGO_LED_ENABLE

// Default Logo LED configuration - can be overridden in keyboard's config.h
#ifndef LED_LOGO_INDEX
#    define LED_LOGO_INDEX 0
#endif

#ifndef LOGO_LED_COUNT
#    define LOGO_LED_COUNT 1
#endif

// Logo LED effect modes (matching VIA config)
#define LOGO_MODE_NONE          0
#define LOGO_MODE_WAVE          1
#define LOGO_MODE_WAVE1         2
#define LOGO_MODE_WAVE2         3
#define LOGO_MODE_FIXED_WAVE    4
#define LOGO_MODE_WAVE_RGB      5
#define LOGO_MODE_SPECTRUM      6
#define LOGO_MODE_BREATHE       7
#define LOGO_MODE_BREATHE_RGB   8
#define LOGO_MODE_LIGHT         9

// Logo LED functions
void Logo_Led_Set_Color(uint8_t r, uint8_t g, uint8_t b);
void Logo_Led_Effect_Solid(void);
void Logo_Led_Effect_Breathe(void);
void Logo_Led_Effect_Breathe_RGB(void);
void Logo_Led_Effect_Spectrum(void);
void Logo_Led_Effect_Wave(void);
void Logo_Led_Effect_Wave_RGB(void);
void Logo_Led_Update(void);

// Logo LED keycode processing - returns true if keycode was handled
bool process_logo_led_keycodes(uint16_t keycode, keyrecord_t *record);

// VIA custom handler for Logo LED settings (channel 2 - rgblight channel)
void via_logo_led_command(uint8_t *data, uint8_t length);

#endif // LOGO_LED_ENABLE
