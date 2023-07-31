#pragma once

#include "quantum.h"

extern pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS];

enum via_dynamic_actuation {
    id_mode = 1,
    id_actuation_point,
    id_press_sensitivity,
    id_release_sensitivity,
    id_press_hysteresis,
    id_release_hysteresis,
};

enum analog_key_modes {
    dynamic_actuation = 0,
    continuous_dynamic_actuation,
    static_actuation,
    flashing
};

//struct to save configs
typedef struct {
    uint8_t mode: 8;
    uint16_t actuation_point: 8;
    uint8_t press_sensitivity: 8;
    uint8_t release_sensitivity: 8;
    uint8_t press_hysteresis: 8;
    uint8_t release_hysteresis: 8;
} via_config; // 48 bits
extern via_config g_config;

typedef struct {
    // For individual analog key states
    uint8_t value;
    uint8_t extremum;
    int16_t offset;
    bool continuous_rapid_trigger;
} key_t;
extern key_t keys[MATRIX_ROWS][MATRIX_COLS];

// function declaration
void via_config_set_value(uint8_t *data);

void via_config_get_value(uint8_t *data);