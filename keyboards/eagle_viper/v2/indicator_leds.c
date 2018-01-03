/*
Copyright 2017 MechMerlin <mechmerlin@gmail.com>

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
#include "quantum.h"

#define T1H  900
#define T1L  600
#define T0H  400
#define T0L  900
#define RES 6000

#define LED_T1H	600
#define LED_T1L 650
#define LED_T0H 250
#define LED_T0L 1000

#define NS_PER_SEC (1000000000L)
#define CYCLES_PER_SEC (F_CPU)
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)

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

void send_bit_d6(bool bitVal)
{
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
        [bit]       "I" (6),
        [onCycles]  "I" (NS_TO_CYCLES(T1H) - 2),
        [offCycles] "I" (NS_TO_CYCLES(T1L) - 2));
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
        [bit]       "I" (6),
        [onCycles]  "I" (NS_TO_CYCLES(T0H) - 2),
        [offCycles] "I" (NS_TO_CYCLES(T0L) - 2));
  }
}

void show(void) {
  _delay_us((RES / 1000UL) + 1);
}

void send_value(uint8_t byte, enum Device device) {
  for(uint8_t b = 0; b < 8; b++) {
    if(device == Device_STATUSLED) {
      send_bit_d4(byte & 0b10000000);
    }
    if(device == Device_PCBRGB) {
      send_bit_d6(byte & 0b10000000);
    }
    byte <<= 1;
  }
}

void send_color(uint8_t r, uint8_t g, uint8_t b, enum Device device) {
  send_value(g, device);
  send_value(r, device);
  send_value(b, device);
}

// Port from backlight_set_state
void indicator_leds_set(bool leds[8]) {
  uint8_t send_bytes[9];
  uint8_t led_cnt;

  for(led_cnt = 0; led_cnt < 8; led_cnt++)
    send_bytes[led_cnt] = leds[led_cnt] ? 255 : 0;

/*
  send_bytes[0] = 255; // LED 3 
  send_bytes[1] = 0; // LED 2
  send_bytes[2] = 255; // LED 1
  send_bytes[3] = 0; // LED 6
  send_bytes[4] = 255; // LED 5
  send_bytes[5] = 0; // LED 4
  send_bytes[6] = 0; // LED 8 
  send_bytes[7] = 255; // LED 7
  send_bytes[8] = 0; // NC
*/
  cli();
  for(led_cnt = 0; led_cnt < 8; led_cnt++)
    send_value(send_bytes[led_cnt], Device_STATUSLED);
  sei();
  show();
}
