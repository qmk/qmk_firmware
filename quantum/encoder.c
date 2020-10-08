/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include "encoder.h"
#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif

// for memcpy
#include <string.h>

#if !defined(ENCODER_RESOLUTIONS) && !defined(ENCODER_RESOLUTION)
#    define ENCODER_RESOLUTION 4
#endif

#if !(defined(ENCODERS_PAD_A) && defined(ENCODERS_PAD_B)) && !(!defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC)) && !(defined(SPLIT_KEYBOARD) && (defined(MATRIX_ENCODER_PINS_ABC) || defined(MATRIX_ENCODER_PINS_ABC_RIGHT)))
#    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B or MATRIX_ENCODER_PINS_ABC or SPLIT_KEYBOARD MATRIX_ENCODER_PINS_ABC and MATRIX_ENCODER_PINS_ABC_RIGHT"
#endif

#if (defined(ENCODERS_PAD_A) && defined(ENCODERS_PAD_B))
#    define ENCODER_BASIC
#endif

#if defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
#    define split_keyboard_both_encoder
#elif defined(SPLIT_KEYBOARD) && !defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
#    define split_keyboard_right_only_encoder
#endif

#if defined(ENCODER_BASIC)
#    define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[] = ENCODERS_PAD_B;
#    if defined(ENCODER_RESOLUTIONS)
static uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
#    endif
#endif

#ifndef ENCODER_DIRECTION_FLIP
#    define ENCODER_CLOCKWISE true
#    define ENCODER_COUNTER_CLOCKWISE false
#else
#    define ENCODER_CLOCKWISE false
#    define ENCODER_COUNTER_CLOCKWISE true
#endif
static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

#if defined(ENCODER_BASIC)

static uint8_t encoder_state[NUMBER_OF_ENCODERS]  = {0};
static int8_t  encoder_pulses[NUMBER_OF_ENCODERS] = {0};

#    ifdef SPLIT_KEYBOARD
// right half encoders come over as second set of encoders
static uint8_t encoder_value[NUMBER_OF_ENCODERS * 2] = {0};
// row offsets for each hand
static uint8_t thisHand, thatHand;
#    else
static uint8_t encoder_value[NUMBER_OF_ENCODERS] = {0};
#    endif

__attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}

__attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) { encoder_update_user(index, clockwise); }

void encoder_init(void) {
#    if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
    if (!isLeftHand) {
        const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
        const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
#        if defined(ENCODER_RESOLUTIONS_RIGHT)
        const uint8_t encoder_resolutions_right[] = ENCODER_RESOLUTIONS_RIGHT;
#        endif
        for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
            encoders_pad_a[i] = encoders_pad_a_right[i];
            encoders_pad_b[i] = encoders_pad_b_right[i];
#        if defined(ENCODER_RESOLUTIONS_RIGHT)
            encoder_resolutions[i] = encoder_resolutions_right[i];
#        endif
        }
    }
#    endif

    for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);

        encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
    }

#    ifdef SPLIT_KEYBOARD
    thisHand = isLeftHand ? 0 : NUMBER_OF_ENCODERS;
    thatHand = NUMBER_OF_ENCODERS - thisHand;
#    endif
}

static void encoder_update(int8_t index, uint8_t state) {
    uint8_t i = index;
#    ifdef ENCODER_RESOLUTIONS
    int8_t resolution = encoder_resolutions[i];
#    else
    int8_t resolution = ENCODER_RESOLUTION;
#    endif
#    ifdef SPLIT_KEYBOARD
    index += thisHand;
#    endif
    encoder_pulses[i] += encoder_LUT[state & 0xF];
    if (encoder_pulses[i] >= resolution) {
        encoder_value[index]++;
        encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
    }
    if (encoder_pulses[i] <= -resolution) {  // direction is arbitrary here, but this clockwise
        encoder_value[index]--;
        encoder_update_kb(index, ENCODER_CLOCKWISE);
    }
    encoder_pulses[i] %= resolution;
}

void encoder_read(void) {
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
        encoder_state[i] <<= 2;
        encoder_state[i] |= (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        encoder_update(i, encoder_state[i]);
    }
}

#    ifdef SPLIT_KEYBOARD
void encoder_state_raw(uint8_t* slave_state) { memcpy(slave_state, &encoder_value[thisHand], sizeof(uint8_t) * NUMBER_OF_ENCODERS); }

