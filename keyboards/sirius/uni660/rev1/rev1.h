#pragma once

#include "quantum.h"

#define UNI660_RED_LED_PIN F5
#define UNI660_GREEN_LED_PIN D1
#define UNI660_BLUE_LED_PIN F4

#define red_led_off gpio_write_pin_high(UNI660_RED_LED_PIN)
#define red_led_on  gpio_write_pin_low(UNI660_RED_LED_PIN)
#define blu_led_off gpio_write_pin_high(UNI660_BLUE_LED_PIN)
#define blu_led_on  gpio_write_pin_low(UNI660_BLUE_LED_PIN)
#define grn_led_off gpio_write_pin_high(UNI660_GREEN_LED_PIN)
#define grn_led_on  gpio_write_pin_low(UNI660_GREEN_LED_PIN)

#define set_led_off     red_led_off; grn_led_off; blu_led_off
#define set_led_red     red_led_on;  grn_led_off; blu_led_off
#define set_led_blue    red_led_off; grn_led_off; blu_led_on
#define set_led_green   red_led_off; grn_led_on;  blu_led_off
#define set_led_yellow  red_led_on;  grn_led_on;  blu_led_off
#define set_led_magenta red_led_on;  grn_led_off; blu_led_on
#define set_led_cyan    red_led_off; grn_led_on;  blu_led_on
#define set_led_white   red_led_on;  grn_led_on;  blu_led_on
