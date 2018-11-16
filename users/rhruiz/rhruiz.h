#ifndef _RHRUIZ_H
#ifdef RAW_ENABLE
#include "rhruiz_api.h"
#endif

#ifdef RAW_ENABLE
#include "raw_hid.h"
#endif

#ifdef RGBLIGHT_ENABLE
void rhruiz_change_leds_to(uint16_t, uint8_t);
void rhruiz_rgblight_reset(void);
void rhruiz_state_will_change(void);
void rhruiz_state_did_change(void);
void rhruiz_matrix_init(void);

typedef struct {
  uint16_t hue;
  uint8_t sat;
} hue_sat_pair;

#endif

#define _RHRUIZ_H
#endif
