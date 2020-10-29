#pragma once
#include "config_common.h"

/* Speaker configuration
 */
#define B7_AUDIO
#define NO_MUSIC_MODE
#define AUDIO_CLICKY

/* Space savings
 */
#define NO_ACTION_TAPPING

/* Backlight configuration
 */
#define BACKLIGHT_LEVELS 1

/* Underlight configuration
 */
#define RGB_DI_PIN D7
#define RGBLED_NUM 26     // Number of LEDs
#define RGBLIGHT_HUE_STEP 32
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#define RGBLIGHT_EFFECT_BREATHE_MAX 200
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 666*2
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 4   // How many LEDs wide to light up
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 16   // The led to start at
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 8  // How many LEDs to travel
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4    // How many LEDs wide to light up
