// this is a single reader [maybe multiple writer?] byte queue
// Copyright 2008 Alex Norman
// writen by Alex Norman
//
// This file is part of avr-bytequeue.
//
// avr-bytequeue is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
// avr-bytequeue is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with avr-bytequeue.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>

typedef uint8_t byteQueueIndex_t;

typedef struct {
    byteQueueIndex_t start;
    byteQueueIndex_t end;
    byteQueueIndex_t length;
    uint8_t*         data;
} byteQueue_t;

// you must have a queue, an array of data which the queue will use, and the length of that array
void bytequeue_init(byteQueue_t* queue, uint8_t* dataArray, byteQueueIndex_t arrayLen);

// add an item to the queue, returns false if the queue is full
bool bytequeue_enqueue(byteQueue_t* queue, uint8_t item);

// get the length of the queue
byteQueueIndex_t bytequeue_length(byteQueue_t* queue);

// this grabs data at the index given [starting at queue->start]
uint8_t bytequeue_get(byteQueue_t* queue, byteQueueIndex_t index);

// update the index in the queue to reflect data that has been dealt with
void bytequeue_remove(byteQueue_t* queue, byteQueueIndex_t numToRemove);

#ifdef __cplusplus
}
#endif