void encoder_update_raw(uint8_t* slave_state) {
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
        uint8_t index = i + thatHand;
        int8_t  delta = slave_state[i] - encoder_value[index];
        while (delta > 0) {
            delta--;
            encoder_value[index]++;
            encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
        }
        while (delta < 0) {
            delta++;
            encoder_value[index]--;
            encoder_update_kb(index, ENCODER_CLOCKWISE);
        }
    }
}
#    endif

#else  // ! defined(ENCODER_BASIC)

extern bool peek_matrix(uint8_t row_index, uint8_t col_index, bool read_raw);

typedef uint8_t encoder_wiring_t;
#    define OUTSIDE_KEYMATRIX (encoder_wiring_t)(~0)
#    define INSIDE_KEYMATRIX (encoder_wiring_t)(~1)
typedef struct {
    uint8_t          state;
    int8_t           pulse;
    uint8_t          value;
    encoder_wiring_t wiring;
    int8_t           pin_index_a;
    int8_t           pin_index_b;
    int8_t           pin_index_c;
} encoder_t;

// clang-format off
#if defined(split_keyboard_both_encoder)
    static pin_t matrix_encoders_pins_left[][3] = MATRIX_ENCODER_PINS_ABC;
    static pin_t matrix_encoders_pins_right[][3] = MATRIX_ENCODER_PINS_ABC_RIGHT;
    #define NUMBER_OF_ENCODERS_LEFT (sizeof(matrix_encoders_pins_left)/ sizeof(*matrix_encoders_pins_left))
    #define NUMBER_OF_ENCODERS_RIGHT (sizeof(matrix_encoders_pins_right)/ sizeof(*matrix_encoders_pins_right))
    static encoder_t encoders_left[NUMBER_OF_ENCODERS_LEFT] = {0};
    static encoder_t encoders_right[NUMBER_OF_ENCODERS_RIGHT] = {0};
    static pin_t row_pins_left[] = MATRIX_ROW_PINS;
    #if defined(MATRIX_ROW_PINS_RIGHT)
    static pin_t row_pins_right[] = MATRIX_ROW_PINS_RIGHT;
    #else
    static pin_t row_pins_right = MATRIX_ROW_PINS;
    #endif
    static pin_t col_pins_left[] = MATRIX_COL_PINS;
    #if defined(MATRIX_COL_PINS_RIGHT)
    static pin_t col_pins_right[] = MATRIX_COL_PINS_RIGHT;
    #else
    static pin_t col_pins_right[] = MATRIX_COL_PINS;
    #endif
#elif defined(split_keyboard_right_only_encoder)
    static pin_t matrix_encoders_pins_right[][3] = MATRIX_ENCODER_PINS_ABC_RIGHT;
    #define NUMBER_OF_ENCODERS_RIGHT (sizeof(matrix_encoders_pins_right)/ sizeof(*matrix_encoders_pins_right))
    #define NUMBER_OF_ENCODERS_LEFT 0
    static encoder_t encoders_right[NUMBER_OF_ENCODERS_RIGHT] = {0};
    #if defined(MATRIX_ROW_PINS_RIGHT)
    static pin_t row_pins_right[] = MATRIX_ROW_PINS_RIGHT;
    #else
    static pin_t row_pins_right = MATRIX_ROW_PINS;
    #endif
    #if defined(MATRIX_COL_PINS_RIGHT)
    static pin_t col_pins_right[] = MATRIX_COL_PINS_RIGHT;
    #else
    static pin_t col_pins_right[] = MATRIX_COL_PINS;
    #endif
#else  //non split keyboard or left only encoder
    static pin_t matrix_encoders_pins[][3] = MATRIX_ENCODER_PINS_ABC;
    #define NUMBER_OF_ENCODERS (sizeof(matrix_encoders_pins)/ sizeof(*matrix_encoders_pins))
    static encoder_t encoders[NUMBER_OF_ENCODERS] = {0};
    static pin_t row_pins[] = MATRIX_ROW_PINS;
    static pin_t col_pins[] = MATRIX_COL_PINS;
#endif
// clang-format on

