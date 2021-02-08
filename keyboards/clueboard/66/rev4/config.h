#pragma once

#include "config_common.h"

/* Address for jumping to bootloader on STM32 chips. */
/* It is chip dependent, the correct number can be looked up here:
 * http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
 */
#define STM32_BOOTLOADER_ADDRESS 0x1FFFD800

 /* Backlight configuration
 */
#define BACKLIGHT_LEVELS 1

/* Underlight configuration
 */
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#define RGBLIGHT_EFFECT_BREATHE_MAX 200
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 666*2
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3   // How many LEDs wide to light up
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 2   // The led to start at
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 5  // How many LEDs to travel
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4    // How many LEDs wide to light up
