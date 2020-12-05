/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 Clueboard
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

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "led_matrix.h"
#include "progmem.h"
#include "config.h"
#include "eeprom.h"
#include <string.h>
#include <math.h>

led_config_t led_matrix_config;

#ifndef MAX
#    define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef MIN
#    define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef LED_DISABLE_AFTER_TIMEOUT
#    define LED_DISABLE_AFTER_TIMEOUT 0
#endif

#ifndef LED_DISABLE_WHEN_USB_SUSPENDED
#    define LED_DISABLE_WHEN_USB_SUSPENDED false
#endif

#ifndef EECONFIG_LED_MATRIX
#    define EECONFIG_LED_MATRIX EECONFIG_RGBLIGHT
#endif

#if !defined(LED_MATRIX_MAXIMUM_BRIGHTNESS) || LED_MATRIX_MAXIMUM_BRIGHTNESS > 255
#    define LED_MATRIX_MAXIMUM_BRIGHTNESS 255
#endif

bool g_suspend_state = false;

// Global tick at 20 Hz
uint32_t g_tick = 0;

// Ticks since this key was last hit.
uint8_t g_key_hit[LED_DRIVER_LED_COUNT];

// Ticks since any key was last hit.
uint32_t g_any_key_hit = 0;

uint32_t eeconfig_read_led_matrix(void) { return eeprom_read_dword(EECONFIG_LED_MATRIX); }

void eeconfig_update_led_matrix(uint32_t config_value) { eeprom_update_dword(EECONFIG_LED_MATRIX, config_value); }

void eeconfig_update_led_matrix_default(void) {
    dprintf("eeconfig_update_led_matrix_default\n");
    led_matrix_config.enable = 1;
    led_matrix_config.mode   = LED_MATRIX_UNIFORM_BRIGHTNESS;
    led_matrix_config.val    = 128;
    led_matrix_config.speed  = 0;
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void eeconfig_debug_led_matrix(void) {
    dprintf("led_matrix_config eeprom\n");
    dprintf("led_matrix_config.enable = %d\n", led_matrix_config.enable);
    dprintf("led_matrix_config.mode = %d\n", led_matrix_config.mode);
    dprintf("led_matrix_config.val = %d\n", led_matrix_config.val);
    dprintf("led_matrix_config.speed = %d\n", led_matrix_config.speed);
}

// Last led hit
#ifndef LED_HITS_TO_REMEMBER
#    define LED_HITS_TO_REMEMBER 8
#endif
uint8_t g_last_led_hit[LED_HITS_TO_REMEMBER] = {255};
uint8_t g_last_led_count                     = 0;

void map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i, uint8_t *led_count) {
    led_matrix led;
    *led_count = 0;

    for (uint8_t i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        // map_index_to_led(i, &led);
        led = g_leds[i];
        if (row == led.matrix_co.row && column == led.matrix_co.col) {
            led_i[*led_count] = i;
            (*led_count)++;
        }
    }
}

void led_matrix_update_pwm_buffers(void) { led_matrix_driver.flush(); }

void led_matrix_set_index_value(int index, uint8_t value) { led_matrix_driver.set_value(index, value); }

void led_matrix_set_index_value_all(uint8_t value) { led_matrix_driver.set_value_all(value); }

bool process_led_matrix(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t led[8], led_count;
        map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        if (led_count > 0) {
            for (uint8_t i = LED_HITS_TO_REMEMBER; i > 1; i--) {
                g_last_led_hit[i - 1] = g_last_led_hit[i - 2];
            }
            g_last_led_hit[0] = led[0];
            g_last_led_count  = MIN(LED_HITS_TO_REMEMBER, g_last_led_count + 1);
        }
        for (uint8_t i = 0; i < led_count; i++) g_key_hit[led[i]] = 0;
        g_any_key_hit = 0;
    } else {
#ifdef LED_MATRIX_KEYRELEASES
        uint8_t led[8], led_count;
        map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        for (uint8_t i = 0; i < led_count; i++) g_key_hit[led[i]] = 255;

        g_any_key_hit = 255;
#endif
    }
    return true;
}

void led_matrix_set_suspend_state(bool state) { g_suspend_state = state; }

// All LEDs off
void led_matrix_all_off(void) { led_matrix_set_index_value_all(0); }

// Uniform brightness
void led_matrix_uniform_brightness(void) { led_matrix_set_index_value_all(LED_MATRIX_MAXIMUM_BRIGHTNESS / BACKLIGHT_LEVELS * led_matrix_config.val); }

void led_matrix_custom(void) {}

void led_matrix_task(void) {
    if (!led_matrix_config.enable) {
        led_matrix_all_off();
        led_matrix_indicators();
        return;
    }

    g_tick++;

    if (g_any_key_hit < 0xFFFFFFFF) {
        g_any_key_hit++;
    }

    for (int led = 0; led < LED_DRIVER_LED_COUNT; led++) {
        if (g_key_hit[led] < 255) {
            if (g_key_hit[led] == 254) g_last_led_count = MAX(g_last_led_count - 1, 0);
            g_key_hit[led]++;
        }
    }

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool    suspend_backlight = ((g_suspend_state && LED_DISABLE_WHEN_USB_SUSPENDED) || (LED_DISABLE_AFTER_TIMEOUT > 0 && g_any_key_hit > LED_DISABLE_AFTER_TIMEOUT * 60 * 20));
    uint8_t effect            = suspend_backlight ? 0 : led_matrix_config.mode;

    // this gets ticked at 20 Hz.
    // each effect can opt to do calculations
    // and/or request PWM buffer updates.
    switch (effect) {
        case LED_MATRIX_UNIFORM_BRIGHTNESS:
            led_matrix_uniform_brightness();
            break;
        default:
            led_matrix_custom();
            break;
    }

    if (!suspend_backlight) {
        led_matrix_indicators();
    }

    // Tell the LED driver to update its state
    led_matrix_driver.flush();
}

