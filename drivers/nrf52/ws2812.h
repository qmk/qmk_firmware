/*
 * light weight WS2812 lib include
 *
 * Version 2.3  - Nev 29th 2015
 * Author: Tim (cpldcpu@gmail.com)
 *
 * Please do not change this file! All configuration is handled in "ws2812_config.h"
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_


#include <stdint.h>
#include "ws2812.h"
#include "color.h"

#include "apidef.h"


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
 *         - Wait 50�ｿｽs to reset the LEDs
 */

void ws2812_setleds     (LED_TYPE *ledarray, uint16_t number_of_leds);
static inline void ws2812_setleds_pin (LED_TYPE *ledarray, uint16_t number_of_leds,uint8_t pinmask)
{
  BMPAPI->ws2812.setleds_pin((bmp_api_led_t*)ledarray, number_of_leds, BMPAPI->app.get_config()->led.pin); // ignore pinmask
}
void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t number_of_leds);


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
