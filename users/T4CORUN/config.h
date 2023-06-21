#pragma once

/*
https://docs.qmk.fm/#/squeezing_avr?id=configh-settings
https://docs.qmk.fm/#/config_options?id=hardware-options
*/

#include "config\tapping_config.h"

#if defined(RGB_MATRIX_ENABLE)
#   include "config\rgbmatrix_config.h"
#endif //RGB_MATRIX_ENABLE

#if defined(COMBO_ENABLE)
#   include "config\combo_config.h"
#endif //COMBO_ENABLE

#if defined(CAPS_WORD_ENABLE)
#   include "config\capsword_config.h"
#endif //COMBO_ENABLE

#if defined(MOUSEKEY_ENABLE) || defined(POINTING_DEVICE_ENABLE)
#   include "config\mouse_config.h"
#endif //MOUSEKEY_ENABLE


//Turn off settings we won't use to save memory
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

//Clear variables we plan to use that might be set elsewhere
#undef USB_POLLING_INTERVAL_MS
#undef SPLIT_TRANSPORT_MIRROR
#undef SPLIT_LAYER_STATE_ENABLE
#undef SPLIT_LED_STATE_ENABLE
#undef SPLIT_MODS_ENABLE
#undef SPLIT_USB_DETECT

//Set common configuration for all keyboards
#define USB_POLLING_INTERVAL_MS 1

#if defined(SPLIT_KEYBOARD)
#   define SPLIT_TRANSPORT_MIRROR
#   define SPLIT_LAYER_STATE_ENABLE
#   define SPLIT_LED_STATE_ENABLE
#   define SPLIT_MODS_ENABLE
//#   define SPLIT_USB_DETECT
#endif //SPLIT_KEYBOARD
