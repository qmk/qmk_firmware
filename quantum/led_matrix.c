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

#include "led_matrix.h"
#include "progmem.h"
#include "config.h"
#include "eeprom.h"
#include <string.h>
#include <math.h>
#include "led_tables.h"

#include <lib/lib8tion/lib8tion.h>

#ifndef MAX
#    define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef MIN
#    define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#if defined(LED_DISABLE_AFTER_TIMEOUT) && !defined(LED_DISABLE_TIMEOUT)
#    define LED_DISABLE_TIMEOUT (LED_DISABLE_AFTER_TIMEOUT * 1200UL)
#endif

#ifndef LED_DISABLE_TIMEOUT
#    define LED_DISABLE_TIMEOUT 0
#endif

#ifndef LED_DISABLE_WHEN_USB_SUSPENDED
#    define LED_DISABLE_WHEN_USB_SUSPENDED false
#endif

#if !defined(LED_MATRIX_MAXIMUM_BRIGHTNESS) || LED_MATRIX_MAXIMUM_BRIGHTNESS > UINT8_MAX
#    undef LED_MATRIX_MAXIMUM_BRIGHTNESS
#    define LED_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#endif

#if !defined(LED_MATRIX_VAL_STEP)
#    define LED_MATRIX_VAL_STEP 8
#endif

#if !defined(LED_MATRIX_SPD_STEP)
#    define LED_MATRIX_SPD_STEP 16
#endif

#if !defined(LED_MATRIX_STARTUP_MODE)
#    define LED_MATRIX_STARTUP_MODE LED_MATRIX_UNIFORM_BRIGHTNESS
#endif

#if !defined(LED_MATRIX_STARTUP_VAL)
#    define LED_MATRIX_STARTUP_VAL LED_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#if !defined(LED_MATRIX_STARTUP_SPD)
#    define LED_MATRIX_STARTUP_SPD UINT8_MAX / 2
#endif

// globals
bool           g_suspend_state = false;
led_eeconfig_t led_matrix_eeconfig;  // TODO: would like to prefix this with g_ for global consistancy, do this in another pr

// Global tick at 20 Hz
uint32_t g_tick = 0;

// Ticks since this key was last hit.
uint8_t g_key_hit[DRIVER_LED_TOTAL];

// Ticks since any key was last hit.
uint32_t g_any_key_hit = 0;

void eeconfig_read_led_matrix(void) { eeprom_read_block(&led_matrix_eeconfig, EECONFIG_LED_MATRIX, sizeof(led_matrix_eeconfig)); }

void eeconfig_update_led_matrix(void) { eeprom_update_block(&led_matrix_eeconfig, EECONFIG_LED_MATRIX, sizeof(led_matrix_eeconfig)); }

void eeconfig_update_led_matrix_default(void) {
    dprintf("eeconfig_update_led_matrix_default\n");
    led_matrix_eeconfig.enable = 1;
    led_matrix_eeconfig.mode   = LED_MATRIX_STARTUP_MODE;
    led_matrix_eeconfig.val    = LED_MATRIX_STARTUP_VAL;
    led_matrix_eeconfig.speed  = LED_MATRIX_STARTUP_SPD;
    eeconfig_update_led_matrix();
}

void eeconfig_debug_led_matrix(void) {
    dprintf("led_matrix_eeconfig EEPROM\n");
    dprintf("led_matrix_eeconfig.enable = %d\n", led_matrix_eeconfig.enable);
    dprintf("led_matrix_eeconfig.mode = %d\n", led_matrix_eeconfig.mode);
    dprintf("led_matrix_eeconfig.val = %d\n", led_matrix_eeconfig.val);
    dprintf("led_matrix_eeconfig.speed = %d\n", led_matrix_eeconfig.speed);
}

uint8_t g_last_led_hit[LED_HITS_TO_REMEMBER] = {255};
uint8_t g_last_led_count                     = 0;

__attribute__((weak)) uint8_t led_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) { return 0; }

uint8_t led_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i) {
    uint8_t led_count = led_matrix_map_row_column_to_led_kb(row, column, led_i);
    uint8_t led_index = g_led_config.matrix_co[row][column];
    if (led_index != NO_LED) {
        led_i[led_count] = led_index;
        led_count++;
    }
    return led_count;
}

void led_matrix_update_pwm_buffers(void) { led_matrix_driver.flush(); }

void led_matrix_set_value(int index, uint8_t value) {
#ifdef USE_CIE1931_CURVE
    led_matrix_driver.set_value(index, pgm_read_byte(&CIE1931_CURVE[value]));
#else
    led_matrix_driver.set_value(index, value);
#endif
}

void led_matrix_set_value_all(uint8_t value) {
#ifdef USE_CIE1931_CURVE
    led_matrix_driver.set_value_all(pgm_read_byte(&CIE1931_CURVE[value]));
#else
    led_matrix_driver.set_value_all(value);
#endif
}

