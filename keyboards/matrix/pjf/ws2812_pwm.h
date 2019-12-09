/*
 * ws2812.h
 *
 */

#ifndef WS2812_H__
#define WS2812_H__

#include <stdint.h>
//#include "rgblight_types.h"

void ws2812_init(void);
void ws2812_setleds(uint8_t* leds, uint16_t number);

#endif
