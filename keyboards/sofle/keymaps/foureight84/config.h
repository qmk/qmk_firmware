#pragma once

#define EE_HANDS

/* clear default encoder def */
#undef TAP_CODE_DELAY

/* encoder support */
#define TAP_CODE_DELAY 100

#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define POINTING_DEVICE_ROTATION_90
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_TASK_THROTTLE_MS 8