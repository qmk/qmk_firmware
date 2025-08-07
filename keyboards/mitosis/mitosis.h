#pragma once

#include "quantum.h"

#define MITOSIS_RED_LED_PIN F5
#define MITOSIS_GREEN_LED_PIN D1
#define MITOSIS_BLUE_LED_PIN F4

#define red_led_off   gpio_write_pin_high(MITOSIS_RED_LED_PIN)
#define red_led_on    gpio_write_pin_low(MITOSIS_RED_LED_PIN)
#define blu_led_off   gpio_write_pin_high(MITOSIS_BLUE_LED_PIN)
#define blu_led_on    gpio_write_pin_low(MITOSIS_BLUE_LED_PIN)
#define grn_led_off   gpio_write_pin_high(MITOSIS_GREEN_LED_PIN)
#define grn_led_on    gpio_write_pin_low(MITOSIS_GREEN_LED_PIN)

#define set_led_off     red_led_off; grn_led_off; blu_led_off
#define set_led_red     red_led_on;  grn_led_off; blu_led_off
#define set_led_blue    red_led_off; grn_led_off; blu_led_on
#define set_led_green   red_led_off; grn_led_on;  blu_led_off
#define set_led_yellow  red_led_on;  grn_led_on;  blu_led_off
#define set_led_magenta red_led_on;  grn_led_off; blu_led_on
#define set_led_cyan    red_led_off; grn_led_on;  blu_led_on
#define set_led_white   red_led_on;  grn_led_on;  blu_led_on
