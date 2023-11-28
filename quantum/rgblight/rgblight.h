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

#pragma once

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
|       37        | RGBLIGHT_MODE_TWINKLE             |
|       38        | RGBLIGHT_MODE_TWINKLE + 1         |
|       39        | RGBLIGHT_MODE_TWINKLE + 2         |
|       40        | RGBLIGHT_MODE_TWINKLE + 3         |
|       41        | RGBLIGHT_MODE_TWINKLE + 4         |
|       42        | RGBLIGHT_MODE_TWINKLE + 5         |
|-----------------|-----------------------------------|
 *****/

// clang-format off

// check dynamic animation effects chose ?
#if  defined(RGBLIGHT_EFFECT_BREATHING)     \
  || defined(RGBLIGHT_EFFECT_RAINBOW_MOOD)  \
  || defined(RGBLIGHT_EFFECT_RAINBOW_SWIRL) \
  || defined(RGBLIGHT_EFFECT_SNAKE)         \
  || defined(RGBLIGHT_EFFECT_KNIGHT)        \
  || defined(RGBLIGHT_EFFECT_CHRISTMAS)     \
  || defined(RGBLIGHT_EFFECT_RGB_TEST)      \
  || defined(RGBLIGHT_EFFECT_ALTERNATING)   \
  || defined(RGBLIGHT_EFFECT_TWINKLE)
#    define RGBLIGHT_USE_TIMER
#endif

// clang-format on

#define _RGBM_SINGLE_STATIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_SINGLE_DYNAMIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_MULTI_STATIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_MULTI_DYNAMIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_TMP_STATIC(sym, msym) RGBLIGHT_MODE_##sym,
#define _RGBM_TMP_DYNAMIC(sym, msym) RGBLIGHT_MODE_##sym,
enum RGBLIGHT_EFFECT_MODE {
    RGBLIGHT_MODE_zero = 0,
#include "rgblight_modes.h"
    RGBLIGHT_MODE_last
};

#define RGBLIGHT_MODES (RGBLIGHT_MODE_last - 1)

// sample: #define RGBLIGHT_EFFECT_BREATHE_CENTER   1.85

#ifndef RGBLIGHT_EFFECT_BREATHE_MAX
#    define RGBLIGHT_EFFECT_BREATHE_MAX 255 // 0-255
#endif

#ifndef RGBLIGHT_EFFECT_SNAKE_LENGTH
#    define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#endif

#ifndef RGBLIGHT_EFFECT_SNAKE_INCREMENT
#    define RGBLIGHT_EFFECT_SNAKE_INCREMENT 1
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_LENGTH
#    define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_INCREMENT
#    define RGBLIGHT_EFFECT_KNIGHT_INCREMENT 1
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_OFFSET
#    define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0
#endif

#ifndef RGBLIGHT_EFFECT_KNIGHT_LED_NUM
#    define RGBLIGHT_EFFECT_KNIGHT_LED_NUM (rgblight_ranges.effect_num_leds)
#endif

#ifndef RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL
#    define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 40
#endif

#ifndef RGBLIGHT_EFFECT_CHRISTMAS_STEP
#    define RGBLIGHT_EFFECT_CHRISTMAS_STEP 2
#endif

#ifndef RGBLIGHT_EFFECT_TWINKLE_LIFE
#    define RGBLIGHT_EFFECT_TWINKLE_LIFE 200
#endif

#ifndef RGBLIGHT_EFFECT_TWINKLE_PROBABILITY
#    define RGBLIGHT_EFFECT_TWINKLE_PROBABILITY 1 / 127
#endif

#ifndef RGBLIGHT_HUE_STEP
#    define RGBLIGHT_HUE_STEP 8
#endif
#ifndef RGBLIGHT_SAT_STEP
#    define RGBLIGHT_SAT_STEP 17
#endif
#ifndef RGBLIGHT_VAL_STEP
#    define RGBLIGHT_VAL_STEP 17
#endif
#ifndef RGBLIGHT_LIMIT_VAL
#    define RGBLIGHT_LIMIT_VAL 255
#endif

