#pragma once

#include <stdint.h>

__attribute__((weak)) void side_mode_control(uint8_t dir);
__attribute__((weak)) void side_color_control(uint8_t dir);
__attribute__((weak)) void side_speed_control(uint8_t dir);
__attribute__((weak)) void side_brightness_control(uint8_t brighten);
