/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#define PHYSICAL_LEDS_ENABLE

#define RGBLIGHT_TIMER

#ifndef IOS_DEVICE_ENABLE
#if RGBLIGHT_LED_COUNT <= 6
#define RGBLIGHT_LIMIT_VAL 255
#else
#define RGBLIGHT_LIMIT_VAL 130
#endif
#define RGBLIGHT_VAL_STEP 8
#else
#if RGBLIGHT_LED_COUNT <= 6
#define RGBLIGHT_LIMIT_VAL 90
#else
#define RGBLIGHT_LIMIT_VAL 45
#endif
#define RGBLIGHT_VAL_STEP 4
#endif

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
#define USB_MAX_POWER_CONSUMPTION 400
#else
// iOS device need lessthan 100
#define USB_MAX_POWER_CONSUMPTION 100
#endif

#define NUM_LOCK_LED_PIN B6
#define CAPS_LOCK_LED_PIN B5
// #define SCROLL_LOCK_LED_PIN B6

// #define NUM_NMOSFET  //uncomment this if you using n-mosfet
// #define CAPS_NMOSFET  //uncomment this if you using n-mosfet
// #define SCROLL_NMOSFET  //uncomment this if you using n-mosfet

// #define NUM_INVERT // uncomment this if you want to reverse logic of numlock
// This will make it light up only when lock is off
// (Doesn't work on mac. There is no num lock, so it will be always off and lit)

#ifdef NUM_NMOSFET
#define RESET_NUM_LOCK_LED() writePinLow(NUM_LOCK_LED_PIN)
#ifdef NUM_INVERT
#define UPDATE_NUM_LOCK_LED() writePin(NUM_LOCK_LED_PIN, !led_state.num_lock)
#else
#define UPDATE_NUM_LOCK_LED() writePin(NUM_LOCK_LED_PIN, led_state.num_lock)
#endif // NUM_INVERT
#else
#define RESET_NUM_LOCK_LED() writePinHigh(NUM_LOCK_LED_PIN)
#ifdef NUM_INVERT
#define UPDATE_NUM_LOCK_LED() writePin(NUM_LOCK_LED_PIN, led_state.num_lock)
#else
#define UPDATE_NUM_LOCK_LED() writePin(NUM_LOCK_LED_PIN, !led_state.num_lock)
#endif // NUM_INVERT
#endif // NUM_NMOSFET

#ifdef CAPS_NMOSFET
#define RESET_CAPS_LOCK_LED() writePinLow(CAPS_LOCK_LED_PIN)
#define UPDATE_CAPS_LOCK_LED() writePin(CAPS_LOCK_LED_PIN, led_state.caps_lock)
#else
#define RESET_CAPS_LOCK_LED() writePinHigh(CAPS_LOCK_LED_PIN)
#define UPDATE_CAPS_LOCK_LED() writePin(CAPS_LOCK_LED_PIN, !led_state.caps_lock)
#endif // CAPS_NMOSFET

#ifdef SCROLL_NMOSFET
#define RESET_SCROLL_LOCK_LED() writePinLow(SCROLL_LOCK_LED_PIN)
#define UPDATE_SCROLL_LOCK_LED() writePin(SCROLL_LOCK_LED_PIN, led_state.scroll_lock)
#else
#define RESET_SCROLL_LOCK_LED() writePinHigh(SCROLL_LOCK_LED_PIN)
#define UPDATE_SCROLL_LOCK_LED() writePin(SCROLL_LOCK_LED_PIN, !led_state.scroll_lock)
#endif // SCROLL_NMOSFET
