#include "rgb.h"

#ifdef RGBLIGHT_EFFECT_BREATHING
const uint8_t PROGMEM RGBLED_BREATHING_INTERVALS[] = { 20, 30, 5, 10 };
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
const uint8_t PROGMEM RGBLED_RAINBOW_SWIRL_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
const uint8_t PROGMEM RGBLED_SNAKE_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
const uint8_t PROGMEM RGBLED_KNIGHT_INTERVALS[] = { 20, 50, 100 };
#endif

const HSV godspeed_blue     = { GODSPEED_BLUE };
const HSV godspeed_yellow   = { GODSPEED_YELLOW };
const HSV modern_dolch_cyan = { MODERN_DOLCH_CYAN };
const HSV modern_dolch_red  = { MODERN_DOLCH_RED };
