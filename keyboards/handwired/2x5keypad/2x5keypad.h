#pragma once

#include "quantum.h"

#define RED_LED D0
#define BLUE_LED B5
#define GREEN_LED B6

void turn_off_leds(void);
void turn_on_led(pin_t pin);
