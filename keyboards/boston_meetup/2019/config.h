#pragma once

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
#define DRV2605L_FB_ERM_LRA 1 /* For ERM:0 or LRA:1*/
#define DRV2605L_FB_BRAKEFACTOR 6 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* default 3V ERM vibration motor voltage and library*/
#if DRV2605L_FB_ERM_LRA == 0
#define DRV2605L_RATED_VOLTAGE 3
#define DRV2605L_V_RMS 2.3
#define DRV2605L_V_PEAK 3.30
/* Library Selection */
#define DRV2605L_LIBRARY 4 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

/* default 2V LRA voltage and library */
#elif DRV2605L_FB_ERM_LRA == 1
#define DRV2605L_RATED_VOLTAGE 2
#define DRV2605L_V_RMS 2.0
#define DRV2605L_V_PEAK 2.85
#define DRV2605L_F_LRA 200
/* Library Selection */
#define DRV2605L_LIBRARY 6 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */

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

#define RGB_MATRIX_LED_COUNT 10

#define RGB_MATRIX_KEYPRESSES

#define SOLENOID_PIN A14