#include <stdint.h>
#include <stdbool.h>
#include "progmem.h"
#include "eeconfig.h"
#include "ws2812.h"
#include "color.h"

#ifdef RGBLIGHT_LAYERS
typedef struct {
    uint8_t index; // The first LED to light
    uint8_t count; // The number of LEDs to light
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
} rgblight_segment_t;

// rgblight_set_layer_state doesn't take effect until the next time
// rgblight_task runs, so timers must be enabled for layers to work.
#    define RGBLIGHT_USE_TIMER

#    define RGBLIGHT_END_SEGMENT_INDEX (255)
#    define RGBLIGHT_END_SEGMENTS \
        { RGBLIGHT_END_SEGMENT_INDEX, 0, 0, 0 }
#    ifndef RGBLIGHT_MAX_LAYERS
#        define RGBLIGHT_MAX_LAYERS 8
#    endif
#    if RGBLIGHT_MAX_LAYERS <= 0
#        error invalid RGBLIGHT_MAX_LAYERS value (must be >= 1)
#    elif RGBLIGHT_MAX_LAYERS <= 8
typedef uint8_t rgblight_layer_mask_t;
#    elif RGBLIGHT_MAX_LAYERS <= 16
typedef uint16_t rgblight_layer_mask_t;
#    elif RGBLIGHT_MAX_LAYERS <= 32
typedef uint32_t rgblight_layer_mask_t;
#    else
#        error invalid RGBLIGHT_MAX_LAYERS value (must be <= 32)
#    endif
#    define RGBLIGHT_LAYER_SEGMENTS(...) \
        { __VA_ARGS__, RGBLIGHT_END_SEGMENTS }
#    define RGBLIGHT_LAYERS_LIST(...) \
        { __VA_ARGS__, NULL }

// Get/set enabled rgblight layers
void rgblight_set_layer_state(uint8_t layer, bool enabled);
bool rgblight_get_layer_state(uint8_t layer);

// Point this to an array of rgblight_segment_t arrays in keyboard_post_init_user to use rgblight layers
extern const rgblight_segment_t *const *rgblight_layers;

#    ifdef RGBLIGHT_LAYER_BLINK
#        define RGBLIGHT_USE_TIMER
void rgblight_blink_layer(uint8_t layer, uint16_t duration_ms);
void rgblight_blink_layer_repeat(uint8_t layer, uint16_t duration_ms, uint8_t times);
/**
 * \brief Stop blinking on one layer.
 *
 * Stop a layer that is blinking. If the layer is not blinking it will
 * be unaffected.
 *
 * \param layer Layer number to stop blinking.
 */
void rgblight_unblink_layer(uint8_t layer);
/**
 * \brief Stop blinking all layers except one.
 *
 * Stop all layers that are blinking except for one specific layer.
 * Layers that are not blinking are unaffected.
 *
 * \param layer Layer number to keep blinking.
 */
void rgblight_unblink_all_but_layer(uint8_t layer);
#    endif

#endif

extern rgb_led_t led[RGBLED_NUM];

extern const uint8_t  RGBLED_BREATHING_INTERVALS[4] PROGMEM;
extern const uint8_t  RGBLED_RAINBOW_MOOD_INTERVALS[3] PROGMEM;
extern const uint8_t  RGBLED_RAINBOW_SWIRL_INTERVALS[3] PROGMEM;
extern const uint8_t  RGBLED_SNAKE_INTERVALS[3] PROGMEM;
extern const uint8_t  RGBLED_KNIGHT_INTERVALS[3] PROGMEM;
extern const uint16_t RGBLED_RGBTEST_INTERVALS[1] PROGMEM;
extern const uint8_t  RGBLED_TWINKLE_INTERVALS[3] PROGMEM;
extern bool           is_rgblight_initialized;

typedef union {
    uint64_t raw;
    struct {
        bool    enable : 1;
        bool    velocikey : 1;
        uint8_t mode : 6;
        uint8_t hue : 8;
        uint8_t sat : 8;
        uint8_t val : 8;
        uint8_t speed : 8;
    };
} rgblight_config_t;

_Static_assert(sizeof(rgblight_config_t) == sizeof(uint64_t), "RGB Light EECONFIG out of spec.");

