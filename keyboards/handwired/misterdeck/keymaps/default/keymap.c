#include QMK_KEYBOARD_H
#include "joystick.h"

enum layers {
  NORMAL_LAYER = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [NORMAL_LAYER] = LAYOUT( C(S(KC_F1)), C(S(KC_F2)), C(S(KC_F3)), C(S(KC_F4)),
			   C(S(KC_F5)), C(S(KC_F6)), C(S(KC_F7)), C(S(KC_F8)),
			   JS_BUTTON0,  JS_BUTTON1,  JS_BUTTON2,  JS_BUTTON3 ),
};



joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_IN(F4, 0, 512, 1023),
    [1] = JOYSTICK_AXIS_IN(F5, 0, 512, 1023),
    [2] = JOYSTICK_AXIS_IN(F6, 0, 512, 1023),
    [3] = JOYSTICK_AXIS_IN(F7, 0, 512, 1023)
};
