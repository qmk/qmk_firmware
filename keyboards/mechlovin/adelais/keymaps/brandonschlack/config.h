#pragma once

#define USE_LEDS_FOR_LAYERS
#define STOPLIGHT_LED

// LEDs
#define TOP_LED    B2
#define MIDDLE_LED C15
#define BOTTOM_LED B9
// #define LED_PIN_FLIP
#ifdef LED_PIN_FLIP
    #define LED_ON(flag) !flag
#else
    #define LED_ON(flag) flag
#endif
