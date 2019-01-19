// Based off of this section:
// https://github.com/qmk/qmk_firmware/blob/master/doc/BUILD_GUIDE.md#the-configh-file
#ifndef CONFIG_SCHAEFERDEV_H
#define CONFIG_SCHAEFERDEV_H

// Bring in original defaults
#include "../../config.h"

// Define mousekey settings
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_INTERVAL       4
#define MOUSEKEY_MAX_SPEED      1
#define MOUSEKEY_TIME_TO_MAX    70
#define MOUSEKEY_WHEEL_DELAY    0
#define MOUSEKEY_WHEEL_MAX_SPEED   160
#define MOUSEKEY_WHEEL_TIME_TO_MAX 200


#endif