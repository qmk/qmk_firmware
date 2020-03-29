#include QMK_KEYBOARD_H

#include "joystick.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( JS_BUTTON0 )
};
//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
  [0] = JOYSTICK_AXIS_IN(A0, 0, 512, 1024)
};