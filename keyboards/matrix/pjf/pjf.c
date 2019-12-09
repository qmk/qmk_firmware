/**
 * pjf.c
 */

#include "pjf.h"

#ifdef RGBLIGHT_ENABLE
#include <string.h>
#include "rgblight.h"
#include "ws2812_pwm.h"
extern rgblight_config_t rgblight_config;

void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }

  ws2812_setleds((uint8_t*)led, RGBLED_NUM);
}
#endif

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

__attribute__((weak))
void matrix_init_user(void) {
    // caps lock
    setPinOutput(B6);
    // num lock
    setPinOutput(B5);
#ifdef RGBLIGHT_ENABLE
    ws2812_init();
#endif
}

__attribute__((weak))
void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_task();
#endif
}
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(B6, led_state.num_lock);
        writePin(B5, led_state.caps_lock);
    }
    return res;
}
