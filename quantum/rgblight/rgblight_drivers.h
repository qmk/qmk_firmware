#pragma once

#include <stdint.h>
#include "color.h"

typedef struct {
    void (*setleds)(rgb_led_t *ledarray, uint16_t number_of_leds);
} rgblight_driver_t;

extern const rgblight_driver_t rgblight_driver;
