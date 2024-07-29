/*
Copyright 2022 x123 <@x123>
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

#define SPLIT_USB_DETECT
// #define SPLIT_USB_TIMEOUT 2500
#define EE_HANDS
#define SWAP_HANDS_ENABLE

#define TAPPING_TOGGLE 1
#define TAPPING_TERM 180

#define CAPS_WORD_IDLE_TIMEOUT 3000
#define LEADER_TIMEOUT 1000
#define LEADER_NO_TIMEOUT
#define MAX_DEFERRED_EXECUTORS 10
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define OLED_FADE_OUT
#define SPLIT_OLED_ENABLE
#define SPLIT_ACTIVITY_ENABLE
#define SPLIT_LED_STATE_ENABLE
#ifdef BIG_MEMORY
#define SPLIT_MODS_ENABLE
#endif
#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define RGB_MATRIX_DEFAULT_SPD 100
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define SPLIT_TRANSPORT_MIRROR
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
