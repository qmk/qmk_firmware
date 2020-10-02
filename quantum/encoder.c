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

#if !(defined(ENCODERS_PAD_A) && defined(ENCODERS_PAD_B)) \
    && !(!defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC)) \
    && !(defined(SPLIT_KEYBOARD) && (defined(MATRIX_ENCODER_PINS_ABC) || defined(MATRIX_ENCODER_PINS_ABC_RIGHT)))
#    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B or MATRIX_ENCODER_PINS_ABC or SPLIT_KEYBOARD MATRIX_ENCODER_PINS_ABC and MATRIX_ENCODER_PINS_ABC_RIGHT"
#endif

#if (defined(ENCODERS_PAD_A) && defined(ENCODERS_PAD_B))
    #define ENCODER_SIMPLE
#elif defined(SPLIT_KEYBOARD)
    #define ENCODER_MATRIX_SPLIT
#else
    #define ENCODER_MATRIX
#endif

#ifdef ENCODER_SIMPLE
    #define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
    static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
    static pin_t encoders_pad_b[] = ENCODERS_PAD_B;
    #ifdef ENCODER_RESOLUTIONS
    static uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
    #endif
#endif

#ifndef ENCODER_DIRECTION_FLIP
#    define ENCODER_CLOCKWISE true
#    define ENCODER_COUNTER_CLOCKWISE false
#else
#    define ENCODER_CLOCKWISE false
#    define ENCODER_COUNTER_CLOCKWISE true
#endif
static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