void led_matrix_indicators(void) {
    led_matrix_indicators_kb();
    led_matrix_indicators_user();
}

__attribute__((weak)) void led_matrix_indicators_kb(void) {}

__attribute__((weak)) void led_matrix_indicators_user(void) {}

// void led_matrix_set_indicator_index(uint8_t *index, uint8_t row, uint8_t column)
// {
//  if (row >= MATRIX_ROWS)
//  {
//      // Special value, 255=none, 254=all
//      *index = row;
//  }
//  else
//  {
//      // This needs updated to something like
//      // uint8_t led[8], led_count;
//      // map_row_column_to_led(row,column,led,&led_count);
//      // for(uint8_t i = 0; i < led_count; i++)
//      map_row_column_to_led(row, column, index);
//  }
// }

void led_matrix_init(void) {
    led_matrix_driver.init();

    // Wait half a second for the driver to finish initializing
    wait_ms(500);

    // clear the key hits
    for (int led = 0; led < LED_DRIVER_LED_COUNT; led++) {
        g_key_hit[led] = 255;
    }

    if (!eeconfig_is_enabled()) {
        dprintf("led_matrix_init_drivers eeconfig is not enabled.\n");
        eeconfig_init();
        eeconfig_update_led_matrix_default();
    }

    led_matrix_config.raw = eeconfig_read_led_matrix();

    if (!led_matrix_config.mode) {
        dprintf("led_matrix_init_drivers led_matrix_config.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_led_matrix_default();
        led_matrix_config.raw = eeconfig_read_led_matrix();
    }

    eeconfig_debug_led_matrix();  // display current eeprom values
}

// Deals with the messy details of incrementing an integer
static uint8_t increment(uint8_t value, uint8_t step, uint8_t min, uint8_t max) {
    int16_t new_value = value;
    new_value += step;
    return MIN(MAX(new_value, min), max);
}

static uint8_t decrement(uint8_t value, uint8_t step, uint8_t min, uint8_t max) {
    int16_t new_value = value;
    new_value -= step;
    return MIN(MAX(new_value, min), max);
}

// void *backlight_get_custom_key_value_eeprom_address(uint8_t led) {
//     // 3 bytes per value
//     return EECONFIG_LED_MATRIX + (led * 3);
// }

// void backlight_get_key_value(uint8_t led, uint8_t *value) {
//     void *address = backlight_get_custom_key_value_eeprom_address(led);
//     value = eeprom_read_byte(address);
// }

// void backlight_set_key_value(uint8_t row, uint8_t column, uint8_t value) {
//     uint8_t led[8], led_count;
//     map_row_column_to_led(row,column,led,&led_count);
//     for(uint8_t i = 0; i < led_count; i++) {
//         if (led[i] < LED_DRIVER_LED_COUNT) {
//             void *address = backlight_get_custom_key_value_eeprom_address(led[i]);
//             eeprom_update_byte(address, value);
//         }
//     }
// }

uint32_t led_matrix_get_tick(void) { return g_tick; }

void led_matrix_toggle(void) {
    led_matrix_config.enable ^= 1;
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void led_matrix_enable(void) {
    led_matrix_config.enable = 1;
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void led_matrix_enable_noeeprom(void) { led_matrix_config.enable = 1; }

void led_matrix_disable(void) {
    led_matrix_config.enable = 0;
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void led_matrix_disable_noeeprom(void) { led_matrix_config.enable = 0; }

void led_matrix_step(void) {
    led_matrix_config.mode++;
    if (led_matrix_config.mode >= LED_MATRIX_EFFECT_MAX) {
        led_matrix_config.mode = 1;
    }
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void led_matrix_step_reverse(void) {
    led_matrix_config.mode--;
    if (led_matrix_config.mode < 1) {
        led_matrix_config.mode = LED_MATRIX_EFFECT_MAX - 1;
    }
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void led_matrix_increase_val(void) {
    led_matrix_config.val = increment(led_matrix_config.val, 8, 0, LED_MATRIX_MAXIMUM_BRIGHTNESS);
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void led_matrix_decrease_val(void) {
    led_matrix_config.val = decrement(led_matrix_config.val, 8, 0, LED_MATRIX_MAXIMUM_BRIGHTNESS);
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void led_matrix_increase_speed(void) {
    led_matrix_config.speed = increment(led_matrix_config.speed, 1, 0, 3);
    eeconfig_update_led_matrix(led_matrix_config.raw);  // EECONFIG needs to be increased to support this
}

void led_matrix_decrease_speed(void) {
    led_matrix_config.speed = decrement(led_matrix_config.speed, 1, 0, 3);
    eeconfig_update_led_matrix(led_matrix_config.raw);  // EECONFIG needs to be increased to support this
}

void led_matrix_mode(uint8_t mode, bool eeprom_write) {
    led_matrix_config.mode = mode;
    if (eeprom_write) {
        eeconfig_update_led_matrix(led_matrix_config.raw);
    }
}

uint8_t led_matrix_get_mode(void) { return led_matrix_config.mode; }

void led_matrix_set_value_noeeprom(uint8_t val) { led_matrix_config.val = val; }

void led_matrix_set_value(uint8_t val) {
    led_matrix_set_value_noeeprom(val);
    eeconfig_update_led_matrix(led_matrix_config.raw);
}

void backlight_set(uint8_t val) { led_matrix_set_value(val); }
