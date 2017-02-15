#ifndef PROMETHIUM_H
#define PROMETHIUM_H

#include "stdint.h"

void battery_poll(uint8_t level);
void led_set_kb(uint8_t usb_led);
void led_set_user(uint8_t usb_led);

#endif
