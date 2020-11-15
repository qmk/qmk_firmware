/* Copyright 2016-2017 Yang Liu
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
#include <math.h>
#include <string.h>
#include <stdlib.h>
#ifdef __AVR__
#    include <avr/eeprom.h>
#    include <avr/interrupt.h>
#endif
#ifdef EEPROM_ENABLE
#    include "eeprom.h"
#endif
#ifdef STM32_EEPROM_ENABLE
#    include "hal.h"
#    include "eeprom_stm32.h"
#endif
#include "wait.h"
#include "progmem.h"
#include "timer.h"
#include "rgblight.h"
#include "color.h"
#include "debug.h"
#include "led_tables.h"
#include "lib/lib8tion/lib8tion.h"
#ifdef VELOCIKEY_ENABLE
#    include "velocikey.h"
#endif

#ifndef MIN
#    define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef RGBLIGHT_SPLIT
/* for split keyboard */
#    define RGBLIGHT_SPLIT_SET_CHANGE_MODE rgblight_status.change_flags |= RGBLIGHT_STATUS_CHANGE_MODE
#    define RGBLIGHT_SPLIT_SET_CHANGE_HSVS rgblight_status.change_flags |= RGBLIGHT_STATUS_CHANGE_HSVS
#    define RGBLIGHT_SPLIT_SET_CHANGE_MODEHSVS rgblight_status.change_flags |= (RGBLIGHT_STATUS_CHANGE_MODE | RGBLIGHT_STATUS_CHANGE_HSVS)
#    define RGBLIGHT_SPLIT_SET_CHANGE_LAYERS rgblight_status.change_flags |= RGBLIGHT_STATUS_CHANGE_LAYERS
#    define RGBLIGHT_SPLIT_SET_CHANGE_TIMER_ENABLE rgblight_status.change_flags |= RGBLIGHT_STATUS_CHANGE_TIMER
#    define RGBLIGHT_SPLIT_ANIMATION_TICK rgblight_status.change_flags |= RGBLIGHT_STATUS_ANIMATION_TICK
#else
#    define RGBLIGHT_SPLIT_SET_CHANGE_MODE
#    define RGBLIGHT_SPLIT_SET_CHANGE_HSVS
#    define RGBLIGHT_SPLIT_SET_CHANGE_MODEHSVS
#    define RGBLIGHT_SPLIT_SET_CHANGE_LAYERS
#    define RGBLIGHT_SPLIT_SET_CHANGE_TIMER_ENABLE
#    define RGBLIGHT_SPLIT_ANIMATION_TICK
#endif

#define _RGBM_SINGLE_STATIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_SINGLE_DYNAMIC(sym)
#define _RGBM_MULTI_STATIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_MULTI_DYNAMIC(sym)
#define _RGBM_TMP_STATIC(sym, msym) RGBLIGHT_MODE_##sym,
#define _RGBM_TMP_DYNAMIC(sym, msym)
static uint8_t static_effect_table[] = {
#include "rgblight_modes.h"
};

#define _RGBM_SINGLE_STATIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_SINGLE_DYNAMIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_MULTI_STATIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_MULTI_DYNAMIC(sym) RGBLIGHT_MODE_##sym,
#define _RGBM_TMP_STATIC(sym, msym) RGBLIGHT_MODE_##msym,
#define _RGBM_TMP_DYNAMIC(sym, msym) RGBLIGHT_MODE_##msym,
static uint8_t mode_base_table[] = {
    0,  // RGBLIGHT_MODE_zero
#include "rgblight_modes.h"
};

static inline int is_static_effect(uint8_t mode) { return memchr(static_effect_table, mode, sizeof(static_effect_table)) != NULL; }

#ifdef RGBLIGHT_LED_MAP
const uint8_t led_map[] PROGMEM = RGBLIGHT_LED_MAP;
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
__attribute__((weak)) const uint8_t RGBLED_GRADIENT_RANGES[] PROGMEM = {255, 170, 127, 85, 64};
#endif

rgblight_config_t rgblight_config;
rgblight_status_t rgblight_status         = {.timer_enabled = false};
bool              is_rgblight_initialized = false;

#ifdef RGBLIGHT_USE_TIMER
animation_status_t animation_status = {};
#endif

#ifndef LED_ARRAY
LED_TYPE led[RGBLED_NUM];
#    define LED_ARRAY led
#endif

#ifdef RGBLIGHT_LAYERS
rgblight_segment_t const *const *rgblight_layers = NULL;
#endif

rgblight_ranges_t rgblight_ranges = {0, RGBLED_NUM, 0, RGBLED_NUM, RGBLED_NUM};

void rgblight_set_clipping_range(uint8_t start_pos, uint8_t num_leds) {
    rgblight_ranges.clipping_start_pos = start_pos;
    rgblight_ranges.clipping_num_leds  = num_leds;
}

void rgblight_set_effect_range(uint8_t start_pos, uint8_t num_leds) {
    if (start_pos >= RGBLED_NUM) return;
    if (start_pos + num_leds > RGBLED_NUM) return;
    rgblight_ranges.effect_start_pos = start_pos;
    rgblight_ranges.effect_end_pos   = start_pos + num_leds;
    rgblight_ranges.effect_num_leds  = num_leds;
}

void sethsv_raw(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1) {
    HSV hsv = {hue, sat, val};
    RGB rgb = hsv_to_rgb(hsv);
    setrgb(rgb.r, rgb.g, rgb.b, led1);
}

void sethsv(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1) { sethsv_raw(hue, sat, val > RGBLIGHT_LIMIT_VAL ? RGBLIGHT_LIMIT_VAL : val, led1); }

void setrgb(uint8_t r, uint8_t g, uint8_t b, LED_TYPE *led1) {
    led1->r = r;
    led1->g = g;
    led1->b = b;
#ifdef RGBW
    led1->w = 0;
#endif
}

void rgblight_check_config(void) {
    /* Add some out of bound checks for RGB light config */

    if (rgblight_config.mode < RGBLIGHT_MODE_STATIC_LIGHT) {
        rgblight_config.mode = RGBLIGHT_MODE_STATIC_LIGHT;
    } else if (rgblight_config.mode > RGBLIGHT_MODES) {
        rgblight_config.mode = RGBLIGHT_MODES;
    }

    if (rgblight_config.val > RGBLIGHT_LIMIT_VAL) {
        rgblight_config.val = RGBLIGHT_LIMIT_VAL;
    }
}

