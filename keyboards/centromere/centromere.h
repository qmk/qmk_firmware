#pragma once

#include "quantum.h"

#if MCU == atmega32u2
#define red_led_off   gpio_write_pin_high(C5)
#define red_led_on    gpio_write_pin_low(C5)
#define blu_led_off   gpio_write_pin_high(C4)
#define blu_led_on    gpio_write_pin_low(C4)

#else
#define red_led_off   gpio_write_pin_high(F5)
#define red_led_on    gpio_write_pin_low(F5)
#define blu_led_off   gpio_write_pin_high(F4)
#define blu_led_on    gpio_write_pin_low(F4)

#endif

#define grn_led_off   gpio_write_pin_high(D1)
#define grn_led_on    gpio_write_pin_low(D1)

#define set_led_off     red_led_off; blu_led_off
#define set_led_red     red_led_on;  grn_led_off; blu_led_off
#define set_led_blue    red_led_off; grn_led_off; blu_led_on
#define set_led_green   red_led_off; grn_led_on;  blu_led_off
#define set_led_yellow  red_led_on;  grn_led_on;  blu_led_off
#define set_led_magenta red_led_on;  grn_led_off; blu_led_on
#define set_led_cyan    red_led_off; grn_led_on;  blu_led_on
#define set_led_white   red_led_on;  grn_led_on;  blu_led_on
