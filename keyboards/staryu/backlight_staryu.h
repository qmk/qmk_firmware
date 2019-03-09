#ifndef STARYU_BL
#define STARYU_BL

#include <stdint.h>

void init_backlight_led(void);

void backlight_led_on(uint8_t index);

void backlight_led_off(uint8_t index);

#endif
