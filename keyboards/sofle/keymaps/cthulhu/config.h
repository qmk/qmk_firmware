#pragma once

#define EE_HANDS

/* clear default encoder def */
#undef TAP_CODE_DELAY

/* encoder support */
#define TAP_CODE_DELAY 100

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define POINTING_DEVICE_ROTATION_90
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_TASK_THROTTLE_MS 8


/* ws2812 RGB LED */
#define RGB_DI_PIN D3

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    // #define RGBLIGHT_ANIMATIONS
	// #define RGBLIGHT_EFFECT_BREATHING
	// #define RGBLIGHT_EFFECT_RAINBOW_MOOD
	// #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	// #define RGBLIGHT_EFFECT_SNAKE
	// #define RGBLIGHT_EFFECT_KNIGHT
	// #define RGBLIGHT_EFFECT_CHRISTMAS
	// #define RGBLIGHT_EFFECT_STATIC_GRADIENT
	// #define RGBLIGHT_EFFECT_RGB_TEST
	// #define RGBLIGHT_EFFECT_ALTERNATING
	// #define RGBLIGHT_EFFECT_TWINKLE

    #define RGBLED_NUM 70
	//#define RGBLED_SPLIT
	#define RGBLED_SPLIT { 35, 35 } // haven't figured out how to use this yet

	//#define RGBLED_NUM 30
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
