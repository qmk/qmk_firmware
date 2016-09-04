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

#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include "serial_link/protocol/byte_stuffer.c"
#include "serial_link/protocol/frame_validator.c"
#include "serial_link/protocol/frame_router.c"
#include "serial_link/protocol/transport.h"

static uint8_t received_data[256];
static uint16_t received_data_size;

typedef struct {
    uint8_t sent_data[256];
    uint16_t sent_data_size;
} receive_buffer_t;

typedef struct {
    receive_buffer_t send_buffers[2];
} router_buffer_t;

router_buffer_t router_buffers[8];

router_buffer_t* current_router_buffer;


Describe(FrameRouter);
BeforeEach(FrameRouter) {
    init_byte_stuffer();
    memset(router_buffers, 0, sizeof(router_buffers));
    current_router_buffer = 0;
}
AfterEach(FrameRouter) {}

typedef struct {
    uint32_t data;
    uint8_t extra[16];
} frame_buffer_t;


void send_data(uint8_t link, const uint8_t* data, uint16_t size) {
    receive_buffer_t* buffer = &current_router_buffer->send_buffers[link];
    memcpy(buffer->sent_data + buffer->sent_data_size, data, size);
    buffer->sent_data_size += size;
}

static void receive_data(uint8_t link, uint8_t* data, uint16_t size) {
    int i;
    for(i=0;i<size;i++) {
        byte_stuffer_recv_byte(link, data[i]);
    }
}

static void activate_router(uint8_t num) {
    current_router_buffer = router_buffers + num;
    router_set_master(num==0);
}

static void simulate_transport(uint8_t from, uint8_t to) {
   activate_router(to);
   if (from > to) {
       receive_data(DOWN_LINK,
               router_buffers[from].send_buffers[UP_LINK].sent_data,
               router_buffers[from].send_buffers[UP_LINK].sent_data_size);
   }
   else if(to > from) {
       receive_data(UP_LINK,
               router_buffers[from].send_buffers[DOWN_LINK].sent_data,
               router_buffers[from].send_buffers[DOWN_LINK].sent_data_size);
   }
}

void transport_recv_frame(uint8_t from, uint8_t* data, uint16_t size) {
    mock(from, data, size);
}


Ensure(FrameRouter, master_broadcast_is_received_by_everyone) {
    frame_buffer_t data;
    data.data = 0xAB7055BB;
    activate_router(0);
    router_send_frame(0xFF, (uint8_t*)&data, 4);
    assert_that(router_buffers[0].send_buffers[DOWN_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[0].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));

    expect(transport_recv_frame,
        when(from, is_equal_to(0)),
        when(size, is_equal_to(4)),
        when(data, is_equal_to_contents_of(&data.data, 4))
    );
    simulate_transport(0, 1);
    assert_that(router_buffers[1].send_buffers[DOWN_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[1].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));

    expect(transport_recv_frame,
        when(from, is_equal_to(0)),
        when(size, is_equal_to(4)),
        when(data, is_equal_to_contents_of(&data.data, 4))
    );
    simulate_transport(1, 2);
    assert_that(router_buffers[2].send_buffers[DOWN_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[2].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));
}

Ensure(FrameRouter, master_send_is_received_by_targets) {
    frame_buffer_t data;
    data.data = 0xAB7055BB;
    activate_router(0);
    router_send_frame((1 << 1) | (1 << 2), (uint8_t*)&data, 4);
    assert_that(router_buffers[0].send_buffers[DOWN_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[0].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));

    simulate_transport(0, 1);
    assert_that(router_buffers[1].send_buffers[DOWN_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[1].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));

    expect(transport_recv_frame,
        when(from, is_equal_to(0)),
        when(size, is_equal_to(4)),
        when(data, is_equal_to_contents_of(&data.data, 4))
    );
    simulate_transport(1, 2);
    assert_that(router_buffers[2].send_buffers[DOWN_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[2].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));

    expect(transport_recv_frame,
        when(from, is_equal_to(0)),
        when(size, is_equal_to(4)),
        when(data, is_equal_to_contents_of(&data.data, 4))
    );
    simulate_transport(2, 3);
    assert_that(router_buffers[3].send_buffers[DOWN_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[3].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));
}

Ensure(FrameRouter, first_link_sends_to_master) {
    frame_buffer_t data;
    data.data = 0xAB7055BB;
    activate_router(1);
    router_send_frame(0, (uint8_t*)&data, 4);
    assert_that(router_buffers[1].send_buffers[UP_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[1].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));

    expect(transport_recv_frame,
        when(from, is_equal_to(1)),
        when(size, is_equal_to(4)),
        when(data, is_equal_to_contents_of(&data.data, 4))
    );
    simulate_transport(1, 0);
    assert_that(router_buffers[0].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));
    assert_that(router_buffers[0].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));
}

Ensure(FrameRouter, second_link_sends_to_master) {
    frame_buffer_t data;
    data.data = 0xAB7055BB;
    activate_router(2);
    router_send_frame(0, (uint8_t*)&data, 4);
    assert_that(router_buffers[2].send_buffers[UP_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[2].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));

    simulate_transport(2, 1);
    assert_that(router_buffers[1].send_buffers[UP_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[1].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));

    expect(transport_recv_frame,
        when(from, is_equal_to(2)),
        when(size, is_equal_to(4)),
        when(data, is_equal_to_contents_of(&data.data, 4))
    );
    simulate_transport(1, 0);
    assert_that(router_buffers[0].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));
    assert_that(router_buffers[0].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));
}

Ensure(FrameRouter, master_sends_to_master_does_nothing) {
    frame_buffer_t data;
    data.data = 0xAB7055BB;
    activate_router(0);
    router_send_frame(0, (uint8_t*)&data, 4);
    assert_that(router_buffers[0].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));
    assert_that(router_buffers[0].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));
}

Ensure(FrameRouter, link_sends_to_other_link_does_nothing) {
    frame_buffer_t data;
    data.data = 0xAB7055BB;
    activate_router(1);
    router_send_frame(2, (uint8_t*)&data, 4);
    assert_that(router_buffers[1].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));
    assert_that(router_buffers[1].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));
}

Ensure(FrameRouter, master_receives_on_uplink_does_nothing) {
    frame_buffer_t data;
    data.data = 0xAB7055BB;
    activate_router(1);
    router_send_frame(0, (uint8_t*)&data, 4);
    assert_that(router_buffers[1].send_buffers[UP_LINK].sent_data_size, is_greater_than(0));
    assert_that(router_buffers[1].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));

    never_expect(transport_recv_frame);
    activate_router(0);
    receive_data(UP_LINK,
        router_buffers[1].send_buffers[UP_LINK].sent_data,
        router_buffers[1].send_buffers[UP_LINK].sent_data_size);
    assert_that(router_buffers[0].send_buffers[UP_LINK].sent_data_size, is_equal_to(0));
    assert_that(router_buffers[0].send_buffers[DOWN_LINK].sent_data_size, is_equal_to(0));
}
