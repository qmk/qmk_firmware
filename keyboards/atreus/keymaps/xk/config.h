/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define TAPPING_TOGGLE 1
#define TAPPING_TERM 300
#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_LAYER_TOGGLE 3
#define ONESHOT_TIMEOUT 800

#define MOUSEKEY_INTERVAL 50
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7

#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

#define PREVENT_STUCK_MODIFIERS
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

#endif