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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "util.h"

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef ENCODERS_PAD_A
#    define ENCODER_A_PINS ENCODERS_PAD_A
#endif
#ifdef ENCODERS_PAD_B
#    define ENCODER_B_PINS ENCODERS_PAD_B
#endif
#ifdef ENCODERS_PAD_A_RIGHT
#    define ENCODER_A_PINS_RIGHT ENCODERS_PAD_A_RIGHT
#endif
#ifdef ENCODERS_PAD_B_RIGHT
#    define ENCODER_B_PINS_RIGHT ENCODERS_PAD_B_RIGHT
#endif
// ========

#ifdef ENCODER_ENABLE

__attribute__((weak)) bool should_process_encoder(void);

void encoder_init(void);
bool encoder_task(void);
bool encoder_queue_event(uint8_t index, bool clockwise);
bool encoder_dequeue_event(uint8_t *index, bool *clockwise);

bool encoder_update_kb(uint8_t index, bool clockwise);
bool encoder_update_user(uint8_t index, bool clockwise);

#    ifdef SPLIT_KEYBOARD

#        if defined(ENCODER_A_PINS_RIGHT)
#            ifndef NUM_ENCODERS_LEFT
#                define NUM_ENCODERS_LEFT ARRAY_SIZE(((pin_t[])ENCODER_A_PINS))
#            endif
#            ifndef NUM_ENCODERS_RIGHT
#                define NUM_ENCODERS_RIGHT ARRAY_SIZE(((pin_t[])ENCODER_A_PINS_RIGHT))
#            endif
#        else
#            ifndef NUM_ENCODERS_LEFT
#                define NUM_ENCODERS_LEFT ARRAY_SIZE(((pin_t[])ENCODER_A_PINS))
#            endif
#            ifndef NUM_ENCODERS_RIGHT
#                define NUM_ENCODERS_RIGHT NUM_ENCODERS_LEFT
#            endif
#        endif
#        ifndef NUM_ENCODERS
#            define NUM_ENCODERS (NUM_ENCODERS_LEFT + NUM_ENCODERS_RIGHT)
#        endif

#    else // SPLIT_KEYBOARD

#        ifndef NUM_ENCODERS
#            define NUM_ENCODERS ARRAY_SIZE(((pin_t[])ENCODER_A_PINS))
#        endif
#        define NUM_ENCODERS_LEFT NUM_ENCODERS
#        define NUM_ENCODERS_RIGHT 0

#    endif // SPLIT_KEYBOARD

#    define NUM_ENCODERS_MAX_PER_SIDE MAX(NUM_ENCODERS_LEFT, NUM_ENCODERS_RIGHT)

#    ifndef MAX_QUEUED_ENCODER_EVENTS
#        define MAX_QUEUED_ENCODER_EVENTS MAX(4, ((NUM_ENCODERS_MAX_PER_SIDE) + 1))
#    endif // MAX_QUEUED_ENCODER_EVENTS

typedef struct encoder_event_t {
    uint8_t index : 7;
    uint8_t clockwise : 1;
} encoder_event_t;

typedef struct encoder_events_t {
    uint8_t         enqueued;
    uint8_t         dequeued;
    uint8_t         head;
    uint8_t         tail;
    encoder_event_t queue[MAX_QUEUED_ENCODER_EVENTS];
} encoder_events_t;

// Get the current queued events
void encoder_retrieve_events(encoder_events_t *events);

// Encoder event queue management
bool encoder_queue_event_advanced(encoder_events_t *events, uint8_t index, bool clockwise);
bool encoder_dequeue_event_advanced(encoder_events_t *events, uint8_t *index, bool *clockwise);

// Reset the queue to be empty
void encoder_signal_queue_drain(void);

#    ifdef ENCODER_MAP_ENABLE
#        define NUM_DIRECTIONS 2
#        define ENCODER_CCW_CW(ccw, cw) \
            { (cw), (ccw) }
extern const uint16_t encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS];
#    endif // ENCODER_MAP_ENABLE

// "Custom encoder lite" support
void encoder_driver_init(void);
void encoder_driver_task(void);

#endif // ENCODER_ENABLE
