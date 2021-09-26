#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4C4D
#define PRODUCT_ID      0x4C01
#define DEVICE_VER      0x0001
#define MANUFACTURER    LM STUDIO
#define PRODUCT         LMJ60


/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { B4, B5, B6, C6, C7 }
#define MATRIX_COL_PINS {F7,F6,F5,F4,F1,F0,E6,B0,B1,B2,B3,D0,D1,D2}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D4
#define RGBLIGHT_EFFECT_STATIC_GRADIEN//启用静态渐变模式。
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL//启用彩虹漩涡动画模式。
#define RGBLIGHT_EFFECT_BREATHING//呼吸动画

#define RGBLIGHT_LAYERS//启用动画层
#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF //RGB LAYERS在RGB关闭的情况下仍然有效，实现全局分层指示灯。

#define RGBLIGHT_EFFECT_BREATHE_MAX 255//限制亮度
#define RGBLED_NUM 16
#endif

#ifdef MK_COMBINED //鼠标速度
#define MK_3_SPEED
#define MK_C_OFFSET_UNMOD	12	//每次运动的光标偏移量（未修改）默认是16
#define MK_C_INTERVAL_UNMOD	16	//光标移动之间的时间（未修改）

#define MK_C_OFFSET_0	3       //个每次运动的光标偏移量（KC_ACL0）默认是1
#define MK_C_INTERVAL_0	16	     //光标移动之间的时间（KC_ACL0）默认是32

#define MK_C_OFFSET_1	5	//每次运动的光标偏移量（KC_ACL1）默认是4
#define MK_C_INTERVAL_1	4	//光标移动之间的时间（KC_ACL1）默认是16

#define MK_C_OFFSET_2	5	//每次运动的光标偏移量（KC_ACL2）默认是32
#define MK_C_INTERVAL_2	2	//光标移动之间的时间（KC_ACL2）默认是16
/*
#define MK_3_SPEED
#define MK_C_OFFSET_UNMOD	12	//每次运动的光标偏移量（未修改）默认是16
#define MK_C_INTERVAL_UNMOD	16	//光标移动之间的时间（未修改）

#define MK_C_OFFSET_0	5       //个每次运动的光标偏移量（KC_ACL0）默认是1
#define MK_C_INTERVAL_0	32	     //光标移动之间的时间（KC_ACL0）默认是32

#define MK_C_OFFSET_1	12	//每次运动的光标偏移量（KC_ACL1）默认是4
#define MK_C_INTERVAL_1	16	//光标移动之间的时间（KC_ACL1）默认是16

#define MK_C_OFFSET_2	16	//每次运动的光标偏移量（KC_ACL2）默认是32
#define MK_C_INTERVAL_2	16	//光标移动之间的时间（KC_ACL2）默认是16*/
#endif



#ifndef VIA
#define FORCE_NKRO  //修复via下无法全键无冲
#define VIA_HAS_BROKEN_KEYCODES//修复via键值
#endif


// #define MK_MOMENTARY_ACCEL
// #define MK_KINETIC_SPEED


// Max 32
#define JOYSTICK_BUTTON_COUNT 0
// Max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXES_COUNT 2
//摇杆


#endif
