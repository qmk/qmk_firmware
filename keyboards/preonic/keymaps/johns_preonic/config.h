#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#ifdef TAP_DANCE_ENABLE

#define TAPPING_TERM 200

/* #define MK_3_SPEED */
#define MK_MOMENTARY_ACCEL
#define MOUSEKEY_MAX_SPEED         8

void dance_raise_press(qk_tap_dance_state_t *state, void *user_data){// Called on each tap
  switch(state->count){      // Only turn the layer on once
    case 1:
        layer_off(_UNICODES);
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        break;
  }
};
void dance_raise_lift(qk_tap_dance_state_t *state, void *user_data){ // Called on release
  switch(state->count){
    case 1:         // Normal action. Turn off layers
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        layer_off(_UNICODES);
        break;
  }
};
/////////////////////////////////////////////////////////////////////
void dance_lower_press(qk_tap_dance_state_t *state, void *user_data){// Called on tap
  switch(state->count){
    case 1:         // Turn on lower
        layer_off(_UNICODES);
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        break;
  }
};
void dance_lower_lift(qk_tap_dance_state_t *state, void *user_data){ // Called on release
  switch(state->count){
    case 1:         // Normal action. Turn off layers
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        layer_off(_UNICODES);
        break;
    case 2:         // Turn on _UNICODES layer
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        layer_on(_UNICODES);
        #ifdef AUDIO_ENABLE
            PLAY_SONG(tone_ctrl_mod);
        #endif
        break;
  }
};
/////////////////////////////////////////////////////////////////////
void dance_super_press(qk_tap_dance_state_t *state, void *user_data){   // Called on down
    if(state->count == 1){
        register_code(KC_LGUI);
    }
}
void dance_super_done(qk_tap_dance_state_t *state, void *user_data){    // Called on timeout
  switch(state->count){
    case 2:
        register_code(KC_LGUI);
        tap(KC_L);
        unregister_code(KC_LGUI);
        break;
  }
}
void dance_super_lift(qk_tap_dance_state_t *state, void *user_data){        // Called on up
    unregister_code(KC_LGUI);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [RAI] = ACTION_TAP_DANCE_FN_ADVANCED(dance_raise_press, NULL, dance_raise_lift),
    [LOW] = ACTION_TAP_DANCE_FN_ADVANCED(dance_lower_press, NULL, dance_lower_lift),
    [SUP] = ACTION_TAP_DANCE_FN_ADVANCED(dance_super_press, dance_super_done, dance_super_lift)
};
#endif

#undef MUSICAL_NOTE
#define MUSICAL_NOTE(note, duration) {((NOTE##note) * 1.3348398541700344), duration}

#define CUSTOM_STARTUP \
    QD_NOTE(_A6),  \
    QD_NOTE(_C7),  \
    QD_NOTE(_A7),  \
    QD_NOTE(_F7),  \
    QD_NOTE(_G7),  \
    HD_NOTE(_C8),

#undef MUSICAL_NOTE
#define MUSICAL_NOTE(note, duration) {(NOTE##note), duration}

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(CUSTOM_STARTUP)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND), \
                                  SONG(WORKMAN_SOUND), \
                                  SONG(PREONIC_SOUND), \
                                  SONG(GUITAR_SOUND), \
                                  SONG(UNICODE_WINDOWS), \
                                  SONG(UNICODE_LINUX) \
                                }
#endif

#define MUSIC_MASK (keycode != KC_NO)
#define NO_ACTION_TAPPING
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define MIDI_BASIC

#endif


