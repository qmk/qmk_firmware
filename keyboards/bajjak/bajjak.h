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

#define LAYOUT_6x7( \
                        L00, L01, L02, L03, L04, L05, L06,  R00, R01, R02, R03, R04, R05, R06, \
                        L10, L11, L12, L13, L14, L15, L16,  R10, R11, R12, R13, R14, R15, R16, \
                        L20, L21, L22, L23, L24, L25, L26,  R20, R21, R22, R23, R24, R25, R26, \
                        L30, L31, L32, L33, L34, L35, L36,  R30, R31, R32, R33, R34, R35, R36, \
                        L40, L41, L42, L43, L44, L45,            R41, R42, R43, R44, R45, R46, \
                        L50, L51, L52, L53, L54,                      R52, R53, R54, R55, R56, \
                                                 L65, L66,  R60, R61,                          \
                                                      L64,  R62,                               \
                                            L63, L62, L61,  R65, R64, R63                      \
                        ) { \
        { L00, L10, L20, L30, L40,   L50,   KC_NO }, \
        { L01, L11, L21, L31, L41,   L51,   L61   }, \
        { L02, L12, L22, L32, L42,   L52,   L62   }, \
        { L03, L13, L23, L33, L43,   L53,   L63   }, \
        { L04, L14, L24, L34, L44,   L54,   L64   }, \
        { L05, L15, L25, L35, L45,   KC_NO, L65   }, \
        { L06, L16, L26, L36, KC_NO, KC_NO, L66   }, \
        { R00, R10, R20, R30, KC_NO, KC_NO, R60   }, \
        { R01, R11, R21, R31, R41,   KC_NO, R61   }, \
        { R02, R12, R22, R32, R42,   R52,   R62   }, \
        { R03, R13, R23, R33, R43,   R53,   R63   }, \
        { R04, R14, R24, R34, R44,   R54,   R64   }, \
        { R05, R15, R25, R35, R45,   R55,   R65   },\
        { R06, R16, R26, R36, R46,   R56,   KC_NO } \
    }
