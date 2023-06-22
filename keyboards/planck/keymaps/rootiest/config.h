/* Copyright 2021 Chris Laprade
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

/*
 * USB/POWER OPTIONS
 */
// #define USB_MAX_POWER_CONSUMPTION 500
#define USB_SUSPEND_WAKEUP_DELAY 200
#define USB_POLLING_INTERVAL_MS 1

/*
 * MUSIC/AUDIO options
 */
#ifdef AUDIO_ENABLE
#    define AUDIO_CLICKY
#    define MUSIC_MAP
#    define AUDIO_VOICES
#    define AUDIO_VOICE_DEFAULT something
#    define AUDIO_DAC_SAMPLE_MAX 2732U

#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND) }

/* Plays during keyboard startup */
#    define STARTUP_SONG SONG(NO_SOUND)

#endif

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

/*
 * ENCODER options
 */
#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 4  // Define number of stages between detents on encoders
#define ENCODERS_PAD_A \
    { B12 }
#define ENCODERS_PAD_B \
    { B13 }

/*
 * RGB options
 */
#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP // Allows rgb to sleep when the host/keyboard does
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_LAYERS                  // Enable indicating layers using layered rgb assignments
#    define RGBLIGHT_LAYER_BLINK             // Allows rgb layers to be blinked (activate for a set amount of time)
#    define RGBLIGHT_MAX_LAYERS 32           // Overides the default (8) max number of rgb layers
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Allows rgb layers to work even when rgb is toggled off
#endif

/*
 * UNICODE options
 */
#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_LINUX, UNICODE_MODE_MACOS  // Define the methods used for in/outputting unicode

/*
 * TAP-DANCE options
 */
#define TAPPING_TERM_PER_KEY // Control Tap-Dance time individually by key
#define TAPPING_TERM 250     // Default time allowed before resetting a Tap-Dance combo
#define ONESHOT_TAP_TOGGLE 5 /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000 /* Time (in ms) before the one shot key is released */
#define TAPPING_TOGGLE 3

/*
 * LEADER-KEY options
 */     // Used for on-board chording
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 500

/*
 * COMBO-KEY options
 */
#define COMBO_TERM 300
/*
 * MACRO per-key options
 */
#define RETRO_TAPPING_PER_KEY             // Control Retro-Tap individually by key
#define QUICK_TAP_TERM_PER_KEY            // Control Quick-Tap individually by key
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY   // Control Hold-on-Other-Key-Press individually by key
#define PERMISSIVE_HOLD_PER_KEY           // Control Permissive-Hold individually by key

#define MK_KINETIC_SPEED  // Use kinetic acceleration for mouse-keys

// Fall-back defines to prevent compile errors if user_song_list is missing
#ifndef ZELDA_PUZZLE2
#    define ZELDA_PUZZLE2 Q__NOTE(_G5)
#endif
#ifndef SONIC_RING2
#    define SONIC_RING2 E__NOTE(_E6)
#endif
#ifndef ZELDA_CHEST2
#    define ZELDA_CHEST2 Q__NOTE(_G5)
#endif
#ifndef COIN_SOUND2
#    define COIN_SOUND2 E__NOTE(_A5)
#endif
#ifndef ONE_UP_SOUND2
#    define ONE_UP_SOUND2 Q__NOTE(_E6)
#endif
#ifndef IMPERIAL_MARCH
#    define IMPERIAL_MARCH HD_NOTE(_A4)
#endif
#ifndef MARIO_GAMEOVER
#    define MARIO_GAMEOVER HD_NOTE(_C5)
#endif
#ifndef LEAD_START_SOUND
#    define LEAD_START_SOUND E__NOTE(_C5)
#endif
#ifndef LEAD_SUCCESS_SOUND
#    define LEAD_SUCCESS_SOUND E__NOTE(_A5), HD_NOTE(_E6),
#endif
#ifndef LEAD_FAIL_SOUND
#    define LEAD_FAIL_SOUND E__NOTE(_A5), HD_NOTE(_E4),
#endif
