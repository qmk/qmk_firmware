#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_rgb_gradient_td
#    define RGB_DISABLE_TIMEOUT 600000 /* 10 minutes */
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES /* additional rgb modes */
#endif
