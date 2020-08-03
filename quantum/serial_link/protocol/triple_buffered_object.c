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

#include "serial_link/protocol/triple_buffered_object.h"
#include "serial_link/system/serial_link.h"
#include <stdbool.h>
#include <stddef.h>

#define GET_READ_INDEX() object->state & 3
#define GET_WRITE_INDEX() (object->state >> 2) & 3
#define GET_SHARED_INDEX() (object->state >> 4) & 3
#define GET_DATA_AVAILABLE() (object->state >> 6) & 1

#define SET_READ_INDEX(i) object->state = ((object->state & ~3) | i)
#define SET_WRITE_INDEX(i) object->state = ((object->state & ~(3 << 2)) | (i << 2))
#define SET_SHARED_INDEX(i) object->state = ((object->state & ~(3 << 4)) | (i << 4))
#define SET_DATA_AVAILABLE(i) object->state = ((object->state & ~(1 << 6)) | (i << 6))

void triple_buffer_init(triple_buffer_object_t* object) {
    object->state = 0;
    SET_WRITE_INDEX(0);
    SET_READ_INDEX(1);
    SET_SHARED_INDEX(2);
    SET_DATA_AVAILABLE(0);
}

void* triple_buffer_read_internal(uint16_t object_size, triple_buffer_object_t* object) {
    serial_link_lock();
    if (GET_DATA_AVAILABLE()) {
        uint8_t shared_index = GET_SHARED_INDEX();
        uint8_t read_index   = GET_READ_INDEX();
        SET_READ_INDEX(shared_index);
        SET_SHARED_INDEX(read_index);
        SET_DATA_AVAILABLE(false);
        serial_link_unlock();
        return object->buffer + object_size * shared_index;
    } else {
        serial_link_unlock();
        return NULL;
    }
}

void* triple_buffer_begin_write_internal(uint16_t object_size, triple_buffer_object_t* object) {
    uint8_t write_index = GET_WRITE_INDEX();
    return object->buffer + object_size * write_index;
}

void triple_buffer_end_write_internal(triple_buffer_object_t* object) {
    serial_link_lock();
    uint8_t shared_index = GET_SHARED_INDEX();
    uint8_t write_index  = GET_WRITE_INDEX();
    SET_SHARED_INDEX(write_index);
    SET_WRITE_INDEX(shared_index);
    SET_DATA_AVAILABLE(true);
    serial_link_unlock();
}
