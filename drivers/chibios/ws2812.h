#pragma once

#include "quantum/color.h"

/* User Interface
 *
 * Input:
 *         ledarray:           An array of GRB data describing the LED colors
 *         number_of_leds:     The number of LEDs to write
 *
 * The functions will perform the following actions:
 *         - Set the data-out pin as output
 *         - Send out the LED data
 *         - Wait 50us to reset the LEDs
 */
void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds);
