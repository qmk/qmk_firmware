#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    /*#define DEFAULT_LAYER_SONGS {
        SONG(QWERTY_SOUND), \
        SONG(COLEMAK_SOUND), \
        SONG(DVORAK_SOUND) \
    }*/

    #define PING_SOUND Q__NOTE(_A6), WD_NOTE(_E7)
#endif

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

//#define MIDI_BASIC

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

#define COMBO_COUNT 4

#ifdef AUDIO_ENABLE
    #define DAC_SAMPLE_MAX 65535/2
#endif

#define RGBLIGHT_LAYERS
#define RGBLIGHT_SAT_STEP 5
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#define RGBLED_NUM 9

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

#define RGBLIGHT_RAINBOW_SWIRL_RANGE 127