#    if defined(ENCODER_RESOLUTIONS)
static uint8_t encoder_resolutions[]       = ENCODER_RESOLUTIONS;
#    endif
#    if defined(ENCODER_RESOLUTIONS_RIGHT)
static uint8_t encoder_resolutions_right[] = ENCODER_RESOLUTIONS_RIGHT;
#    endif

static inline void encoder_update_common(uint8_t state, encoder_t *current_encoder, uint8_t total_index, int8_t resolution) {
    current_encoder->pulse += encoder_LUT[state & 0xF];

    if (current_encoder->pulse >= resolution) {
        current_encoder->value++;
        encoder_update_kb(total_index, ENCODER_COUNTER_CLOCKWISE);
    }
    if (current_encoder->pulse <= -resolution) {
        current_encoder->value--;
        encoder_update_kb(total_index, ENCODER_CLOCKWISE);
    }
    current_encoder->pulse %= resolution;
}
static void encoder_update(int8_t index, uint8_t state) {
// clang-format off
    #if defined(split_keyboard_both_encoder)
        if(isLeftHand){
            #if defined(ENCODER_RESOLUTIONS)
                int8_t resolution = encoder_resolutions[index];
            #else
                int8_t resolution = ENCODER_RESOLUTION;
            #endif
            encoder_update_common(state,(encoder_t *)&encoders_left[index],index,resolution);
        }else{
            #if defined(ENCODER_RESOLUTIONS_RIGHT)
                int8_t resolution = encoder_resolutions_right[index];
            #else
                int8_t resolution = ENCODER_RESOLUTION;
            #endif
            encoder_update_common(state,(encoder_t *)&encoders_right[index],index + NUMBER_OF_ENCODERS_LEFT,resolution);
        }
    #elif defined(split_keyboard_right_only_encoder)
        #if defined(ENCODER_RESOLUTIONS_RIGHT)
            int8_t resolution = encoder_resolutions_right[index];
        #else
            int8_t resolution = ENCODER_RESOLUTION;
        #endif
        encoder_update_common(state,(encoder_t *)&encoders_right[index],index + NUMBER_OF_ENCODERS_LEFT,resolution);
    #else //non split keyboard or left only encoder
        #if defined(ENCODER_RESOLUTIONS)
            int8_t resolution = encoder_resolutions[index];
        #else
            int8_t resolution = ENCODER_RESOLUTION;
        #endif
        encoder_update_common(state,(encoder_t *)&encoders[index],index,resolution);
    #endif
    // clang-format on
}

static inline void encoder_read_all_common(pin_t *current_rows, pin_t *current_matrix, uint8_t encoder_count, encoder_t *current_encoders) {
    bool isFirstScan = true;
    for (int i = 0; i < encoder_count; i++) {
        if (current_encoders[i].wiring == INSIDE_KEYMATRIX) {
            // Since each pin of the encoder is in the key matrix, it references the scanned value
            current_encoders[i].state <<= 2;
            current_encoders[i].state |= (peek_matrix(current_encoders[i].pin_index_c, current_encoders[i].pin_index_a, true) << 0) | (peek_matrix(current_encoders[i].pin_index_c, current_encoders[i].pin_index_b, true) << 1);
        } else {
            // If C/Common is wired to GND, do not select Row and read Col.
            if (current_matrix[i * 3 + 2] != NO_PIN) {
                if (isFirstScan) {
                    // unselect rows(all)
                    for (int i = 0; i < MATRIX_ROWS; i++) {
                        setPinOutput(current_rows[i]);
                        writePinHigh(current_rows[i]);
                    }
                    isFirstScan = false;
                }
                // select row(C)
                writePinLow(current_matrix[i * 3 + 2]);
            }

            // select cols(A&B)
            setPinInputHigh(current_matrix[i * 3 + 0]);
            setPinInputHigh(current_matrix[i * 3 + 1]);
            matrix_io_delay();
            // read cols
            current_encoders[i].state <<= 2;
            current_encoders[i].state |= (readPin(current_matrix[i * 3 + 0]) << 0) | (readPin(current_matrix[i * 3 + 1]) << 1);

            if (current_matrix[i * 3 + 2] != NO_PIN) {
                // unselect row(C)
                writePinHigh(current_matrix[i * 3 + 2]);
            }
        }
        encoder_update(i, current_encoders[i].state);
    }
}

