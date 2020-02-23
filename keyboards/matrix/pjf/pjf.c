/**
 * pjf.c
 */

#include "pjf.h"

#ifdef RGBLIGHT_ENABLE
#include "ws2812.h"
#include "rgblight.h"

extern rgblight_config_t rgblight_config;
static bool pjf_led_mode = true;

void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    } else if( pjf_led_mode) {
        led_t led_state = (led_t)host_keyboard_leds();
        if( !led_state.num_lock) {
            led[0].r = 0;
            led[0].g = 0;
            led[0].b = 0;
        }
        if( !led_state.caps_lock) {
            led[1].r = 0;
            led[1].g = 0;
            led[1].b = 0;
        }
    }
    ws2812_setleds(led, RGBLED_NUM);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
    case PJF_MODE:
        pjf_led_mode = !pjf_led_mode;
        return false;
    default:
        break;
    }
  }
  return true;
}

#endif

void led_init_ports(void) {
    // caps lock
    setPinOutput(B6);
    // num lock
    setPinOutput(B5);
}
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(B6, led_state.caps_lock);
        writePin(B5, led_state.num_lock);
    }
    return res;
}
