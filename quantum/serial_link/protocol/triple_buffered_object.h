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

#ifndef SERIAL_LINK_TRIPLE_BUFFERED_OBJECT_H
#define SERIAL_LINK_TRIPLE_BUFFERED_OBJECT_H

#include <stdint.h>

typedef struct {
    uint8_t state;
    uint8_t buffer[] __attribute__((aligned(4)));
}triple_buffer_object_t;

void triple_buffer_init(triple_buffer_object_t* object);

#define triple_buffer_begin_write(object) \
    (typeof(*object.buffer[0])*)triple_buffer_begin_write_internal(sizeof(*object.buffer[0]), (triple_buffer_object_t*)object)

#define triple_buffer_end_write(object) \
    triple_buffer_end_write_internal((triple_buffer_object_t*)object)

#define triple_buffer_read(object) \
    (typeof(*object.buffer[0])*)triple_buffer_read_internal(sizeof(*object.buffer[0]), (triple_buffer_object_t*)object)

void* triple_buffer_begin_write_internal(uint16_t object_size, triple_buffer_object_t* object);
void triple_buffer_end_write_internal(triple_buffer_object_t* object);
void* triple_buffer_read_internal(uint16_t object_size, triple_buffer_object_t* object);


#endif
