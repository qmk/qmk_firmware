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

#ifndef SERIAL_LINK_TRANSPORT_H
#define SERIAL_LINK_TRANSPORT_H

#include "protocol/triple_buffered_object.h"

#define NUM_SLAVES 8

typedef struct {
    uint16_t element_size;
    uint16_t buffer_size;
    uint8_t is_master;
    uint8_t buffer[] __attribute__((aligned(4)));
} remote_object_t;

typedef struct {
    uint16_t element_size;
    uint8_t destination;
    uint8_t buffer[] __attribute__((aligned(4)));
} local_object_t;

#define REMOTE_OBJECT_BUFFER(id, type) \
typedef struct { \
    triple_buffer_object_t object; \
    type buffer[3]; \
} remote_object_buffer_##id##_t;

#define MASTER_REMOTE_OBJECT(id, type) \
REMOTE_OBJECT_BUFFER(id, type) \
typedef struct { \
    remote_object_t object; \
    remote_object_buffer_##id##_t buffer; \
} master_remote_object_##id##_t; \
master_remote_object_##id##_t remote_object_##id = { \
     .object = { \
        .element_size = sizeof(type), \
        .buffer_size = sizeof(remote_object_buffer_##id##_t), \
        .is_master = true \
    }};

#define SLAVE_REMOTE_OBJECT(id, type) \
REMOTE_OBJECT_BUFFER(id, type) \
typedef struct { \
    remote_object_t object; \
    remote_object_buffer_##id##_t buffer[NUM_SLAVES];\
} slave_remote_object_##id##_t; \
slave_remote_object_##id##_t remote_object_##id = { \
     .object = { \
        .element_size = sizeof(type), \
        .buffer_size = sizeof(remote_object_buffer_##id##_t), \
        .is_master = true \
    }};

#define LOCAL_OBJECT(id, type) \
typedef struct { \
    uint32_t element_size; \
    uint8_t buffer[NUM_SLAVES][sizeof(type) + 16][3]; \
} remote_object_##id##_t; \
remote_object_##id##_t remote_object_##id = {.element_size = sizeof(type) + 16};

#define REMOTE_OBJECT(id) (remote_object_t*)&remote_object_##id


void init_transport(void);
void transport_recv_frame(uint8_t from, uint8_t* data, uint16_t size);
uint32_t transport_send_frame(uint8_t to, uint8_t* data, uint16_t size);

void transport_register_master_remote_object(uint8_t id, void* ptr, uint16_t size);
void transport_register_slave_remote_object(uint8_t id, void* ptr, uint16_t size);

#endif