uint32_t eeconfig_read_rgblight(void) {
#ifdef EEPROM_ENABLE
    return eeprom_read_dword(EECONFIG_RGBLIGHT);
#else
    return 0;
#endif
}

void eeconfig_update_rgblight(uint32_t val) {
#ifdef EEPROM_ENABLE
    rgblight_check_config();
    eeprom_update_dword(EECONFIG_RGBLIGHT, val);
#endif
}

void eeconfig_update_rgblight_current(void) { eeconfig_update_rgblight(rgblight_config.raw); }

void eeconfig_update_rgblight_default(void) {
    rgblight_config.enable = 1;
    rgblight_config.mode   = RGBLIGHT_MODE_STATIC_LIGHT;
    rgblight_config.hue    = 0;
    rgblight_config.sat    = UINT8_MAX;
    rgblight_config.val    = RGBLIGHT_LIMIT_VAL;
    rgblight_config.speed  = 0;
    RGBLIGHT_SPLIT_SET_CHANGE_MODEHSVS;
    eeconfig_update_rgblight(rgblight_config.raw);
}

void eeconfig_debug_rgblight(void) {
    dprintf("rgblight_config EEPROM:\n");
    dprintf("rgblight_config.enable = %d\n", rgblight_config.enable);
    dprintf("rghlight_config.mode = %d\n", rgblight_config.mode);
    dprintf("rgblight_config.hue = %d\n", rgblight_config.hue);
    dprintf("rgblight_config.sat = %d\n", rgblight_config.sat);
    dprintf("rgblight_config.val = %d\n", rgblight_config.val);
    dprintf("rgblight_config.speed = %d\n", rgblight_config.speed);
}

