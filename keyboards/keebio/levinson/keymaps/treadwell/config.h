#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define TAPPING_TERM 150

/* default layer sounds */
#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                              SONG(GAME_SOUND), \
                              SONG(COLEMAK_SOUND) \
                            }

//#undef RGBLED_NUM
//#define RGBLED_NUM 12
//#define RGBLIGHT_HUE_STEP 8
//#define RGBLIGHT_SAT_STEP 8
//#define RGBLIGHT_VAL_STEP 8

#endif
