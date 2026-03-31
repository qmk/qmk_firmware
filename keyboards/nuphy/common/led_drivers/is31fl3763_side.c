#include "common/led_drivers/is31fl3763_side.h"
#include "drivers/led/issi/is31fl3763.h"
#include "color.h"

void is31fl3763_side_init(void) {
    // Initialize both drivers (left and right sides)
    is31fl3763_init(0);
#if DRIVER_COUNT > 1
    is31fl3763_init(1);
#endif
}

void is31fl3763_side_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    is31fl3763_set_color(index, r, g, b);
}

void is31fl3763_side_refresh(void) {
    // Update both drivers (left and right sides)
    is31fl3763_update_pwm_buffers(0);
#if DRIVER_COUNT > 1
    is31fl3763_update_pwm_buffers(1);
#endif
}