void rgblight_init(void) {
    /* if already initialized, don't do it again.
       If you must do it again, extern this and set to false, first.
       This is a dirty, dirty hack until proper hooks can be added for keyboard startup. */
    if (is_rgblight_initialized) {
        return;
    }

    dprintf("rgblight_init called.\n");
    dprintf("rgblight_init start!\n");
    if (!eeconfig_is_enabled()) {
        dprintf("rgblight_init eeconfig is not enabled.\n");
        eeconfig_init();
        eeconfig_update_rgblight_default();
    }
    rgblight_config.raw = eeconfig_read_rgblight();
    RGBLIGHT_SPLIT_SET_CHANGE_MODEHSVS;
    if (!rgblight_config.mode) {
        dprintf("rgblight_init rgblight_config.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_rgblight_default();
        rgblight_config.raw = eeconfig_read_rgblight();
    }
    rgblight_check_config();

    eeconfig_debug_rgblight();  // display current eeprom values

    rgblight_timer_init();  // setup the timer

    if (rgblight_config.enable) {
        rgblight_mode_noeeprom(rgblight_config.mode);
    }

    is_rgblight_initialized = true;
}

uint32_t rgblight_read_dword(void) { return rgblight_config.raw; }

void rgblight_update_dword(uint32_t dword) {
    RGBLIGHT_SPLIT_SET_CHANGE_MODEHSVS;
    rgblight_config.raw = dword;
    if (rgblight_config.enable)
        rgblight_mode_noeeprom(rgblight_config.mode);
    else {
        rgblight_timer_disable();
        rgblight_set();
    }
}

void rgblight_increase(void) {
    uint8_t mode = 0;
    if (rgblight_config.mode < RGBLIGHT_MODES) {
        mode = rgblight_config.mode + 1;
    }
    rgblight_mode(mode);
}
void rgblight_decrease(void) {
    uint8_t mode = 0;
    // Mode will never be < 1. If it ever is, eeprom needs to be initialized.
    if (rgblight_config.mode > RGBLIGHT_MODE_STATIC_LIGHT) {
        mode = rgblight_config.mode - 1;
    }
    rgblight_mode(mode);
}
void rgblight_step_helper(bool write_to_eeprom) {
    uint8_t mode = 0;
    mode         = rgblight_config.mode + 1;
    if (mode > RGBLIGHT_MODES) {
        mode = 1;
    }
    rgblight_mode_eeprom_helper(mode, write_to_eeprom);
}
void rgblight_step_noeeprom(void) { rgblight_step_helper(false); }
void rgblight_step(void) { rgblight_step_helper(true); }
void rgblight_step_reverse_helper(bool write_to_eeprom) {
    uint8_t mode = 0;
    mode         = rgblight_config.mode - 1;
    if (mode < 1) {
        mode = RGBLIGHT_MODES;
    }
    rgblight_mode_eeprom_helper(mode, write_to_eeprom);
}
void rgblight_step_reverse_noeeprom(void) { rgblight_step_reverse_helper(false); }
void rgblight_step_reverse(void) { rgblight_step_reverse_helper(true); }

uint8_t rgblight_get_mode(void) {
    if (!rgblight_config.enable) {
        return false;
    }

    return rgblight_config.mode;
}

void rgblight_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
    if (!rgblight_config.enable) {
        return;
    }
    if (mode < RGBLIGHT_MODE_STATIC_LIGHT) {
        rgblight_config.mode = RGBLIGHT_MODE_STATIC_LIGHT;
    } else if (mode > RGBLIGHT_MODES) {
        rgblight_config.mode = RGBLIGHT_MODES;
    } else {
        rgblight_config.mode = mode;
    }
    RGBLIGHT_SPLIT_SET_CHANGE_MODE;
    if (write_to_eeprom) {
        eeconfig_update_rgblight(rgblight_config.raw);
        dprintf("rgblight mode [EEPROM]: %u\n", rgblight_config.mode);
    } else {
        dprintf("rgblight mode [NOEEPROM]: %u\n", rgblight_config.mode);
    }
    if (is_static_effect(rgblight_config.mode)) {
        rgblight_timer_disable();
    } else {
        rgblight_timer_enable();
    }
#ifdef RGBLIGHT_USE_TIMER
    animation_status.restart = true;
#endif
    rgblight_sethsv_noeeprom(rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
}

void rgblight_mode(uint8_t mode) { rgblight_mode_eeprom_helper(mode, true); }

void rgblight_mode_noeeprom(uint8_t mode) { rgblight_mode_eeprom_helper(mode, false); }

void rgblight_toggle(void) {
    dprintf("rgblight toggle [EEPROM]: rgblight_config.enable = %u\n", !rgblight_config.enable);
    if (rgblight_config.enable) {
        rgblight_disable();
    } else {
        rgblight_enable();
    }
}

void rgblight_toggle_noeeprom(void) {
    dprintf("rgblight toggle [NOEEPROM]: rgblight_config.enable = %u\n", !rgblight_config.enable);
    if (rgblight_config.enable) {
        rgblight_disable_noeeprom();
    } else {
        rgblight_enable_noeeprom();
    }
}

void rgblight_enable(void) {
    rgblight_config.enable = 1;
    // No need to update EEPROM here. rgblight_mode() will do that, actually
    // eeconfig_update_rgblight(rgblight_config.raw);
    dprintf("rgblight enable [EEPROM]: rgblight_config.enable = %u\n", rgblight_config.enable);
    rgblight_mode(rgblight_config.mode);
}

void rgblight_enable_noeeprom(void) {
    rgblight_config.enable = 1;
    dprintf("rgblight enable [NOEEPROM]: rgblight_config.enable = %u\n", rgblight_config.enable);
    rgblight_mode_noeeprom(rgblight_config.mode);
}

void rgblight_disable(void) {
    rgblight_config.enable = 0;
    eeconfig_update_rgblight(rgblight_config.raw);
    dprintf("rgblight disable [EEPROM]: rgblight_config.enable = %u\n", rgblight_config.enable);
    rgblight_timer_disable();
    RGBLIGHT_SPLIT_SET_CHANGE_MODE;
    wait_ms(50);
    rgblight_set();
}

void rgblight_disable_noeeprom(void) {
    rgblight_config.enable = 0;
    dprintf("rgblight disable [NOEEPROM]: rgblight_config.enable = %u\n", rgblight_config.enable);
    rgblight_timer_disable();
    RGBLIGHT_SPLIT_SET_CHANGE_MODE;
    wait_ms(50);
    rgblight_set();
}

bool rgblight_is_enabled(void) { return rgblight_config.enable; }

void rgblight_increase_hue_helper(bool write_to_eeprom) {
    uint8_t hue = rgblight_config.hue + RGBLIGHT_HUE_STEP;
    rgblight_sethsv_eeprom_helper(hue, rgblight_config.sat, rgblight_config.val, write_to_eeprom);
}
void rgblight_increase_hue_noeeprom(void) { rgblight_increase_hue_helper(false); }
void rgblight_increase_hue(void) { rgblight_increase_hue_helper(true); }
void rgblight_decrease_hue_helper(bool write_to_eeprom) {
    uint8_t hue = rgblight_config.hue - RGBLIGHT_HUE_STEP;
    rgblight_sethsv_eeprom_helper(hue, rgblight_config.sat, rgblight_config.val, write_to_eeprom);
}
void rgblight_decrease_hue_noeeprom(void) { rgblight_decrease_hue_helper(false); }
void rgblight_decrease_hue(void) { rgblight_decrease_hue_helper(true); }
void rgblight_increase_sat_helper(bool write_to_eeprom) {
    uint8_t sat = qadd8(rgblight_config.sat, RGBLIGHT_SAT_STEP);
    rgblight_sethsv_eeprom_helper(rgblight_config.hue, sat, rgblight_config.val, write_to_eeprom);
}
void rgblight_increase_sat_noeeprom(void) { rgblight_increase_sat_helper(false); }
void rgblight_increase_sat(void) { rgblight_increase_sat_helper(true); }
void rgblight_decrease_sat_helper(bool write_to_eeprom) {
    uint8_t sat = qsub8(rgblight_config.sat, RGBLIGHT_SAT_STEP);
    rgblight_sethsv_eeprom_helper(rgblight_config.hue, sat, rgblight_config.val, write_to_eeprom);
}
void rgblight_decrease_sat_noeeprom(void) { rgblight_decrease_sat_helper(false); }
void rgblight_decrease_sat(void) { rgblight_decrease_sat_helper(true); }
void rgblight_increase_val_helper(bool write_to_eeprom) {
    uint8_t val = qadd8(rgblight_config.val, RGBLIGHT_VAL_STEP);
    rgblight_sethsv_eeprom_helper(rgblight_config.hue, rgblight_config.sat, val, write_to_eeprom);
}
void rgblight_increase_val_noeeprom(void) { rgblight_increase_val_helper(false); }
void rgblight_increase_val(void) { rgblight_increase_val_helper(true); }
void rgblight_decrease_val_helper(bool write_to_eeprom) {
    uint8_t val = qsub8(rgblight_config.val, RGBLIGHT_VAL_STEP);
    rgblight_sethsv_eeprom_helper(rgblight_config.hue, rgblight_config.sat, val, write_to_eeprom);
}
void rgblight_decrease_val_noeeprom(void) { rgblight_decrease_val_helper(false); }
void rgblight_decrease_val(void) { rgblight_decrease_val_helper(true); }

void rgblight_increase_speed_helper(bool write_to_eeprom) {
    if (rgblight_config.speed < 3) rgblight_config.speed++;
    // RGBLIGHT_SPLIT_SET_CHANGE_HSVS; // NEED?
    if (write_to_eeprom) {
        eeconfig_update_rgblight(rgblight_config.raw);  // EECONFIG needs to be increased to support this
    }
}
void rgblight_increase_speed(void) { rgblight_increase_speed_helper(true); }
void rgblight_increase_speed_noeeprom(void) { rgblight_increase_speed_helper(false); }

void rgblight_decrease_speed_helper(bool write_to_eeprom) {
    if (rgblight_config.speed > 0) rgblight_config.speed--;
    // RGBLIGHT_SPLIT_SET_CHANGE_HSVS; // NEED??
    if (write_to_eeprom) {
        eeconfig_update_rgblight(rgblight_config.raw);  // EECONFIG needs to be increased to support this
    }
}
void rgblight_decrease_speed(void) { rgblight_decrease_speed_helper(true); }
void rgblight_decrease_speed_noeeprom(void) { rgblight_decrease_speed_helper(false); }

void rgblight_sethsv_noeeprom_old(uint8_t hue, uint8_t sat, uint8_t val) {
    if (rgblight_config.enable) {
        LED_TYPE tmp_led;
        sethsv(hue, sat, val, &tmp_led);
        rgblight_setrgb(tmp_led.r, tmp_led.g, tmp_led.b);
    }
}

void rgblight_sethsv_eeprom_helper(uint8_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom) {
    if (rgblight_config.enable) {
        rgblight_status.base_mode = mode_base_table[rgblight_config.mode];
        if (rgblight_config.mode == RGBLIGHT_MODE_STATIC_LIGHT) {
            // same static color
            LED_TYPE tmp_led;
            sethsv(hue, sat, val, &tmp_led);
            rgblight_setrgb(tmp_led.r, tmp_led.g, tmp_led.b);
        } else {
            // all LEDs in same color
            if (1 == 0) {  // dummy
            }
#ifdef RGBLIGHT_EFFECT_BREATHING
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_BREATHING) {
                // breathing mode, ignore the change of val, use in memory value instead
                val = rgblight_config.val;
            }
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_MOOD) {
                // rainbow mood, ignore the change of hue
                hue = rgblight_config.hue;
            }
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_SWIRL) {
                // rainbow swirl, ignore the change of hue
                hue = rgblight_config.hue;
            }
#endif
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_STATIC_GRADIENT) {
                // static gradient
                uint8_t delta     = rgblight_config.mode - rgblight_status.base_mode;
                bool    direction = (delta % 2) == 0;
#    ifdef __AVR__
                // probably due to how pgm_read_word is defined for ARM, but the ARM compiler really hates this line
                uint8_t range = pgm_read_word(&RGBLED_GRADIENT_RANGES[delta / 2]);
#    else
                uint8_t range = RGBLED_GRADIENT_RANGES[delta / 2];
#    endif
                for (uint8_t i = 0; i < rgblight_ranges.effect_num_leds; i++) {
                    uint8_t _hue = ((uint16_t)i * (uint16_t)range) / rgblight_ranges.effect_num_leds;
                    if (direction) {
                        _hue = hue + _hue;
                    } else {
                        _hue = hue - _hue;
                    }
                    dprintf("rgblight rainbow set hsv: %d,%d,%d,%u\n", i, _hue, direction, range);
                    sethsv(_hue, sat, val, (LED_TYPE *)&led[i + rgblight_ranges.effect_start_pos]);
                }
                rgblight_set();
            }
