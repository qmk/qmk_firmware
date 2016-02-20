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

#include "protocol/triple_buffered_object.h"

#define GET_READ_INDEX() object->state & 3
#define GET_WRITE1_INDEX() (object->state >> 2) & 3
#define GET_WRITE2_INDEX() (object->state >> 4) & 3
#define GET_FREE_INDEX() (object->state >> 6) & 3

#define SET_READ_INDEX(i) object->state = ((object->state & ~3) | i)
#define SET_WRITE1_INDEX(i) object->state = ((object->state & ~(3 << 2)) | (i << 2))
#define SET_WRITE2_INDEX(i) object->state = ((object->state & ~(3 << 4)) | (i << 4))
#define SET_FREE_INDEX(i) object->state = ((object->state & ~(3 << 6)) | (i << 6))

void triple_buffer_init(triple_buffer_object_t* object) {
    object->state = 0;
    SET_WRITE1_INDEX(0);
    SET_WRITE2_INDEX(0);
    SET_READ_INDEX(1);
    SET_FREE_INDEX(2);
}

static void triple_buffer_begin_read(uint16_t object_size, triple_buffer_object_t* object) {
    uint8_t newest = GET_WRITE2_INDEX();
    uint8_t free_index = GET_READ_INDEX();
    SET_READ_INDEX(newest);
    SET_FREE_INDEX(free_index);
}

static void triple_buffer_actual_read(uint16_t object_size, triple_buffer_object_t* object, void* dst) {
    uint8_t read_index = GET_READ_INDEX();
    memcpy(dst, object->buffer + object_size*read_index, object_size);
}

static void triple_buffer_end_read(uint16_t object_size, triple_buffer_object_t* object) {
}

void triple_buffer_write(uint16_t object_size, triple_buffer_object_t* object, void* src) {
    uint8_t write1_index = GET_WRITE1_INDEX();
    uint8_t write2_index = GET_WRITE2_INDEX();
    uint8_t read_index = GET_READ_INDEX();
    uint8_t free_index = GET_FREE_INDEX();

    if (write2_index == read_index) {
        // We are reading from the other write index
        SET_WRITE1_INDEX(free_index);
        memcpy(object->buffer + object_size * free_index, src, object_size);
        SET_WRITE2_INDEX(free_index);
    }
    else {
        SET_WRITE1_INDEX(write2_index);
        memcpy(object->buffer + object_size * write2_index, src, object_size);
        SET_WRITE2_INDEX(write2_index);
    }
}

void triple_buffer_read(uint16_t object_size, triple_buffer_object_t* object, void* dst) {
    triple_buffer_begin_read(object_size, object);
    triple_buffer_actual_read(object_size, object, dst);
    triple_buffer_end_read(object_size, object);
}