void process_led_matrix(uint8_t row, uint8_t col, bool pressed) {
    if (pressed) {
        uint8_t led[8];
        uint8_t led_count = led_matrix_map_row_column_to_led(row, col, led);
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
        uint8_t led[8];
        uint8_t led_count = led_matrix_map_row_column_to_led(row, .col, led);
        for (uint8_t i = 0; i < led_count; i++) g_key_hit[led[i]] = 255;

        g_any_key_hit = 255;
#endif
    }
}

static void led_matrix_none(void) { led_matrix_set_value_all(0); }

// Uniform brightness
void led_matrix_uniform_brightness(void) { led_matrix_set_value_all(led_matrix_eeconfig.val); }

void led_matrix_custom(void) {}

void led_matrix_task(void) {
    if (!led_matrix_eeconfig.enable) {
        led_matrix_none();
        led_matrix_indicators();
        return;
    }

    g_tick++;

    if (g_any_key_hit < 0xFFFFFFFF) {
        g_any_key_hit++;
    }

    for (int led = 0; led < DRIVER_LED_TOTAL; led++) {
        if (g_key_hit[led] < 255) {
            if (g_key_hit[led] == 254) g_last_led_count = MAX(g_last_led_count - 1, 0);
            g_key_hit[led]++;
        }
    }

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool    suspend_backlight = 
#if LED_DISABLE_WHEN_USB_SUSPENDED == true
        g_suspend_state ||
#endif  // LED_DISABLE_WHEN_USB_SUSPENDED == true
#if LED_DISABLE_TIMEOUT > 0
        (g_any_key_hit > (uint32_t)LED_DISABLE_TIMEOUT) ||
#endif  // LED_DISABLE_TIMEOUT > 0
        false;

    uint8_t effect = suspend_backlight || !led_matrix_eeconfig.enable ? 0 : led_matrix_eeconfig.mode;

    // this gets ticked at 20 Hz.
    // each effect can opt to do calculations
    // and/or request PWM buffer updates.
    switch (effect) {
        case LED_MATRIX_NONE:
            led_matrix_none();
        case LED_MATRIX_UNIFORM_BRIGHTNESS:
            led_matrix_uniform_brightness();
            break;
        default:
            led_matrix_custom();
            break;
    }

    if (effect) {
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

void led_matrix_init(void) {
    led_matrix_driver.init();

    // Wait half a second for the driver to finish initializing
    wait_ms(500);

    // clear the key hits
    for (int led = 0; led < DRIVER_LED_TOTAL; led++) {
        g_key_hit[led] = 255;
    }

    if (!eeconfig_is_enabled()) {
        dprintf("led_matrix_init_drivers eeconfig is not enabled.\n");
        eeconfig_init();
        eeconfig_update_led_matrix_default();
    }

    eeconfig_read_led_matrix();
    if (!led_matrix_eeconfig.mode) {
        dprintf("led_matrix_init_drivers led_matrix_eeconfig.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_led_matrix_default();
    }
    eeconfig_debug_led_matrix();  // display current eeprom values
}

void led_matrix_set_suspend_state(bool state) {
    if (LED_DISABLE_WHEN_USB_SUSPENDED && state) {
        led_matrix_set_value_all(0);  // turn off all LEDs when suspending
    }
    g_suspend_state = state;
}

bool led_matrix_get_suspend_state(void) { return g_suspend_state; }

void led_matrix_toggle_eeprom_helper(bool write_to_eeprom) {
    led_matrix_eeconfig.enable ^= 1;
    if (write_to_eeprom) {
        eeconfig_update_led_matrix();
    }
    dprintf("led matrix toggle [%s]: led_matrix_eeconfig.enable = %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.enable);
}
void led_matrix_toggle_noeeprom(void) { led_matrix_toggle_eeprom_helper(false); }
void led_matrix_toggle(void) { led_matrix_toggle_eeprom_helper(true); }

void led_matrix_enable(void) {
    led_matrix_enable_noeeprom();
    eeconfig_update_led_matrix();
}

void led_matrix_enable_noeeprom(void) { led_matrix_eeconfig.enable = 1; }

void led_matrix_disable(void) {
    led_matrix_disable_noeeprom();
    eeconfig_update_led_matrix();
}

void led_matrix_disable_noeeprom(void) { led_matrix_eeconfig.enable = 0; }

uint8_t led_matrix_is_enabled(void) { return led_matrix_eeconfig.enable; }

void led_matrix_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
    if (!led_matrix_eeconfig.enable) {
        return;
    }
    if (mode < 1) {
        led_matrix_eeconfig.mode = 1;
    } else if (mode >= LED_MATRIX_EFFECT_MAX) {
        led_matrix_eeconfig.mode = LED_MATRIX_EFFECT_MAX - 1;
    } else {
        led_matrix_eeconfig.mode = mode;
    }
    if (write_to_eeprom) {
        eeconfig_update_led_matrix();
    }
    dprintf("led matrix mode [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.mode);
}
void led_matrix_mode_noeeprom(uint8_t mode) { led_matrix_mode_eeprom_helper(mode, false); }
void led_matrix_mode(uint8_t mode) { led_matrix_mode_eeprom_helper(mode, true); }

uint8_t led_matrix_get_mode(void) { return led_matrix_eeconfig.mode; }

void led_matrix_step_helper(bool write_to_eeprom) {
    uint8_t mode = led_matrix_eeconfig.mode + 1;
    led_matrix_mode_eeprom_helper((mode < LED_MATRIX_EFFECT_MAX) ? mode : 1, write_to_eeprom);
}
void led_matrix_step_noeeprom(void) { led_matrix_step_helper(false); }
void led_matrix_step(void) { led_matrix_step_helper(true); }

void led_matrix_step_reverse_helper(bool write_to_eeprom) {
    uint8_t mode = led_matrix_eeconfig.mode - 1;
    led_matrix_mode_eeprom_helper((mode < 1) ? LED_MATRIX_EFFECT_MAX - 1 : mode, write_to_eeprom);
}
void led_matrix_step_reverse_noeeprom(void) { led_matrix_step_reverse_helper(false); }
void led_matrix_step_reverse(void) { led_matrix_step_reverse_helper(true); }

void led_matrix_set_val_eeprom_helper(uint8_t val, bool write_to_eeprom) {
    if (!led_matrix_eeconfig.enable) {
        return;
    }
    led_matrix_eeconfig.val = (val > LED_MATRIX_MAXIMUM_BRIGHTNESS) ? LED_MATRIX_MAXIMUM_BRIGHTNESS : val;
    if (write_to_eeprom) {
        eeconfig_update_led_matrix();
    }
    dprintf("led matrix set val [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.val);
}
void led_matrix_set_val_noeeprom(uint8_t val) { led_matrix_set_val_eeprom_helper(val, false); }
void led_matrix_set_val(uint8_t val) { led_matrix_set_val_eeprom_helper(val, true); }

uint8_t led_matrix_get_val(void) { return led_matrix_eeconfig.val; }

void led_matrix_increase_val_helper(bool write_to_eeprom) { led_matrix_set_val_eeprom_helper(qadd8(led_matrix_eeconfig.val, LED_MATRIX_VAL_STEP), write_to_eeprom); }
void led_matrix_increase_val_noeeprom(void) { led_matrix_increase_val_helper(false); }
void led_matrix_increase_val(void) { led_matrix_increase_val_helper(true); }

void led_matrix_decrease_val_helper(bool write_to_eeprom) { led_matrix_set_val_eeprom_helper(qsub8(led_matrix_eeconfig.val, LED_MATRIX_VAL_STEP), write_to_eeprom); }
void led_matrix_decrease_val_noeeprom(void) { led_matrix_decrease_val_helper(false); }
void led_matrix_decrease_val(void) { led_matrix_decrease_val_helper(true); }

void led_matrix_set_speed_eeprom_helper(uint8_t speed, bool write_to_eeprom) {
    led_matrix_eeconfig.speed = speed;
    if (write_to_eeprom) {
        eeconfig_update_led_matrix();
    }
    dprintf("led matrix set speed [%s]: %u\n", (write_to_eeprom) ? "EEPROM" : "NOEEPROM", led_matrix_eeconfig.speed);
}
void led_matrix_set_speed_noeeprom(uint8_t speed) { led_matrix_set_speed_eeprom_helper(speed, false); }
void led_matrix_set_speed(uint8_t speed) { led_matrix_set_speed_eeprom_helper(speed, true); }

uint8_t led_matrix_get_speed(void) { return led_matrix_eeconfig.speed; }

void led_matrix_increase_speed_helper(bool write_to_eeprom) { led_matrix_set_speed_eeprom_helper(qadd8(led_matrix_eeconfig.speed, LED_MATRIX_SPD_STEP), write_to_eeprom); }
void led_matrix_increase_speed_noeeprom(void) { led_matrix_increase_speed_helper(false); }
void led_matrix_increase_speed(void) { led_matrix_increase_speed_helper(true); }

void led_matrix_decrease_speed_helper(bool write_to_eeprom) { led_matrix_set_speed_eeprom_helper(qsub8(led_matrix_eeconfig.speed, LED_MATRIX_SPD_STEP), write_to_eeprom); }
void led_matrix_decrease_speed_noeeprom(void) { led_matrix_decrease_speed_helper(false); }
void led_matrix_decrease_speed(void) { led_matrix_decrease_speed_helper(true); }
