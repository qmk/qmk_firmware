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

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <array>
extern "C" {
    #include "serial_link/protocol/transport.h"
    #include "serial_link/protocol/byte_stuffer.h"
    #include "serial_link/protocol/frame_router.h"
}

using testing::_;
using testing::ElementsAreArray;
using testing::Args;

class FrameRouter : public testing::Test {
public:
    FrameRouter() :
        current_router_buffer(nullptr)
    {
        Instance = this;
        init_byte_stuffer();
    }

    ~FrameRouter() {
        Instance = nullptr;
    }

    void send_data(uint8_t link, const uint8_t* data, uint16_t size) {
        auto& buffer = current_router_buffer->send_buffers[link];
        std::copy(data, data + size, std::back_inserter(buffer));
    }

    void receive_data(uint8_t link, uint8_t* data, uint16_t size) {
        int i;
        for(i=0;i<size;i++) {
            byte_stuffer_recv_byte(link, data[i]);
        }
    }

    void activate_router(uint8_t num) {
        current_router_buffer = router_buffers + num;
        router_set_master(num==0);
    }

    void simulate_transport(uint8_t from, uint8_t to) {
       activate_router(to);
       if (from > to) {
           receive_data(DOWN_LINK,
                   router_buffers[from].send_buffers[UP_LINK].data(),
                   router_buffers[from].send_buffers[UP_LINK].size());
       }
       else if(to > from) {
           receive_data(UP_LINK,
                   router_buffers[from].send_buffers[DOWN_LINK].data(),
                   router_buffers[from].send_buffers[DOWN_LINK].size());
       }
    }

    MOCK_METHOD3(transport_recv_frame, void (uint8_t from, uint8_t* data, uint16_t size));

    std::vector<uint8_t> received_data;

    struct router_buffer {
        std::vector<uint8_t> send_buffers[2];
    };

    router_buffer router_buffers[8];
    router_buffer* current_router_buffer;

    static FrameRouter* Instance;
};

FrameRouter* FrameRouter::Instance = nullptr;


typedef struct {
    std::array<uint8_t, 4> data;
    uint8_t extra[16];
} frame_buffer_t;


extern "C" {
    void send_data(uint8_t link, const uint8_t* data, uint16_t size) {
        FrameRouter::Instance->send_data(link, data, size);
    }


    void transport_recv_frame(uint8_t from, uint8_t* data, uint16_t size) {
        FrameRouter::Instance->transport_recv_frame(from, data, size);
    }
}

TEST_F(FrameRouter, master_broadcast_is_received_by_everyone) {
    frame_buffer_t data;
    data.data = {0xAB, 0x70, 0x55, 0xBB};
    activate_router(0);
    router_send_frame(0xFF, (uint8_t*)&data, 4);
    EXPECT_GT(router_buffers[0].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[0].send_buffers[UP_LINK].size(), 0);
    EXPECT_CALL(*this, transport_recv_frame(0, _, _))
        .With(Args<1, 2>(ElementsAreArray(data.data)));
    simulate_transport(0, 1);
    EXPECT_GT(router_buffers[1].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[1].send_buffers[UP_LINK].size(), 0);

    EXPECT_CALL(*this, transport_recv_frame(0, _, _))
        .With(Args<1, 2>(ElementsAreArray(data.data)));
    simulate_transport(1, 2);
    EXPECT_GT(router_buffers[2].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[2].send_buffers[UP_LINK].size(), 0);
}

TEST_F(FrameRouter, master_send_is_received_by_targets) {
    frame_buffer_t data;
    data.data = {0xAB, 0x70, 0x55, 0xBB};
    activate_router(0);
    router_send_frame((1 << 1) | (1 << 2), (uint8_t*)&data, 4);
    EXPECT_GT(router_buffers[0].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[0].send_buffers[UP_LINK].size(), 0);

    simulate_transport(0, 1);
    EXPECT_GT(router_buffers[1].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[1].send_buffers[UP_LINK].size(), 0);

    EXPECT_CALL(*this, transport_recv_frame(0, _, _))
        .With(Args<1, 2>(ElementsAreArray(data.data)));
    simulate_transport(1, 2);
    EXPECT_GT(router_buffers[2].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[2].send_buffers[UP_LINK].size(), 0);

    EXPECT_CALL(*this, transport_recv_frame(0, _, _))
        .With(Args<1, 2>(ElementsAreArray(data.data)));
    simulate_transport(2, 3);
    EXPECT_GT(router_buffers[3].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[3].send_buffers[UP_LINK].size(), 0);
}

