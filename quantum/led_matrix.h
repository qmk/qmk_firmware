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

#pragma once

#ifndef BACKLIGHT_ENABLE
#    error You must define BACKLIGHT_ENABLE with LED_MATRIX_ENABLE
#endif

typedef struct Point {
    uint8_t x;
    uint8_t y;
} __attribute__((packed)) Point;

typedef struct led_matrix {
    union {
        uint8_t raw;
        struct {
            uint8_t row : 4;  // 16 max
            uint8_t col : 4;  // 16 max
        };
    } matrix_co;
    Point   point;
    uint8_t modifier : 1;
} __attribute__((packed)) led_matrix;

extern const led_matrix g_leds[LED_DRIVER_LED_COUNT];

typedef struct {
    uint8_t index;
    uint8_t value;
} led_indicator;

typedef union {
    uint32_t raw;
    struct {
        bool    enable : 1;
        uint8_t mode : 6;
        uint8_t hue : 8;  // Unused by led_matrix
        uint8_t sat : 8;  // Unused by led_matrix
        uint8_t val : 8;
        uint8_t speed : 8;  // EECONFIG needs to be increased to support this
    };
} led_config_t;

enum led_matrix_effects {
    LED_MATRIX_UNIFORM_BRIGHTNESS = 1,
    // All new effects go above this line
    LED_MATRIX_EFFECT_MAX
};

void led_matrix_set_index_value(int index, uint8_t value);
void led_matrix_set_index_value_all(uint8_t value);

// This runs after another backlight effect and replaces
// colors already set
void led_matrix_indicators(void);
void led_matrix_indicators_kb(void);
void led_matrix_indicators_user(void);

void led_matrix_init(void);
void led_matrix_setup_drivers(void);

void led_matrix_set_suspend_state(bool state);
void led_matrix_set_indicator_state(uint8_t state);

void led_matrix_task(void);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void led_matrix_update_pwm_buffers(void);

bool process_led_matrix(uint16_t keycode, keyrecord_t *record);

uint32_t led_matrix_get_tick(void);

void    led_matrix_toggle(void);
void    led_matrix_enable(void);
void    led_matrix_enable_noeeprom(void);
void    led_matrix_disable(void);
void    led_matrix_disable_noeeprom(void);
void    led_matrix_step(void);
void    led_matrix_step_reverse(void);
void    led_matrix_increase_val(void);
void    led_matrix_decrease_val(void);
void    led_matrix_increase_speed(void);
void    led_matrix_decrease_speed(void);
void    led_matrix_mode(uint8_t mode, bool eeprom_write);
void    led_matrix_mode_noeeprom(uint8_t mode);
uint8_t led_matrix_get_mode(void);
void    led_matrix_set_value(uint8_t mode);
void    led_matrix_set_value_noeeprom(uint8_t mode);

typedef struct {
    /* Perform any initialisation required for the other driver functions to work. */
    void (*init)(void);

    /* Set the brightness of a single LED in the buffer. */
    void (*set_value)(int index, uint8_t value);
    /* Set the brightness of all LEDS on the keyboard in the buffer. */
    void (*set_value_all)(uint8_t value);
    /* Flush any buffered changes to the hardware. */
    void (*flush)(void);
} led_matrix_driver_t;

extern const led_matrix_driver_t led_matrix_driver;
