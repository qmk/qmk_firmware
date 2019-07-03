#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

#define PLANCK_EZ_USER_LAYER_LIGHT_HANDLING 1

#define RGB_DISABLE_WHEN_USB_SUSPENDED true

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#define RETRO_TAPPING
//#define COMBO_COUNT 1
//#define TAPPING_TERM 200

#undef EZ_LEFT_LED_LAYER
#undef EZ_RIGHT_LED_LAYER
#undef EZ_BOTH_LED_LAYER

#define EZ_LEFT_LED_LAYER 2
#define EZ_RIGHT_LED_LAYER 3
#define EZ_BOTH_LED_LAYER 4