#endif
        }
#ifdef RGBLIGHT_SPLIT
        if (rgblight_config.hue != hue || rgblight_config.sat != sat || rgblight_config.val != val) {
            RGBLIGHT_SPLIT_SET_CHANGE_HSVS;
        }
#endif
        rgblight_config.hue = hue;
        rgblight_config.sat = sat;
        rgblight_config.val = val;
        if (write_to_eeprom) {
            eeconfig_update_rgblight(rgblight_config.raw);
            dprintf("rgblight set hsv [EEPROM]: %u,%u,%u\n", rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
        } else {
            dprintf("rgblight set hsv [NOEEPROM]: %u,%u,%u\n", rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
        }
    }
}

void rgblight_sethsv(uint8_t hue, uint8_t sat, uint8_t val) { rgblight_sethsv_eeprom_helper(hue, sat, val, true); }

void rgblight_sethsv_noeeprom(uint8_t hue, uint8_t sat, uint8_t val) { rgblight_sethsv_eeprom_helper(hue, sat, val, false); }

uint8_t rgblight_get_speed(void) { return rgblight_config.speed; }

void rgblight_set_speed_eeprom_helper(uint8_t speed, bool write_to_eeprom) {
    rgblight_config.speed = speed;
    if (write_to_eeprom) {
        eeconfig_update_rgblight(rgblight_config.raw);  // EECONFIG needs to be increased to support this
        dprintf("rgblight set speed [EEPROM]: %u\n", rgblight_config.speed);
    } else {
        dprintf("rgblight set speed [NOEEPROM]: %u\n", rgblight_config.speed);
    }
}

void rgblight_set_speed(uint8_t speed) { rgblight_set_speed_eeprom_helper(speed, true); }

void rgblight_set_speed_noeeprom(uint8_t speed) { rgblight_set_speed_eeprom_helper(speed, false); }

uint8_t rgblight_get_hue(void) { return rgblight_config.hue; }

uint8_t rgblight_get_sat(void) { return rgblight_config.sat; }

uint8_t rgblight_get_val(void) { return rgblight_config.val; }

HSV rgblight_get_hsv(void) { return (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val}; }

void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b) {
    if (!rgblight_config.enable) {
        return;
    }

    for (uint8_t i = rgblight_ranges.effect_start_pos; i < rgblight_ranges.effect_end_pos; i++) {
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
#ifdef RGBW
        led[i].w = 0;
#endif
    }
    rgblight_set();
}

void rgblight_setrgb_at(uint8_t r, uint8_t g, uint8_t b, uint8_t index) {
    if (!rgblight_config.enable || index >= RGBLED_NUM) {
        return;
    }

    led[index].r = r;
    led[index].g = g;
    led[index].b = b;
#ifdef RGBW
    led[index].w = 0;
#endif
    rgblight_set();
}

void rgblight_sethsv_at(uint8_t hue, uint8_t sat, uint8_t val, uint8_t index) {
    if (!rgblight_config.enable) {
        return;
    }

    LED_TYPE tmp_led;
    sethsv(hue, sat, val, &tmp_led);
    rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b, index);
}

#if defined(RGBLIGHT_EFFECT_BREATHING) || defined(RGBLIGHT_EFFECT_RAINBOW_MOOD) || defined(RGBLIGHT_EFFECT_RAINBOW_SWIRL) || defined(RGBLIGHT_EFFECT_SNAKE) || defined(RGBLIGHT_EFFECT_KNIGHT) || defined(RGBLIGHT_EFFECT_TWINKLE)

static uint8_t get_interval_time(const uint8_t *default_interval_address, uint8_t velocikey_min, uint8_t velocikey_max) {
    return
#    ifdef VELOCIKEY_ENABLE
        velocikey_enabled() ? velocikey_match_speed(velocikey_min, velocikey_max) :
#    endif
                            pgm_read_byte(default_interval_address);
}

#endif

void rgblight_setrgb_range(uint8_t r, uint8_t g, uint8_t b, uint8_t start, uint8_t end) {
    if (!rgblight_config.enable || start < 0 || start >= end || end > RGBLED_NUM) {
        return;
    }

    for (uint8_t i = start; i < end; i++) {
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
#ifdef RGBW
        led[i].w = 0;
#endif
    }
    rgblight_set();
    wait_ms(1);
}

void rgblight_sethsv_range(uint8_t hue, uint8_t sat, uint8_t val, uint8_t start, uint8_t end) {
    if (!rgblight_config.enable) {
        return;
    }

    LED_TYPE tmp_led;
    sethsv(hue, sat, val, &tmp_led);
    rgblight_setrgb_range(tmp_led.r, tmp_led.g, tmp_led.b, start, end);
}

