#pragma once

/* Use I2C rather than serial communicaiton to reduce latency. */
#define USE_I2C

/* Turn off RGB lighting when the host goes to sleep. */
#define RGBLIGHT_SLEEP

/* Use an extra LED on the right side since it's wider on the 65% PCB. */
#undef RGBLED_NUM
#define RGBLED_NUM 17

/* Set up RGB lighting so it works with either side as master. */
#define RGBLED_SPLIT { 8, 9 }

/* Make mouse operation smoother. */
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16

/* Lower mouse speed to adjust for reduced MOUSEKEY_INTERVAL. */
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_TIME_TO_MAX 150
#define MOUSEKEY_WHEEL_MAX_SPEED 4
#define MOUSEKEY_WHEEL_TIME_TO_MAX 150
