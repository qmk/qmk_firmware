#pragma once

#undef MATRIX_ROWS
#undef MATRIX_COLS
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

#define MATRIX_ROW_PINS { A3, B8, B9, B1 }
#define MATRIX_COL_PINS { A7, A8, B2, B10 }

#define ENCODERS_PAD_A { B13 }
#define ENCODERS_PAD_B { B14 }

//Audio
#undef AUDIO_VOICES
#undef AUDIO_PIN
#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(ONE_UP_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

#define AUDIO_CLICKY
  /* to enable clicky on startup */
  //#define AUDIO_CLICKY_ON
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.5f
#endif

// configure oled driver for the 128x32 oled
#define OLED_UPDATE_INTERVAL 33 // ~30fps

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 6

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* Haptic Driver initialization settings
 * Feedback Control Settings */
#define FB_ERM_LRA 1 /* For ERM:0 or LRA:1*/
#define FB_BRAKEFACTOR 6 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* default 3V ERM vibration motor voltage and library*/
#if FB_ERM_LRA == 0
#define RATED_VOLTAGE 3
#define V_RMS 2.3
#define V_PEAK 3.30
/* Library Selection */
#define LIB_SELECTION 4 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

/* default 2V LRA voltage and library */
#elif FB_ERM_LRA == 1
#define RATED_VOLTAGE 2
#define V_RMS 2.0
#define V_PEAK 2.85
#define F_LRA 200
/* Library Selection */
#define LIB_SELECTION 6 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

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

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

#define RGBLED_NUM 10
#define RGB_DI_PIN B5
#define RGB_MATRIX_LED_COUNT RGBLED_NUM

#define RGB_MATRIX_KEYPRESSES

#define SOLENOID_PIN A14