typedef struct _rgblight_status_t {
    uint8_t base_mode;
    bool    timer_enabled;
#ifdef RGBLIGHT_SPLIT
    uint8_t change_flags;
#endif
#ifdef RGBLIGHT_LAYERS
    rgblight_layer_mask_t enabled_layer_mask;
#endif
} rgblight_status_t;

/*
 * Structure for RGB Light clipping ranges
 */
typedef struct _rgblight_ranges_t {
    uint8_t clipping_start_pos;
    uint8_t clipping_num_leds;
    uint8_t effect_start_pos;
    uint8_t effect_end_pos;
    uint8_t effect_num_leds;
} rgblight_ranges_t;

extern rgblight_ranges_t rgblight_ranges;

/* === Utility Functions ===*/
void sethsv(uint8_t hue, uint8_t sat, uint8_t val, rgb_led_t *led1);
void sethsv_raw(uint8_t hue, uint8_t sat, uint8_t val, rgb_led_t *led1); // without RGBLIGHT_LIMIT_VAL check
void setrgb(uint8_t r, uint8_t g, uint8_t b, rgb_led_t *led1);

/* === Low level Functions === */
void rgblight_set(void);
void rgblight_set_clipping_range(uint8_t start_pos, uint8_t num_leds);

/* === Effects and Animations Functions === */
/*   effect range setting */
void rgblight_set_effect_range(uint8_t start_pos, uint8_t num_leds);

/*   direct operation */
void rgblight_setrgb_at(uint8_t r, uint8_t g, uint8_t b, uint8_t index);
void rgblight_sethsv_at(uint8_t hue, uint8_t sat, uint8_t val, uint8_t index);
void rgblight_setrgb_range(uint8_t r, uint8_t g, uint8_t b, uint8_t start, uint8_t end);
void rgblight_sethsv_range(uint8_t hue, uint8_t sat, uint8_t val, uint8_t start, uint8_t end);
void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b);

#ifndef RGBLIGHT_SPLIT
void rgblight_setrgb_master(uint8_t r, uint8_t g, uint8_t b);
void rgblight_setrgb_slave(uint8_t r, uint8_t g, uint8_t b);
void rgblight_sethsv_master(uint8_t hue, uint8_t sat, uint8_t val);
void rgblight_sethsv_slave(uint8_t hue, uint8_t sat, uint8_t val);
#endif

/*   effect mode change */
void rgblight_mode(uint8_t mode);
void rgblight_mode_noeeprom(uint8_t mode);
void rgblight_increase(void);
void rgblight_decrease(void);
void rgblight_step(void);
void rgblight_step_noeeprom(void);
void rgblight_step_reverse(void);
void rgblight_step_reverse_noeeprom(void);

/*   effects mode disable/enable */
void rgblight_toggle(void);
void rgblight_toggle_noeeprom(void);
void rgblight_enable(void);
void rgblight_enable_noeeprom(void);
void rgblight_disable(void);
void rgblight_disable_noeeprom(void);
void rgblight_enabled_noeeprom(bool state);

/*   hue, sat, val change */
void rgblight_increase_hue(void);
void rgblight_increase_hue_noeeprom(void);
void rgblight_decrease_hue(void);
void rgblight_decrease_hue_noeeprom(void);
void rgblight_increase_sat(void);
void rgblight_increase_sat_noeeprom(void);
void rgblight_decrease_sat(void);
void rgblight_decrease_sat_noeeprom(void);
void rgblight_increase_val(void);
void rgblight_increase_val_noeeprom(void);
void rgblight_decrease_val(void);
void rgblight_decrease_val_noeeprom(void);
void rgblight_increase_speed(void);
void rgblight_increase_speed_noeeprom(void);
void rgblight_decrease_speed(void);
void rgblight_decrease_speed_noeeprom(void);
void rgblight_sethsv(uint8_t hue, uint8_t sat, uint8_t val);
void rgblight_sethsv_noeeprom(uint8_t hue, uint8_t sat, uint8_t val);

/*   effect speed */
uint8_t rgblight_get_speed(void);
void    rgblight_set_speed(uint8_t speed);
void    rgblight_set_speed_noeeprom(uint8_t speed);

