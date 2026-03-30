#pragma once

#include "common/led_drivers/side_driver.h"
#include "drivers/led/issi/is31fl3733.h"

// Initialize the IS31FL3733 driver
void is31fl3733_side_init(void);

// Set color for a specific LED
void is31fl3733_side_set_color(int index, uint8_t r, uint8_t g, uint8_t b);

// Refresh/push LED data to hardware
void is31fl3733_side_refresh(void);