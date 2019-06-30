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

#include "rgblight_reconfig.h"

/***** rgblight_mode(mode)/rgblight_mode_noeeprom(mode) ****

 old mode number (before 0.6.117) to new mode name table

|-----------------|-----------------------------------|
| old mode number | new mode name                     |
|-----------------|-----------------------------------|
|        1        | RGBLIGHT_MODE_STATIC_LIGHT        |
|        2        | RGBLIGHT_MODE_BREATHING           |
|        3        | RGBLIGHT_MODE_BREATHING + 1       |
|        4        | RGBLIGHT_MODE_BREATHING + 2       |
|        5        | RGBLIGHT_MODE_BREATHING + 3       |
|        6        | RGBLIGHT_MODE_RAINBOW_MOOD        |
|        7        | RGBLIGHT_MODE_RAINBOW_MOOD + 1    |
|        8        | RGBLIGHT_MODE_RAINBOW_MOOD + 2    |
|        9        | RGBLIGHT_MODE_RAINBOW_SWIRL       |
|       10        | RGBLIGHT_MODE_RAINBOW_SWIRL + 1   |
|       11        | RGBLIGHT_MODE_RAINBOW_SWIRL + 2   |
|       12        | RGBLIGHT_MODE_RAINBOW_SWIRL + 3   |
|       13        | RGBLIGHT_MODE_RAINBOW_SWIRL + 4   |
|       14        | RGBLIGHT_MODE_RAINBOW_SWIRL + 5   |
|       15        | RGBLIGHT_MODE_SNAKE               |
|       16        | RGBLIGHT_MODE_SNAKE + 1           |
|       17        | RGBLIGHT_MODE_SNAKE + 2           |
|       18        | RGBLIGHT_MODE_SNAKE + 3           |
|       19        | RGBLIGHT_MODE_SNAKE + 4           |
|       20        | RGBLIGHT_MODE_SNAKE + 5           |
|       21        | RGBLIGHT_MODE_KNIGHT              |
|       22        | RGBLIGHT_MODE_KNIGHT + 1          |
|       23        | RGBLIGHT_MODE_KNIGHT + 2          |
|       24        | RGBLIGHT_MODE_CHRISTMAS           |
|       25        | RGBLIGHT_MODE_STATIC_GRADIENT     |
|       26        | RGBLIGHT_MODE_STATIC_GRADIENT + 1 |
|       27        | RGBLIGHT_MODE_STATIC_GRADIENT + 2 |
|       28        | RGBLIGHT_MODE_STATIC_GRADIENT + 3 |
|       29        | RGBLIGHT_MODE_STATIC_GRADIENT + 4 |
|       30        | RGBLIGHT_MODE_STATIC_GRADIENT + 5 |
|       31        | RGBLIGHT_MODE_STATIC_GRADIENT + 6 |
|       32        | RGBLIGHT_MODE_STATIC_GRADIENT + 7 |
|       33        | RGBLIGHT_MODE_STATIC_GRADIENT + 8 |
|       34        | RGBLIGHT_MODE_STATIC_GRADIENT + 9 |
|       35        | RGBLIGHT_MODE_RGB_TEST            |
|       36        | RGBLIGHT_MODE_ALTERNATING         |
|-----------------|-----------------------------------|
 *****/

#define _RGBM_SINGLE_STATIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_SINGLE_DYNAMIC(sym)  RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_STATIC(sym)    RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_DYNAMIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_STATIC(sym)      RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_DYNAMIC(sym)     RGBLIGHT_MODE_ ## sym,
enum RGBLIGHT_EFFECT_MODE {
    RGBLIGHT_MODE_zero = 0,
#include "rgblight.h"
    RGBLIGHT_MODE_last
};

#ifndef RGBLIGHT_H_DUMMY_DEFINE

#define RGBLIGHT_MODES (RGBLIGHT_MODE_last-1)

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

#ifndef RGBLIGHT_EFFECT_BEAM_LENGTH
#define RGBLIGHT_EFFECT_BEAM_LENGTH 16
#endif

