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

// Last led hit
#define LED_HITS_TO_REMEMBER 8

typedef struct PACKED {
  // Global tick at 20 Hz
  uint32_t tick;
  // Ticks since this key was last hit.
  uint32_t any_key_hit;
  // Ticks since any key was last hit.
  uint8_t key_hit[DRIVER_LED_TOTAL];
  // Last led hit
  uint8_t last_led_hit[LED_HITS_TO_REMEMBER];

  uint8_t last_led_count;
} rgb_counters;

typedef struct PACKED {
	uint8_t x;
	uint8_t y;
} Point;

typedef struct PACKED {
	union {
		uint8_t raw;
		struct {
			uint8_t row:4; // 16 max
			uint8_t col:4; // 16 max
		};
	} matrix_co;
	Point point;
	uint8_t modifier:1;
} rgb_led;

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
} rgb_config_t;

#if defined(_MSC_VER)
#pragma pack( pop )
#endif
