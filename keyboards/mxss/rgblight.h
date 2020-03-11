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

#ifndef RGBLIGHT_H_DUMMY_DEFINE

#    define RGBLIGHT_MODES (RGBLIGHT_MODE_last - 1)

// sample: #define RGBLIGHT_EFFECT_BREATHE_CENTER   1.85

#    ifndef RGBLIGHT_EFFECT_BREATHE_MAX
#        define RGBLIGHT_EFFECT_BREATHE_MAX 255  // 0-255
#    endif

#    ifndef RGBLIGHT_EFFECT_SNAKE_LENGTH
#        define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#    endif

#    ifndef RGBLIGHT_EFFECT_KNIGHT_LENGTH
#        define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#    endif

#    ifndef RGBLIGHT_EFFECT_KNIGHT_OFFSET
#        define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0
#    endif

#    ifndef RGBLIGHT_EFFECT_KNIGHT_LED_NUM
#        define RGBLIGHT_EFFECT_KNIGHT_LED_NUM (effect_num_leds)
#    endif

#    ifndef RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL
#        define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 1000
#    endif

#    ifndef RGBLIGHT_EFFECT_CHRISTMAS_STEP
#        define RGBLIGHT_EFFECT_CHRISTMAS_STEP 2
#    endif

#    ifndef RGBLIGHT_HUE_STEP
#        define RGBLIGHT_HUE_STEP 8
#    endif
#    ifndef RGBLIGHT_SAT_STEP
#        define RGBLIGHT_SAT_STEP 17
#    endif
#    ifndef RGBLIGHT_VAL_STEP
#        define RGBLIGHT_VAL_STEP 17
#    endif
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL 255
#    endif

#    define RGBLED_TIMER_TOP F_CPU / (256 * 64)
// #define RGBLED_TIMER_TOP 0xFF10

#    include <stdint.h>
#    include <stdbool.h>
#    include "eeconfig.h"
#    ifndef RGBLIGHT_CUSTOM_DRIVER
#        include "ws2812.h"
#    endif
#    include "color.h"
#    include "rgblight_list.h"

#    if defined(__AVR__)
#        include <avr/pgmspace.h>
#    endif

extern LED_TYPE led[RGBLED_NUM];

extern const uint8_t  RGBLED_BREATHING_INTERVALS[4] PROGMEM;
extern const uint8_t  RGBLED_RAINBOW_MOOD_INTERVALS[3] PROGMEM;
extern const uint8_t  RGBLED_RAINBOW_SWIRL_INTERVALS[3] PROGMEM;
extern const uint8_t  RGBLED_SNAKE_INTERVALS[3] PROGMEM;
extern const uint8_t  RGBLED_KNIGHT_INTERVALS[3] PROGMEM;
extern const uint16_t RGBLED_RGBTEST_INTERVALS[1] PROGMEM;
extern bool           is_rgblight_initialized;

// Should stay in sycn with rgb matrix config as we reuse eeprom storage for both (for now)
typedef union {
    uint32_t raw;
    struct {
        bool    enable : 1;
        uint8_t mode : 7;
        uint8_t hue : 8;
        uint8_t sat : 8;
        uint8_t val : 8;
        uint8_t speed : 8;  // EECONFIG needs to be increased to support this
    };
} rgblight_config_t;

typedef struct _rgblight_status_t {
    uint8_t base_mode;
    bool    timer_enabled;
#    ifdef RGBLIGHT_SPLIT
    uint8_t change_flags;
#    endif
} rgblight_status_t;

/* === Utility Functions ===*/
void sethsv(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1);
void sethsv_raw(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1);  // without RGBLIGHT_LIMIT_VAL check
void setrgb(uint8_t r, uint8_t g, uint8_t b, LED_TYPE *led1);

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

#    ifndef RGBLIGHT_SPLIT
void rgblight_setrgb_master(uint8_t r, uint8_t g, uint8_t b);
void rgblight_setrgb_slave(uint8_t r, uint8_t g, uint8_t b);
void rgblight_sethsv_master(uint8_t hue, uint8_t sat, uint8_t val);
void rgblight_sethsv_slave(uint8_t hue, uint8_t sat, uint8_t val);
#    endif

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
void rgblight_decrease_speed(void);
void rgblight_sethsv(uint8_t hue, uint8_t sat, uint8_t val);
void rgblight_sethsv_noeeprom(uint8_t hue, uint8_t sat, uint8_t val);

/*   effect speed */
uint8_t rgblight_get_speed(void);
void rgblight_set_speed(uint8_t speed);
void rgblight_set_speed_noeeprom(uint8_t speed);

/*       query */
uint8_t rgblight_get_mode(void);
uint8_t rgblight_get_hue(void);
uint8_t rgblight_get_sat(void);
uint8_t rgblight_get_val(void);

/* === qmk_firmware (core)internal Functions === */
void     rgblight_init(void);
uint32_t rgblight_read_dword(void);
void     rgblight_update_dword(uint32_t dword);
uint32_t eeconfig_read_rgblight(void);
void     eeconfig_update_rgblight(uint32_t val);
void     eeconfig_update_rgblight_current(void);
void     eeconfig_update_rgblight_default(void);
void     eeconfig_debug_rgblight(void);

void rgb_matrix_increase(void);
void rgb_matrix_decrease(void);

void rgblight_sethsv_eeprom_helper(uint8_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom);
void rgblight_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom);

#    define EZ_RGB(val) rgblight_show_solid_color((val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF)
void rgblight_show_solid_color(uint8_t r, uint8_t g, uint8_t b);

void rgblight_task(void);

void rgblight_timer_init(void);
void rgblight_timer_enable(void);
void rgblight_timer_disable(void);
void rgblight_timer_toggle(void);

#    ifdef RGBLIGHT_SPLIT
#        define RGBLIGHT_STATUS_CHANGE_MODE (1 << 0)
#        define RGBLIGHT_STATUS_CHANGE_HSVS (1 << 1)
#        define RGBLIGHT_STATUS_CHANGE_TIMER (1 << 2)
#        define RGBLIGHT_STATUS_ANIMATION_TICK (1 << 3)

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
#    endif

#    ifdef RGBLIGHT_USE_TIMER

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

#    endif

#endif  // #ifndef RGBLIGHT_H_DUMMY_DEFINE
#endif  // RGBLIGHT_H
