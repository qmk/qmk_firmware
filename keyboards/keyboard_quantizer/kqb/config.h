
#pragma once

#undef PRODUCT_ID
#define PRODUCT_ID   0x999b

#define BMP_PAGE_SIZE 1024

#define MATRIX_SCAN_TIME_MS 5 // Minimum is 5ms
#define BMP_FORCE_SAFE_MODE false
#define DISABLE_MSC 1


/* key matrix size */
#define MATRIX_ROWS_DEFAULT 24
#define MATRIX_COLS_DEFAULT 8
#define THIS_DEVICE_ROWS 24
#define THIS_DEVICE_COLS 8
#define MATRIX_MODIFIER_ROW 21
#define MATRIX_MSBTN_ROW 22
#define MATRIX_MSGES_ROW 23
#define MATRIX_MSWHEEL_ROW 23
#define MATRIX_MSWHEEL_COL 4
#define IS_LEFT_HAND true
#define BMP_DEFAULT_MODE SINGLE

#define QUANTIZER_REPORT_PARSER REPORT_PARSER_USER

#define MATRIX_ROW_PINS \
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define MATRIX_COL_PINS \
    { 0, 0, 0, 0, 0, 0, 0, 0 }
#define MATRIX_LAYOUT                                                          \
    { 42, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 0, \
    54, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 46, 47, 138, 43, 74, 75, 76, 84, 85, 86, 87, 0, \
    44, 21, 27, 9, 22, 24, 29, 25, 13, 19, 20, 48, 49, 41, 77, 78, 79, 96, 97, 98, 88, 0, \
    58, 5, 23, 8, 10, 11, 12, 14, 15, 16, 52, 53, 51, 93, 94, 95, 0, \
    170, 30, 28, 7, 26, 6, 18, 17, 55, 56, 57, 136, 174, 83, 90, 91, 92, 89, 0, \
    169, 172, 171, 140, 45, 139, 137, 175, 176, 102, 173, 81, 82, 80, 99, 100, 255 }

#define KEYMAP_PRIOR_LOCALE 0
#define KEYMAP_ASCII 0
#define CONFIG_RESERVED \
    { 0, 7, 0, 0, 0, 90, 0, 0 }

#ifndef __ASSEMBLER__
#    include "microshell/core/msconf.h"
#    include "microshell/util/mscmd.h"
#    define USER_DEFINED_MSCMD \
        { "chboot", usrcmd_chboot, "Start CH559 programming" }, \
        { "chreset", usrcmd_chreset, "Reset CH559" }, \
        { "chload", usrcmd_chload, "Current load test CH559" },\
        { "chled", usrcmd_chled, "Send LED command to CH559" },\
        { "chdev", usrcmd_chdev, "Show devices connected to CH559" },\
        { "chver", usrcmd_chver, "Show CH559 FW version" },\
        { "chprsr", usrcmd_chparser, "Change parser type" },
MSCMD_USER_RESULT usrcmd_chboot(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
MSCMD_USER_RESULT usrcmd_chreset(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
MSCMD_USER_RESULT usrcmd_chload(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
MSCMD_USER_RESULT usrcmd_chled(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
MSCMD_USER_RESULT usrcmd_chdev(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
MSCMD_USER_RESULT usrcmd_chver(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
MSCMD_USER_RESULT usrcmd_chparser(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
#endif

#define RGBLIGHT_SPLIT
#define G00 255 // Dummy for bin/qmk config generation
#define RGB_DI_PIN G00
#ifdef RGB_DI_PIN
#    define RGBLED_NUM_DEFAULT 128
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP /* If defined, the RGB lighting will be switched \
                              off when the host goes to sleep */
                           /*== all animations enable ==*/
#    define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
#    define RGBLIGHT_BREATHE_TABLE_SIZE 256  // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
#    define RGBLIGHT_EFFECT_BREATHE_MAX 255      // 0 to 255
#endif
