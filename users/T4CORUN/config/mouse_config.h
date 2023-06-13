#pragma once

/*
https://docs.qmk.fm/#/feature_mouse_keys

Notes:
I am only putting down settings for accelerated mode

Explore these:
#undef MOUSEKEY_MOVE_DELTA
#undef MOUSEKEY_WHEEL_DELAY
#undef MOUSEKEY_WHEEL_INTERVAL
#undef MOUSEKEY_WHEEL_MAX_SPEED
#undef MOUSEKEY_WHEEL_TIME_TO_MAX

other modes:
- Accelerated (default): Holding movement keys accelerates the cursor until it reaches its maximum speed.
- Kinetic: Holding movement keys accelerates the cursor with its speed following a quadratic curve until it reaches its maximum speed.
- Constant: Holding movement keys moves the cursor at constant speeds.
- Combined: Holding movement keys accelerates the cursor until it reaches its maximum speed, but holding acceleration and movement keys simultaneously moves the cursor at constant speeds.
- Inertia: Cursor accelerates when key held, and decelerates after key release. Tracks X and Y velocity separately for more nuanced movements. Applies to cursor only, not scrolling.


https://docs.qmk.fm/#/feature_pointing_device

notes:
there are way more settings but I don't want to mess anything that Quentin set for the nano
I will only include stuff for auto mouse layer

Explore These:
#undef AUTO_MOUSE_DELAY
#undef AUTO_MOUSE_DEBOUNCE
#undef AUTO_MOUSE_DEFAULT_LAYER
*/

//Clear variables we plan to use that might be set elsewhere
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_TIME_TO_MAX
#undef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#undef AUTO_MOUSE_TIME



//Set common configuration for all keyboards
#if defined(MOUSEKEY_ENABLE)
#   define MOUSEKEY_INTERVAL 12
#   define MOUSEKEY_MAX_SPEED 6
#   define MOUSEKEY_TIME_TO_MAX 50
#   define MOUSEKEY_DELAY 20
#endif //MOUSEKEY_ENABLE

#if defined(AUTOMOUSE_ENABLE)
#   define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#   define AUTO_MOUSE_TIME 300
#endif //AUTOMOUSE_ENABLED