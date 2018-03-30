#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define LEADER_TIMEOUT 300
//#define BACKLIGHT_BREATHING
#define PREVENT_STUCK_MODIFIERS

#define USE_I2C
#define SSD1306OLED
#define OLED_ROTATE180

/* ws2812 RGB LED*/
#define RGB_DI_PIN D4
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#endif
