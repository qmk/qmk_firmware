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

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05,      k06, k07, k08, k09, k0A, k0B, \
    k10, k11, k12, k13, k14, k15,      k16, k17, k18, k19, k1A, k1B, \
    k20, k21, k22, k23, k24, k25,      k26, k27, k28, k29, k2A, k2B, \
                   k33, k34, k35,      k36, k37, k38, \
              k42, k43, k44, k45,      k46, k47, k48, k49 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B }, \
    { XXX, XXX, XXX, k33, k34, k35, k36, k37, k38, XXX, XXX, XXX }, \
    { XXX, XXX, k42, k43, k44, k45, k46, k47, k48, k49, XXX, XXX } \
}
