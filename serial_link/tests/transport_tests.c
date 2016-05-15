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
#include "serial_link/protocol/transport.c"
#include "serial_link/protocol/triple_buffered_object.c"

void signal_data_written(void) {
    mock();
}

static uint8_t sent_data[2048];
static uint16_t sent_data_size;

void router_send_frame(uint8_t destination, uint8_t* data, uint16_t size) {
    mock(destination);
    memcpy(sent_data + sent_data_size, data, size);
    sent_data_size += size;
}

typedef struct {
    uint32_t test;
} test_object1_t;

typedef struct {
    uint32_t test1;
    uint32_t test2;
} test_object2_t;

MASTER_TO_ALL_SLAVES_OBJECT(master_to_slave, test_object1_t);
MASTER_TO_SINGLE_SLAVE_OBJECT(master_to_single_slave, test_object1_t);
SLAVE_TO_MASTER_OBJECT(slave_to_master, test_object1_t);

static remote_object_t* test_remote_objects[] = {
    REMOTE_OBJECT(master_to_slave),
    REMOTE_OBJECT(master_to_single_slave),
    REMOTE_OBJECT(slave_to_master),
};

Describe(Transport);
BeforeEach(Transport) {
    add_remote_objects(test_remote_objects, sizeof(test_remote_objects) / sizeof(remote_object_t*));
    sent_data_size = 0;
}
AfterEach(Transport) {}

Ensure(Transport, write_to_local_signals_an_event) {
    begin_write_master_to_slave();
    expect(signal_data_written);
    end_write_master_to_slave();
    begin_write_slave_to_master();
    expect(signal_data_written);
    end_write_slave_to_master();
    begin_write_master_to_single_slave(1);
    expect(signal_data_written);
    end_write_master_to_single_slave(1);
}

Ensure(Transport, writes_from_master_to_all_slaves) {
    update_transport();
    test_object1_t* obj = begin_write_master_to_slave();
    obj->test = 5;
    expect(signal_data_written);
    end_write_master_to_slave();
    expect(router_send_frame,
            when(destination, is_equal_to(0xFF)));
    update_transport();
    transport_recv_frame(0, sent_data, sent_data_size);
    test_object1_t* obj2 = read_master_to_slave();
    assert_that(obj2, is_not_equal_to(NULL));
    assert_that(obj2->test, is_equal_to(5));
}

Ensure(Transport, writes_from_slave_to_master) {
    update_transport();
    test_object1_t* obj = begin_write_slave_to_master();
    obj->test = 7;
    expect(signal_data_written);
    end_write_slave_to_master();
    expect(router_send_frame,
            when(destination, is_equal_to(0)));
    update_transport();
    transport_recv_frame(3, sent_data, sent_data_size);
    test_object1_t* obj2 = read_slave_to_master(2);
    assert_that(read_slave_to_master(0), is_equal_to(NULL));
    assert_that(obj2, is_not_equal_to(NULL));
    assert_that(obj2->test, is_equal_to(7));
}

Ensure(Transport, writes_from_master_to_single_slave) {
    update_transport();
    test_object1_t* obj = begin_write_master_to_single_slave(3);
    obj->test = 7;
    expect(signal_data_written);
    end_write_master_to_single_slave(3);
    expect(router_send_frame,
            when(destination, is_equal_to(4)));
    update_transport();
    transport_recv_frame(0, sent_data, sent_data_size);
    test_object1_t* obj2 = read_master_to_single_slave();
    assert_that(obj2, is_not_equal_to(NULL));
    assert_that(obj2->test, is_equal_to(7));
}

Ensure(Transport, ignores_object_with_invalid_id) {
    update_transport();
    test_object1_t* obj = begin_write_master_to_single_slave(3);
    obj->test = 7;
    expect(signal_data_written);
    end_write_master_to_single_slave(3);
    expect(router_send_frame,
            when(destination, is_equal_to(4)));
    update_transport();
    sent_data[sent_data_size - 1] = 44;
    transport_recv_frame(0, sent_data, sent_data_size);
    test_object1_t* obj2 = read_master_to_single_slave();
    assert_that(obj2, is_equal_to(NULL));
}

Ensure(Transport, ignores_object_with_size_too_small) {
    update_transport();
    test_object1_t* obj = begin_write_master_to_slave();
    obj->test = 7;
    expect(signal_data_written);
    end_write_master_to_slave();
    expect(router_send_frame);
    update_transport();
    sent_data[sent_data_size - 2] = 0;
    transport_recv_frame(0, sent_data, sent_data_size - 1);
    test_object1_t* obj2 = read_master_to_slave();
    assert_that(obj2, is_equal_to(NULL));
}

Ensure(Transport, ignores_object_with_size_too_big) {
    update_transport();
    test_object1_t* obj = begin_write_master_to_slave();
    obj->test = 7;
    expect(signal_data_written);
    end_write_master_to_slave();
    expect(router_send_frame);
    update_transport();
    sent_data[sent_data_size + 21] = 0;
    transport_recv_frame(0, sent_data, sent_data_size + 22);
    test_object1_t* obj2 = read_master_to_slave();
    assert_that(obj2, is_equal_to(NULL));
}
