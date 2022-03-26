#include "joystick.h"

// clang-format off
joystick_t joystick_status = {
    .buttons = {0},
    .axes = {
#if JOYSTICK_AXES_COUNT > 0
        0
#endif
    },
    .status = 0
};
// clang-format on

// array defining the reading of analog values for each axis
__attribute__((weak)) joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {};
