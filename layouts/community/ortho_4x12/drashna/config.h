/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#if defined(RGBLIGHT_ENABLE) && !defined(RGBLED_NUM)
#    if defined(KEYBOARD_planck_light)
#        define WS2812_DI_PIN A0
#        define RGBLED_NUM 13  // Number of LEDs
#    endif
#    define RGBLIGHT_HUE_STEP 12
#    define RGBLIGHT_SAT_STEP 12
#    define RGBLIGHT_VAL_STEP 12
#    define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#    define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#    ifdef RGB_MATRIX_ENABLE
#        define RGBLIGHT_DISABLE_KEYCODES
#    endif
#endif  // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses (will slow down matrix scan by a lot)
// #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (not recommened)
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#    undef RGB_MATRIX_LED_PROCESS_LIMIT
#    undef RGB_MATRIX_LED_FLUSH_LIMIT
#    ifdef KEYBOARD_planck_rev6
#        define RGB_MATRIX_LED_COUNT RGBLED_NUM
#    endif
#endif

#if defined(KEYBOARD_lets_split_rev2)
#    undef USE_I2C
#    define EE_HANDS
#endif

#if !defined(KEYBOARD_planck_light)
#    ifdef RGBLIGHT_ENABLE
#        define NO_MUSIC_MODE
#    endif  // RGBLIGHT_ENABLE
#else
#    undef QMK_ESC_OUTPUT
#    define QMK_ESC_OUTPUT E6  // usually COL
#    undef QMK_ESC_INPUT
#    define QMK_ESC_INPUT B0  // usually ROW
#    undef QMK_LED
#    define QMK_LED D6
#    undef QMK_SPEAKER
#    define QMK_SPEAKER B5
#    define SOLENOID_PIN A1
#endif  // KEYBOARD_planck_light

#if defined(KEYBOARD_planck)
#    if defined(KEYBOARD_planck_light)
#        undef PRODUCT
#        define PRODUCT "Drashna Hacked RGB Beacon(Planck Light)"
#    elif defined(KEYBOARD_planck_rev6)
#        undef PRODUCT
#        define PRODUCT "Drashna Hacked Planck Rev6"
#    elif defined(KEYBOARD_planck_ez)
#        undef PRODUCT
#        define PRODUCT "Drashna Hacked Planck EZ"
#        define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 4095
#    endif
#endif
#undef NO_USB_STARTUP_CHECK


#define EEPROM_I2C_RM24C512C

#define ENCODER_DIRECTION_FLIP
/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

// #define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

#define DRV2605L_FB_ERM_LRA 1     /* For ERM:0 or LRA:1*/
#define DRV2605L_FB_BRAKEFACTOR 6 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define DRV2605L_FB_LOOPGAIN 1    /* For  Low:0, Medium:1, High:2, Very High:3 */

/* default 3V ERM vibration motor voltage and library*/
#if DRV2605L_FB_ERM_LRA == 0
#    define DRV2605L_RATED_VOLTAGE 3
#    define DRV2605L_V_RMS 2.3
#    define DRV2605L_V_PEAK 3.30
/* Library Selection */
#    define DRV2605L_LIBRARY 4 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

/* default 2V LRA voltage and library */
#elif DRV2605L_FB_ERM_LRA == 1
#    define DRV2605L_RATED_VOLTAGE 2
#    define DRV2605L_V_RMS 2.0
#    define DRV2605L_V_PEAK 2.85
#    define DRV2605L_F_LRA 200
/* Library Selection */
#    define DRV2605L_LIBRARY 6 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

#endif

/* Control 1 register settings */
#define DRV2605L_DRIVE_TIME 25
#define DRV2605L_AC_COUPLE 0
#define DRV2605L_STARTUP_BOOST 1

/* Control 2 Settings */
#define DRV2605L_BIDIR_INPUT 1
#define DRV2605L_BRAKE_STAB 1 /* Loopgain is reduced when braking is almost complete to improve stability */
#define DRV2605L_SAMPLE_TIME 3
#define DRV2605L_BLANKING_TIME 1
#define DRV2605L_IDISS_TIME 1

/* Control 3 settings */
#define DRV2605L_NG_THRESH 2
#define DRV2605L_ERM_OPEN_LOOP 1
#define DRV2605L_SUPPLY_COMP_DIS 0
#define DRV2605L_DATA_FORMAT_RTO 0
#define DRV2605L_LRA_DRIVE_MODE 0
#define DRV2605L_N_PWM_ANALOG 0
#define DRV2605L_LRA_OPEN_LOOP 0
/* Control 4 settings */
#define DRV2605L_ZC_DET_TIME 0
#define DRV2605L_AUTO_CAL_TIME 3
