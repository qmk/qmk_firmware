/* Copyright 2017 Yang Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef RGBLIGHT_H
#define RGBLIGHT_H

#ifdef RGBLIGHT_ANIMATIONS
	#define RGBLIGHT_MODES 34
#else
	#define RGBLIGHT_MODES 1
#endif

#ifndef RGBLIGHT_EFFECT_BREATHE_CENTER
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1-2.7
#endif

#ifndef RGBLIGHT_EFFECT_BREATHE_MAX
#define RGBLIGHT_EFFECT_BREATHE_MAX 255   // 0-255
#endif

#ifndef RGBLIGHT_EFFECT_SNAKE_LENGTH
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_LENGTH
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_OFFSET
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_LED_NUM
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM RGBLED_NUM
#endif

#ifndef RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 1000
#endif

#ifndef RGBLIGHT_EFFECT_CHRISTMAS_STEP
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 2
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
// #define RGBLED_TIMER_TOP 0xFF10

#include <stdint.h>
#include <stdbool.h>
#include "eeconfig.h"
#ifndef RGBLIGHT_CUSTOM_DRIVER
#include "ws2812.h"
#endif
#include "rgblight_types.h"
#include "rgblight_list.h"

extern LED_TYPE led[RGBLED_NUM];

extern const uint8_t RGBLED_BREATHING_INTERVALS[4] PROGMEM;
extern const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[3] PROGMEM;
extern const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[3] PROGMEM;
extern const uint8_t RGBLED_SNAKE_INTERVALS[3] PROGMEM;
extern const uint8_t RGBLED_KNIGHT_INTERVALS[3] PROGMEM;

typedef union {
  uint32_t raw;
  struct {
    bool     enable  :1;
    uint8_t  mode    :6;
    uint16_t hue     :9;
    uint8_t  sat     :8;
    uint8_t  val     :8;
    uint8_t  speed   :8;//EECONFIG needs to be increased to support this
  };
} rgblight_config_t;

void rgblight_init(void);
void rgblight_increase(void);
void rgblight_decrease(void);
void rgblight_toggle(void);
void rgblight_enable(void);
void rgblight_disable(void);
void rgblight_step(void);
void rgblight_step_reverse(void);
uint32_t rgblight_get_mode(void);
void rgblight_mode(uint8_t mode);
void rgblight_set(void);
void rgblight_update_dword(uint32_t dword);
void rgblight_increase_hue(void);
void rgblight_decrease_hue(void);
void rgblight_increase_sat(void);
void rgblight_decrease_sat(void);
void rgblight_increase_val(void);
void rgblight_decrease_val(void);
void rgblight_increase_speed(void);
void rgblight_decrease_speed(void);
void rgblight_sethsv(uint16_t hue, uint8_t sat, uint8_t val);
uint16_t rgblight_get_hue(void);
uint8_t rgblight_get_sat(void);
uint8_t rgblight_get_val(void);
void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b);
void rgblight_setrgb_at(uint8_t r, uint8_t g, uint8_t b, uint8_t index);
void rgblight_sethsv_at(uint16_t hue, uint8_t sat, uint8_t val, uint8_t index);

uint32_t eeconfig_read_rgblight(void);
void eeconfig_update_rgblight(uint32_t val);
void eeconfig_update_rgblight_default(void);
void eeconfig_debug_rgblight(void);

void rgb_matrix_increase(void);
void rgb_matrix_decrease(void);

void sethsv(uint16_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1);
void setrgb(uint8_t r, uint8_t g, uint8_t b, LED_TYPE *led1);
void rgblight_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val);

#define EZ_RGB(val) rgblight_show_solid_color((val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF)
void rgblight_show_solid_color(uint8_t r, uint8_t g, uint8_t b);

void rgblight_task(void);

void rgblight_timer_init(void);
void rgblight_timer_enable(void);
void rgblight_timer_disable(void);
void rgblight_timer_toggle(void);
void rgblight_effect_breathing(uint8_t interval);
void rgblight_effect_rainbow_mood(uint8_t interval);
void rgblight_effect_rainbow_swirl(uint8_t interval);
void rgblight_effect_snake(uint8_t interval);
void rgblight_effect_knight(uint8_t interval);
void rgblight_effect_christmas(void);

#endif