#ifndef RGBLIGHT_SPLIT
void rgblight_setrgb_master(uint8_t r, uint8_t g, uint8_t b) { rgblight_setrgb_range(r, g, b, 0, (uint8_t)RGBLED_NUM / 2); }

void rgblight_setrgb_slave(uint8_t r, uint8_t g, uint8_t b) { rgblight_setrgb_range(r, g, b, (uint8_t)RGBLED_NUM / 2, (uint8_t)RGBLED_NUM); }

void rgblight_sethsv_master(uint8_t hue, uint8_t sat, uint8_t val) { rgblight_sethsv_range(hue, sat, val, 0, (uint8_t)RGBLED_NUM / 2); }

void rgblight_sethsv_slave(uint8_t hue, uint8_t sat, uint8_t val) { rgblight_sethsv_range(hue, sat, val, (uint8_t)RGBLED_NUM / 2, (uint8_t)RGBLED_NUM); }
#endif  // ifndef RGBLIGHT_SPLIT

#ifdef RGBLIGHT_LAYERS
void rgblight_set_layer_state(uint8_t layer, bool enabled) {
    rgblight_layer_mask_t mask = 1 << layer;
    if (enabled) {
        rgblight_status.enabled_layer_mask |= mask;
    } else {
        rgblight_status.enabled_layer_mask &= ~mask;
    }
    RGBLIGHT_SPLIT_SET_CHANGE_LAYERS;
    // Static modes don't have a ticker running to update the LEDs
    if (rgblight_status.timer_enabled == false) {
        rgblight_mode_noeeprom(rgblight_config.mode);
    }

#    ifdef RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgblight_config.enable) {
        rgblight_set();
    }
#    endif
}

bool rgblight_get_layer_state(uint8_t layer) {
    rgblight_layer_mask_t mask = 1 << layer;
    return (rgblight_status.enabled_layer_mask & mask) != 0;
}

// Write any enabled LED layers into the buffer
static void rgblight_layers_write(void) {
    uint8_t i = 0;
    // For each layer
    for (const rgblight_segment_t *const *layer_ptr = rgblight_layers; i < RGBLIGHT_MAX_LAYERS; layer_ptr++, i++) {
        if (!rgblight_get_layer_state(i)) {
            continue;  // Layer is disabled
        }
        const rgblight_segment_t *segment_ptr = pgm_read_ptr(layer_ptr);
        if (segment_ptr == NULL) {
            break;  // No more layers
        }
        // For each segment
        while (1) {
            rgblight_segment_t segment;
            memcpy_P(&segment, segment_ptr, sizeof(rgblight_segment_t));
            if (segment.index == RGBLIGHT_END_SEGMENT_INDEX) {
                break;  // No more segments
            }
            // Write segment.count LEDs
            LED_TYPE *const limit = &led[MIN(segment.index + segment.count, RGBLED_NUM)];
            for (LED_TYPE *led_ptr = &led[segment.index]; led_ptr < limit; led_ptr++) {
                sethsv(segment.hue, segment.sat, segment.val, led_ptr);
            }
            segment_ptr++;
        }
    }
}

#    ifdef RGBLIGHT_LAYER_BLINK
rgblight_layer_mask_t _blinked_layer_mask = 0;
uint16_t              _blink_duration     = 0;
static uint16_t       _blink_timer;

void rgblight_blink_layer(uint8_t layer, uint16_t duration_ms) {
    rgblight_set_layer_state(layer, true);
    _blinked_layer_mask |= 1 << layer;
    _blink_timer    = timer_read();
    _blink_duration = duration_ms;
}

void rgblight_unblink_layers(void) {
    if (_blinked_layer_mask != 0 && timer_elapsed(_blink_timer) > _blink_duration) {
        for (uint8_t layer = 0; layer < RGBLIGHT_MAX_LAYERS; layer++) {
            if ((_blinked_layer_mask & 1 << layer) != 0) {
                rgblight_set_layer_state(layer, false);
            }
        }
        _blinked_layer_mask = 0;
    }
}
#    endif

#endif

__attribute__((weak)) void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) { ws2812_setleds(start_led, num_leds); }

#ifndef RGBLIGHT_CUSTOM_DRIVER

void rgblight_set(void) {
    LED_TYPE *start_led;
    uint8_t   num_leds = rgblight_ranges.clipping_num_leds;

    if (!rgblight_config.enable) {
        for (uint8_t i = rgblight_ranges.effect_start_pos; i < rgblight_ranges.effect_end_pos; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
#    ifdef RGBW
            led[i].w = 0;
#    endif
        }
    }

#    ifdef RGBLIGHT_LAYERS
    if (rgblight_layers != NULL
#        ifndef RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
        && rgblight_config.enable
#        endif
    ) {
        rgblight_layers_write();
    }
#    endif

#    ifdef RGBLIGHT_LED_MAP
    LED_TYPE led0[RGBLED_NUM];
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        led0[i] = led[pgm_read_byte(&led_map[i])];
    }
    start_led = led0 + rgblight_ranges.clipping_start_pos;
#    else
    start_led = led + rgblight_ranges.clipping_start_pos;
#    endif

#    ifdef RGBW
    for (uint8_t i = 0; i < num_leds; i++) {
        convert_rgb_to_rgbw(&start_led[i]);
    }
#    endif
    rgblight_call_driver(start_led, num_leds);
}
#endif

#ifdef RGBLIGHT_SPLIT
/* for split keyboard master side */
uint8_t rgblight_get_change_flags(void) { return rgblight_status.change_flags; }

void rgblight_clear_change_flags(void) { rgblight_status.change_flags = 0; }

void rgblight_get_syncinfo(rgblight_syncinfo_t *syncinfo) {
    syncinfo->config = rgblight_config;
    syncinfo->status = rgblight_status;
}

