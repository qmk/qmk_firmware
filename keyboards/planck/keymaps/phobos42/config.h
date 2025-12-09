#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define ORYX_CONFIGURATOR

#define PLANCK_EZ_LED_LOWER 3
#define PLANCK_EZ_LED_RAISE 4
#define PLANCK_EZ_LED_ADJUST 5

#ifdef AUDIO_ENABLE
   
   #ifdef PHOBOS_QWERTY_SOUND
   #undef PHOBOS_QWERTY_SOUND
   #endif
   #ifdef PHOBOS_DVORAK_SOUND
   #undef PHOBOS_DVORAK_SOUND
   #endif
   
   #define PHOBOS_QWERTY_SOUND E__NOTE(_GS4), E__NOTE(_A4), S__NOTE(_REST), Q__NOTE(_E5),
   #define PHOBOS_DVORAK_SOUND E__NOTE(_GS4), E__NOTE(_A4), S__NOTE(_REST), E__NOTE(_E5), S__NOTE(_REST), E__NOTE(_FS5), S__NOTE(_REST), E__NOTE(_E5),
   
   #define BYE_SOUND ED_NOTE(_E5), E__NOTE(_A4), E__NOTE(_E4), 
   #define HI_SOUND  E__NOTE(_E4), E__NOTE(_A4), ED_NOTE(_E5),

    #define STARTUP_SONG SONG(HI_SOUND)
    #define GOODBYE_SONG SONG(BYE_SOUND)
    #define _SONG

    #define DEFAULT_LAYER_SONGS { SONG(PHOBOS_QWERTY_SOUND), \
                                  SONG(PHOBOS_DVORAK_SOUND) \
                                }
#endif

#define MUSIC_MASK (keycode != KC_NO)


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

#endif