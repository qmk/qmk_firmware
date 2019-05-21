#pragma once

#include "quantum.h"

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

extern const hsv_t GODSPEED_BLUE;
extern const hsv_t GODSPEED_YELLOW;
