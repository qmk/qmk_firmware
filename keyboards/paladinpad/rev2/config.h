#ifndef REV2_CONFIG_H
#define REV2_CONFIG_H

#include "config_common.h"

#define DEVICE_VER      0x0002

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F6, D7, B4, D6 }
#define MATRIX_COL_PINS { F7, F5, D3, B7 }
#define UNUSED_PINS

#define AUDIO_VOICES
#define C6_AUDIO

#ifdef AUDIO_ENABLE
#define AUDIO_CLICKY
#define STARTUP_SONG SONG(MARIO_THEME)
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f

#endif

#define RGB_DI_PIN D0

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 7
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 12
#endif

#endif
