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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xC0DE
#define PRODUCT_ID      0x1337
#define DEVICE_VER      0x0200
#define MANUFACTURER    KgOfHedgehogs
#define PRODUCT         Jian

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 6
#define DIODE_DIRECTION COL2ROW

// wiring of each half
#define MATRIX_ROW_PINS { F4, F5, B1, B3 }
#define MATRIX_COL_PINS { D3, D2, B4, F6, F7, B2 }

//#define USE_I2C
#define USE_SERIAL
#define SOFT_SERIAL_PIN D1

//#define EE_HANDS
#define SPLIT_HAND_PIN E6

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT D3
#define QMK_ESC_INPUT B1

#define IOS_DEVICE_ENABLE

#ifdef BACKLIGHT_ENABLE
#define BACKLIGHT_PIN C6
#define BACKLIGHT_LEVELS 5
// #define BACKLIGHT_BREATHING //not working with splits right now
#define BREATHING_PERIOD 6
#endif

/* ws2812 RGB LED */
#define RGB_DI_PIN D4
#define RGBLIGHT_TIMER
#define RGBLED_NUM 7    // Number of LEDs
#define RGBLIGHT_ANIMATIONS //not working with splits right now

#define RGBLIGHT_SLEEP
#define RGBLIGHT_SPLIT

#ifndef IOS_DEVICE_ENABLE
#if RGBLED_NUM <= 6
#define RGBLIGHT_LIMIT_VAL 255
#else
#define RGBLIGHT_LIMIT_VAL 130
#endif
#define RGBLIGHT_VAL_STEP 8
#else
#if RGBLED_NUM <= 6
#define RGBLIGHT_LIMIT_VAL 90
#else
#define RGBLIGHT_LIMIT_VAL 45
#endif
#define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
#define USB_MAX_POWER_CONSUMPTION 400
#else
// iOS device need lessthan 100
#define USB_MAX_POWER_CONSUMPTION 100
#endif

#define PHYSICAL_LEDS_ENABLE

#define NUM_LOCK_LED_PIN D7
#define CAPS_LOCK_LED_PIN B5
#define SCROLL_LOCK_LED_PIN B6

// uncomment this if you are using n-mosfets
// #define NUM_NMOSFET
// #define CAPS_NMOSFET
// #define SCROLL_NMOSFET

// #define NUM_INVERT // uncomment this if you want to reverse logic of numlock
// This will make it light up only when lock is off
// (Doesn't work on mac. There is no num lock, so it will be always off and lit)

#if defined(NUM_LOCK_LED_PIN) && defined(PHYSICAL_LEDS_ENABLE)
  #if defined(NUM_NMOSFET) != defined(NUM_INVERT)
      #define UPDATE_NUM_LOCK_LED(led_state) writePin(NUM_LOCK_LED_PIN, led_state)
  #else
      #define UPDATE_NUM_LOCK_LED(led_state) writePin(NUM_LOCK_LED_PIN, !led_state)
  #endif
  #ifdef NUM_NMOSFET
      #define INIT_NUM_LOCK_PIN() setPinOutput(NUM_LOCK_LED_PIN); writePinLow(NUM_LOCK_LED_PIN)
  #else
      #define INIT_NUM_LOCK_PIN() setPinOutput(NUM_LOCK_LED_PIN); writePinHigh(NUM_LOCK_LED_PIN)
  #endif
#else
    #define UPDATE_NUM_LOCK_LED(led_state)
    #define INIT_NUM_LOCK_PIN()
#endif

#if defined(CAPS_LOCK_LED_PIN) && defined(PHYSICAL_LEDS_ENABLE)
    #ifdef CAPS_NMOSFET
        #define UPDATE_CAPS_LOCK_LED(led_state) writePin(CAPS_LOCK_LED_PIN, led_state)
    #else
        #define UPDATE_CAPS_LOCK_LED(led_state) writePin(CAPS_LOCK_LED_PIN, !led_state)
    #endif
    #define INIT_CAPS_LOCK_PIN() setPinOutput(CAPS_LOCK_LED_PIN); UPDATE_CAPS_LOCK_LED(0)
#else
    #define UPDATE_CAPS_LOCK_LED(led_state)
    #define INIT_CAPS_LOCK_PIN()
#endif

#if defined(SCROLL_LOCK_LED_PIN) && defined(PHYSICAL_LEDS_ENABLE)
    #ifdef SCROLL_NMOSFET
        #define UPDATE_SCROLL_LOCK_LED(led_state) writePin(SCROLL_LOCK_LED_PIN, led_state)
    #else
        #define UPDATE_SCROLL_LOCK_LED(led_state) writePin(SCROLL_LOCK_LED_PIN, !led_state)
    #endif
    #define INIT_SCROLL_LOCK_PIN() setPinOutput(SCROLL_LOCK_LED_PIN); UPDATE_SCROLL_LOCK_LED(0)
#else
    #define UPDATE_SCROLL_LOCK_LED(led_state)
    #define INIT_SCROLL_LOCK_PIN()
#endif
