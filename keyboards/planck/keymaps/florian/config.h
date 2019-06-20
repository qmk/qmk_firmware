#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define AUTO_SHIFT_TIMEOUT 170
  #define RGB_DISABLE_WHEN_USB_SUSPENDED true

  #define EECONFIG_RGB_MATRIX (uint32_t *)16
