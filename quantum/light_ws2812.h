/*
 * light weight WS2812 lib include
 *
 * Version 2.3  - Nev 29th 2015
 * Author: Tim (cpldcpu@gmail.com)
 *
 * Please do not change this file! All configuration is handled in "ws2812_config.h"
 *
 * License: GNU GPL v2 (see License.txt)
 +
 */

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_

#include <avr/io.h>
#include <avr/interrupt.h>
//#include "ws2812_config.h"
//#include "i2cmaster.h"

#ifdef RGBW
  #define LED_TYPE struct cRGBW
#else
  #define LED_TYPE struct cRGB
#endif


/*
 *  Structure of the LED array
 *
 * cRGB:     RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
 * cRGBW:    RGBW for SK6812RGBW
 */

struct cRGB  { uint8_t g; uint8_t r; uint8_t b; };
struct cRGBW { uint8_t g; uint8_t r; uint8_t b; uint8_t w;};



/* User Interface
 *
 * Input:
 *         ledarray:           An array of GRB data describing the LED colors
 *         number_of_leds:     The number of LEDs to write
 *         pinmask (optional): Bitmask describing the output bin. e.g. _BV(PB0)
 *
 * The functions will perform the following actions:
 *         - Set the data-out pin as output
 *         - Send out the LED data
 *         - Wait 50�s to reset the LEDs
 */

void ws2812_setleds     (LED_TYPE *ledarray, uint16_t number_of_leds);
void ws2812_setleds_pin (LED_TYPE *ledarray, uint16_t number_of_leds,uint8_t pinmask);
void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t number_of_leds);

/*
 * Old interface / Internal functions
 *
 * The functions take a byte-array and send to the data output as WS2812 bitstream.
 * The length is the number of bytes to send - three per LED.
 */

void ws2812_sendarray     (uint8_t *array,uint16_t length);
void ws2812_sendarray_mask(uint8_t *array,uint16_t length, uint8_t pinmask);


/*
 * Internal defines
 */
#ifndef CONCAT
#define CONCAT(a, b)            a ## b
#endif
#ifndef CONCAT_EXP
#define CONCAT_EXP(a, b)   CONCAT(a, b)
#endif

// #define ws2812_PORTREG  CONCAT_EXP(PORT,ws2812_port)
// #define ws2812_DDRREG   CONCAT_EXP(DDR,ws2812_port)

#endif /* LIGHT_WS2812_H_ */
