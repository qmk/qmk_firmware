#pragma once

#ifdef RAW_ENABLE
#include "rhruiz_api.h"
#include "raw_hid.h"
#endif

#ifdef RGBLIGHT_ENABLE
void rhruiz_rgblight_reset(void);
void rhruiz_change_leds_to(uint16_t, uint8_t);

typedef struct {
  uint16_t hue;
  uint8_t sat;
} hue_sat_pair;

#endif
