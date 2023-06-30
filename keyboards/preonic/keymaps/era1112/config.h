// Copyright 2022 Era James(@Era1112)
// SPDX - License - Identifier: GPL - 2.0 - or -later

#pragma once


//----------- Default statements -----------//
//------------------------------------------//
#define MUSIC_MASK (keycode < 0xFF)

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
#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2


//----------- Added statements -------------//
//------------------------------------------//
#define TAPPING_TERM 200                        // For tapdances

// Commented to see if it helps stalls on clicky mode #define DYNAMIC_MACRO_NO_NESTING                // Improve dynamic macro stability
#ifdef AUDIO_ENABLE
	#define AUDIO_INIT_DELAY                    // to make startup audio work
	#define STARTUP_SONG SONG(PREONIC_SOUND)
	#define AUDIO_CLICKY                        // enable clicky mode

	// Clicky mode parameters
	#define AUDIO_CLICKY_FREQ_MIN 65.0f         // Default 65
	#define AUDIO_CLICKY_FREQ_DEFAULT 800.0f    // Default 440
	#define AUDIO_CLICKY_FREQ_MAX 1500.0f       // Defaul 1500
	#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f   // Default 0.05
	#define AUDIO_CLICKY_DELAY_DURATION 0.1f    // Default 1
#endif  //AUDIO_ENABLE

#define RGBLIGHT_SLEEP                  // RGB lights turn off when host sleeps

// Firmware minimization

// Commented to see if it helps stalls on clicky mode
// #define NO_ACTION_ONESHOT
// #undef LOCKING_SUPPORT_ENABLE
// #undef LOCKING_RESYNC_ENABLE
// #define NO_MUSIC_MODE
// #define LAYER_STATE_8BIT        // Limits keymap to 8 layers
