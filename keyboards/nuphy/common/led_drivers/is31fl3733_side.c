#include "common/led_drivers/is31fl3733_side.h"
#include "drivers/led/issi/is31fl3733.h"
#include "color.h"

void is31fl3733_side_init(void) {
    // Initialize all drivers via QMK's init function
    is31fl3733_init_drivers();
}

void is31fl3733_side_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    is31fl3733_set_color(index, r, g, b);
}

void is31fl3733_side_refresh(void) {
    // Update all drivers via QMK's flush function
    is31fl3733_flush();
}