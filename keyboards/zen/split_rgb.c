#include <stdint.h>
#include <stdbool.h>
#include "split_util.h"
#include "progmem.h"
#include "print.h"
#include "rgblight.h"

#ifdef USE_I2C
#  include "i2c.h"
#else // USE_SERIAL
#  include "serial.h"
#endif


rgblight_config_t rgblight_config;

void rgblight_slave_update(void) {
  //rgblight_effect_christmas();
}


void rgblight_set(void) {
  if (rgblight_config.enable) {
    #ifdef RGBW
      ws2812_setleds_rgbw(led, RGBLED_NUM);
    #else
      ws2812_setleds(led, RGBLED_NUM);
    #endif
  } else {
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
      led[i].r = 0;
      led[i].g = 0;
      led[i].b = 0;
    }
    #ifdef RGBW
      ws2812_setleds_rgbw(led, RGBLED_NUM);
    #else
      ws2812_setleds(led, RGBLED_NUM);
    #endif
  }
}
