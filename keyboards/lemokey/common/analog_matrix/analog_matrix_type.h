/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include <stdbool.h>

// Analog key mode
enum {
    AKM_GLOBAL = 0,
    // Basic mode
    AKM_REGULAR = 1,  // Static actuation point
    AKM_RAPID = 2,   // Rapid Trigger
    // Advance mode
    AKM_DKS,
    AKM_GAMEPAD,
    AKM_TOGGLE,
};

// Analog key state
enum {
    AKS_REGULAR_RELEASED,
    AKS_REGULAR_PRESSED,
    AKS_RAPID_RELEASED,
    AKS_RAPID_PRESSED,
    AKS_FULL_PRESSED,
};

#pragma pack(push)
#pragma pack(1)

typedef struct __attribute__((__packed__)){
    uint8_t actn_pt;
    uint8_t deactn_pt;
} activity_point_t;

typedef struct __attribute__((__packed__)){
    uint8_t  mode;                  // 1 byte
    uint8_t  state;                 // 1 byte
    uint8_t  travel;                // 1 byte
    uint8_t last_travel;            // for debug
    bool    debug;
    uint8_t r;
    uint8_t c;
    uint16_t value;                 // 2 bytes, value
    uint16_t last_val;              // 2 bytes, last value

    activity_point_t regular;       // 4 bytes, actuation point
    union {                         // 4 bytes
        activity_point_t rapid;
        activity_point_t full;
    };
    union {                         // 2 bytes
        uint8_t rpd_trig_sen;       // rapid trig sensitivity
        uint8_t okmc_idx;
        uint8_t js_axis;            // joystick x/y axis
        uint8_t hold;
    };
    uint8_t rpd_trig_sen_rls;
} analog_key_t;
// size of analog_key_t is 16 bytes

typedef struct __attribute__((__packed__)) {
    uint8_t actn_pt;                        // unit: 0.1mm
    uint8_t deactn_pt;                      // unit: 0.1mm
} traval_config_t;

typedef struct __attribute__((__packed__)) {
    uint8_t mode:2;                         // 2 bits, basic mode
    uint8_t act_pt:6;                       // 6 bits
    uint8_t rpd_trig_sen:6;                 // 6 bits rapid trig sensitivity, unit: 0.1mm
    uint8_t rpd_trig_sen_deact:6;           // 6 bits
    uint8_t adv_mode:4;                     // 4 bits, advance mode
    union {                                 // 1 byte, additional information of advance mode
        uint8_t adv_mode_data;
        uint8_t okmc_idx;                   //  okmc setting index
        uint8_t js_axis;                    //  joystick x/y axis
    };
} analog_key_config_t;
// size of analog_key_config_t is 4 bytes

typedef struct __attribute__((__packed__)) {
    uint8_t shallow_act:6;                  // unit: 0.1mm
    uint8_t shallow_deact:6;                // unit: 0.1mm
    uint8_t deep_act:6;                     // unit: 0.1mm
    uint8_t deep_deact:6;                   // unit: 0.1mm
} okmc_traval_config_t;
// size  = 3 bytes

typedef struct
{
    uint8_t shallow_act:4;
    uint8_t shallow_deact:4;
    uint8_t deep_act:4;
    uint8_t deep_deact:4;
} okmc_action_t;
// size  = 2 bytes

typedef struct __attribute__((__packed__)) {
    okmc_traval_config_t travel;             // 3
    uint16_t keycode[4];                     // 2*4
    okmc_action_t action[4];                 // 2*4
} okmc_config_t;
// size  = 19 bytes

typedef struct __attribute__((__packed__)) {
    uint8_t key_1_row:3;
    uint8_t key_1_col:5;
    uint8_t key_2_row:3;
    uint8_t key_2_col:5;
    uint8_t type;
} socd_config_t;
// size  = 3 bytes

typedef struct __attribute__((__packed__)) {
    uint8_t x;                              // 1
    uint8_t y;;                             // 1
} point_t;
// size  = 2 bytes

typedef struct __attribute__((__packed__)) {
    analog_key_config_t global;
    analog_key_config_t key_config[MATRIX_ROWS][MATRIX_COLS];
    okmc_config_t okmc[OKMC_COUNT];
    socd_config_t socd[SOCD_COUNT];
    uint8_t name[PROFILE_NAME_LEN];
    uint16_t crc16;
} analog_matrix_profile_t;

typedef struct __attribute__((__packed__)){
    uint16_t zero_travel:12;       // zero travel
    uint16_t full_travel:12;       // zero travel
} calibrated_value_t;

typedef struct __attribute__((__packed__)){
    bool calibrated:1;
    uint8_t pressed:1;
    uint8_t wait_For_release:1;
    uint8_t new_calib_value:1;
    uint8_t state:4;

    uint8_t confidence;
    calibrated_value_t value;
    uint32_t full_travel_time;
    uint8_t cycle;
} calibration_t;

#pragma pack(pop)