#ifndef RGBLIGHT_EFFECT_HYPER_LENGTH
#define RGBLIGHT_EFFECT_HYPER_LENGTH  104
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
#include "color.h"
#include "rgblight_list.h"

#if defined(__AVR__)
    #include <avr/pgmspace.h>
#endif

extern LED_TYPE led[RGBLED_NUM];

extern const uint8_t RGBLED_BREATHING_INTERVALS[4] PROGMEM;
extern const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[3] PROGMEM;
extern const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[3] PROGMEM;
extern const uint8_t RGBLED_RAINBOW_SPARKLE_INTERVALS[3] PROGMEM;
extern const uint8_t RGBLED_SNAKE_INTERVALS[3] PROGMEM;
extern const uint8_t RGBLED_KNIGHT_INTERVALS[3] PROGMEM;
extern const uint16_t RGBLED_RGBTEST_INTERVALS[1] PROGMEM;

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
uint8_t rgblight_get_mode(void);
void rgblight_mode(uint8_t mode);
void rgblight_set(void);
uint32_t rgblight_read_dword(void);
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
void rgblight_setrgb_range(uint8_t r, uint8_t g, uint8_t b, uint8_t start, uint8_t end);
void rgblight_sethsv_range(uint16_t hue, uint8_t sat, uint8_t val, uint8_t start, uint8_t end);
void rgblight_setrgb_master(uint8_t r, uint8_t g, uint8_t b);
void rgblight_setrgb_slave(uint8_t r, uint8_t g, uint8_t b);
void rgblight_sethsv_master(uint16_t hue, uint8_t sat, uint8_t val);
void rgblight_sethsv_slave(uint16_t hue, uint8_t sat, uint8_t val);
void rgblight_set_clipping_range(uint8_t start_pos, uint8_t num_leds);

uint32_t eeconfig_read_rgblight(void);
void eeconfig_update_rgblight(uint32_t val);
void eeconfig_update_rgblight_default(void);
void eeconfig_debug_rgblight(void);

void rgb_matrix_increase(void);
void rgb_matrix_decrease(void);

void sethsv(uint16_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1);
void setrgb(uint8_t r, uint8_t g, uint8_t b, LED_TYPE *led1);

void rgblight_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val);
void rgblight_mode_noeeprom(uint8_t mode);
void rgblight_toggle_noeeprom(void);
void rgblight_enable_noeeprom(void);
void rgblight_disable_noeeprom(void);
void rgblight_step_noeeprom(void);
void rgblight_step_reverse_noeeprom(void);
void rgblight_increase_hue_noeeprom(void);
void rgblight_decrease_hue_noeeprom(void);
void rgblight_increase_sat_noeeprom(void);
void rgblight_decrease_sat_noeeprom(void);
void rgblight_increase_val_noeeprom(void);
void rgblight_decrease_val_noeeprom(void);

void rgblight_sethsv_eeprom_helper(uint16_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom);
void rgblight_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom);


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
void rgblight_effect_rainbow_sparkle(uint8_t interval);
void rgblight_effect_beam(uint8_t interval);
void rgblight_effect_hyper(uint8_t interval);
void rgblight_effect_snake(uint8_t interval);
void rgblight_effect_knight(uint8_t interval);
void rgblight_effect_christmas(void);
void rgblight_effect_rgbtest(void);
void rgblight_effect_alternating(void);

#endif // #ifndef RGBLIGHT_H_DUMMY_DEFINE
#endif // RGBLIGHT_H

