

#pragma once
/* Includes ------------------------------------------------------------------*/
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID                       0x0903  /* <ldq> */
#define PRODUCT_ID                      0x0220  /* <cjl> */
#define DEVICE_VER                      0x0001
#define MANUFACTURER                    HMC
#define PRODUCT                         Duck_Blackbird_for XL
#define DESCRIPTION                     Duck_Blackbird_for XL
#define SERIAL_NUMBER                   00000000/* <序列号> */
#define BLE_KEYBOARD_NAME               "sp60"



/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* key matrix pins */
#define MATRIX_ROW_PINS {               \
                        LINE_ROW0,      \
                        LINE_ROW1,      \
                        LINE_ROW2,      \
                        LINE_ROW3,      \
                        LINE_ROW4,      \
                        LINE_ROW5       \
                        }

#define MATRIX_COL_PINS {               \
                        LINE_COL0,      \
                        LINE_COL1,      \
                        LINE_COL2,      \
                        LINE_COL3,      \
                        LINE_COL4,      \
                        LINE_COL5,      \
                        LINE_COL6,      \
                        LINE_COL7,      \
                        LINE_COL8,      \
                        LINE_COL9,      \
                        LINE_COL10,     \
                        LINE_COL11,     \
                        LINE_COL12,     \
                        LINE_COL13,     \
                        LINE_COL14,     \
                        LINE_COL15,     \
                        LINE_COL16      \
                        }
#define UNUSED_PINS

        /**<   二极管方向  */
// #define DIODE_DIRECTION COL2ROW
// 二极管反向
#define DIODE_DIRECTION ROW2COL

        /**<   去抖延时  */
#define DEBOUNCING_DELAY 5

        /**<   宏数量  */
#define DYNAMIC_KEYMAP_MACRO_COUNT 15
        /**<   Flash模拟eeprom  */
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  5120-1

        /**<   VIA 按键层数量  */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 100

#define VIA_CUSTOM_LIGHTING_ENABLE
/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#define RGB_DI_PIN           LINE_WS2812
#define RGBLED_TOTAL         4    //RGB灯的总数
#define RGBLED_KEY_LED       2       //轴灯的数量
#define DRIVER_LED_TOTAL     RGBLED_TOTAL
#define RGB_BOTTOM_LED_NUM   (RGBLED_TOTAL-RGBLED_KEY_LED)
#define RGBLED_NUM           (RGB_BOTTOM_LED_NUM)


#define RGBLIGHT_ANIMATIONS
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT     16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 160 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_HUE        100 // Sets the default hue value, if none has been set
#define RGB_MATRIX_STARTUP_SAT        255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_STARTUP_VAL        100 // Sets the default brightness value, if none has been set
#define RGB_MATRIX_STARTUP_SPD        127 // Sets the default animation speed, if none has been set


#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_BREATHE_MAX     255
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH   8
#define RGBLIGHT_EFFECT_SNAKE_LENGTH    8
#define RGBLIGHT_EFFECT_TWINKLE_LIFE    100
#define RGBLIGHT_DISABLE_KEYCODES
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_LIMIT_VAL              180


/* <RGB指示灯设置> */
#ifdef  LG_Indicator_Enable
   #define  CAPSLK_Indicator  0     /* <大小写灯的序号> */
   #define   NUMLK_Indicator  NO_LED  /* <NUMLK指示灯的序号> */
   #define   SCRLK_Indicator  NO_LED 
   #define   KANA_Indicator   NO_LED
   #define COMPOSE_Indicator  NO_LED
#endif


#ifdef VIA_CUSTOM_LIGHTING_ENABLE
/* <音乐律动相关参数设定> */
    #define RGB_LED_COL_MAX  19
    #define RGB_LED_ROW_MAX  6
#endif


//#define NO_USB_STARTUP_CHECK

