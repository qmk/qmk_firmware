
#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define VENDOR_ID       0x4F53  //defines your VID, and for most DIY projects, can be whatever you want, 0x4F53 OS for owl studio
#define PRODUCT_ID      0x5657  //VW for voice65 weld
#define DEVICE_VER      0x0002 //reversion 2 for weld
#define MANUFACTURER    OWL STUDIO 
#define PRODUCT         VOICE65_WELD
#define DESCRIPTION     A custom 65% Keyboard by owl studio

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B0, B1, B2, B10, B11 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A15, B8, B9, B12, B13 }


/* NKRO */
#ifdef NKRO_ENABLE
#         define FORCE_NKRO
#endif


#ifdef RGB_MATRIX_ENABLE
#    define USE_I2CV2
#    define DRIVER_ADDR_1 0b0110000
#    define DRIVER_ADDR_2 0b0110000
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 71
#    define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL 

#    define RGB_MATRIX_DISABLE_KEYCODES   
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects

#    define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 
#    define RGB_MATRIX_STARTUP_VAL     128 


#endif





#define RGB_DI_PIN B15

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 20
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_LIMIT_VAL 180    

#define OWL_VOLUME_RANGE 50
#endif




#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10

#define DEBOUNCING_DELAY 5

#define IS_COMMAND() ( \
     keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)



#endif