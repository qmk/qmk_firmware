#include "joystick.h"

joystick_t joystick_status = { 
  .buttons = {0},
  .axes = {0},
  .status = 0
};

//array defining the reading of analog values for each axis
__attribute__ ((weak))
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {};
