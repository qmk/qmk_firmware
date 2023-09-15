#pragma once
#include QMK_KEYBOARD_H
#include "custom_keycodes.h"

#ifdef JOYSTICK_ENABLE
#    include "gamepad.h"
#endif
#ifdef TAIPO_ENABLE
#    include "taipo.h"
#endif