#pragma once

#include "quantum.h"

#if MCU == atmega32u2
#define red_led_off   writePinHigh(C5)
#define red_led_on    writePinLow(C5)
#define blu_led_off   writePinHigh(C4)
#define blu_led_on    writePinLow(C4)

#else
#define red_led_off   writePinHigh(F5)
#define red_led_on    writePinLow(F5)
#define blu_led_off   writePinHigh(F4)
#define blu_led_on    writePinLow(F4)

#endif

#define grn_led_off   writePinHigh(D1)
#define grn_led_on    writePinLow(D1)

#define set_led_off     red_led_off; blu_led_off
#define set_led_red     red_led_on;  grn_led_off; blu_led_off
#define set_led_blue    red_led_off; grn_led_off; blu_led_on
#define set_led_green   red_led_off; grn_led_on;  blu_led_off
#define set_led_yellow  red_led_on;  grn_led_on;  blu_led_off
#define set_led_magenta red_led_on;  grn_led_off; blu_led_on
#define set_led_cyan    red_led_off; grn_led_on;  blu_led_on
#define set_led_white   red_led_on;  grn_led_on;  blu_led_on

// For readability
#define ___ KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_split_3x6_3( \
  k0a, k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09, k0b, \
  k1a, k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19, k1b,\
  k2a, k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29, k2b,\
                 k32, k33, k34,      k35, k36, k37  \
) \
  {                                                       \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { ___, ___, k32, k33, k34, k35, k36, k37, ___, ___ }, \
    { ___, ___, k2a, k1a, k0a, k0b, k1b, k2b, ___, ___ }  \
  }

#define LAYOUT_split_3x5_3( \
  k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09, \
  k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19,\
  k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29,\
            k32, k33, k34,      k35, k36, k37  \
) \
  {                                                       \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { ___, ___, k32, k33, k34, k35, k36, k37, ___, ___ }, \
    { ___, ___, ___, ___, ___, ___, ___, ___, ___, ___ }  \
  }

#define LAYOUT LAYOUT_split_3x6_3
