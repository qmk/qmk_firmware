#pragma once


#include "tapping_config.h"
#if defined(RGB_MATRIX_ENABLE)
#   include "rgb_matrix_config.h"
#endif //RGB_MATRIX_ENABLE
#if defined(COMBO_ENABLE)
#   include "combo_config.h"
#endif //COMBO_ENABLE
#if defined(MOUSEKEY_ENABLE) || defined(POINTING_DEVICE_ENABLE)
#   include "mouse_config.h"
#endif //MOUSEKEY_ENABLE

//Turn off settings we won't use to save memory
#define NO_ACTION_ONESHOT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

//Clear variables that might have been defined elsewhere
#undef USB_POLLING_INTERVAL_MS


//Set common configuration for all keyboards
#define USB_POLLING_INTERVAL_MS 1         //default varies, either 1 or 10
