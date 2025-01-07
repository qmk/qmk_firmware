
#define RGBLIGHT_EFFECT_BREATHING true

#undef RGBLIGHT_MODE_BREATHING
#define RGBLIGHT_MODE_BREATHING 0


#undef BREATHING_PERIOD
#define BREATHING_PERIOD 1000


#ifdef RGBLIGHT_LIMIT_VAL
    #undef RGBLIGHT_LIMIT_VAL
    #define RGBLIGHT_LIMIT_VAL 40
#endif

// The default brightness level of the OLED, from 0 to 255.
#undef OLED_BRIGHTNESS
#define OLED_BRIGHTNESS 128

// Turns off the OLED screen after 60000ms of screen update inactivity.
// Helps reduce OLED Burn-in. Set to 0 to disable.
// Default is 60000ms ie 60 seconds
#undef OLED_TIMEOUT
#define OLED_TIMEOUT 60000
