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

#include "serial_link/protocol/transport.h"
#include "serial_link/protocol/frame_router.h"
#include "serial_link/protocol/triple_buffered_object.h"
#include <string.h>

#define MAX_REMOTE_OBJECTS 16
static remote_object_t* remote_objects[MAX_REMOTE_OBJECTS];
static uint32_t num_remote_objects = 0;

void reinitialize_serial_link_transport(void) {
    num_remote_objects = 0;
}

void add_remote_objects(remote_object_t** _remote_objects, uint32_t _num_remote_objects) {
    unsigned int i;
    for(i=0;i<_num_remote_objects;i++) {
        remote_object_t* obj = _remote_objects[i];
        remote_objects[num_remote_objects++] = obj;
        if (obj->object_type == MASTER_TO_ALL_SLAVES) {
            triple_buffer_object_t* tb = (triple_buffer_object_t*)obj->buffer;
            triple_buffer_init(tb);
            uint8_t* start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
            tb = (triple_buffer_object_t*)start;
            triple_buffer_init(tb);
        }
        else if(obj->object_type == MASTER_TO_SINGLE_SLAVE) {
            uint8_t* start = obj->buffer;
            unsigned int j;
            for (j=0;j<NUM_SLAVES;j++) {
                triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
                triple_buffer_init(tb);
                start += LOCAL_OBJECT_SIZE(obj->object_size);
            }
            triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
            triple_buffer_init(tb);
        }
        else {
            uint8_t* start = obj->buffer;
            triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
            triple_buffer_init(tb);
            start += LOCAL_OBJECT_SIZE(obj->object_size);
            unsigned int j;
            for (j=0;j<NUM_SLAVES;j++) {
                tb = (triple_buffer_object_t*)start;
                triple_buffer_init(tb);
                start += REMOTE_OBJECT_SIZE(obj->object_size);
            }
        }
    }
}

void transport_recv_frame(uint8_t from, uint8_t* data, uint16_t size) {
    uint8_t id = data[size-1];
    if (id < num_remote_objects) {
        remote_object_t* obj = remote_objects[id];
        if (obj->object_size == size - 1) {
            uint8_t* start;
            if (obj->object_type == MASTER_TO_ALL_SLAVES) {
                start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
            }
            else if(obj->object_type == SLAVE_TO_MASTER) {
                start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
                start += (from - 1) * REMOTE_OBJECT_SIZE(obj->object_size);
            }
            else {
                start = obj->buffer + NUM_SLAVES * LOCAL_OBJECT_SIZE(obj->object_size);
            }
            triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
            void* ptr = triple_buffer_begin_write_internal(obj->object_size, tb);
            memcpy(ptr, data, size - 1);
            triple_buffer_end_write_internal(tb);
        }
    }
}

void update_transport(void) {
    unsigned int i;
    for(i=0;i<num_remote_objects;i++) {
        remote_object_t* obj = remote_objects[i];
        if (obj->object_type == MASTER_TO_ALL_SLAVES || obj->object_type == SLAVE_TO_MASTER) {
            triple_buffer_object_t* tb = (triple_buffer_object_t*)obj->buffer;
            uint8_t* ptr = (uint8_t*)triple_buffer_read_internal(obj->object_size + LOCAL_OBJECT_EXTRA, tb);
            if (ptr) {
                ptr[obj->object_size] = i;
                uint8_t dest = obj->object_type == MASTER_TO_ALL_SLAVES ? 0xFF : 0;
                router_send_frame(dest, ptr, obj->object_size + 1);
            }
        }
        else {
            uint8_t* start = obj->buffer;
            unsigned int j;
            for (j=0;j<NUM_SLAVES;j++) {
                triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
                uint8_t* ptr = (uint8_t*)triple_buffer_read_internal(obj->object_size + LOCAL_OBJECT_EXTRA, tb);
                if (ptr) {
                    ptr[obj->object_size] = i;
                    uint8_t dest = j + 1;
                    router_send_frame(dest, ptr, obj->object_size + 1);
                }
                start += LOCAL_OBJECT_SIZE(obj->object_size);
            }
        }
    }
}