static void encoder_read_all(void) {
#    if defined(split_keyboard_both_encoder)
    if (isLeftHand) {
        encoder_read_all_common(row_pins_left, (pin_t *)matrix_encoders_pins_left, NUMBER_OF_ENCODERS_LEFT, encoders_left);
    } else {
        encoder_read_all_common(row_pins_right, (pin_t *)matrix_encoders_pins_right, NUMBER_OF_ENCODERS_RIGHT, encoders_right);
    }
#    elif defined(split_keyboard_right_only_encoder)
    encoder_read_all_common(row_pins_right, (pin_t *)matrix_encoders_pins_right, NUMBER_OF_ENCODERS_RIGHT, encoders_right);
#    else  // non split keyboard or left only encoder
    encoder_read_all_common(row_pins, (pin_t *)matrix_encoders_pins, NUMBER_OF_ENCODERS, encoders);
#    endif
}

static int8_t get_pin_index(pin_t *source, uint8_t count, pin_t value) {
    for (int i = 0; i < count; i++) {
        if (source[i] != NO_PIN && source[i] == value) {
            return i;
        }
    }
    return -1;
}
__attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}
__attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) { encoder_update_user(index, clockwise); }

static inline void encoder_init_common(pin_t *current_rows, pin_t *current_cols, pin_t *current_matrix, uint8_t encoder_count, encoder_t *current_encoders) {
    // First check if each encoder is inside or outside the key matrix
    // If each pin of the encoder is in the key matrix, there is no need to read the pins, so
    for (int i = 0; i < encoder_count; i++) {
        int8_t pin_index_a = get_pin_index(current_cols, MATRIX_COLS, current_matrix[i * 3 + 0]);
        int8_t pin_index_b = get_pin_index(current_cols, MATRIX_COLS, current_matrix[i * 3 + 1]);
        int8_t pin_index_c = get_pin_index(current_rows, MATRIX_ROWS, current_matrix[i * 3 + 2]);
        if ((pin_index_a != -1 && pin_index_b != -1 && pin_index_c != -1) || (pin_index_a != -1 && pin_index_b != -1 && current_matrix[i * 3 + 2] == NO_PIN)) {
            current_encoders[i].wiring = INSIDE_KEYMATRIX;
        } else {
            current_encoders[i].wiring = OUTSIDE_KEYMATRIX;
        }
        current_encoders[i].pin_index_a = pin_index_a;
        current_encoders[i].pin_index_b = pin_index_b;
        current_encoders[i].pin_index_c = pin_index_c;
    }
    encoder_read_all();
}
void encoder_init(void) {
#    if defined(split_keyboard_both_encoder)
    if (isLeftHand) {
        encoder_init_common(row_pins_left, col_pins_left, (pin_t *)matrix_encoders_pins_left, NUMBER_OF_ENCODERS_LEFT, encoders_left);
    } else {
        encoder_init_common(row_pins_right, col_pins_right, (pin_t *)matrix_encoders_pins_right, NUMBER_OF_ENCODERS_RIGHT, encoders_right);
    }
#    elif defined(split_keyboard_right_only_encoder)
    encoder_init_common(row_pins_right, col_pins_right, (pin_t *)matrix_encoders_pins_right, NUMBER_OF_ENCODERS_RIGHT, encoders_right);
#    else  // non split keyboard or left only encoder
    encoder_init_common(row_pins, col_pins, (pin_t *)matrix_encoders_pins, NUMBER_OF_ENCODERS, encoders);
#    endif
}

void encoder_read(void) { encoder_read_all(); }

#    if defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
void encoder_state_raw(uint8_t *slave_state) {
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS_RIGHT; i++) {
        slave_state[i] = encoders_right[i].value;
    }
}
void encoder_update_raw(uint8_t *slave_state) {
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS_RIGHT; i++) {
        uint8_t total_index = i + NUMBER_OF_ENCODERS_LEFT;
        int8_t  delta       = slave_state[i] - encoders_right[i].value;
        while (delta > 0) {
            delta--;
            encoders_right[i].value++;
            encoder_update_kb(total_index, ENCODER_COUNTER_CLOCKWISE);
        }
        while (delta < 0) {
            delta++;
            encoders_right[i].value--;
            encoder_update_kb(total_index, ENCODER_CLOCKWISE);
        }
    }
}
#    endif

#endif  // end of  #if defined(ENCODER_BASIC)