#ifdef _RGBM_SINGLE_STATIC
  _RGBM_SINGLE_STATIC( STATIC_LIGHT )
  #ifdef RGBLIGHT_EFFECT_BREATHING
    _RGBM_MULTI_DYNAMIC( BREATHING )
    _RGBM_TMP_DYNAMIC( breathing_3 )
    _RGBM_TMP_DYNAMIC( breathing_4 )
    _RGBM_TMP_DYNAMIC( BREATHING_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
    _RGBM_MULTI_DYNAMIC( RAINBOW_MOOD )
    _RGBM_TMP_DYNAMIC( rainbow_mood_7 )
    _RGBM_TMP_DYNAMIC( RAINBOW_MOOD_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    _RGBM_MULTI_DYNAMIC( RAINBOW_SWIRL )
    _RGBM_TMP_DYNAMIC( rainbow_swirl_10 )
    _RGBM_TMP_DYNAMIC( rainbow_swirl_11 )
    _RGBM_TMP_DYNAMIC( rainbow_swirl_12 )
    _RGBM_TMP_DYNAMIC( rainbow_swirl_13 )
    _RGBM_TMP_DYNAMIC( RAINBOW_SWIRL_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_RAINBOW_SPARKLE
    _RGBM_MULTI_DYNAMIC( RAINBOW_SPARKLE )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_10 )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_11 )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_12 )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_13 )
    _RGBM_TMP_DYNAMIC( RAINBOW_SPARKLE_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_SNAKE
    _RGBM_MULTI_DYNAMIC( SNAKE )
    _RGBM_TMP_DYNAMIC( snake_16 )
    _RGBM_TMP_DYNAMIC( snake_17 )
    _RGBM_TMP_DYNAMIC( snake_18 )
    _RGBM_TMP_DYNAMIC( snake_19 )
    _RGBM_TMP_DYNAMIC( SNAKE_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_KNIGHT
    _RGBM_MULTI_DYNAMIC( KNIGHT )
    _RGBM_TMP_DYNAMIC( knight_22 )
    _RGBM_TMP_DYNAMIC( KNIGHT_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_CHRISTMAS
    _RGBM_SINGLE_DYNAMIC( CHRISTMAS )
  #endif
  #ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    _RGBM_MULTI_STATIC( STATIC_GRADIENT )
    _RGBM_TMP_STATIC( static_gradient_26 )
    _RGBM_TMP_STATIC( static_gradient_27 )
    _RGBM_TMP_STATIC( static_gradient_28 )
    _RGBM_TMP_STATIC( static_gradient_29 )
    _RGBM_TMP_STATIC( static_gradient_30 )
    _RGBM_TMP_STATIC( static_gradient_31 )
    _RGBM_TMP_STATIC( static_gradient_32 )
    _RGBM_TMP_STATIC( static_gradient_33 )
    _RGBM_TMP_STATIC( STATIC_GRADIENT_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_BEAM
    _RGBM_MULTI_DYNAMIC( BEAM )
    _RGBM_TMP_DYNAMIC( beam_37 )
    //_RGBM_TMP_DYNAMIC( beam_38 )
    //_RGBM_TMP_DYNAMIC( beam_39 )
    //_RGBM_TMP_DYNAMIC( beam_40 )
    _RGBM_TMP_DYNAMIC( BEAM_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_HYPER
    _RGBM_MULTI_DYNAMIC( HYPER )
    //_RGBM_TMP_DYNAMIC( hyper_50 )
    //_RGBM_TMP_DYNAMIC( hyper_90 )
    //_RGBM_TMP_DYNAMIC( hyper_100 )
    //_RGBM_TMP_DYNAMIC( hyper_200 )
    _RGBM_TMP_DYNAMIC( HYPER_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_RGB_TEST
    _RGBM_SINGLE_DYNAMIC( RGB_TEST )
  #endif
  #ifdef RGBLIGHT_EFFECT_ALTERNATING
    _RGBM_SINGLE_DYNAMIC( ALTERNATING )
  #endif
  ////  Add a new mode here.
  // #ifdef RGBLIGHT_EFFECT_<name>
  //    _RGBM_<SINGLE|MULTI>_<STATIC|DYNAMIC>( <name> )
  // #endif
#endif

#undef _RGBM_SINGLE_STATIC
#undef _RGBM_SINGLE_DYNAMIC
#undef _RGBM_MULTI_STATIC
#undef _RGBM_MULTI_DYNAMIC
#undef _RGBM_TMP_STATIC
#undef _RGBM_TMP_DYNAMIC
