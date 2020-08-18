#define USE_LEDS_FOR_LAYERS
#define STOPLIGHT_LED

#define TOP_LED    C7
#define MIDDLE_LED C6
#define BOTTOM_LED B6

// #define LED_PIN_FLIP
#ifdef LED_PIN_FLIP
    #define LED_ON(flag) !flag
#else
    #define LED_ON(flag) flag
#endif
