#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

#ifdef RGBLIGHT_ENABLE
#   undef RGBLED_NUM
//#   define RGBLIGHT_ANIMATIONS
//#   define RGBLIGHT_EFFECT_BREATHING
//#   define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#   define RGBLED_NUM 9
#   define RGBLIGHT_ANIMATIONS
#   define RGBLIGHT_HUE_STEP 12
#   define RGBLIGHT_SAT_STEP 12
#   define RGBLIGHT_VAL_STEP 12
#endif

/*
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_LAYERS
#endif
*/

/*
 * MIDI options
 */

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
//#define ENCODER_RESOLUTION 4