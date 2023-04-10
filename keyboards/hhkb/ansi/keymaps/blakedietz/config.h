// Based off of this section:
// https://github.com/qmk/qmk_firmware/blob/master/doc/BUILD_GUIDE.md#the-configh-file
#ifndef CONFIG_BLAKEDIETZ_H
#define CONFIG_BLAKEDIETZ_H

// Bring in original defaults
#include "../../config.h"

// Define mousekey settings
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_MAX_SPEED      2
#define MOUSEKEY_TIME_TO_MAX    5
#define MOUSEKEY_WHEEL_DELAY    0

// Set up tapdance functionality
//#define TAPPING_TOGGLE  1
// TAPPING_TERM is set in config.h this defaults to 200

#endif
