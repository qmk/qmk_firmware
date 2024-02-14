/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

// No need for the single versions when multi performance isn't a problem =D
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH

// 20m timeout (20m * 60s * 1000mil)
// #define RGB_DISABLE_TIMEOUT 1200000
#define RGB_DISABLE_TIMEOUT 1200000
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define STM32_ONBOARD_EEPROM_SIZE 2048

#define MK_KINETIC_SPEED					true	// Enable kinetic mode
#define MOUSEKEY_DELAY					5	// Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL				10	// Time between cursor movements in milliseconds
#define MOUSEKEY_MOVE_DELTA				16	// Step size for accelerating from initial to base speed
#define MOUSEKEY_INITIAL_SPEED			500	// Initial speed of the cursor in pixel per second
#define MOUSEKEY_BASE_SPEED				5000	// Maximum cursor speed at which acceleration stops
#define MOUSEKEY_DECELERATED_SPEED			400	// Decelerated cursor speed
#define MOUSEKEY_ACCELERATED_SPEED			3000	// Accelerated cursor speed
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS	4	// Initial number of movements of the mouse wheel
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS		16	// Maximum number of movements at which acceleration stops
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS	48	// Accelerated wheel movements
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS	8	// Decelerated wheel movements


#define TAPPING_TERM 200
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
