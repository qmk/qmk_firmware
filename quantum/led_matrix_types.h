#pragma once

#include <stdint.h>
#include <stdbool.h>

#if defined(__GNUC__)
#    define PACKED __attribute__((__packed__))
#else
#    define PACKED
#endif

#if defined(_MSC_VER)
#    pragma pack(push, 1)
#endif

// Last led hit
#ifndef LED_HITS_TO_REMEMBER
#    define LED_HITS_TO_REMEMBER 8
#endif  // LED_HITS_TO_REMEMBER

typedef struct PACKED {
    uint8_t x;
    uint8_t y;
} point_t;

#define LED_FLAG_ALL 0xFF
#define LED_FLAG_NONE 0x00
#define LED_FLAG_MODIFIER 0x01
#define LED_FLAG_KEYLIGHT 0x04
#define LED_FLAG_INDICATOR 0x08

#define NO_LED 255

typedef struct PACKED {
    uint8_t matrix_co[MATRIX_ROWS][MATRIX_COLS];
    point_t point[LED_DRIVER_LED_COUNT];
    uint8_t flags[LED_DRIVER_LED_COUNT];
} led_config_t;

typedef union {
    uint32_t raw;
    struct PACKED {
        uint8_t  enable : 2;
        uint8_t  mode : 6;
        uint16_t reserved;
        uint8_t  val;
        uint8_t  speed;  // EECONFIG needs to be increased to support this
    };
} led_eeconfig_t;

#if defined(_MSC_VER)
#    pragma pack(pop)
#endif
