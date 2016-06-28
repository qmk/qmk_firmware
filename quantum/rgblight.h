#ifndef RGBLIGHT_H
#define RGBLIGHT_H

#ifndef RGBLIGHT_MODES
#define RGBLIGHT_MODES 23
#endif

#ifndef RGBLIGHT_EFFECT_SNAKE_LENGTH
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 7
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_LENGTH
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 7
#endif
#ifndef RGBLIGHT_EFFECT_KNIGHT_OFFSET
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 9
#endif

#ifndef RGBLIGHT_EFFECT_DUALKNIGHT_LENGTH
#define RGBLIGHT_EFFECT_DUALKNIGHT_LENGTH 4
#endif

#ifndef RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 10
#endif
#ifndef RGBLIGHT_SAT_STEP
#define RGBLIGHT_SAT_STEP 17
#endif
#ifndef RGBLIGHT_VAL_STEP
#define RGBLIGHT_VAL_STEP 17
#endif

#define RGBLED_TIMER_TOP F_CPU/(256*64)

#include <stdint.h>
#include <stdbool.h>
#include "eeconfig.h"
#include "light_ws2812.h"

typedef union {
  uint32_t raw;
  struct {
    bool     enable  :1;
    uint8_t  mode    :6;
    uint16_t hue     :9;
    uint8_t  sat     :8;
    uint8_t  val     :8;
  };
} rgblight_config_t;

void rgblight_init(void);
void rgblight_increase(void);
void rgblight_decrease(void);
void rgblight_toggle(void);
void rgblight_step(void);
void rgblight_mode(uint8_t mode);
void rgblight_set(void);
void rgblight_increase_hue(void);
void rgblight_decrease_hue(void);
void rgblight_increase_sat(void);
void rgblight_decrease_sat(void);
void rgblight_increase_val(void);
void rgblight_decrease_val(void);
void rgblight_sethsv(uint16_t hue, uint8_t sat, uint8_t val);
void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b);

uint32_t eeconfig_read_rgblight(void);
void eeconfig_update_rgblight(uint32_t val);
void eeconfig_update_rgblight_default(void);
void eeconfig_debug_rgblight(void);

void sethsv(uint16_t hue, uint8_t sat, uint8_t val, struct cRGB *led1);
void setrgb(uint8_t r, uint8_t g, uint8_t b, struct cRGB *led1);
void rgblight_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val);

void rgblight_timer_init(void);
void rgblight_timer_enable(void);
void rgblight_timer_disable(void);
void rgblight_timer_toggle(void);
void rgblight_effect_breathing(uint8_t interval);
void rgblight_effect_rainbow_mood(uint8_t interval);
void rgblight_effect_rainbow_swirl(uint8_t interval);
void rgblight_effect_snake(uint8_t interval);
void rgblight_effect_knight(uint8_t interval);

#endif
