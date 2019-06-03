#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

//#define LEADER_TIMEOUT 300
//#define BACKLIGHT_BREATHING
//#define PERMISSIVE_HOLD
// #define QMK_KEYS_PER_SCAN 4

//audio clicky
  //#define AUDIO_CLICKY
  // to enable clicky on startup
  //#define AUDIO_CLICKY_ON
  //#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f

/* ws2812 RGB LED
#define RGB_DI_PIN B5
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
*/
#undef PLANCK_MIT_LAYOUT

//#define MUON_LEFT

#undef DEBOUNCE
#define DEBOUNCE 0

//rgb-reactive
//#define RGB_MATRIX_KEYPRESSES
//#define EECONFIG_RGB_MATRIX (uint32_t *)16

//skip usb startup check
//#define NO_USB_STARTUP_CHECK


/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

#endif