/* for split keyboard slave side */
void rgblight_update_sync(rgblight_syncinfo_t *syncinfo, bool write_to_eeprom) {
#    ifdef RGBLIGHT_LAYERS
    if (syncinfo->status.change_flags & RGBLIGHT_STATUS_CHANGE_LAYERS) {
        rgblight_status.enabled_layer_mask = syncinfo->status.enabled_layer_mask;
    }
#    endif
    if (syncinfo->status.change_flags & RGBLIGHT_STATUS_CHANGE_MODE) {
        if (syncinfo->config.enable) {
            rgblight_config.enable = 1;  // == rgblight_enable_noeeprom();
            rgblight_mode_eeprom_helper(syncinfo->config.mode, write_to_eeprom);
        } else {
            rgblight_disable_noeeprom();
        }
    }
    if (syncinfo->status.change_flags & RGBLIGHT_STATUS_CHANGE_HSVS) {
        rgblight_sethsv_eeprom_helper(syncinfo->config.hue, syncinfo->config.sat, syncinfo->config.val, write_to_eeprom);
        // rgblight_config.speed = config->speed; // NEED???
    }
#    ifdef RGBLIGHT_USE_TIMER
    if (syncinfo->status.change_flags & RGBLIGHT_STATUS_CHANGE_TIMER) {
        if (syncinfo->status.timer_enabled) {
            rgblight_timer_enable();
        } else {
            rgblight_timer_disable();
        }
    }
#        ifndef RGBLIGHT_SPLIT_NO_ANIMATION_SYNC
    if (syncinfo->status.change_flags & RGBLIGHT_STATUS_ANIMATION_TICK) {
        animation_status.restart = true;
    }
#        endif /* RGBLIGHT_SPLIT_NO_ANIMATION_SYNC */
#    endif     /* RGBLIGHT_USE_TIMER */
}
#endif /* RGBLIGHT_SPLIT */

#ifdef RGBLIGHT_USE_TIMER

typedef void (*effect_func_t)(animation_status_t *anim);

// Animation timer -- use system timer (AVR Timer0)
void rgblight_timer_init(void) {
    // OLD!!!! Animation timer -- AVR Timer3
    // static uint8_t rgblight_timer_is_init = 0;
    // if (rgblight_timer_is_init) {
    //   return;
    // }
    // rgblight_timer_is_init = 1;
    // /* Timer 3 setup */
    // TCCR3B = _BV(WGM32) // CTC mode OCR3A as TOP
    //       | _BV(CS30); // Clock selelct: clk/1
    // /* Set TOP value */
    // uint8_t sreg = SREG;
    // cli();
    // OCR3AH = (RGBLED_TIMER_TOP >> 8) & 0xff;
    // OCR3AL = RGBLED_TIMER_TOP & 0xff;
    // SREG = sreg;

    rgblight_status.timer_enabled = false;
    RGBLIGHT_SPLIT_SET_CHANGE_TIMER_ENABLE;
}
void rgblight_timer_enable(void) {
    if (!is_static_effect(rgblight_config.mode)) {
        rgblight_status.timer_enabled = true;
    }
    animation_status.last_timer = timer_read();
    RGBLIGHT_SPLIT_SET_CHANGE_TIMER_ENABLE;
    dprintf("rgblight timer enabled.\n");
}
void rgblight_timer_disable(void) {
    rgblight_status.timer_enabled = false;
    RGBLIGHT_SPLIT_SET_CHANGE_TIMER_ENABLE;
    dprintf("rgblight timer disable.\n");
}
void rgblight_timer_toggle(void) {
    dprintf("rgblight timer toggle.\n");
    if (rgblight_status.timer_enabled) {
        rgblight_timer_disable();
    } else {
        rgblight_timer_enable();
    }
}

void rgblight_show_solid_color(uint8_t r, uint8_t g, uint8_t b) {
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(r, g, b);
}

static void rgblight_effect_dummy(animation_status_t *anim) {
    // do nothing
    /********
    dprintf("rgblight_task() what happened?\n");
    dprintf("is_static_effect %d\n", is_static_effect(rgblight_config.mode));
    dprintf("mode = %d, base_mode = %d, timer_enabled %d, ",
            rgblight_config.mode, rgblight_status.base_mode,
            rgblight_status.timer_enabled);
    dprintf("last_timer = %d\n",anim->last_timer);
    **/
}

void rgblight_task(void) {
    if (rgblight_status.timer_enabled) {
        effect_func_t effect_func   = rgblight_effect_dummy;
        uint16_t      interval_time = 2000;  // dummy interval
        uint8_t       delta         = rgblight_config.mode - rgblight_status.base_mode;
        animation_status.delta      = delta;

        // static light mode, do nothing here
        if (1 == 0) {  // dummy
        }
#    ifdef RGBLIGHT_EFFECT_BREATHING
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_BREATHING) {
            // breathing mode
            interval_time = get_interval_time(&RGBLED_BREATHING_INTERVALS[delta], 1, 100);
            effect_func   = rgblight_effect_breathing;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_MOOD) {
            // rainbow mood mode
            interval_time = get_interval_time(&RGBLED_RAINBOW_MOOD_INTERVALS[delta], 5, 100);
            effect_func   = rgblight_effect_rainbow_mood;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_SWIRL) {
            // rainbow swirl mode
            interval_time = get_interval_time(&RGBLED_RAINBOW_SWIRL_INTERVALS[delta / 2], 1, 100);
            effect_func   = rgblight_effect_rainbow_swirl;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_SNAKE
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_SNAKE) {
            // snake mode
            interval_time = get_interval_time(&RGBLED_SNAKE_INTERVALS[delta / 2], 1, 200);
            effect_func   = rgblight_effect_snake;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_KNIGHT
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_KNIGHT) {
            // knight mode
            interval_time = get_interval_time(&RGBLED_KNIGHT_INTERVALS[delta], 5, 100);
            effect_func   = rgblight_effect_knight;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_CHRISTMAS
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_CHRISTMAS) {
            // christmas mode
            interval_time = RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL;
            effect_func   = (effect_func_t)rgblight_effect_christmas;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_RGB_TEST
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_RGB_TEST) {
            // RGB test mode
            interval_time = pgm_read_word(&RGBLED_RGBTEST_INTERVALS[0]);
            effect_func   = (effect_func_t)rgblight_effect_rgbtest;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_ALTERNATING
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_ALTERNATING) {
            interval_time = 500;
            effect_func   = (effect_func_t)rgblight_effect_alternating;
        }
#    endif
#    ifdef RGBLIGHT_EFFECT_TWINKLE
        else if (rgblight_status.base_mode == RGBLIGHT_MODE_TWINKLE) {
            interval_time = get_interval_time(&RGBLED_TWINKLE_INTERVALS[delta % 3], 5, 50);
            effect_func   = (effect_func_t)rgblight_effect_twinkle;
        }
#    endif
        if (animation_status.restart) {
            animation_status.restart    = false;
            animation_status.last_timer = timer_read() - interval_time - 1;
            animation_status.pos16      = 0;  // restart signal to local each effect
        }
        if (timer_elapsed(animation_status.last_timer) >= interval_time) {
#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
            static uint16_t report_last_timer = 0;
            static bool     tick_flag         = false;
            uint16_t        oldpos16;
            if (tick_flag) {
                tick_flag = false;
                if (timer_elapsed(report_last_timer) >= 30000) {
                    report_last_timer = timer_read();
                    dprintf("rgblight animation tick report to slave\n");
                    RGBLIGHT_SPLIT_ANIMATION_TICK;
                }
            }
            oldpos16 = animation_status.pos16;
#    endif
            animation_status.last_timer += interval_time;
            effect_func(&animation_status);
#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
            if (animation_status.pos16 == 0 && oldpos16 != 0) {
                tick_flag = true;
            }
#    endif
        }
    }

