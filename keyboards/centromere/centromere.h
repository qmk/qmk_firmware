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
