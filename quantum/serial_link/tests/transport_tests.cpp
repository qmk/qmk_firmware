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

using testing::_;
using testing::Args;
using testing::ElementsAreArray;

extern "C" {
#include "serial_link/protocol/transport.h"
}

struct test_object1 {
    uint32_t test;
};

struct test_object2 {
    uint32_t test1;
    uint32_t test2;
};

MASTER_TO_ALL_SLAVES_OBJECT(master_to_slave, test_object1);
MASTER_TO_SINGLE_SLAVE_OBJECT(master_to_single_slave, test_object1);
SLAVE_TO_MASTER_OBJECT(slave_to_master, test_object1);

static remote_object_t* test_remote_objects[] = {
    REMOTE_OBJECT(master_to_slave),
    REMOTE_OBJECT(master_to_single_slave),
    REMOTE_OBJECT(slave_to_master),
};

class Transport : public testing::Test {
   public:
    Transport() {
        Instance = this;
        add_remote_objects(test_remote_objects, sizeof(test_remote_objects) / sizeof(remote_object_t*));
    }

    ~Transport() {
        Instance = nullptr;
        reinitialize_serial_link_transport();
    }

    MOCK_METHOD0(signal_data_written, void());
    MOCK_METHOD1(router_send_frame, void(uint8_t destination));

    void router_send_frame(uint8_t destination, uint8_t* data, uint16_t size) {
        router_send_frame(destination);
        std::copy(data, data + size, std::back_inserter(sent_data));
    }

    static Transport* Instance;

    std::vector<uint8_t> sent_data;
};

Transport* Transport::Instance = nullptr;

extern "C" {
void signal_data_written(void) { Transport::Instance->signal_data_written(); }

void router_send_frame(uint8_t destination, uint8_t* data, uint16_t size) { Transport::Instance->router_send_frame(destination, data, size); }
}

TEST_F(Transport, write_to_local_signals_an_event) {
    begin_write_master_to_slave();
    EXPECT_CALL(*this, signal_data_written());
    end_write_master_to_slave();
    begin_write_slave_to_master();
    EXPECT_CALL(*this, signal_data_written());
    end_write_slave_to_master();
    begin_write_master_to_single_slave(1);
    EXPECT_CALL(*this, signal_data_written());
    end_write_master_to_single_slave(1);
}

TEST_F(Transport, writes_from_master_to_all_slaves) {
    update_transport();
    test_object1* obj = begin_write_master_to_slave();
    obj->test         = 5;
    EXPECT_CALL(*this, signal_data_written());
    end_write_master_to_slave();
    EXPECT_CALL(*this, router_send_frame(0xFF));
    update_transport();
    transport_recv_frame(0, sent_data.data(), sent_data.size());
    test_object1* obj2 = read_master_to_slave();
    EXPECT_NE(obj2, nullptr);
    EXPECT_EQ(obj2->test, 5);
}

TEST_F(Transport, writes_from_slave_to_master) {
    update_transport();
    test_object1* obj = begin_write_slave_to_master();
    obj->test         = 7;
    EXPECT_CALL(*this, signal_data_written());
    end_write_slave_to_master();
    EXPECT_CALL(*this, router_send_frame(0));
    update_transport();
    transport_recv_frame(3, sent_data.data(), sent_data.size());
    test_object1* obj2 = read_slave_to_master(2);
    EXPECT_EQ(read_slave_to_master(0), nullptr);
    EXPECT_NE(obj2, nullptr);
    EXPECT_EQ(obj2->test, 7);
}

TEST_F(Transport, writes_from_master_to_single_slave) {
    update_transport();
    test_object1* obj = begin_write_master_to_single_slave(3);
    obj->test         = 7;
    EXPECT_CALL(*this, signal_data_written());
    end_write_master_to_single_slave(3);
    EXPECT_CALL(*this, router_send_frame(4));
    update_transport();
    transport_recv_frame(0, sent_data.data(), sent_data.size());
    test_object1* obj2 = read_master_to_single_slave();
    EXPECT_NE(obj2, nullptr);
    EXPECT_EQ(obj2->test, 7);
}

TEST_F(Transport, ignores_object_with_invalid_id) {
    update_transport();
    test_object1* obj = begin_write_master_to_single_slave(3);
    obj->test         = 7;
    EXPECT_CALL(*this, signal_data_written());
    end_write_master_to_single_slave(3);
    EXPECT_CALL(*this, router_send_frame(4));
    update_transport();
    sent_data[sent_data.size() - 1] = 44;
    transport_recv_frame(0, sent_data.data(), sent_data.size());
    test_object1* obj2 = read_master_to_single_slave();
    EXPECT_EQ(obj2, nullptr);
}

TEST_F(Transport, ignores_object_with_size_too_small) {
    update_transport();
    test_object1* obj = begin_write_master_to_slave();
    obj->test         = 7;
    EXPECT_CALL(*this, signal_data_written());
    end_write_master_to_slave();
    EXPECT_CALL(*this, router_send_frame(_));
    update_transport();
    sent_data[sent_data.size() - 2] = 0;
    transport_recv_frame(0, sent_data.data(), sent_data.size() - 1);
    test_object1* obj2 = read_master_to_slave();
    EXPECT_EQ(obj2, nullptr);
}

TEST_F(Transport, ignores_object_with_size_too_big) {
    update_transport();
    test_object1* obj = begin_write_master_to_slave();
    obj->test         = 7;
    EXPECT_CALL(*this, signal_data_written());
    end_write_master_to_slave();
    EXPECT_CALL(*this, router_send_frame(_));
    update_transport();
    sent_data.resize(sent_data.size() + 22);
    sent_data[sent_data.size() - 1] = 0;
    transport_recv_frame(0, sent_data.data(), sent_data.size());
    test_object1* obj2 = read_master_to_slave();
    EXPECT_EQ(obj2, nullptr);
}
