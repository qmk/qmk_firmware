#include "common/led_drivers/is31fl3763_side.h"
#include "drivers/led/issi/is31fl3763.h"
#include "color.h"

// IS31FL3763 driver index for side LEDs
#define IS31FL3763_SIDE_DRIVER_INDEX 0

void is31fl3763_side_init(void) {
    is31fl3763_init(IS31FL3763_SIDE_DRIVER_INDEX);
}

void is31fl3763_side_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    is31fl3763_set_color(index, r, g, b);
}

void is31fl3763_side_refresh(void) {
    is31fl3763_update_pwm_buffers(IS31FL3763_SIDE_DRIVER_INDEX);
}