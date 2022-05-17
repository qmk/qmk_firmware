// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "config.h"
#include "rgblight.h"

typedef LED_TYPE (*animFunc_t)(LED_TYPE, LED_TYPE, float, uint8_t);

LED_TYPE swimIn(LED_TYPE, LED_TYPE, float, uint8_t);
LED_TYPE swimOut(LED_TYPE, LED_TYPE, float, uint8_t);

void smoothled_set(uint32_t color, uint32_t newDuration, animFunc_t newAnimFunc);
void smoothled_process(void);
void smoothled_render(void);
