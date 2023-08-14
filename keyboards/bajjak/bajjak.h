/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
Copyright 2021 Gary Kong <kongkm88@gmail.com> (@garykong)

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

#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern i2c_status_t mcp23018_status;
#define BAJJAK_EZ_I2C_TIMEOUT 100

void init_bajjak(void);
void bajjak_blink_all_leds(void);
uint8_t init_mcp23018(void);
uint8_t bajjak_left_leds_update(void);

#ifndef LED_BRIGHTNESS_LO
#define LED_BRIGHTNESS_LO       15
#endif
#ifndef LED_BRIGHTNESS_HI
#define LED_BRIGHTNESS_HI       255
#endif


inline void bajjak_board_led_on(void)      { setPinOutput(D6); writePinHigh(D6); }
inline void bajjak_right_led_1_on(void)    { setPinOutput(B5); writePinHigh(B5); }
inline void bajjak_right_led_2_on(void)    { setPinOutput(B6); writePinHigh(B6); }
inline void bajjak_right_led_3_on(void)    { setPinOutput(B7); writePinHigh(B7); }
inline void bajjak_right_led_on(uint8_t led) { setPinOutput(led+4); writePinHigh(led+4); }

inline void bajjak_board_led_off(void)     { setPinInput(D6); writePinLow(D6); }
inline void bajjak_right_led_1_off(void)   { setPinInput(B5); writePinLow(B5); }
inline void bajjak_right_led_2_off(void)   { setPinInput(B6); writePinLow(B6); }
inline void bajjak_right_led_3_off(void)   { setPinInput(B7); writePinLow(B7); }
inline void bajjak_right_led_off(uint8_t led) { setPinInput(led+4); writePinLow(led+4); }

#ifdef LEFT_LEDS
bool bajjak_left_led_1;
bool bajjak_left_led_2;
bool bajjak_left_led_3;

inline void bajjak_left_led_1_on(void)    { bajjak_left_led_1 = 1; }
inline void bajjak_left_led_2_on(void)    { bajjak_left_led_2 = 1; }

inline void bajjak_left_led_1_off(void)    { bajjak_left_led_1 = 0; }
inline void bajjak_left_led_2_off(void)    { bajjak_left_led_2 = 0; }
#endif // LEFT_LEDS

inline void bajjak_led_all_on(void) {
    bajjak_board_led_on();
    bajjak_right_led_1_on();
    bajjak_right_led_2_on();
    bajjak_right_led_3_on();
#ifdef LEFT_LEDS
    bajjak_left_led_1_on();
    bajjak_left_led_2_on();
#endif // LEFT_LEDS
}

inline void bajjak_led_all_off(void)
{
    bajjak_board_led_off();
    bajjak_right_led_1_off();
    bajjak_right_led_2_off();
    bajjak_right_led_3_off();
#ifdef LEFT_LEDS
    bajjak_left_led_1_off();
    bajjak_left_led_2_off();
#endif // LEFT_LEDS
}

inline void bajjak_right_led_1_set(uint8_t n)    { OCR1A = n; }
inline void bajjak_right_led_2_set(uint8_t n)    { OCR1B = n; }
inline void bajjak_right_led_3_set(uint8_t n)    { OCR1C = n; }
inline void bajjak_right_led_set(uint8_t led, uint8_t n)  {
    (led == 1) ? (OCR1A = n) :
    (led == 2) ? (OCR1B = n) :
                 (OCR1C = n);
}

inline void bajjak_led_all_set(uint8_t n) {
    bajjak_right_led_1_set(n);
    bajjak_right_led_2_set(n);
    bajjak_right_led_3_set(n);
}

typedef union {
  uint32_t raw;
  struct {
    uint8_t    led_level :3;
    bool       disable_layer_led   :1;
  };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