#ifdef ENCODER_SIMPLE
    static uint8_t encoder_state[NUMBER_OF_ENCODERS]  = {0};
    static int8_t  encoder_pulses[NUMBER_OF_ENCODERS] = {0};

    #ifdef SPLIT_KEYBOARD
    // right half encoders come over as second set of encoders
    static uint8_t encoder_value[NUMBER_OF_ENCODERS * 2] = {0};
    // row offsets for each hand
    static uint8_t thisHand, thatHand;
    #else
    static uint8_t encoder_value[NUMBER_OF_ENCODERS] = {0};
    #endif

    __attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}

    __attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) { encoder_update_user(index, clockwise); }

    void encoder_init(void) {
    #if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
        if (!isLeftHand) {
            const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
            const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
        #    if defined(ENCODER_RESOLUTIONS_RIGHT)
            const uint8_t encoder_resolutions_right[] = ENCODER_RESOLUTIONS_RIGHT;
        #    endif
            for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
                encoders_pad_a[i] = encoders_pad_a_right[i];
                encoders_pad_b[i] = encoders_pad_b_right[i];
        #    if defined(ENCODER_RESOLUTIONS_RIGHT)
                encoder_resolutions[i] = encoder_resolutions_right[i];
        #    endif
            }
        }
    #endif

        for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
            setPinInputHigh(encoders_pad_a[i]);
            setPinInputHigh(encoders_pad_b[i]);

            encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        }

    #ifdef SPLIT_KEYBOARD
        thisHand = isLeftHand ? 0 : NUMBER_OF_ENCODERS;
        thatHand = NUMBER_OF_ENCODERS - thisHand;
    #endif
    }

    static void encoder_update(int8_t index, uint8_t state) {
        uint8_t i = index;
    #ifdef ENCODER_RESOLUTIONS
        int8_t resolution = encoder_resolutions[i];
    #else
        int8_t resolution = ENCODER_RESOLUTION;
    #endif
    #ifdef SPLIT_KEYBOARD
        index += thisHand;
    #endif
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

    #ifdef SPLIT_KEYBOARD
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
    #endif
#else
    #if defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
        //split keyboard,both encoder
        static pin_t matrix_encoders_pins_left[][3] = MATRIX_ENCODER_PINS_ABC;
        static pin_t matrix_encoders_pins_right[][3] = MATRIX_ENCODER_PINS_ABC_RIGHT;
        #define NUMBER_OF_ENCODERS_LEFT (sizeof(matrix_encoders_pins_left)/ sizeof(*matrix_encoders_pins_left))
        #define NUMBER_OF_ENCODERS_RIGHT (sizeof(matrix_encoders_pins_right)/ sizeof(*matrix_encoders_pins_right))
        static uint8_t encoder_state_left[NUMBER_OF_ENCODERS_LEFT]  = {0};
        static int8_t  encoder_pulses_left[NUMBER_OF_ENCODERS_LEFT] = {0};
        static uint8_t encoder_value_left[NUMBER_OF_ENCODERS_LEFT] = {0};
        static uint8_t encoder_state_right[NUMBER_OF_ENCODERS_RIGHT]  = {0};
        static int8_t  encoder_pulses_right[NUMBER_OF_ENCODERS_RIGHT] = {0};
        static uint8_t encoder_value_right[NUMBER_OF_ENCODERS_RIGHT] = {0};
        static pin_t row_pins_left[] = MATRIX_ROW_PINS;
        #ifdef MATRIX_ROW_PINS_RIGHT
        static pin_t row_pins_right[] = MATRIX_ROW_PINS_RIGHT;
        #else
        static pin_t row_pins_right = MATRIX_ROW_PINS;
        #endif
        static pin_t col_pins_left[] = MATRIX_COL_PINS;
        #ifdef MATRIX_COL_PINS_RIGHT
        static pin_t col_pins_right[] = MATRIX_COL_PINS_RIGHT;
        #else
        static pin_t col_pins_right[] = MATRIX_COL_PINS;
        #endif
    #elif defined(SPLIT_KEYBOARD) && !defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
        //split keyboard,right only encoder
        static pin_t matrix_encoders_pins_right[][3] = MATRIX_ENCODER_PINS_ABC_RIGHT;
        #define NUMBER_OF_ENCODERS_RIGHT (sizeof(matrix_encoders_pins_right)/ sizeof(*matrix_encoders_pins_right))
        #define NUMBER_OF_ENCODERS_LEFT 0
        static uint8_t encoder_state_right[NUMBER_OF_ENCODERS_RIGHT]  = {0};
        static int8_t  encoder_pulses_right[NUMBER_OF_ENCODERS_RIGHT] = {0};
        static uint8_t encoder_value_right[NUMBER_OF_ENCODERS_RIGHT] = {0};
        #ifdef MATRIX_ROW_PINS_RIGHT
        static pin_t row_pins_right[] = MATRIX_ROW_PINS_RIGHT;
        #else
        static pin_t row_pins_right = MATRIX_ROW_PINS;
        #endif
        #ifdef MATRIX_COL_PINS_RIGHT
        static pin_t col_pins_right[] = MATRIX_COL_PINS_RIGHT;
        #else
        static pin_t col_pins_right[] = MATRIX_COL_PINS;
        #endif
    #else
        //non split keyboard or left only encoder
        static pin_t matrix_encoders_pins[][3] = MATRIX_ENCODER_PINS_ABC;
        #define NUMBER_OF_ENCODERS (sizeof(matrix_encoders_pins)/ sizeof(*matrix_encoders_pins))
        static uint8_t encoder_state[NUMBER_OF_ENCODERS]  = {0};
        static int8_t  encoder_pulses[NUMBER_OF_ENCODERS] = {0};
        static uint8_t encoder_value[NUMBER_OF_ENCODERS] = {0};
        static pin_t row_pins[] = MATRIX_ROW_PINS;
        static pin_t col_pins[] = MATRIX_COL_PINS;
    #endif

    #ifdef ENCODER_RESOLUTIONS
        static uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
    #endif
    #ifdef ENCODER_RESOLUTIONS_RIGHT
        static uint8_t encoder_resolutions_right[] = ENCODER_RESOLUTIONS_RIGHT;
    #endif

    static void encoder_update(int8_t index, uint8_t state) {
        #if defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
            //split keyboard,both encoder
            int8_t *current_encoder_pulses = isLeftHand ? encoder_pulses_left:encoder_pulses_right;
            uint8_t *current_encoder_value = isLeftHand ? encoder_value_left:encoder_value_right;
            uint8_t total_index = isLeftHand ? index : index + NUMBER_OF_ENCODERS_LEFT;
            #if defined(ENCODER_RESOLUTIONS) && defined(ENCODER_RESOLUTIONS_RIGHT )
            int8_t resolution = isLeftHand ? encoder_resolutions[index]:encoder_resolutions_right[index];
            #elif defined(ENCODER_RESOLUTIONS)
            int8_t resolution = isLeftHand ? encoder_resolutions[index]:ENCODER_RESOLUTION;
            #elif defined(ENCODER_RESOLUTIONS_RIGHT)
            int8_t resolution = isLeftHand ? ENCODER_RESOLUTION:encoder_resolutions_right[index];
            #else
            int8_t resolution = ENCODER_RESOLUTION;
            #endif
        #elif defined(SPLIT_KEYBOARD) && !defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
            //split keyboard,right only encoder
            int8_t *current_encoder_pulses = encoder_pulses_right;
            uint8_t *current_encoder_value = encoder_value_right;
            uint8_t total_index = index;
            #if defined(ENCODER_RESOLUTIONS_RIGHT)
                int8_t resolution = encoder_resolutions_right[index];
            #else
                int8_t resolution = ENCODER_RESOLUTION;
            #endif
        #else
            //non split keyboard or left only encoder
            int8_t *current_encoder_pulses = encoder_pulses;
            uint8_t *current_encoder_value = encoder_value;
            uint8_t total_index = index;
            #if defined(ENCODER_RESOLUTIONS)
                int8_t resolution = encoder_resolutions[index];
            #else
                int8_t resolution = ENCODER_RESOLUTION;
            #endif
        #endif

        current_encoder_pulses[index] += encoder_LUT[state & 0xF];

        if (current_encoder_pulses[index] >= resolution) {
            current_encoder_value[index]++;
            encoder_update_kb(total_index, ENCODER_COUNTER_CLOCKWISE);
        }
        if (current_encoder_pulses[index] <= -resolution) {
            current_encoder_value[index]--;
            encoder_update_kb(total_index, ENCODER_CLOCKWISE);
        }
        current_encoder_pulses[index] %= resolution;
    }
    static void encoder_read_all(void){
        #if defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
            //split keyboard,both encoder
            pin_t *current_rows = isLeftHand ? row_pins_left:row_pins_right;
            pin_t *current_cols = isLeftHand ? col_pins_left:col_pins_right;
            uint8_t *current_encoder_state = isLeftHand ? encoder_state_left:encoder_state_right;
            pin_t *current_matrix = isLeftHand ? (pin_t *)matrix_encoders_pins_left:(pin_t *)matrix_encoders_pins_right;
            uint8_t encoder_count = isLeftHand ? NUMBER_OF_ENCODERS_LEFT:NUMBER_OF_ENCODERS_RIGHT;
        #elif defined(SPLIT_KEYBOARD) && !defined(MATRIX_ENCODER_PINS_ABC) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
            //split keyboard,right only encoder
            pin_t *current_rows = row_pins_right;
            pin_t *current_cols = col_pins_right;
            uint8_t *current_encoder_state = encoder_state_right;
            pin_t *current_matrix = (pin_t *)matrix_encoders_pins_right;
            uint8_t encoder_count = NUMBER_OF_ENCODERS_RIGHT;
        #else
            //non split keyboard or left only encoder
            pin_t *current_rows = row_pins;
            pin_t *current_cols = col_pins;
            uint8_t *current_encoder_state = encoder_state;
            pin_t *current_matrix = (pin_t *)matrix_encoders_pins;
            uint8_t encoder_count = NUMBER_OF_ENCODERS;
        #endif
        //unselect rows(all)
        for (int i = 0; i < MATRIX_ROWS; i++) {
            setPinOutput(current_rows[i]);
            writePinHigh(current_rows[i]);
        }
        //unselect cols(all)
        for (int i = 0; i < MATRIX_COLS; i++) {
            setPinOutput(current_cols[i]);
            writePinLow(current_cols[i]);
        }

        for (int i = 0; i < encoder_count; i++) {
            //select row(C)
            writePinLow(current_matrix[i*3+2]);
            //select cols(A&B)
            setPinInputHigh(current_matrix[i*3+0]);
            setPinInputHigh(current_matrix[i*3+1]);
            matrix_io_delay();
            //read cols
            current_encoder_state[i] <<= 2;
            current_encoder_state[i] |= (readPin(current_matrix[i*3+0]) << 0) | (readPin(current_matrix[i*3+1]) << 1);
            encoder_update(i, current_encoder_state[i]);

            //unselect row(C)
            writePinHigh(current_matrix[i*3+2]);

            //unselect cols(A&B)
            setPinOutput(current_matrix[i*3+0]);
            writePinLow(current_matrix[i*3+0]);
            setPinOutput(current_matrix[i*3+1]);
            writePinLow(current_matrix[i*3+1]);
        }

        // Before scanning the key matrix, it must be returned to the initial state (all cols InputHigh)
        for (int i = 0; i < MATRIX_COLS; i++) {
            setPinInputHigh(current_cols[i]);
        }
    }

    __attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}
    __attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) { encoder_update_user(index, clockwise); }
    void encoder_init(void) {
        encoder_read_all();
    }
    void encoder_read(void) {
        encoder_read_all();
    }

    #if defined(SPLIT_KEYBOARD) && defined(MATRIX_ENCODER_PINS_ABC_RIGHT)
    void encoder_state_raw(uint8_t* slave_state) {
        memcpy(slave_state, &encoder_value_right[0], sizeof(uint8_t) * NUMBER_OF_ENCODERS_RIGHT);
    }
    void encoder_update_raw(uint8_t* slave_state) {
        for (uint8_t i = 0; i < NUMBER_OF_ENCODERS_RIGHT; i++) {
            uint8_t total_index = i + NUMBER_OF_ENCODERS_LEFT;
            int8_t  delta = slave_state[i] - encoder_value_right[i];
            while (delta > 0) {
                delta--;
                encoder_value_right[i]++;
                encoder_update_kb(total_index, ENCODER_COUNTER_CLOCKWISE);
            }
            while (delta < 0) {
                delta++;
                encoder_value_right[i]--;
                encoder_update_kb(total_index, ENCODER_CLOCKWISE);
            }
        }
    }
    #endif
#endif
