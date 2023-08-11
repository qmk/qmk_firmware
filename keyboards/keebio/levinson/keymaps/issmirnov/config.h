#pragma once

#ifdef RGBLIGHT_ENABLE
   // Enable animations. +5500 bytes
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE


   // Map my custom number of LED's
   #undef RGBLED_NUM
   #define RGBLED_NUM 16
   #define RGBLIGHT_LED_MAP { 0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8 } // When changed, BE SURE to flash EEPROM on both halves and clear it.

   // DO NOT USE RGBLED_SPLIT - the slave board will stop responding.

   // Turn off RGB when computer sleeps
   #define RGBLIGHT_SLEEP

   // custom colors
   #define RGB_CLEAR 0x00, 0x00, 0x00

   // MOD indicators
   #define SHFT_LED1 7
   #define GUI_LED1 8
#endif

#ifdef AUDIO_ENABLE
   #define QMK_SPEAKER C6
   #define AUDIO_PIN C6
   #define NO_MUSIC_MODE // Save 2000 bytes
#endif
