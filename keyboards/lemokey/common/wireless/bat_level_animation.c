
/* Copyright 2022~2024 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"
#include "wireless.h"
#include "indicator.h"
#include "lpm.h"
#if defined(PROTOCOL_CHIBIOS)
#    include <usb_main.h>
#elif if defined(PROTOCOL_LUFA)
#    include "lufa.h"
#endif
#include "eeprom.h"

#ifndef BAT_LEVEL_GROWING_INTERVAL
#    define BAT_LEVEL_GROWING_INTERVAL 150
#endif

#ifndef BAT_LEVEL_ON_INTERVAL
#    define BAT_LEVEL_ON_INTERVAL 3000
#endif

#ifdef LED_MATRIX_ENABLE
#    define LED_DRIVER_IS_ENABLED led_matrix_is_enabled
#endif

#ifdef RGB_MATRIX_ENABLE
#    define LED_DRIVER_IS_ENABLED rgb_matrix_is_enabled
#endif

enum {
    BAT_LVL_ANI_NONE,
    BAT_LVL_ANI_GROWING,
    BAT_LVL_ANI_BLINK_OFF,
    BAT_LVL_ANI_BLINK_ON,
};

static uint8_t  animation_state          = 0;
static uint32_t bat_lvl_ani_timer_buffer = 0;
static uint8_t  bat_percentage;
static uint8_t  cur_percentage;
static uint32_t time_interval;
#ifdef RGB_MATRIX_ENABLE
static uint8_t r, g, b;
#endif

extern indicator_config_t indicator_config;
extern backlight_state_t  original_backlight_state;

#ifdef INDICATOR_LED_PINS
void bat_level_stop(void) {
    pin_t bat_lvl_led_pin_list[] = INDICATOR_LED_PINS;
    for (uint8_t i = 0; i < INDICATOR_LED_COUNT; i++) {
        writePin(bat_lvl_led_pin_list[i], !LED_PIN_ON_STATE);
    }
    animation_state = BAT_LVL_ANI_NONE;
}

__attribute__((weak)) void bat_level_indication(uint8_t percentage) {
    pin_t   bat_lvl_led_pin_list[] = INDICATOR_LED_PINS;
    uint8_t led_cnt                = sizeof(bat_lvl_led_pin_list) / sizeof(bat_lvl_led_pin_list[0]);

    bat_level_stop();
    animation_state = BAT_LVL_ANI_BLINK_ON;
    cur_percentage  = 0;
    time_interval   = 3000;

    if ((percentage / 10) >= 8)
        cur_percentage = 4;
    else if ((percentage / 10) >= 6)
        cur_percentage = 3;
    else if ((percentage / 10) >= 3)
        cur_percentage = 2;
    else
        cur_percentage = 1;

    for (uint8_t i = 0; i < cur_percentage && i < led_cnt; i++) {
        writePin(bat_lvl_led_pin_list[i], LED_PIN_ON_STATE);
    }
}
#endif

void bat_level_animiation_start(uint8_t percentage) {
    /* Turn on backlight mode for indicator */
    animation_state          = BAT_LVL_ANI_GROWING;
    bat_lvl_ani_timer_buffer = timer_read32();
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
    indicator_enable();

    bat_percentage = percentage;
    cur_percentage = 0;
    time_interval  = BAT_LEVEL_GROWING_INTERVAL;
#    ifdef RGB_MATRIX_ENABLE
    r = g = b = 255;
#    endif
#else
    bat_level_indication(percentage);
#endif
}

void bat_level_animiation_stop(void) {
#if !defined(LED_MATRIX_ENABLE) && !defined(RGB_MATRIX_ENABLE)
    pin_t bat_lvl_led_pin_list[INDICATOR_LED_COUNT] = INDICATOR_LED_PINS;
    for (uint8_t i = 0; i < INDICATOR_LED_COUNT; i++) {
        writePin(bat_lvl_led_pin_list[i], !INDICATORS_LED_PIN_ON_STATE);
    }
#endif
    animation_state = BAT_LVL_ANI_NONE;
}

bool bat_level_animiation_actived(void) {
    return animation_state;
}

void bat_level_animiation_indicate(void) {
#ifdef LED_MATRIX_ENABLE
    uint8_t bat_lvl_led_list[10] = BAT_LEVEL_LED_LIST;

    for (uint8_t i = 0; i <= LED_MATRIX_LED_COUNT; i++) {
        led_matrix_set_value(i, 0);
    }

    if (animation_state == BAT_LVL_ANI_GROWING || animation_state == BAT_LVL_ANI_BLINK_ON)
        for (uint8_t i = 0; i < cur_percentage / 10; i++)
            led_matrix_set_value(bat_lvl_led_list[i], 255);
#endif

#ifdef RGB_MATRIX_ENABLE
    uint8_t bat_lvl_led_list[10] = BAT_LEVEL_LED_LIST;

    for (uint8_t i = 0; i <= RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    if (animation_state == BAT_LVL_ANI_GROWING || animation_state == BAT_LVL_ANI_BLINK_ON) {
        for (uint8_t i = 0; i < cur_percentage / 10; i++) {
            rgb_matrix_set_color(bat_lvl_led_list[i], r, g, b);
        }
    }
#endif
}

void bat_level_animiation_update(void) {
    switch (animation_state) {
        case BAT_LVL_ANI_GROWING:
            if (cur_percentage < bat_percentage)
                cur_percentage += 10;
            else {
                if (cur_percentage == 0) cur_percentage = 10;
                animation_state = BAT_LVL_ANI_BLINK_OFF;
            }
            break;

        case BAT_LVL_ANI_BLINK_OFF:
#ifdef RGB_MATRIX_ENABLE
            if (bat_percentage < 30) {
                r = 255;
                b = g = 0;
            } else {
                r = b = 0;
                g     = 255;
            }
#endif
            time_interval   = BAT_LEVEL_ON_INTERVAL;
            animation_state = BAT_LVL_ANI_BLINK_ON;
            break;

        case BAT_LVL_ANI_BLINK_ON:
            animation_state = BAT_LVL_ANI_NONE;
#if defined(RGB_MATRIX_ENABLE) || defined(LED_MATRIX_ENABLE)
            indicator_eeconfig_reload();
            if (indicator_config.value == 0 && !LED_DRIVER_IS_ENABLED()) {
                indicator_disable();
            }
#endif
            lpm_timer_reset();
            break;

        default:
            break;
    }

    bat_lvl_ani_timer_buffer = timer_read32();
}

void bat_level_animiation_task(void) {
    if (animation_state && sync_timer_elapsed32(bat_lvl_ani_timer_buffer) > time_interval) {
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
        bat_level_animiation_update();
#else
        bat_level_stop();
#endif
    }
}