#    ifdef RGBLIGHT_LAYER_BLINK
    rgblight_unblink_layers();
#    endif
}

#endif /* RGBLIGHT_USE_TIMER */

// Effects
#ifdef RGBLIGHT_EFFECT_BREATHING

#    ifndef RGBLIGHT_EFFECT_BREATHE_CENTER
#        ifndef RGBLIGHT_BREATHE_TABLE_SIZE
#            define RGBLIGHT_BREATHE_TABLE_SIZE 256  // 256 or 128 or 64
#        endif
#        include <rgblight_breathe_table.h>
#    endif

__attribute__((weak)) const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};

void rgblight_effect_breathing(animation_status_t *anim) {
    float val;

    // http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/
#    ifdef RGBLIGHT_EFFECT_BREATHE_TABLE
    val = pgm_read_byte(&rgblight_effect_breathe_table[anim->pos / table_scale]);
#    else
    val = (exp(sin((anim->pos / 255.0) * M_PI)) - RGBLIGHT_EFFECT_BREATHE_CENTER / M_E) * (RGBLIGHT_EFFECT_BREATHE_MAX / (M_E - 1 / M_E));
#    endif
    rgblight_sethsv_noeeprom_old(rgblight_config.hue, rgblight_config.sat, val);
    anim->pos = (anim->pos + 1);
}
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
__attribute__((weak)) const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {120, 60, 30};

void rgblight_effect_rainbow_mood(animation_status_t *anim) {
    rgblight_sethsv_noeeprom_old(anim->current_hue, rgblight_config.sat, rgblight_config.val);
    anim->current_hue++;
}
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    ifndef RGBLIGHT_RAINBOW_SWIRL_RANGE
#        define RGBLIGHT_RAINBOW_SWIRL_RANGE 255
#    endif

__attribute__((weak)) const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};

void rgblight_effect_rainbow_swirl(animation_status_t *anim) {
    uint8_t hue;
    uint8_t i;

    for (i = 0; i < rgblight_ranges.effect_num_leds; i++) {
        hue = (RGBLIGHT_RAINBOW_SWIRL_RANGE / rgblight_ranges.effect_num_leds * i + anim->current_hue);
        sethsv(hue, rgblight_config.sat, rgblight_config.val, (LED_TYPE *)&led[i + rgblight_ranges.effect_start_pos]);
    }
    rgblight_set();

    if (anim->delta % 2) {
        anim->current_hue++;
    } else {
        anim->current_hue--;
    }
}
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
__attribute__((weak)) const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {100, 50, 20};

void rgblight_effect_snake(animation_status_t *anim) {
    static uint8_t pos = 0;
    uint8_t        i, j;
    int8_t         k;
    int8_t         increment = 1;

    if (anim->delta % 2) {
        increment = -1;
    }

#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
    if (anim->pos == 0) {  // restart signal
        if (increment == 1) {
            pos = rgblight_ranges.effect_num_leds - 1;
        } else {
            pos = 0;
        }
        anim->pos = 1;
    }
#    endif

    for (i = 0; i < rgblight_ranges.effect_num_leds; i++) {
        LED_TYPE *ledp = led + i + rgblight_ranges.effect_start_pos;
        ledp->r        = 0;
        ledp->g        = 0;
        ledp->b        = 0;
#    ifdef RGBW
        ledp->w = 0;
#    endif
        for (j = 0; j < RGBLIGHT_EFFECT_SNAKE_LENGTH; j++) {
            k = pos + j * increment;
            if (k > RGBLED_NUM) {
                k = k % RGBLED_NUM;
            }
            if (k < 0) {
                k = k + rgblight_ranges.effect_num_leds;
            }
            if (i == k) {
                sethsv(rgblight_config.hue, rgblight_config.sat, (uint8_t)(rgblight_config.val * (RGBLIGHT_EFFECT_SNAKE_LENGTH - j) / RGBLIGHT_EFFECT_SNAKE_LENGTH), ledp);
            }
        }
    }
    rgblight_set();
    if (increment == 1) {
        if (pos - 1 < 0) {
            pos = rgblight_ranges.effect_num_leds - 1;
#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
            anim->pos = 0;
#    endif
        } else {
            pos -= 1;
#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
            anim->pos = 1;
#    endif
        }
    } else {
        pos = (pos + 1) % rgblight_ranges.effect_num_leds;
#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
        anim->pos = pos;
#    endif
    }
}
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
__attribute__((weak)) const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {127, 63, 31};

void rgblight_effect_knight(animation_status_t *anim) {
    static int8_t low_bound  = 0;
    static int8_t high_bound = RGBLIGHT_EFFECT_KNIGHT_LENGTH - 1;
    static int8_t increment  = 1;
    uint8_t       i, cur;

#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
    if (anim->pos == 0) {  // restart signal
        anim->pos  = 1;
        low_bound  = 0;
        high_bound = RGBLIGHT_EFFECT_KNIGHT_LENGTH - 1;
        increment  = 1;
    }
#    endif
    // Set all the LEDs to 0
    for (i = rgblight_ranges.effect_start_pos; i < rgblight_ranges.effect_end_pos; i++) {
        led[i].r = 0;
        led[i].g = 0;
        led[i].b = 0;
#    ifdef RGBW
        led[i].w = 0;
#    endif
    }
    // Determine which LEDs should be lit up
    for (i = 0; i < RGBLIGHT_EFFECT_KNIGHT_LED_NUM; i++) {
        cur = (i + RGBLIGHT_EFFECT_KNIGHT_OFFSET) % rgblight_ranges.effect_num_leds + rgblight_ranges.effect_start_pos;

        if (i >= low_bound && i <= high_bound) {
            sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, (LED_TYPE *)&led[cur]);
        } else {
            led[cur].r = 0;
            led[cur].g = 0;
            led[cur].b = 0;
#    ifdef RGBW
            led[cur].w = 0;
#    endif
        }
    }
    rgblight_set();

    // Move from low_bound to high_bound changing the direction we increment each
    // time a boundary is hit.
    low_bound += increment;
    high_bound += increment;

    if (high_bound <= 0 || low_bound >= RGBLIGHT_EFFECT_KNIGHT_LED_NUM - 1) {
        increment = -increment;
#    if defined(RGBLIGHT_SPLIT) && !defined(RGBLIGHT_SPLIT_NO_ANIMATION_SYNC)
        if (increment == 1) {
            anim->pos = 0;
        }
#    endif
    }
}
#endif

