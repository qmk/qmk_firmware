#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xECED
#define PRODUCT_ID      0x3663
#define DEVICE_VER      0x0001
#define MANUFACTURER    Fancytech
#define PRODUCT         FancyAlice66
#define DESCRIPTION     keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7, C7 }
#define MATRIX_COL_PINS { C6, E6, B5, B4, D7, D6, D4, D5, D3, D2, D1, D0, B7, B3, B2, B1 }


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL
//#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS



#define QMK_KEYS_PER_SCAN 12

#ifdef RGB_MATRIX_ENABLE



// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN B0
// The number of LEDs connected
//#define DRIVER_LED_TOTAL 66
#define DRIVER_LED_TOTAL 82
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED false
#define RGB_MATRIX_CENTER {105,  32}
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50

/* RGB Matrix effect */
#define ENABLE_RGB_MATRIX_ALPHAS_MODS                   // 静态双色相，速度为二级色相的色相
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN              // 静态渐变从上到下，速度控制渐变变化多少
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT           // 静态渐变从左到右，速度控制渐变变化多少
#define ENABLE_RGB_MATRIX_BREATHING                     // 单色调亮度循环动画
#define ENABLE_RGB_MATRIX_BAND_SAT                      // 单色带渐变饱和度从左到右滚动
#define ENABLE_RGB_MATRIX_BAND_VAL                      // 单色带渐变亮度从左到右滚动
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT             // 单色 3 叶片旋转风车淡化饱和度
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL             // 单色 3 叶片旋转风车衰减亮度
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT               // 单色旋转螺旋渐变饱和度
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL               // 单色旋转螺旋渐变亮度 
#define ENABLE_RGB_MATRIX_CYCLE_ALL                     // 全键盘纯色循环通过全渐变
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT              // 从左到右全渐变滚动
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN                 // 从上到下全渐变滚动
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON        // 全梯度雪佛龙形状从左到右滚动
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN                  // 完全渐变向内滚动
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL             // 完全双渐变向外滚动
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL                // 围绕键盘中心的全梯度旋转风车
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL                  // 围绕键盘中心的全梯度旋转螺旋
#define ENABLE_RGB_MATRIX_DUAL_BEACON                   // 围绕键盘中心旋转的全渐变
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON                // 围绕键盘中心旋转的更紧密的渐变
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS             // 旋转两半键盘的全双渐变
#define ENABLE_RGB_MATRIX_RAINDROPS                     // 随机改变单个键的色调
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS           // 随机改变单个键的色调和饱和度
#define ENABLE_RGB_MATRIX_HUE_BREATHING                 // 色调同时略微上移，然后再移回
#define ENABLE_RGB_MATRIX_HUE_PENDULUM                  // 色调以波浪的形式向右移动一点，然后回到左侧
#define ENABLE_RGB_MATRIX_HUE_WAVE                      // 色相略微上移，然后以波浪的形式向右下移
#define ENABLE_RGB_MATRIX_PIXEL_RAIN                    // 随机点亮具有随机色调的键
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL                 // 单色调分形填充键水平脉冲到边缘

/* #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE         // 脉冲键击中色调和值，然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE                // 静态单一色调，脉冲键击中移动色调然后淡入当前色调
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE           // 单次按键附近的色调和值脉冲然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE      // 多个键击附近的色调和值脉冲然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS          // 色调和值脉冲单个键击的同一列和行，然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS     // 色相和值脉冲多个键击的同一列和行，然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS          // 色调和值在单个键击的同一列和行上脉冲消失，然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS     // 色相和值在多个键击的同一列和行上脉冲消失，然后淡出值
#define ENABLE_RGB_MATRIX_SPLASH                        // 完全梯度和值脉冲远离单个键击然后淡出值
#define ENABLE_RGB_MATRIX_MULTISPLASH                   // 远离多个键击的全梯度和值脉冲然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_SPLASH                  // 色调和值脉冲远离单个键击然后淡出值
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH             // 远离多个按键的色调和值脉冲然后淡出值 */

#endif



#ifdef ENCODER_ENABLE

#define ENCODERS_PAD_A { F0 }
#define ENCODERS_PAD_B { F1 }
//#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION  2

#endif


#define FORCE_NKRO


//#ifdef BACKLIGHT_ENABLE

/* number of backlight levels */
//#define BACKLIGHT_PIN B6
//#define BACKLIGHT_BREATHING
//#define BACKLIGHT_LEVELS 3

//#define BACKLIGHT_ON_STATE 1
/*#define BREATHING_PERIOD 4
#define BACKLIGHT_LIMIT_VAL 24
#define BACKLIGHT_DEFAULT_LEVEL BACKLIGHT_LEVELS
#define BACKLIGHT_DEFAULT_BREATHING */


//#endif

#endif
