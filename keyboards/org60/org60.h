#pragma once

#include "quantum.h"
#include "led.h"

/* Org60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 RGB PWM Underglow
 *   2 F5 Backlight LED
 *   3 F4 not connected
 *   B2 Capslock LED
 *   B0 not connected
 */
inline void org60_caps_led_on(void)    { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void org60_bl_led_on(void)    	{ DDRF |=  (1<<5); PORTF &= ~(1<<5); }

inline void org60_caps_led_off(void)   { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }
inline void org60_bl_led_off(void)   	{ DDRF &= ~(1<<5); PORTF &= ~(1<<5); }

#define XXX KC_NO

/* Org60 Keymap Definition Macro */
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k49, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k47, k3D, k3C, \
    k40, k41, k42,           k45,                     k4A, k4B, k48, k4C, k4D \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, k47, k48, k49, k4A, k4B, k4C, k4D } \
}

#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,      k2D, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, \
    k40, k41, k42,           k45,                     k4A, k4B, k4C, k4D \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, XXX, k2D }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4A, k4B, k4C, k4D } \
}
