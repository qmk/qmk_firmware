#pragma once

#include <stdint.h>
#include <stdbool.h>

#if defined(__GNUC__)
#define PACKED __attribute__ ((__packed__))
#else
#define PACKED
#endif

#if defined(_MSC_VER)
#pragma pack( push, 1 )
#endif

#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
  #define RGB_MATRIX_KEYREACTIVE_ENABLED
#endif

// Last led hit
#ifndef LED_HITS_TO_REMEMBER
  #define LED_HITS_TO_REMEMBER 8
#endif // LED_HITS_TO_REMEMBER

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
typedef struct PACKED {
  uint8_t count;
  uint8_t x[LED_HITS_TO_REMEMBER];
  uint8_t y[LED_HITS_TO_REMEMBER];
  uint8_t index[LED_HITS_TO_REMEMBER];
  uint16_t tick[LED_HITS_TO_REMEMBER];
} last_hit_t;
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED

typedef enum rgb_task_states {
  STARTING,
  RENDERING,
  FLUSHING,
  SYNCING
} rgb_task_states;

typedef uint8_t led_flags_t;

typedef struct PACKED {
  uint8_t iter;
  led_flags_t flags;
  bool init;
} effect_params_t;

typedef struct PACKED {
  // Global tick at 20 Hz
  uint32_t tick;
  // Ticks since this key was last hit.
  uint32_t any_key_hit;
} rgb_counters_t;

typedef struct PACKED {
	uint8_t x;
	uint8_t y;
} point_t;

typedef union {
  uint8_t raw;
  struct {
    uint8_t row:4; // 16 max
    uint8_t col:4; // 16 max
  };
} matrix_co_t;

typedef struct PACKED {
	matrix_co_t matrix_co;
	point_t point;
	uint8_t modifier:1;
} rgb_led;

typedef enum {
  RGB_ZONE_OFF = 0,
  RGB_ZONE_ALL,
  RGB_ZONE_KEYS,
  RGB_ZONE_UNDER,
} rgb_zone_t;

typedef union {
  uint32_t raw;
  struct PACKED {
    uint8_t  enable  :2;
    uint8_t  mode    :6;
    uint8_t  hue     :8;
    uint8_t  sat     :8;
    uint8_t  val     :8;
    uint8_t  speed   :8;//EECONFIG needs to be increased to support this
  };
} rgb_config_t;

#if defined(_MSC_VER)
#pragma pack( pop )
#endif
