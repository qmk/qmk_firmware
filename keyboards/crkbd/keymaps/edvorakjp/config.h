#ifndef CONFIG_USER_H
#define CONFIG_USER_H

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SSD1306OLED
#define SWAP_SCLN

// #define TAPPING_FORCE_HOLD
#define TAPPING_TERM 120

#undef RGBLED_NUM
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 100
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#endif // CONFIG_USER_H
