#pragma once

//Clear variables that might have been defined elsewhere
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_DELAY
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