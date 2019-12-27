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

#include "serial_link/protocol/byte_stuffer.h"
#include "serial_link/protocol/frame_validator.h"
#include "serial_link/protocol/physical.h"
#include <stdbool.h>

// This implements the "Consistent overhead byte stuffing protocol"
// https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
// http://www.stuartcheshire.org/papers/COBSforToN.pdf

typedef struct byte_stuffer_state {
    uint16_t next_zero;
    uint16_t data_pos;
    bool     long_frame;
    uint8_t  data[MAX_FRAME_SIZE];
} byte_stuffer_state_t;

static byte_stuffer_state_t states[NUM_LINKS];

void init_byte_stuffer_state(byte_stuffer_state_t* state) {
    state->next_zero  = 0;
    state->data_pos   = 0;
    state->long_frame = false;
}

void init_byte_stuffer(void) {
    int i;
    for (i = 0; i < NUM_LINKS; i++) {
        init_byte_stuffer_state(&states[i]);
    }
}

void byte_stuffer_recv_byte(uint8_t link, uint8_t data) {
    byte_stuffer_state_t* state = &states[link];
    // Start of a new frame
    if (state->next_zero == 0) {
        state->next_zero  = data;
        state->long_frame = data == 0xFF;
        state->data_pos   = 0;
        return;
    }

    state->next_zero--;
    if (data == 0) {
        if (state->next_zero == 0) {
            // The frame is completed
            if (state->data_pos > 0) {
                validator_recv_frame(link, state->data, state->data_pos);
            }
        } else {
            // The frame is invalid, so reset
            init_byte_stuffer_state(state);
        }
    } else {
        if (state->data_pos == MAX_FRAME_SIZE) {
            // We exceeded our maximum frame size
            // therefore there's nothing else to do than reset to a new frame
            state->next_zero  = data;
            state->long_frame = data == 0xFF;
            state->data_pos   = 0;
        } else if (state->next_zero == 0) {
            if (state->long_frame) {
                // This is part of a long frame, so continue
                state->next_zero  = data;
                state->long_frame = data == 0xFF;
            } else {
                // Special case for zeroes
                state->next_zero               = data;
                state->data[state->data_pos++] = 0;
            }
        } else {
            state->data[state->data_pos++] = data;
        }
    }
}

static void send_block(uint8_t link, uint8_t* start, uint8_t* end, uint8_t num_non_zero) {
    send_data(link, &num_non_zero, 1);
    if (end > start) {
        send_data(link, start, end - start);
    }
}

void byte_stuffer_send_frame(uint8_t link, uint8_t* data, uint16_t size) {
    const uint8_t zero = 0;
    if (size > 0) {
        uint16_t num_non_zero = 1;
        uint8_t* end          = data + size;
        uint8_t* start        = data;
        while (data < end) {
            if (num_non_zero == 0xFF) {
                // There's more data after big non-zero block
                // So send it, and start a new block
                send_block(link, start, data, num_non_zero);
                start        = data;
                num_non_zero = 1;
            } else {
                if (*data == 0) {
                    // A zero encountered, so send the block
                    send_block(link, start, data, num_non_zero);
                    start        = data + 1;
                    num_non_zero = 1;
                } else {
                    num_non_zero++;
                }
                ++data;
            }
        }
        send_block(link, start, data, num_non_zero);
        send_data(link, &zero, 1);
    }
}
