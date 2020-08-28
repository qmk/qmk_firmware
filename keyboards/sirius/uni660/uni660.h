#pragma once

#include "quantum.h"

#ifdef KEYBOARD_sirius_uni660_rev1
    #include "rev1.h"
#elif KEYBOARD_sirius_uni660_rev2_iso
    #include "iso.h"
#elif KEYBOARD_sirius_uni660_rev2_ansi
	#include "ansi.h"
#endif

#define red_led_off   writePinHigh(F5)
#define red_led_on    writePinLow(F5)
#define blu_led_off   writePinHigh(F4)
#define blu_led_on    writePinLow(F4)
#define grn_led_off   writePinHigh(D1)
#define grn_led_on    writePinLow(D1)

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
