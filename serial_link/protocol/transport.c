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

#include "protocol/transport.h"
#include "protocol/frame_router.h"
#include "protocol/triple_buffered_object.h"

static remote_object_t** remote_objects;
static uint32_t num_remote_objects;

void init_transport(remote_object_t** _remote_objects, uint32_t _num_remote_objects) {
    remote_objects = _remote_objects;
    num_remote_objects = _num_remote_objects;
    int i;
    for(i=0;i<num_remote_objects;i++) {
        remote_object_t* obj = remote_objects[i];
        if (obj->object_type == MASTER_TO_ALL_SLAVES) {
            triple_buffer_object_t* tb = (triple_buffer_object_t*)obj->buffer;
            triple_buffer_init(tb);
            uint8_t* start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
            tb = (triple_buffer_object_t*)start;
            triple_buffer_init(tb);
        }
        else if(obj->object_type == MASTER_TO_SINGLE_SLAVE) {
            uint8_t* start = obj->buffer;
            int j;
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
            int j;
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
    remote_object_t* obj = remote_objects[id];
    if (obj->object_type == MASTER_TO_ALL_SLAVES) {
        uint8_t* start = obj->buffer + LOCAL_OBJECT_SIZE(obj->object_size);
        triple_buffer_object_t* tb = (triple_buffer_object_t*)start;
        void* ptr = triple_buffer_begin_write_internal(obj->object_size, tb);
        memcpy(ptr, data, size -1);
        triple_buffer_end_write_internal(tb);
    }
}

uint32_t transport_send_frame(uint8_t to, uint8_t* data, uint16_t size) {
}

void update_transport(void) {
    int i;
    for(i=0;i<num_remote_objects;i++) {
        remote_object_t* obj = remote_objects[i];
        if (obj->object_type == MASTER_TO_ALL_SLAVES) {
            triple_buffer_object_t* tb = (triple_buffer_object_t*)obj->buffer;
            uint8_t* ptr = (uint8_t*)triple_buffer_read_internal(obj->object_size + LOCAL_OBJECT_EXTRA, tb);
            if (ptr) {
                ptr[obj->object_size] = i;
                router_send_frame(0xFF, ptr, obj->object_size + 1);
            }
        }
    }
}
