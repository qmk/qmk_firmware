#pragma once
/* USB Device descriptor parameter */
#define VENDOR_ID                       0x0903
#define PRODUCT_ID                      0x0220
#define DEVICE_VER                      0x0001

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* key matrix pins */
#define MATRIX_ROW_PINS {B5,B4,B3,A15,A1,A2}

#define MATRIX_COL_PINS {A10,A9,A8,B15,B14,B13,B12,B11,B10,B2,B0,A7,A6,B1,A5,A4,A3}

#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCING_DELAY 5

#define DYNAMIC_KEYMAP_MACRO_COUNT 16

#define FEE_PAGE_COUNT 5

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define VIA_CUSTOM_LIGHTING_ENABLE
/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#ifdef HOT_PLUG
    #define RGB_DI_PIN           A0
    #define DRIVER_LED_TOTAL     91+27+8
    #define RGB_MATRIX_CENTER    {12*8, 36}
#endif

#ifdef WELDING
    #define RGB_DI_PIN           A0
    #define DRIVER_LED_TOTAL     100+27+8
    #define RGB_MATRIX_CENTER    {12*8, 36}
#endif

#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT     16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 170 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_HUE        100 // Sets the default hue value, if none has been set
#define RGB_MATRIX_STARTUP_SAT        255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_STARTUP_VAL        100 // Sets the default brightness value, if none has been set
#define RGB_MATRIX_STARTUP_SPD        127 // Sets the default animation speed, if none has been set