/*   reset */
void rgblight_reload_from_eeprom(void);

/*       query */
uint8_t rgblight_get_mode(void);
uint8_t rgblight_get_hue(void);
uint8_t rgblight_get_sat(void);
uint8_t rgblight_get_val(void);
bool    rgblight_is_enabled(void);
HSV     rgblight_get_hsv(void);

/* === qmk_firmware (core)internal Functions === */
void     rgblight_init(void);
void     rgblight_suspend(void);
void     rgblight_wakeup(void);
uint64_t rgblight_read_qword(void);
void     rgblight_update_qword(uint64_t qword);
uint64_t eeconfig_read_rgblight(void);
void     eeconfig_update_rgblight(uint64_t val);
void     eeconfig_update_rgblight_current(void);
void     eeconfig_update_rgblight_default(void);
void     eeconfig_debug_rgblight(void);

void rgb_matrix_increase(void);
void rgb_matrix_decrease(void);

void rgblight_sethsv_eeprom_helper(uint8_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom);
void rgblight_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom);

#define EZ_RGB(val) rgblight_show_solid_color((val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF)
void rgblight_show_solid_color(uint8_t r, uint8_t g, uint8_t b);

void preprocess_rgblight(void);
void rgblight_task(void);

#ifdef RGBLIGHT_USE_TIMER
void rgblight_timer_init(void);
void rgblight_timer_enable(void);
void rgblight_timer_disable(void);
void rgblight_timer_toggle(void);
#else
#    define rgblight_timer_init()
#    define rgblight_timer_enable()
#    define rgblight_timer_disable()
#    define rgblight_timer_toggle()
#endif

#ifdef RGBLIGHT_SPLIT
#    define RGBLIGHT_STATUS_CHANGE_MODE (1 << 0)
#    define RGBLIGHT_STATUS_CHANGE_HSVS (1 << 1)
#    define RGBLIGHT_STATUS_CHANGE_TIMER (1 << 2)
#    define RGBLIGHT_STATUS_ANIMATION_TICK (1 << 3)
#    define RGBLIGHT_STATUS_CHANGE_LAYERS (1 << 4)

typedef struct _rgblight_syncinfo_t {
    rgblight_config_t config;
    rgblight_status_t status;
} rgblight_syncinfo_t;

/* for split keyboard master side */
uint8_t rgblight_get_change_flags(void);
void    rgblight_clear_change_flags(void);
void    rgblight_get_syncinfo(rgblight_syncinfo_t *syncinfo);
/* for split keyboard slave side */
void rgblight_update_sync(rgblight_syncinfo_t *syncinfo, bool write_to_eeprom);
#endif

#ifdef RGBLIGHT_USE_TIMER

typedef struct _animation_status_t {
    uint16_t last_timer;
    uint8_t  delta; /* mode - base_mode */
    bool     restart;
    union {
        uint16_t pos16;
        uint8_t  pos;
        int8_t   current_hue;
        uint16_t current_offset;
    };
} animation_status_t;

extern animation_status_t animation_status;

void rgblight_effect_breathing(animation_status_t *anim);
void rgblight_effect_rainbow_mood(animation_status_t *anim);
void rgblight_effect_rainbow_swirl(animation_status_t *anim);
void rgblight_effect_snake(animation_status_t *anim);
void rgblight_effect_knight(animation_status_t *anim);
void rgblight_effect_christmas(animation_status_t *anim);
void rgblight_effect_rgbtest(animation_status_t *anim);
void rgblight_effect_alternating(animation_status_t *anim);
void rgblight_effect_twinkle(animation_status_t *anim);

#endif

#ifdef VELOCIKEY_ENABLE
bool    rgblight_velocikey_enabled(void);
void    rgblight_velocikey_toggle(void);
void    rgblight_velocikey_accelerate(void);
void    rgblight_velocikey_decelerate(void);
uint8_t rgblight_velocikey_match_speed(uint8_t minValue, uint8_t maxValue);

#    define velocikey_enabled rgblight_velocikey_enabled
#    define velocikey_toggle rgblight_velocikey_toggle
#endif
