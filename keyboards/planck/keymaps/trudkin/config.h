#pragma once

#define MAX_LMT 8


#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#undef TAPPING_TERM
#define TAPPING_TERM 390

#define ONESHOT_TAP_TOGGLE 2


#define FIRMWARE_VERSION u8"YnNGZ/oLM3Q"
#define RGB_MATRIX_STARTUP_SPD 60



#ifndef PLANCK_EZ_LED_LOWER
#    define PLANCK_EZ_LED_LOWER 2
#endif
#ifndef PLANCK_EZ_LED_RAISE
#    define PLANCK_EZ_LED_RAISE 3
#endif
#ifndef PLANCK_EZ_LED_ADJUST
#    define PLANCK_EZ_LED_ADJUST 4
#endif
