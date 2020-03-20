#pragma once

#if defined(RGBLIGHT_ENABLE) && !defined(RGBLED_NUM)
#    if defined(KEYBOARD_planck_light)
#        define RGB_DI_PIN A0
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
// #define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
#    undef RGB_MATRIX_LED_PROCESS_LIMIT
#    undef RGB_MATRIX_LED_FLUSH_LIMIT
#    ifdef KEYBOARD_planck_rev6
#        define DRIVER_LED_TOTAL RGBLED_NUM
#    endif
#endif

#if defined(KEYBOARD_lets_split_rev2)
#    define USE_SERIAL
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
#    undef PRODUCT
#    if defined(KEYBOARD_planck_light)
#        define PRODUCT Drashna Hacked RGB Beacon(Planck Light)
#    elif defined(KEYBOARD_planck_rev6)
#        define PRODUCT Drashna Hacked Planck Rev6
#    elif defined(KEYBOARD_planck_ez)
#        define PRODUCT Drashna Hacked Planck EZ
#    endif
#endif

#define ENCODER_DIRECTION_FLIP
/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

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

#define FB_ERM_LRA 1     /* For ERM:0 or LRA:1*/
#define FB_BRAKEFACTOR 6 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN 1    /* For  Low:0, Medium:1, High:2, Very High:3 */

/* default 3V ERM vibration motor voltage and library*/
#if FB_ERM_LRA == 0
#    define RATED_VOLTAGE 3
#    define V_RMS 2.3
#    define V_PEAK 3.30
/* Library Selection */
#    define LIB_SELECTION 4 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

/* default 2V LRA voltage and library */
#elif FB_ERM_LRA == 1
#    define RATED_VOLTAGE 2
#    define V_RMS 2.0
#    define V_PEAK 2.85
#    define F_LRA 200
/* Library Selection */
#    define LIB_SELECTION 6 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

#endif

/* Control 1 register settings */
#define DRIVE_TIME 25
#define AC_COUPLE 0
#define STARTUP_BOOST 1

/* Control 2 Settings */
#define BIDIR_INPUT 1
#define BRAKE_STAB 1 /* Loopgain is reduced when braking is almost complete to improve stability */
#define SAMPLE_TIME 3
#define BLANKING_TIME 1
#define IDISS_TIME 1

/* Control 3 settings */
#define NG_THRESH 2
#define ERM_OPEN_LOOP 1
#define SUPPLY_COMP_DIS 0
#define DATA_FORMAT_RTO 0
#define LRA_DRIVE_MODE 0
#define N_PWM_ANALOG 0
#define LRA_OPEN_LOOP 0
/* Control 4 settings */
#define ZC_DET_TIME 0
#define AUTO_CAL_TIME 3
