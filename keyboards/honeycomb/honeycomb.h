#ifndef honeycomb_H
#define honeycomb_H

#include "quantum.h"
#include "matrix.h"
#include "backlight.h"
#include <stddef.h>

#define red_led_off   PORTF |= (1<<6)
#define red_led_on    PORTF &= ~(1<<6)
#define blu_led_off   PORTF |= (1<<5)
#define blu_led_on    PORTF &= ~(1<<5)
#define grn_led_off   PORTD |= (1<<1)
#define grn_led_on    PORTD &= ~(1<<1)

#define set_led_off     red_led_off; grn_led_off; blu_led_off
#define set_led_red     red_led_on;  grn_led_off; blu_led_off
#define set_led_blue    red_led_off; grn_led_off; blu_led_on
#define set_led_green   red_led_off; grn_led_on;  blu_led_off
#define set_led_yellow  red_led_on;  grn_led_on;  blu_led_off
#define set_led_magenta red_led_on;  grn_led_off; blu_led_on
#define set_led_cyan    red_led_off; grn_led_on;  blu_led_on
#define set_led_white   red_led_on;  grn_led_on;  blu_led_on

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  k13, k14, k15, k16, \
  k09, k10, k11, k12, \
  k05, k06, k07, k08, \
  k01, k02, k03, k04  \
) \
{ \
	{ k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16 } \
}



#endif
