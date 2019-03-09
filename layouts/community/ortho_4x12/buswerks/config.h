#pragma once

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define _MASTER_RIGHT
// #define EE_HANDS

#ifdef AUDIO_ENABLE 
    #define STARTUP_SONG SONG(PLANCK_SOUND) 
    // #define STARTUP_SONG SONG(NO_SOUND) 
    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                	SONG(COLEMAK_SOUND), \
                                    SONG(DVORAK_SOUND) \
                                } 
#endif 

// MIDI notes can be sent when in Music mode
#define MIDI_BASIC

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4
