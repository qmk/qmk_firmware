#pragma once

#include "report.h"
#include "pointing_device.h"
#include "quantum.h"

#define red_led_off()   writePinHigh(F6)
#define red_led_on()    writePinLow(F6)
#define blu_led_off()   writePinHigh(F5)
#define blu_led_on()    writePinLow(F5)
#define grn_led_off()   writePinHigh(D1)
#define grn_led_on()    writePinLow(D1)

#define red_led(flag)   if (flag) red_led_on(); else red_led_off()
#define blu_led(flag)   if (flag) blu_led_on(); else blu_led_off()
#define grn_led(flag)   if (flag) grn_led_on(); else grn_led_off()

#define set_led_off()     red_led_off(); grn_led_off(); blu_led_off()
#define set_led_red()     red_led_on();  grn_led_off(); blu_led_off()
#define set_led_blue()    red_led_off(); grn_led_off(); blu_led_on()
#define set_led_green()   red_led_off(); grn_led_on();  blu_led_off()
#define set_led_yellow()  red_led_on();  grn_led_on();  blu_led_off()
#define set_led_magenta() red_led_on();  grn_led_off(); blu_led_on()
#define set_led_cyan()    red_led_off(); grn_led_on();  blu_led_on()
#define set_led_white()   red_led_on();  grn_led_on();  blu_led_on()
