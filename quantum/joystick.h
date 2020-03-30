#pragma once

#ifndef JOYSTICK_BUTTON_COUNT
#    define JOYSTICK_BUTTON_COUNT 8
#endif

#ifndef JOYSTICK_AXES_COUNT
#    define JOYSTICK_AXES_COUNT 4
#endif

#include <stdint.h>

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

enum joystick_status { JS_INITIALIZED = 1, JS_UPDATED = 2 };

typedef struct {
    uint8_t buttons[JOYSTICK_BUTTON_COUNT / 8 + 1];

    int16_t axes[JOYSTICK_AXES_COUNT];
    uint8_t status : 2;
} joystick_t;

extern joystick_t joystick_status;

// to be implemented in the hid protocol library
void send_joystick_packet(joystick_t* joystick);
