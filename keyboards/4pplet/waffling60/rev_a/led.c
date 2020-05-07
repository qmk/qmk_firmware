
#include "rgblight.h"
#include "led.h"
extern rgblight_config_t rgblight_config; // Declared in rgblight.c

#ifdef RGBLIGHT_ENABLE
    const uint8_t backlight_pwm_map[BACKLIGHT_LEVELS] = BACKLIGHT_PWM_MAP;
#endif

#ifdef RGBLIGHT_ENABLE

//extern rgblight_config_t rgblight_config;

void rgblight_set(void) {

}
/*
void rgblight_disable(void) {

}
*/
void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b){

}

#endif  // RGBLIGHT_ENABLE
