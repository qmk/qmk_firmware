/* Copyright 2021 3araht
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

#include "bandominedoni.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        {     75,     46,     45,     44,     43,     42, NO_LED }, \
        {     47,     48,     49,     50,     51,     52,     53 }, \
        {     60,     59,     58,     57,     56,     55,     54 }, \
        {     61,     62,     63,     64,     65,     66,     67 }, \
        {     74,     73,     72,     71,     70,     69,     68 }, \
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, \
        {      7,      6,      4,      3,      2,      1,      5}, \
        {      8,      9,     10,     11,     12,     13,      0 }, \
        {     19,     18,     17,     16,     15,     14,     41 }, \
        {     20,     21,     22,     23,     24,     25,     40 }, \
        {     30,     29,     28,     27,     26,     39,     38 }, \
        {     31,     32,     33,     34,     35,     36,     37 }
    }, {
        { 145,  6 }, { 157,  5 }, { 153, 14 }, { 149, 22 }, { 145, 32 }, { 136, 35 }, { 139, 48 }, { 134, 61 },
        { 142, 60 }, { 148, 43 }, { 154, 29 }, { 158, 20 }, { 163, 12 }, { 168,  4 },
        { 178,  5 }, { 173, 12 }, { 168, 20 }, { 163, 28 }, { 157, 40 }, { 151, 55 },
        { 160, 52 }, { 166, 39 }, { 172, 28 }, { 177, 20 }, { 182, 13 }, { 188,  7 },
        { 192, 17 }, { 186, 23 }, { 181, 30 }, { 175, 39 }, { 169, 50 },
        { 178, 51 }, { 184, 41 }, { 190, 33 }, { 196, 27 },
        { 199, 37 }, { 193, 45 }, { 187, 53 },
        { 196, 56 }, { 202, 49 },
        { 205, 61 },
        { 202,  4 },
        {  84, 18 }, {  73, 13 }, {  62, 10 }, {  51,  8 }, {  39, 11 }, {  24, 22 },
        {  34, 19 }, {  45, 16 }, {  56, 16 }, {  66, 18 }, {  77, 22 }, {  87, 28 },
        {  92, 40 }, {  81, 32 }, {  71, 27 }, {  61, 24 }, {  51, 24 }, {  41, 24 }, {  30, 28 },
        {  24, 42 }, {  34, 37 }, {  44, 35 }, {  54, 34 }, {  64, 36 }, {  74, 38 }, {  84, 44 },
        {  87, 54 }, {  77, 49 }, {  67, 47 }, {  57, 45 }, {  47, 45 }, {  37, 48 }, {  27, 52 }, {  19, 56 },
    }, {
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4,
        4, 4, 4, 4,
        4, 4, 4,
        4, 4,
        4,
        4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4
    }
};
#endif

#if defined(SPLIT_HAND_MATRIX_GRID)
static uint8_t peek_matrix_intersection(pin_t out_pin, pin_t in_pin) {
    setPinInputHigh(in_pin);
    setPinOutput(out_pin);
    writePinLow(out_pin);
    // It's almost unnecessary, but wait until it's down to low, just in case.
    wait_us(1);
    uint8_t pin_state = readPin(in_pin);
    // Set out_pin to a setting that is less susceptible to noise.
    setPinInputHigh(out_pin);
    matrix_io_delay();  // Wait for the pull-up to go HIGH.
    return pin_state;
}
#endif

//  Overriding is_keyboard_left() in qmk_firmware/quantum/split_common/split_util.c to limit the handedness check only once.
//  reason: bandoMIneDonI has no space on right hand side to use "SPLIT_HAND_MATRIX_GRID".
//          However, It enables to decide the handedness by the HW by adding one condition: "not to press any keys (especially r30) dusing startup."
bool is_keyboard_left(void) {
static enum { UNKNOWN, LEFT, RIGHT } hand_side = UNKNOWN;

    // only check once, as this is called often
    if (hand_side == UNKNOWN) {
#if defined(SPLIT_HAND_PIN)
        // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
        setPinInput(SPLIT_HAND_PIN);
        hand_side = readPin(SPLIT_HAND_PIN) ? LEFT : RIGHT;
        return (hand_side == LEFT);
#elif defined(SPLIT_HAND_MATRIX_GRID)
#    ifdef SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
        hand_side = peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID) ? LEFT : RIGHT;
        return (hand_side == LEFT);
#    else
        hand_side = peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID) ? RIGHT : LEFT;
        return (hand_side == LEFT);
#    endif
#elif defined(EE_HANDS)
        hand_side = eeconfig_read_handedness() ? LEFT : RIGHT;
        return (hand_side == LEFT);
#elif defined(MASTER_RIGHT)
        hand_side = !is_keyboard_master() ? LEFT : RIGHT;
        return (hand_side == LEFT);
#endif
        hand_side = is_keyboard_master() ? LEFT : RIGHT;
        return (hand_side == LEFT);
    } else {
        return (hand_side == LEFT);
    }
}

#ifdef ENCODER_ENABLE
#   ifdef ENCODERS
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[ENCODERS]   = ENCODERS_CCW_KEY;
#   endif

void encoder_action_unregister(void) {
#   ifdef ENCODERS
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
#   endif
}

void encoder_action_register(uint8_t index, bool clockwise) {
#   ifdef ENCODERS
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
#       ifdef CONSOLE_ENABLE
    uprintf("encoder_action_register index = %u, clockwise = %u, row = %u, col = %u\n", index, clockwise, encoder_event.key.row, encoder_event.key.col);
#       endif
    action_exec(encoder_event);
#   endif
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    // don't return user actions, because they are in the keymap
    // encoder_update_user(index, clockwise);
    return true;
};

#endif
