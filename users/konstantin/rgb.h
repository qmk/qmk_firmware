#pragma once

#include "quantum.h"

typedef struct {
  uint16_t h;
  uint8_t  s;
  uint8_t  v;
} hsv_t;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;

extern const hsv_t GODSPEED_BLUE;
