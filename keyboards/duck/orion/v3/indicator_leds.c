/*
Copyright 2019 MechMerlin <mechmerlin@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "indicator_leds.h"
#include "duck_led/duck_led.h"

#define LED_T1H	600
#define LED_T1L 650
#define LED_T0H 250
#define LED_T0L 1000

void send_bit_d4(bool bitVal) {
  if(bitVal) {
    asm volatile (
        "sbi %[port], %[bit] \n\t"
        ".rept %[onCycles] \n\t"
        "nop \n\t"
        ".endr \n\t"
        "cbi %[port], %[bit] \n\t"
        ".rept %[offCycles] \n\t"
        "nop \n\t"
        ".endr \n\t"
        ::
        [port]      "I" (_SFR_IO_ADDR(PORTD)),
        [bit]       "I" (4),
        [onCycles]  "I" (NS_TO_CYCLES(LED_T1H) - 2),
        [offCycles] "I" (NS_TO_CYCLES(LED_T1L) - 2));
  } else {
    asm volatile (
        "sbi %[port], %[bit] \n\t"
        ".rept %[onCycles] \n\t"
        "nop \n\t"
        ".endr \n\t"
        "cbi %[port], %[bit] \n\t"
        ".rept %[offCycles] \n\t"
        "nop \n\t"
        ".endr \n\t"
        ::
        [port]      "I" (_SFR_IO_ADDR(PORTD)),
        [bit]       "I" (4),
        [onCycles]  "I" (NS_TO_CYCLES(LED_T0H) - 2),
        [offCycles] "I" (NS_TO_CYCLES(LED_T0L) - 2));
  }
}

void send_value(uint8_t byte, enum Device device) {
  for(uint8_t b = 0; b < 8; b++) {
    if(device == Device_STATUSLED) {
      send_bit_d4(byte & 0b10000000);
      byte <<= 1;
    }
  }
}

// Send the LED indicators to the WS2811S chips
void indicator_leds_set(bool leds[8]) {
  uint8_t led_cnt;

  cli();
  for(led_cnt = 0; led_cnt < 8; led_cnt++)
    send_value(leds[led_cnt] ? 255 : 0, Device_STATUSLED);
  sei();
  show();
}

