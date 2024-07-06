/* Copyright 2023 splitkb.com <support@splitkb.com>
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

// Myriad boilerplate
#define MYRIAD_ENABLE

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed
#define DEBOUNCE 2

// Automatically turn on NKRO
#define FORCE_NKRO

// Sets USB Polling interval
#define USB_POLLING_INTERVAL_MS 1

// Encoder Resolution 
// defined in splitkb/elora/rev1/config.h

// RGB Animations
// Sleep when computer turned off
#define RGBLIGHT_SLEEP
#define RGB_DISABLE_WHEN_USB_SUSPENDED
// Split Keyboard support
#define RGBLIGHT_SPLIT
// Default RGB Mode
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
// Default Brightness
#define RGBLIGHT_DEFAULT_VAL 128
// Default On/Off
#define RGBLIGHT_DEFAULT_ON true
// Enable animations
#define RGBLIGHT_EFFECT_BREATHING
#define BREATHING_PERIOD 10
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
