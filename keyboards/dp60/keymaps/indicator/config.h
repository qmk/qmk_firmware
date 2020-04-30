/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

#define RGB_INDICATOR_NUM 8
#undef RGBLED_NUM
#define RGBLED_NUM  (18+RGB_INDICATOR_NUM)

#define RGB_INDICATOR_PIN B1
#define RGBLIGHT_LAYERS
