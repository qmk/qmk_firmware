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

#pragma once

#include "serial_link/protocol/triple_buffered_object.h"
#include "serial_link/system/serial_link.h"

#define NUM_SLAVES 8
#define LOCAL_OBJECT_EXTRA 16

// master -> slave = 1 local(target all), 1 remote object
// slave -> master = 1 local(target 0), multiple remote objects
// master -> single slave (multiple local, target id), 1 remote object
typedef enum {
    MASTER_TO_ALL_SLAVES,
    MASTER_TO_SINGLE_SLAVE,
    SLAVE_TO_MASTER,
} remote_object_type;

typedef struct {
    remote_object_type object_type;
    uint16_t           object_size;
    uint8_t            buffer[] __attribute__((aligned(4)));
} remote_object_t;

#define REMOTE_OBJECT_SIZE(objectsize) (sizeof(triple_buffer_object_t) + objectsize * 3)
#define LOCAL_OBJECT_SIZE(objectsize) (sizeof(triple_buffer_object_t) + (objectsize + LOCAL_OBJECT_EXTRA) * 3)

#define REMOTE_OBJECT_HELPER(name, type, num_local, num_remote)                                                              \
    typedef struct {                                                                                                         \
        remote_object_t object;                                                                                              \
        uint8_t         buffer[num_remote * REMOTE_OBJECT_SIZE(sizeof(type)) + num_local * LOCAL_OBJECT_SIZE(sizeof(type))]; \
    } remote_object_##name##_t;

#define MASTER_TO_ALL_SLAVES_OBJECT(name, type)                                                                     \
    REMOTE_OBJECT_HELPER(name, type, 1, 1)                                                                          \
    remote_object_##name##_t remote_object_##name = {.object = {                                                    \
                                                         .object_type = MASTER_TO_ALL_SLAVES,                       \
                                                         .object_size = sizeof(type),                               \
                                                     }};                                                            \
    type*                    begin_write_##name(void) {                                                             \
        remote_object_t*        obj = (remote_object_t*)&remote_object_##name;                   \
        triple_buffer_object_t* tb  = (triple_buffer_object_t*)obj->buffer;                      \
        return (type*)triple_buffer_begin_write_internal(sizeof(type) + LOCAL_OBJECT_EXTRA, tb); \
    }                                                                                                               \
    void end_write_##name(void) {                                                                                   \
        remote_object_t*        obj = (remote_object_t*)&remote_object_##name;                                      \
        triple_buffer_object_t* tb  = (triple_buffer_object_t*)obj->buffer;                                         \
        triple_buffer_end_write_internal(tb);                                                                       \
        signal_data_written();                                                                                      \
    }                                                                                                               \
    type* read_##name(void) {                                                                                       \
        remote_object_t*        obj   = (remote_object_t*)&remote_object_##name;                                    \
        uint8_t*                start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);                          \
        triple_buffer_object_t* tb    = (triple_buffer_object_t*)start;                                             \
        return (type*)triple_buffer_read_internal(obj->object_size, tb);                                            \
    }

#define MASTER_TO_SINGLE_SLAVE_OBJECT(name, type)                                                                   \
    REMOTE_OBJECT_HELPER(name, type, NUM_SLAVES, 1)                                                                 \
    remote_object_##name##_t remote_object_##name = {.object = {                                                    \
                                                         .object_type = MASTER_TO_SINGLE_SLAVE,                     \
                                                         .object_size = sizeof(type),                               \
                                                     }};                                                            \
    type*                    begin_write_##name(uint8_t slave) {                                                    \
        remote_object_t* obj   = (remote_object_t*)&remote_object_##name;                        \
        uint8_t*         start = obj->buffer;                                                    \
        start += slave * LOCAL_OBJECT_SIZE(obj->object_size);                                    \
        triple_buffer_object_t* tb = (triple_buffer_object_t*)start;                             \
        return (type*)triple_buffer_begin_write_internal(sizeof(type) + LOCAL_OBJECT_EXTRA, tb); \
    }                                                                                                               \
    void end_write_##name(uint8_t slave) {                                                                          \
        remote_object_t* obj   = (remote_object_t*)&remote_object_##name;                                           \
        uint8_t*         start = obj->buffer;                                                                       \
        start += slave * LOCAL_OBJECT_SIZE(obj->object_size);                                                       \
        triple_buffer_object_t* tb = (triple_buffer_object_t*)start;                                                \
        triple_buffer_end_write_internal(tb);                                                                       \
        signal_data_written();                                                                                      \
    }                                                                                                               \
    type* read_##name() {                                                                                           \
        remote_object_t*        obj   = (remote_object_t*)&remote_object_##name;                                    \
        uint8_t*                start = obj->buffer + NUM_SLAVES * LOCAL_OBJECT_SIZE(obj->object_size);             \
        triple_buffer_object_t* tb    = (triple_buffer_object_t*)start;                                             \
        return (type*)triple_buffer_read_internal(obj->object_size, tb);                                            \
    }

#define SLAVE_TO_MASTER_OBJECT(name, type)                                                                          \
    REMOTE_OBJECT_HELPER(name, type, 1, NUM_SLAVES)                                                                 \
    remote_object_##name##_t remote_object_##name = {.object = {                                                    \
                                                         .object_type = SLAVE_TO_MASTER,                            \
                                                         .object_size = sizeof(type),                               \
                                                     }};                                                            \
    type*                    begin_write_##name(void) {                                                             \
        remote_object_t*        obj = (remote_object_t*)&remote_object_##name;                   \
        triple_buffer_object_t* tb  = (triple_buffer_object_t*)obj->buffer;                      \
        return (type*)triple_buffer_begin_write_internal(sizeof(type) + LOCAL_OBJECT_EXTRA, tb); \
    }                                                                                                               \
    void end_write_##name(void) {                                                                                   \
        remote_object_t*        obj = (remote_object_t*)&remote_object_##name;                                      \
        triple_buffer_object_t* tb  = (triple_buffer_object_t*)obj->buffer;                                         \
        triple_buffer_end_write_internal(tb);                                                                       \
        signal_data_written();                                                                                      \
    }                                                                                                               \
    type* read_##name(uint8_t slave) {                                                                              \
        remote_object_t* obj   = (remote_object_t*)&remote_object_##name;                                           \
        uint8_t*         start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);                                 \
        start += slave * REMOTE_OBJECT_SIZE(obj->object_size);                                                      \
        triple_buffer_object_t* tb = (triple_buffer_object_t*)start;                                                \
        return (type*)triple_buffer_read_internal(obj->object_size, tb);                                            \
    }

#define REMOTE_OBJECT(name) (remote_object_t*)&remote_object_##name

void add_remote_objects(remote_object_t** remote_objects, uint32_t num_remote_objects);
void reinitialize_serial_link_transport(void);
void transport_recv_frame(uint8_t from, uint8_t* data, uint16_t size);
void update_transport(void);
