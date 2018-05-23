/*
 * LEDDriver.h
 *
 *  Created on: Aug 26, 2013
 *      Author: Omri Iluz
 */

#ifndef WS2812_H_
#define WS2812_H_

#include "hal.h"
#include "rgblight_types.h"

#define sign(x) (( x > 0 ) - ( x < 0 ))

typedef struct Color Color;
struct Color {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

void ledDriverInit(int leds, stm32_gpio_t *port, uint32_t mask, uint8_t **o_fb);
void setColorRGB(Color c, uint8_t *buf, uint32_t mask);
void testPatternFB(uint8_t *fb);
void ledDriverWaitCycle(void);

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds);
void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t number_of_leds);

#endif /* LEDDRIVER_H_ */
