#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC
#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_DEFAULT 2354.0f
#define AUDIO_CLICKY_FREQ_MAX 9500.0f
#define AUDIO_CLICKY_FREQ_RANDOMNESS 0.05f
#define DAC_SAMPLE_MAX 9350U

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