#ifdef RGBLIGHT_EFFECT_CHRISTMAS
#    define CUBED(x) ((x) * (x) * (x))

/**
 * Christmas lights effect, with a smooth animation between red & green.
 */
void rgblight_effect_christmas(animation_status_t *anim) {
    static int8_t increment = 1;
    const uint8_t max_pos   = 32;
    const uint8_t hue_green = 85;

    uint32_t xa;
    uint8_t  hue, val;
    uint8_t  i;

    // The effect works by animating anim->pos from 0 to 32 and back to 0.
    // The pos is used in a cubic bezier formula to ease-in-out between red and green, leaving the interpolated colors visible as short as possible.
    xa  = CUBED((uint32_t)anim->pos);
    hue = ((uint32_t)hue_green) * xa / (xa + CUBED((uint32_t)(max_pos - anim->pos)));
    // Additionally, these interpolated colors get shown with a slightly darker value, to make them less prominent than the main colors.
    val = 255 - (3 * (hue < hue_green / 2 ? hue : hue_green - hue) / 2);

    for (i = 0; i < rgblight_ranges.effect_num_leds; i++) {
        uint8_t local_hue = (i / RGBLIGHT_EFFECT_CHRISTMAS_STEP) % 2 ? hue : hue_green - hue;
        sethsv(local_hue, rgblight_config.sat, val, (LED_TYPE *)&led[i + rgblight_ranges.effect_start_pos]);
    }
    rgblight_set();

    if (anim->pos == 0) {
        increment = 1;
    } else if (anim->pos == max_pos) {
        increment = -1;
    }
    anim->pos += increment;
}
#endif

#ifdef RGBLIGHT_EFFECT_RGB_TEST
__attribute__((weak)) const uint16_t RGBLED_RGBTEST_INTERVALS[] PROGMEM = {1024};

void rgblight_effect_rgbtest(animation_status_t *anim) {
    static uint8_t maxval = 0;
    uint8_t        g;
    uint8_t        r;
    uint8_t        b;

    if (maxval == 0) {
        LED_TYPE tmp_led;
        sethsv(0, 255, RGBLIGHT_LIMIT_VAL, &tmp_led);
        maxval = tmp_led.r;
    }
    g = r = b = 0;
    switch (anim->pos) {
        case 0:
            r = maxval;
            break;
        case 1:
            g = maxval;
            break;
        case 2:
            b = maxval;
            break;
    }
    rgblight_setrgb(r, g, b);
    anim->pos = (anim->pos + 1) % 3;
}
#endif

#ifdef RGBLIGHT_EFFECT_ALTERNATING
void rgblight_effect_alternating(animation_status_t *anim) {
    for (int i = 0; i < rgblight_ranges.effect_num_leds; i++) {
        LED_TYPE *ledp = led + i + rgblight_ranges.effect_start_pos;
        if (i < rgblight_ranges.effect_num_leds / 2 && anim->pos) {
            sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, ledp);
        } else if (i >= rgblight_ranges.effect_num_leds / 2 && !anim->pos) {
            sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, ledp);
        } else {
            sethsv(rgblight_config.hue, rgblight_config.sat, 0, ledp);
        }
    }
    rgblight_set();
    anim->pos = (anim->pos + 1) % 2;
}
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
__attribute__((weak)) const uint8_t RGBLED_TWINKLE_INTERVALS[] PROGMEM = {50, 25, 10};

typedef struct PACKED {
    HSV     hsv;
    uint8_t life;
    bool    up;
} TwinkleState;

static TwinkleState led_twinkle_state[RGBLED_NUM];

void rgblight_effect_twinkle(animation_status_t *anim) {
    bool random_color = anim->delta / 3;
    bool restart      = anim->pos == 0;
    anim->pos         = 1;

    for (uint8_t i = 0; i < rgblight_ranges.effect_num_leds; i++) {
        TwinkleState *t = &(led_twinkle_state[i]);
        HSV *         c = &(t->hsv);
        if (restart) {
            // Restart
            t->life  = 0;
            t->hsv.v = 0;
        } else if (t->life) {
            // This LED is already on, either brightening or dimming
            t->life--;
            uint8_t on = t->up ? RGBLIGHT_EFFECT_TWINKLE_LIFE - t->life : t->life;
            c->v       = (uint16_t)rgblight_config.val * on / RGBLIGHT_EFFECT_TWINKLE_LIFE;
            if (t->life == 0 && t->up) {
                t->up   = false;
                t->life = RGBLIGHT_EFFECT_TWINKLE_LIFE;
            }
            if (!random_color) {
                c->h = rgblight_config.hue;
                c->s = rgblight_config.sat;
            }
        } else if (rand() < RAND_MAX * RGBLIGHT_EFFECT_TWINKLE_PROBABILITY) {
            // This LED is off, but was randomly selected to start brightening
            c->h    = random_color ? rand() % 0xFF : rgblight_config.hue;
            c->s    = random_color ? (rand() % (rgblight_config.sat / 2)) + (rgblight_config.sat / 2) : rgblight_config.sat;
            c->v    = 0;
            t->life = RGBLIGHT_EFFECT_TWINKLE_LIFE;
            t->up   = true;
        } else {
            // This LED is off, and was NOT selected to start brightening
        }

        LED_TYPE *ledp = led + i + rgblight_ranges.effect_start_pos;
        sethsv(c->h, c->s, c->v, ledp);
    }

    rgblight_set();
}
#endif
