#pragma once

#define USE_LEDS_FOR_LAYERS
#define STOPLIGHT_LED

#define TOP_LED    B1
#define MIDDLE_LED B2
#define BOTTOM_LED B3

// #define LED_PIN_FLIP
#ifdef LED_PIN_FLIP
    #define LED_ON(flag) !flag
#else
    #define LED_ON(flag) flag
#endif
