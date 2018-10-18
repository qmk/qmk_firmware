#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(NO_SOUND)
#endif

#define MUSIC_MASK (keycode != KC_NO)

#define FORCE_NKRO 1
#define PREVENT_STUCK_MODIFIERS
#define GRAVE_ESC_GUI_OVERRIDE

#define MIDI_BASIC

#endif
