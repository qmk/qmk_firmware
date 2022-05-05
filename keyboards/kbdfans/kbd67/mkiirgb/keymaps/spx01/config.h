#pragma once

/* --- custom defines only used in my own code --- */

/* easily switch on debugging features */
#define CUSTOM_DEBUG false

/* hexrgb mode special keys, these shouldn't be KC_A to KC_F or KC_0 to KC_9 */
/* keycode that triggers saving the current rgb_static color into eeprom */
#define HEXRGB_SAVE_KC KC_S
/* keycode that triggers resetting rgb_static to the color saved in the eeprom */
#define HEXRGB_RESET_KC KC_R

/* --- keyboard configuration macros --- */

#define USB_POLLING_INTERVAL_MS 2

#if CUSTOM_DEBUG
#    define NO_DEBUG
#    define NO_PRINT
#endif

#define RETRO_TAPPING
#define PERMISSIVE_HOLD

#undef RGB_MATRIX_STARTUP_MODE
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_RGB_STATIC
