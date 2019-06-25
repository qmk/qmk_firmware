#pragma once

#include "quantum.h"

#ifndef RGBLIGHT_RECONFIG_H
#define RGBLIGHT_RECONFIG_H

typedef union {
  uint32_t raw;
  struct {
    bool     enable  :1;
    uint8_t  mode    :6;
    uint16_t hue     :9;
    uint8_t  sat     :8;
    uint8_t  val     :8;
    uint8_t  speed   :8;//EECONFIG needs to be increased to support this
  };
} rgblight_config_t;


#ifdef RGBLIGHT_ANIMATIONS

   #define RGBLIGHT_EFFECT_HYPERBEAM

#endif

#if defined(RGBLIGHT_EFFECT_HYPERBEAM)
  #define RGBLIGHT_USE_TIMER
  #ifndef RGBLIGHT_ANIMATIONS
    #define RGBLIGHT_ANIMATIONS  // for backward compatibility
  #endif
#endif

typedef struct {
    uint16_t h;  // 0–360
    uint8_t  s;  // 0–255
    uint8_t  v;  // 0–255
} hsv_t;

typedef struct {
    uint8_t r;  // 0–255
    uint8_t g;  // 0–255
    uint8_t b;  // 0–255
} rgb_t;

#ifndef RGBLIGHT_EFFECT_HYPERBEAM_LENGTH
#define RGBLIGHT_EFFECT_HYPERBEAM_LENGTH 16
#endif

void rgblight_effect_hyperbeam(uint8_t interval);
#ifdef RGBLIGHT_EFFECT_HYPERBEAM
    _RGBM_MULTI_DYNAMIC( BEAM )
    _RGBM_TMP_DYNAMIC( beam_37 )
    //_RGBM_TMP_DYNAMIC( beam_38 )
    //_RGBM_TMP_DYNAMIC( beam_39 )
    //_RGBM_TMP_DYNAMIC( beam_40 )
    _RGBM_TMP_DYNAMIC( BEAM_end )
  #endif

#endif
