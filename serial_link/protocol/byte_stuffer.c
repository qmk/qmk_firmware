/*
The MIT License (MIT)

Copyright (c) 2016 Fred Sundvik

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "protocol/byte_stuffer.h"
#include "protocol/frame_validator.h"
#include <stdio.h>

// This implements the "Consistent overhead byte stuffing protocol"
// https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
// http://www.stuartcheshire.org/papers/COBSforToN.pdf

#define MAX_FRAME_SIZE 1024

typedef struct byte_stuffer_state {
    uint16_t next_zero;
    uint16_t data_pos;
    bool long_frame;
    uint8_t data[MAX_FRAME_SIZE];
}byte_stuffer_state_t;

void init_byte_stuffer_state(byte_stuffer_state_t* state) {
    state->next_zero = 0;
    state->data_pos = 0;
    state->long_frame = false;
}

static void start_frame(byte_stuffer_state_t* state, uint8_t data) {
}

void recv_byte(byte_stuffer_state_t* state, uint8_t data) {
    // Start of a new frame
    if (state->next_zero == 0) {
        state->next_zero = data;
        state->long_frame = data == 0xFF;
        state->data_pos = 0;
        return;
    }

    state->next_zero--;
    if (data == 0) {
        if (state->next_zero == 0) {
            // The frame is completed
            recv_frame(state->data, state->data_pos);
        }
        else {
            // The frame is invalid, so reset
            init_byte_stuffer_state(state);
        }
    }
    else {
        if (state->next_zero == 0) {
            if (state->long_frame) {
                state->next_zero = data;
                state->long_frame = data == 0xFF;
            }
            else {
                // Special case for zeroes
                state->next_zero = data;
                state->data[state->data_pos++] = 0;
            }
        }
        else {
            state->data[state->data_pos++] = data;
        }
    }
}
