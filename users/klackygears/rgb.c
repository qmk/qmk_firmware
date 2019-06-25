#include "rgb.h"
#include "rgblight.h"
#include "led_tables.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 255
#endif

#define _RGBM_SINGLE_STATIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_SINGLE_DYNAMIC(sym)
#define _RGBM_MULTI_STATIC(sym)    RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_DYNAMIC(sym)
#define _RGBM_TMP_STATIC(sym)      RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_DYNAMIC(sym)
static uint8_t static_effect_table [] = {
#include "rgblight.h"
};


void eeconfig_update_rgblight_default(void) {
  //dprintf("eeconfig_update_rgblight_default\n");
  rgblight_config.enable = 1;
  rgblight_config.mode = RGBLIGHT_MODE_STATIC_LIGHT;
  rgblight_config.hue = 0;
  rgblight_config.sat = 255;
  rgblight_config.val = RGBLIGHT_LIMIT_VAL;
  rgblight_config.speed = 0;
  eeconfig_update_rgblight(rgblight_config.raw);

rgblight_config_t rgblight_config;

void rgblight_task(void) {
#ifdef RGBLIGHT_EFFECT_HYPERBEAM
       if (rgblight_config.mode >= RGBLIGHT_MODE_HYPERBEAM &&
               rgblight_config.mode <= RGBLIGHT_MODE_HYPERBEAM_end) {
        // ignore the change of hue
        hue = rgblight_config.hue;
      }
#endif
}

#ifdef RGBLIGHT_EFFECT_HYPERBEAM
    else if (rgblight_config.mode >= RGBLIGHT_MODE_HYPERBEAM &&
               rgblight_config.mode <= RGBLIGHT_MODE_HYPERBEAM_end) {
      // beam mode
      rgblight_effect_hyperbeam(rgblight_config.mode - RGBLIGHT_MODE_HYPERBEAM);
    }
#endif

// #ifdef RGBLIGHT_EFFECT_BREATHING
// const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {20, 30, 5, 10};
// #endif

// #ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
// const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {20, 50, 100};
// #endif

// #ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
// const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {20, 50, 100};
// #endif

// #ifdef RGBLIGHT_EFFECT_SNAKE
// const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {20, 50, 100};
// #endif

// #ifdef RGBLIGHT_EFFECT_KNIGHT
// const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {20, 50, 100};
// #endif

#ifdef RGBLIGHT_EFFECT_HYPERBEAM
__attribute__ ((weak))
const uint8_t RGBLED_HYPERBEAM_INTERVALS[] PROGMEM = {100, 50, 20};

void rgblight_effect_hyperbeam(uint8_t interval) {
  static uint16_t current_hue = 0;
  static uint8_t pos = 0;
  static uint16_t last_timer = 0;
  uint8_t i, j;
  int8_t k;
  int8_t increment = 1;
  if (interval % 2) {
    increment = -1;
  }
  if (timer_elapsed(last_timer) < pgm_read_byte(&RGBLED_HYPERBEAM_INTERVALS[interval / 2])) {
    return;
  }
  last_timer = timer_read();
  for (i = 0; i < RGBLED_NUM; i++) {
    led[i].r = 0;
    led[i].g = 0;
    led[i].b = 0;
    for (j = 0; j < RGBLIGHT_EFFECT_HYPERBEAM_LENGTH; j++) {
      k = pos + j * increment;
      if (k < 0) {
        k = k + RGBLED_NUM;
      }
      if (i == k) {
        sethsv(current_hue, rgblight_config.sat, (uint8_t)(rgblight_config.val*(RGBLIGHT_EFFECT_HYPERBEAM_LENGTH-j)/rgblight_effect_hyperbeam_LENGTH), (LED_TYPE *)&led[i]);
        //sethsv(rgblight_config.hue, rgblight_config.sat, (uint8_t)(rgblight_config.val*(RGBLIGHT_EFFECT_SNAKE_LENGTH-j)/RGBLIGHT_EFFECT_SNAKE_LENGTH), (LED_TYPE *)&led[i]);
        //current_hue = (current_hue + 1) % 360;
        current_hue = (uint8_t)(rgblight_config.hue*(pos)) % 360;
      }
    }
  }
  rgblight_set();
  if (increment == 1) {
    if (pos - 1 < 0) {
      pos = RGBLED_NUM - 1;
    } else {
      pos -= 1;
    }
  } else {
    pos = (pos + 1) % RGBLED_NUM;
  }
}


#endif
