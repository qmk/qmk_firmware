/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#define EE_HANDS

// Fix for Elite C rev3
#define SPLIT_USB_DETECT
// Speed up slave half startup
#define SPLIT_USB_TIMEOUT 1000

#ifdef OLED_DRIVER_ENABLE
#    define OLED_DISPLAY_128X64

#    ifdef OLED_CUSTOM_TIMEOUT
#        undef OLED_CUSTOM_TIMEOUT
#        define OLED_CUSTOM_TIMEOUT 30000
#    endif
#    define OLED_INFO_TIMEOUT 1000

#    define OLED_ANIM_STARFIELD
#    define OLED_ANIM_STARFIELD_WANDER
// #    define OLED_ANIM_STARFIELD_DUALLAYER
// #    define OLED_ANIM_IMAGE_BOUNCE
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_LED_MAP \
        { 0, 1, 2, 9, 8, 7, 4, 3, 5, 6, 19, 18, 17, 10, 11, 12, 15, 16, 14, 13 }  // Orients Kyria LEDs to a circle around both halves.
#endif

#ifdef ENCODER_ENABLE
#    define ENCODER_DIRECTION_FLIP
#    define ENCODER_RESOLUTION 2
#endif

#ifdef THUMBSTICK_ENABLE
#    define THUMBSTICK_FLIP_X
#    define THUMBSTICK_PIN_X F0
#    define THUMBSTICK_PIN_Y F1
#endif