TEST_F(FrameRouter, first_link_sends_to_master) {
    frame_buffer_t data;
    data.data = {0xAB, 0x70, 0x55, 0xBB};
    activate_router(1);
    router_send_frame(0, (uint8_t*)&data, 4);
    EXPECT_GT(router_buffers[1].send_buffers[UP_LINK].size(), 0);
    EXPECT_EQ(router_buffers[1].send_buffers[DOWN_LINK].size(), 0);

    EXPECT_CALL(*this, transport_recv_frame(1, _, _))
        .With(Args<1, 2>(ElementsAreArray(data.data)));
    simulate_transport(1, 0);
    EXPECT_EQ(router_buffers[0].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[0].send_buffers[UP_LINK].size(), 0);
}

TEST_F(FrameRouter, second_link_sends_to_master) {
    frame_buffer_t data;
    data.data = {0xAB, 0x70, 0x55, 0xBB};
    activate_router(2);
    router_send_frame(0, (uint8_t*)&data, 4);
    EXPECT_GT(router_buffers[2].send_buffers[UP_LINK].size(), 0);
    EXPECT_EQ(router_buffers[2].send_buffers[DOWN_LINK].size(), 0);

    simulate_transport(2, 1);
    EXPECT_GT(router_buffers[1].send_buffers[UP_LINK].size(), 0);
    EXPECT_EQ(router_buffers[1].send_buffers[DOWN_LINK].size(), 0);

    EXPECT_CALL(*this, transport_recv_frame(2, _, _))
        .With(Args<1, 2>(ElementsAreArray(data.data)));
    simulate_transport(1, 0);
    EXPECT_EQ(router_buffers[0].send_buffers[DOWN_LINK].size(), 0);
    EXPECT_EQ(router_buffers[0].send_buffers[UP_LINK].size(), 0);
}

TEST_F(FrameRouter, master_sends_to_master_does_nothing) {
    frame_buffer_t data;
    data.data = {0xAB, 0x70, 0x55, 0xBB};
    activate_router(0);
    router_send_frame(0, (uint8_t*)&data, 4);
    EXPECT_EQ(router_buffers[0].send_buffers[UP_LINK].size(), 0);
    EXPECT_EQ(router_buffers[0].send_buffers[DOWN_LINK].size(), 0);
}

TEST_F(FrameRouter, link_sends_to_other_link_does_nothing) {
    frame_buffer_t data;
    data.data = {0xAB, 0x70, 0x55, 0xBB};
    activate_router(1);
    router_send_frame(2, (uint8_t*)&data, 4);
    EXPECT_EQ(router_buffers[1].send_buffers[UP_LINK].size(), 0);
    EXPECT_EQ(router_buffers[1].send_buffers[DOWN_LINK].size(), 0);
}

TEST_F(FrameRouter, master_receives_on_uplink_does_nothing) {
    frame_buffer_t data;
    data.data = {0xAB, 0x70, 0x55, 0xBB};
    activate_router(1);
    router_send_frame(0, (uint8_t*)&data, 4);
    EXPECT_GT(router_buffers[1].send_buffers[UP_LINK].size(), 0);
    EXPECT_EQ(router_buffers[1].send_buffers[DOWN_LINK].size(), 0);

    EXPECT_CALL(*this, transport_recv_frame(_, _, _))
        .Times(0);
    activate_router(0);
    receive_data(UP_LINK,
        router_buffers[1].send_buffers[UP_LINK].data(),
        router_buffers[1].send_buffers[UP_LINK].size());
    EXPECT_EQ(router_buffers[0].send_buffers[UP_LINK].size(), 0);
    EXPECT_EQ(router_buffers[0].send_buffers[DOWN_LINK].size(), 0);
}
