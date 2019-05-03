#ifndef PROMETHIUM_H
#define PROMETHIUM_H

#include "stdint.h"

void battery_poll(uint8_t level);
void led_set_kb(uint8_t usb_led);
void led_set_user(uint8_t usb_led);

#define LAYOUT( \
    k11, k12, k13, k14, k15, k16,      k17, k18, k19, k1a, k1b, k1c, \
    k21, k22, k23, k24, k25, k26,      k27, k28, k29, k2a, k2b, k2c, \
    k31, k32, k33, k34, k35, k36,      k37, k38, k39, k3a, k3b, k3c, \
    k41, k42, k43, k44, k45, k46,      k47, k48, k49, k4a, k4b, k4c, \
                             tp1, tp2, tp3 \
) \
{ \
    {k11, k12, k13, k14,   k15,   k16}, \
    {k21, k22, k23, k24,   k25,   k26}, \
    {k31, k32, k33, k34,   k35,   k36}, \
    {k41, k42, k43, k44,   k45,   k46}, \
    {k17, k18, k19, k1a,   k1b,   k1c}, \
    {k27, k28, k29, k2a,   k2b,   k2c}, \
    {k37, k38, k39, k3a,   k3b,   k3c}, \
    {k47, k48, k49, k4a,   k4b,   k4c}, \
    {tp1, tp2, tp3, KC_NO, KC_NO, KC_NO}  \
}

#endif
