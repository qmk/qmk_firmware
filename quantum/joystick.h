/* Copyright 2022
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

#include <stdint.h>
#include "gpio.h"

#ifndef JOYSTICK_BUTTON_COUNT
#    define JOYSTICK_BUTTON_COUNT 8
#elif JOYSTICK_BUTTON_COUNT > 32
#    error Joystick feature only supports up to 32 buttons
#endif

#ifndef JOYSTICK_AXES_COUNT
#    define JOYSTICK_AXES_COUNT 4
#elif JOYSTICK_AXES_COUNT > 6
#    error Joystick feature only supports up to 6 axes
#endif

#if JOYSTICK_AXES_COUNT == 0 && JOYSTICK_BUTTON_COUNT == 0
#    error Joystick feature requires at least one axis or button
#endif

#ifndef JOYSTICK_AXES_RESOLUTION
#    define JOYSTICK_AXES_RESOLUTION 8
#elif JOYSTICK_AXES_RESOLUTION < 8 || JOYSTICK_AXES_RESOLUTION > 16
#    error JOYSTICK_AXES_RESOLUTION must be between 8 and 16
#endif

#define JOYSTICK_RESOLUTION ((1L << (JOYSTICK_AXES_RESOLUTION - 1)) - 1)

// configure on input_pin of the joystick_axes array entry to JS_VIRTUAL_AXIS
// to prevent it from being read from the ADC. This allows outputing forged axis value.
//
#define JS_VIRTUAL_AXIS 0xFF

#define JOYSTICK_AXIS_VIRTUAL \
    { JS_VIRTUAL_AXIS, JS_VIRTUAL_AXIS, JS_VIRTUAL_AXIS, 0, 1023 }
#define JOYSTICK_AXIS_IN(INPUT_PIN, LOW, REST, HIGH) \
    { JS_VIRTUAL_AXIS, INPUT_PIN, JS_VIRTUAL_AXIS, LOW, REST, HIGH }
#define JOYSTICK_AXIS_IN_OUT(INPUT_PIN, OUTPUT_PIN, LOW, REST, HIGH) \
    { OUTPUT_PIN, INPUT_PIN, JS_VIRTUAL_AXIS, LOW, REST, HIGH }
#define JOYSTICK_AXIS_IN_OUT_GROUND(INPUT_PIN, OUTPUT_PIN, GROUND_PIN, LOW, REST, HIGH) \
    { OUTPUT_PIN, INPUT_PIN, GROUND_PIN, LOW, REST, HIGH }

typedef struct {
    pin_t output_pin;
    pin_t input_pin;
    pin_t ground_pin;

    // the AVR ADC offers 10 bit precision, with significant bits on the higher part
    uint16_t min_digit;
    uint16_t mid_digit;
    uint16_t max_digit;
} joystick_config_t;

extern joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT];

enum joystick_status {
    JS_INITIALIZED = 1,
    JS_UPDATED,
};

typedef struct {
    uint8_t buttons[(JOYSTICK_BUTTON_COUNT - 1) / 8 + 1];

    int16_t axes[JOYSTICK_AXES_COUNT];
    uint8_t status : 2;
} joystick_t;

extern joystick_t joystick_status;

void joystick_task(void);
void joystick_flush(void);

void register_joystick_button(uint8_t button);
void unregister_joystick_button(uint8_t button);

int16_t joystick_read_axis(uint8_t axis);
void    joystick_read_axes(void);
void    joystick_set_axis(uint8_t axis, int16_t value);

void host_joystick_send(joystick_t *joystick);
