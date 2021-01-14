#pragma once

#include "quantum.h"

#define red_led_off writePinHigh(F5)
#define red_led_on  writePinLow(F5)
#define blu_led_off writePinHigh(F4)
#define blu_led_on  writePinLow(F4)
#define grn_led_off writePinHigh(D1)
#define grn_led_on  writePinLow(D1)

#define set_led_off     red_led_off; grn_led_off; blu_led_off
#define set_led_red     red_led_on;  grn_led_off; blu_led_off
#define set_led_blue    red_led_off; grn_led_off; blu_led_on
#define set_led_green   red_led_off; grn_led_on;  blu_led_off
#define set_led_yellow  red_led_on;  grn_led_on;  blu_led_off
#define set_led_magenta red_led_on;  grn_led_off; blu_led_on
#define set_led_cyan    red_led_off; grn_led_on;  blu_led_on
#define set_led_white   red_led_on;  grn_led_on;  blu_led_on

/*
#define LED_B 5
#define LED_R 6
#define LED_G 7

#define all_leds_off PORTF &= ~(1<<LED_B) & ~(1<<LED_R) & ~(1<<LED_G)

#define red_led_on   PORTF |= (1<<LED_R)
#define red_led_off  PORTF &= ~(1<<LED_R)
#define grn_led_on   PORTF |= (1<<LED_G)
#define grn_led_off  PORTF &= ~(1<<LED_G)
#define blu_led_on   PORTF |= (1<<LED_B)
#define blu_led_off  PORTF &= ~(1<<LED_B)

#define set_led_off     PORTF &= ~(1<<LED_B) & ~(1<<LED_R) & ~(1<<LED_G)
#define set_led_red     PORTF = PORTF & ~(1<<LED_B) & ~(1<<LED_G) | (1<<LED_R)
#define set_led_blue    PORTF = PORTF & ~(1<<LED_G) & ~(1<<LED_R) | (1<<LED_B)
#define set_led_green   PORTF = PORTF & ~(1<<LED_B) & ~(1<<LED_R) | (1<<LED_G)
#define set_led_yellow  PORTF = PORTF & ~(1<<LED_B) | (1<<LED_R) | (1<<LED_G)
#define set_led_magenta PORTF = PORTF & ~(1<<LED_G) | (1<<LED_R) | (1<<LED_B)
#define set_led_cyan    PORTF = PORTF & ~(1<<LED_R) | (1<<LED_B) | (1<<LED_G)
#define set_led_white   PORTF |= (1<<LED_B) | (1<<LED_R) | (1<<LED_G)
*/

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00,    k01, k02, k03, k04, k05, k06, k46, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k3F,\
    k10,    k11, k12, k13, k14, k15, k16, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k2F,\
    k20,    k21, k22, k23, k24, k25, k26, k28, k29, k2A, k2B, k2C, k2D, k2E,\
    k30,    k31, k32, k33, k34, k35, k36, k38, k39, k3A, k3B, k3C, k3D, k3E, \
    k40,    k41, k42, k43, k44, k45, k48, k49, k4A, k4C, k4D, k4E, k4F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, XXX, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, XXX, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, XXX, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, XXX, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, k43, k44, k45, k46, XXX, k48, k49, k4A, XXX, k4C, k4D, k4E, k4F } \
}
